#ifndef SHADER_ID_H_
#define SHADER_ID_H_
// シェーダー
struct Sh {
    enum Name {
        Player,          // プレイヤー
        BloomExtract,    // 高輝度ピクセル抽出
        GaussianBlur,    // ガウシアンブラー
        BloomCombine,    // ブルームエフェクト合成
        Fog,             // フォグ
        Dissolve        //ディゾルブ
    };
};
#endif