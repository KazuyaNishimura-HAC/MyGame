#ifndef POSTEFFECT_H_
#define POSTEFFECT_H_
#include "../../Screen.h"
class PostEffect
{
public:
    static PostEffect& Instance();
	PostEffect();
	~PostEffect();
    void Load();
	void Bloom(GSuint n, GScolor col);
    void SetIntensity(float intensity);
	void Fog(GSuint n, GScolor col);
	void Dissolve(GSuint n, GSuint m);
	void MargeShader(GSuint n, GSuint m);
private:
	const float width_ = Screen::ScreenWidth;
	const float height_ = Screen::ScreenHeight;
	void CreateRender();
	void LoadShader();

    void bloomExtract(GSuint n, GScolor col);
    void bloomCombine(GSuint n);
    // ガウシアンブラー
    // source : 元画像のレンダーターゲット
    // size   : 縮小バッファのサイズ
    // blur_h : 水平方向ブラー用のレンダーターゲット
    // blur_v : 垂直方向ブラー用のレンダーターゲット
    void gaussianBlur(GSuint source, GSvector2 size, GSuint blur_h, GSuint blur_v);

    GSvector4 zBufferParams(float near, float far);

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
};

#endif