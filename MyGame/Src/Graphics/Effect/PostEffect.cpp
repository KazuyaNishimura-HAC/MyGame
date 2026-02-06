#include "PostEffect.h"
#include "../Shader/Shader.h"
#include "../Shader/RenderTexture.h"

#include <imgui/imgui.h>

PostEffect& PostEffect::Instance()
{
    static PostEffect instance;
    return instance;
}

PostEffect::PostEffect()
{
	
}

PostEffect::~PostEffect()
{
}

void PostEffect::Load()
{
    CreateRender();
    LoadShader();
    //入力・出力レンダーターゲットの設定
    SetInputOutputRender(Rt::BaseScene,Rt::FinalScene);
}

void PostEffect::Bloom()
{
    // 輝度の高い部分を取り出す
    bloomExtract(Rt::BaseScene, bloomParam_.color);
    // ガウシアンブラーでぼかす
    gaussianBlur(Rt::BloomExtract, { width_ / 4.0f, height_ / 4.0f }, Rt::BlurH1, Rt::BlurV1);
    gaussianBlur(Rt::BlurV1, { width_ / 8.0f, height_ / 8.0f }, Rt::BlurH2, Rt::BlurV2);
    gaussianBlur(Rt::BlurV2, { width_ / 16.0f, height_ / 16.0f }, Rt::BlurH3, Rt::BlurV3);
    gaussianBlur(Rt::BlurV3, { width_ / 32.0f, height_ / 32.0f }, Rt::BlurH4, Rt::BlurV4);
    // ブルームの合成
    bloomCombine(inputRT_);
}

void PostEffect::SetBloomParam(BloomEffectParam param)
{
    bloomParam_ = param;
}

void PostEffect::SetIntensity(float intensity)
{
    // ブルームの強さを設定
    bloomIntencity_ = intensity;
}

void PostEffect::Fog(GSuint n, GScolor col)
{
    // シェーダーを有効にする
    gsBeginShader(Sh::Fog);
    gsBeginRenderTarget(n);
    // 元画像テクスチャの設定
    gsSetShaderParamTexture("u_RenderTexture", 0);
    gsBindRenderTargetTextureEx(Rt::BloomCombine, 0, 0);
    // デプスバッファテクスチャの設定
    gsSetShaderParamTexture("u_DepthTexture", 1);
    gsBindRenderTargetDepthEx(n, 1);
    // zバッファパラメータの設定
    GSvector4 zparams = zBufferParams(0.3f, 1000.0f);
    gsSetShaderParam4f("u_ZBufferParams", &zparams);
    // フォグのカラーの設定
    gsSetShaderParam4f("u_FogColor", &col);
    // フォグの開始位置の設定
    gsSetShaderParam1f("u_FogStart", fogStart_);
    // フォグの終了位置の設定
    gsSetShaderParam1f("u_FogEnd", fogEnd_);
    // レンダーターゲットを描画
    gsDrawRenderTargetEx(n);
    gsEndRenderTarget();
    // テクスチャのバインド解除
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    gsUnbindRenderTargetDepthEx(n, 1);
    // シェーダーを無効にする
    gsEndShader();
}

void PostEffect::Dissolve(GSuint n, GSuint m)
{
    // シェーダー有効に
    gsBeginShader(Sh::Dissolve);
    // 元画像
    gsSetShaderParamTexture("u_RenderTexture", 0);
    gsBindRenderTargetTextureEx(n, 0, 0);
    // マスクテクスチャの設定
    gsSetShaderParamTexture("u_MaskTexture", 1);
    gsBindTextureEx(m, 1);
    // UV座標のタイリング
    gsSetShaderParam2f("u_Tilling", &tilling_);
    // UV座標のオフセット
    gsSetShaderParam2f("u_Offset", &offset_);
    // ディゾルブするしきい値
    gsSetShaderParam1f("u_Threshold", threshold_);
    // エッジの幅
    gsSetShaderParam1f("u_EdgeWidth", edge_width_);
    // エッジのカラー
    gsSetShaderParam4f("u_EdgeColor", &edge_color_);
    // エッジの輝度
    gsSetShaderParam1f("u_EdgeColorIntensity", edge_color_intensity_);
    // レンダーターゲットを描画
    gsDrawRenderTargetEx(n);
    // テクスチャのバインド解除
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    gsUnbindTextureEx(m, 1);
    // シェーダーを無効にする
    gsEndShader();
}

