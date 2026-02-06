#ifndef POSTEFFECT_H_
#define POSTEFFECT_H_
#include "../../Screen.h"
#include "../Shader/RenderTextureID.h"
#include "../Shader/ShaderID.h"
struct BloomEffectParam {
    // テクセルの閾値
    float threshold{ 0.01f };
    // エフェクトの強さ
    float intencity{ 0.35f };
    //ブルームカラー
    GScolor color{ 1.0f, 1.0f, 1.0f, 1.0f };
};

struct VignetteParam {
    float intencity{ 0.5f };
    float radius{ 0.4f };
    float softness{ 0.25f };
    GSvector3 color{ 0.0f,0.0f,0.0f };
};

struct RadialBlurParam {
    GSvector2 center{ 0.5f,0.5f };
    float intencity{ 0.5f };
    int sampleCount{ 8 };
};

class PostEffect
{
public:
    static PostEffect& Instance();
	PostEffect();
	~PostEffect();
    void Load();
	void Bloom();
    void SetBloomParam(BloomEffectParam param);
    void SetIntensity(float intensity);
	void Fog(GSuint n, GScolor col);
	void Dissolve(GSuint n, GSuint m);
	void ApplyRenderTexture(GSuint input, GSuint output);
    void GaussianBlur();
    void IsBlur(bool blur);

    void Vignette();
    void SetVignetteParam(VignetteParam param);

    void RadialBlur();
    void SetRadialBlurParam(RadialBlurParam param);
    void Clear();
    void Debug();

    void BeginBlend();
    void EndBlend();
private:
    void SetInputOutputRender(GSuint input,GSuint output);
	void CreateRender();
	void LoadShader();

    void bloomExtract(GSuint n, GScolor col);
    void bloomCombine(GSuint n);

    void gaussianBlur(GSuint source, GSvector2 size, GSuint blur_h, GSuint blur_v);

    GSvector4 zBufferParams(float near, float far);

    const float width_ = Screen::ScreenWidth;
    const float height_ = Screen::ScreenHeight;

    // テクセルの閾値
    float bloomThreshold_{ 0.01f };
    // エフェクトの強さ
    float bloomIntencity_{ 0.35f };
    // エフェクトカラー
    GScolor bloomColor_{ 1.0f,1.0f,1.0f,1.0f };
    // フォグのカラー
    GScolor fogColor_{ 1.0f, 1.0f, 1.0f, 1.0f };
    // フォグの開始位置
    float fogStart_{ 500.0f };
    // フォグの終了位置
    float fogEnd_{ 1500.0f };

    // UV座標のタイリング
    GSvector2 tilling_{ 1.0f, 1.0f };
    // UV座標のオフセット
    GSvector2 offset_{ 0.0f, 0.0f };
    // ディゾルブするしきい値
    float threshold_{ 0.0f };
    // エッジの幅
    float edge_width_{ 0.0f };
    // エッジのカラー
    GScolor edge_color_{ 1.0f, 1.0f, 1.0f, 1.0f };
    // エッジの輝度
    float edge_color_intensity_{ 1.0f };
    //ブラーの強さ
    float blurIntencity_{ 1.0f };
    //ブラーをかけるか
    bool isBlur_{ false };

    //ブルームパラメータ
    BloomEffectParam bloomParam_{};
    //ビネットパラメータ
    VignetteParam vignetteParam_{};

    //ラジアルブラーパラメータ
    RadialBlurParam radialBlurParam_{};

    //入力元レンダーテクスチャ
    GSuint inputRT_{ Rt::BaseScene };
    //出力先レンダーテクスチャ
    GSuint outputRT_{ Rt::FinalScene };
    //レンダーテクスチャのブレンドを行うか
    bool isBlend_{ false };
};

#endif
