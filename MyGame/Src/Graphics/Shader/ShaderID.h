#ifndef SHADER_ID_H_
#define SHADER_ID_H_
// シェーダー
struct Sh {
    enum Name {
        Player,          // プレイヤー
        CopyRender,       //コピーレンダー
        BloomExtract,    // 高輝度ピクセル抽出
        GaussianBlur,    // ガウシアンブラー
        RadialBlur,      //ラジアルブラー
        BloomCombine,    // ブルームエフェクト合成
        Fog,             // フォグ
        Dissolve,        // ディゾルブ
        Vignette        // ビネット
    };
};
#endif