void PostEffect::ApplyRenderTexture(GSuint input, GSuint output)
{
    //レンダーターゲット設定
    gsBeginRenderTarget(output);
    //テクスチャバインド
    gsBindRenderTargetTextureEx(input, 0, 0);
    // レンダーターゲットを描画
    gsDrawRenderTargetEx(output);
    // テクスチャのバインド解除
    gsUnbindRenderTargetTextureEx(input, 0, 0);
    //レンダーターゲット解除
    gsEndRenderTarget();
}

void PostEffect::GaussianBlur()
{
    // ブラーに使う解像度（必要なら調整）
    GSvector2 size = GSvector2{ width_, height_} / blurIntencity_;

    // 1段階のガウシアンブラー
    gaussianBlur(inputRT_, size, Rt::BlurH1, outputRT_);
}

void PostEffect::IsBlur(bool flg)
{
    isBlur_ = flg;
}

void PostEffect::Vignette()
{
    
    // シェーダーを有効にする
    gsBeginShader(Sh::Vignette);
    // 各パラメーター設定
    gsSetShaderParam1f("u_VignetteIntensity", vignetteParam_.intencity);
    gsSetShaderParam1f("u_VignetteRadius", vignetteParam_.radius);
    gsSetShaderParam1f("u_VignetteSoftness", vignetteParam_.softness);
    gsSetShaderParam3f("u_VignetteColor", &vignetteParam_.color);
    // 元画像テクスチャの設定
    gsSetShaderParamTexture("u_BaseTexture", 0);
    //レンダーテクスチャをブレンド
    ApplyRenderTexture(inputRT_, outputRT_);
    //合成する場合、変更後のレンダーを入力先に
    if (isBlend_) std::swap(inputRT_, outputRT_);
    // シェーダーを無効にする
    gsEndShader();
}

void PostEffect::SetVignetteParam(VignetteParam param)
{
    vignetteParam_ = param;
}

void PostEffect::RadialBlur()
{
    // シェーダーを有効にする
    gsBeginShader(Sh::RadialBlur);
    // 各パラメーター設定
    gsSetShaderParam1f("u_BlurIntensity", radialBlurParam_.intencity);
    gsSetShaderParam1f("u_SampleCount", radialBlurParam_.sampleCount);
    gsSetShaderParam2f("u_Center", &radialBlurParam_.center);
    // 元画像テクスチャの設定
    gsSetShaderParamTexture("u_BaseTexture", 0);
    //レンダーテクスチャをブレンド
    ApplyRenderTexture(inputRT_, outputRT_);
    //合成する場合、変更後のレンダーを入力先に
    if(isBlend_) std::swap(inputRT_, outputRT_);
    // シェーダーを無効にする
    gsEndShader();
}

void PostEffect::SetRadialBlurParam(RadialBlurParam param)
{
    radialBlurParam_ = param;
}

void PostEffect::Clear()
{
    //値を初期化
    bloomThreshold_ = { 0.01f };
    bloomIntencity_ = { 0.35f };
    bloomColor_={ 1.0f,1.0f,1.0f,1.0f };
    fogColor_={ 1.0f, 1.0f, 1.0f, 1.0f };
    fogStart_={ 500.0f };
    fogEnd_={ 1500.0f };
    tilling_={ 1.0f, 1.0f };
    offset_ = { 0.0f, 0.0f };
    threshold_ ={ 0.0f };
    edge_width_ = { 0.0f };
    edge_color_={ 1.0f, 1.0f, 1.0f, 1.0f };
    edge_color_intensity_={ 1.0f };
    blurIntencity_ = { 1.0f };
}

void PostEffect::Debug()
{
    ImGui::Begin("PostEffect");
    ImGui::InputFloat("BloomIntencity",&bloomIntencity_);
    ImGui::InputFloat("BlurIntencity", &blurIntencity_);
    ImGui::Checkbox("IsBlur", &isBlur_);
    ImGui::InputFloat("VignettePower", &vignetteParam_.intencity);
    ImGui::InputFloat("VignetteRadius", &vignetteParam_.radius);
    ImGui::InputFloat("VignetteSoftness", &vignetteParam_.softness);
    ImGui::InputFloat3("VignetteColor", vignetteParam_.color);

    ImGui::DragFloat("RadialBlurPower", &radialBlurParam_.intencity);
    ImGui::DragInt("RadialSampleCount", &radialBlurParam_.sampleCount);
    ImGui::DragFloat2("RadialBlurCenter", radialBlurParam_.center);
    ImGui::End();
    //PostEffect::Instance().SetVignetteParam({ 0.5f,0.4f,0.2f,GSvector3{1.0f,0.0f,0.0f} });
}

