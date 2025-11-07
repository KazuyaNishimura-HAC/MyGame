#ifndef RENDER_TEXTURE_ID_H_
#define RENDER_TEXTURE_ID_H_
// レンダーターゲット
struct Rt {
    enum Name {
        BaseScene,   // シーン
        FinalScene,  // 最終画面
        BloomExtract,// 高輝度テクセル抽出
        BlurH1,	    // 水平方向ブラー(1/4縮小バッファ)
        BlurV1,	    // 垂直方向ブラー(1/4縮小バッファ)
        BlurH2,	    // 水平方向ブラー(1/8縮小バッファ)
        BlurV2,	    // 垂直方向ブラー(1/8縮小バッファ)
        BlurH3,	    // 水平方向ブラー(1/16縮小バッファ)
        BlurV3,	    // 垂直方向ブラー(1/16縮小バッファ)
        BlurH4,	    // 水平方向ブラー(1/32縮小バッファ)
        BlurV4,	    // 垂直方向ブラー(1/32縮小バッファ)
        BloomCombine,// ブルームエフェクト合成
    };
};


#endif