void PostEffect::BeginBlend()
{
    if (isBlend_) return;
    isBlend_ = true;
    //alpha値がオーバーする為ブレンドを一時的に切る
    //glDisable(GL_BLEND);
    //ベースシーンをPostWorkにコピー
    gsBeginShader(Sh::CopyRender);
    gsSetShaderParamTexture("u_BaseTexture", 0);
    ApplyRenderTexture(Rt::BaseScene,Rt::PostWork0);
    gsEndShader();
    //glEnable(GL_BLEND);
    SetInputOutputRender(Rt::PostWork0,Rt::PostWork1);
}

void PostEffect::EndBlend()
{
    if (!isBlend_) return;
    isBlend_ = false;
    gsBeginShader(Sh::CopyRender);
    gsSetShaderParamTexture("u_BaseTexture", 0);
    //合成結果を最終画面レンダーに描画
    ApplyRenderTexture(inputRT_, Rt::FinalScene);
    gsEndShader();
}

void PostEffect::SetInputOutputRender(GSuint input, GSuint output)
{
    inputRT_ = input;
    outputRT_ = output;
}

void PostEffect::CreateRender()
{
    // 元シーン用のレンダーターゲットの作成
    RenderTexture::CreateRenderTarget(Rt::BaseScene, { width_,height_ }, GS_TRUE, GS_TRUE, GS_TRUE);
    // PingPongレンダーテクスチャの作成
    RenderTexture::CreateRenderTarget(Rt::PostWork0, { width_,height_ }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::PostWork1, { width_,height_ }, GS_TRUE, GS_FALSE, GS_TRUE);
    // 高輝度抽出シェーダー用のレンダーターゲットの作成
    RenderTexture::CreateRenderTarget(Rt::BloomExtract, { width_ / 4,height_ / 4 }, GS_TRUE, GS_FALSE, GS_TRUE);
    // ガウシアンブラー用の縮小バッファを作成
    RenderTexture::CreateRenderTarget(Rt::BlurH1, { width_ / 4,height_ / 4 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV1, { width_ / 4,height_ / 4 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurH2, { width_ / 8,height_ / 8 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV2, { width_ / 8,height_ / 8 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurH3, { width_ / 16,height_ / 16 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV3, { width_ / 16,height_ / 16 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurH4, { width_ / 32,height_ / 32 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV4, { width_ / 32,height_ / 32 }, GS_TRUE, GS_FALSE, GS_TRUE);

    // ブルーム合成シェーダー用のレンダーターゲットの作成
    RenderTexture::CreateRenderTarget(Rt::BloomCombine, { width_,height_ }, GS_TRUE, GS_FALSE, GS_TRUE);
    //最終的な描画シーン
    RenderTexture::CreateRenderTarget(Rt::FinalScene, { width_,height_ }, GS_TRUE, GS_FALSE, GS_FALSE);

}

void PostEffect::LoadShader()
{
    // シェーダーの読み込み
    gsLoadShader(Sh::BloomExtract, "Assets/Shader/RenderTexture.vert", "Assets/Shader/BloomExtract.frag");
    gsLoadShader(Sh::GaussianBlur, "Assets/Shader/RenderTexture.vert", "Assets/Shader/GaussianBlur.frag");
    gsLoadShader(Sh::BloomCombine, "Assets/Shader/RenderTexture.vert", "Assets/Shader/BloomCombine.frag");
    gsLoadShader(Sh::Fog,          "Assets/Shader/RenderTexture.vert", "Assets/Shader/Fog.frag");
    gsLoadShader(Sh::Dissolve,     "Assets/Shader/RenderTexture.vert", "Assets/Shader/Dissolve.frag");
    gsLoadShader(Sh::Vignette,     "Assets/Shader/RenderTexture.vert", "Assets/Shader/Vignette.frag");
    gsLoadShader(Sh::RadialBlur,   "Assets/Shader/RenderTexture.vert", "Assets/Shader/RadialBlur.frag");
    gsLoadShader(Sh::CopyRender, "Assets/Shader/RenderTexture.vert", "Assets/Shader/CopyRender.frag");
}

void PostEffect::bloomExtract(GSuint n, GScolor col)
{
    // 高輝度ピクセル抽出シェーダーを有効にする
    gsBeginShader(Sh::BloomExtract);
    // ブルームの対象にするピクセルの輝度を設定
    gsSetShaderParam1f("u_BloomThreshold", bloomThreshold_);
    // ブルームのカラーを設定
    gsSetShaderParam4f("u_BloomColor", &col);
    // テクスチャの設定
    gsSetShaderParamTexture("u_RenderTexture", 0);
    // 輝度抽出用のレンダーターゲットをバインドする
    gsBeginRenderTarget(Rt::BloomExtract);
    // バインド
    gsBindRenderTargetTextureEx(n, 0, 0);
    // レンダーターゲットの描画
    gsDrawRenderTargetEx(Rt::BloomExtract);
    // 元シーン画像用のテクスチャのバインド解除
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    // レンダーターゲットの解除
    gsEndRenderTarget();
    // シェーダーを無効にする
    gsEndShader();
}

void PostEffect::bloomCombine(GSuint n)
{
    // ブルーム合成用シェーダーを有効にする
    gsBeginShader(Sh::BloomCombine);
    gsSetShaderParamTexture("u_BaseTexture", 0);
    gsSetShaderParamTexture("u_BlurTexture1", 1);
    gsSetShaderParamTexture("u_BlurTexture2", 2);
    gsSetShaderParamTexture("u_BlurTexture3", 3);
    //gsSetShaderParamTexture("u_BlurTexture4", 4);
    gsSetShaderParam1f("u_BloomIntensity", bloomIntencity_);
    // ブルーム合成用レンダーターゲットを描画先にする
    gsBeginRenderTarget(outputRT_);
    // バインド
    gsBindRenderTargetTextureEx(n, 0, 0);
    // ブラーテクスチャをバインド
    gsBindRenderTargetTextureEx(Rt::BlurV1, 0, 1);
    gsBindRenderTargetTextureEx(Rt::BlurV2, 0, 2);
    gsBindRenderTargetTextureEx(Rt::BlurV3, 0, 3);
    //gsBindRenderTargetTextureEx(Rt_BlurV4, 0, 4);
    // ブルーム合成用レンダーターゲットを描画
    gsDrawRenderTargetEx(outputRT_);
    // バインド解除
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    // ブラーテクスチャをバインド解除
    gsUnbindRenderTargetTextureEx(Rt::BlurV1, 0, 1);
    gsUnbindRenderTargetTextureEx(Rt::BlurV2, 0, 2);
    gsUnbindRenderTargetTextureEx(Rt::BlurV3, 0, 3);
    //gsUnbindRenderTargetTextureEx(Rt_BlurV4, 0, 4);
    // レンダーターゲットの解除　
    gsEndRenderTarget();
    // シェーダーを無効にする
    gsEndShader();
    //合成する場合、変更後のレンダーを入力先に
    if (isBlend_) std::swap(inputRT_, outputRT_);
}

void PostEffect::gaussianBlur(GSuint source, GSvector2 size, GSuint blur_h, GSuint blur_v)
{
    // ブラーテクスチャのテクセルサイズ
    GSvector2 blur_texel_size{ 1.0f / size.x, 1.0f / size.y };
    // 水平ブラーの方向
    GSvector2 blur_h_direction{ 1.0f, 0.0f };
    // 垂直ブラーの方向
    GSvector2 blur_v_direction{ 0.0f, 1.0f };
    // ガウシアンブラー用シェーダーを有効にする
    gsBeginShader(Sh::GaussianBlur);
    // テクセルサイズの設定
    gsSetShaderParam2f("u_TexelSize", &blur_texel_size);
    // ブラーの方向を水平方向にする
    gsSetShaderParam2f("u_Direction", &blur_h_direction);
    // テクスチャの設定
    gsSetShaderParamTexture("u_RenderTexture", 0);
    //水平方向ブラー用のレンダーターゲットをブレンド
    ApplyRenderTexture(source,blur_h);

    // ブラーの方向を垂直方向にする
    gsSetShaderParam2f("u_Direction", &blur_v_direction);
    //垂直方向ブラー用のレンダーターゲットをブレンド
    ApplyRenderTexture(blur_h, blur_v);
    // シェーダーを無効にする
    gsEndShader();
}

GSvector4 PostEffect::zBufferParams(float near, float far)
{
    float x = 1.0f - (far / near);
    float y = (far / near);
    float z = x / far;
    float w = y / far;
    return GSvector4{ x, y, z, w };
}
