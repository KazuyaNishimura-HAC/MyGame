#version 330
layout(location = 0) out vec4 out_FragColor;

// テクスチャ座標
in vec2 v_TexCoord;

// レンダーテクスチャ 
uniform sampler2D u_RenderTexture;
// マスク用テクスチャ
uniform sampler2D u_MaskTexture;
// UV座標のタイリング
uniform vec2 u_Tilling;
// UV座標のオフセット
uniform vec2 u_Offset;
// ディゾルブするしきい値
uniform float u_Threshold;
// エッジの幅
uniform float u_EdgeWidth;
// エッジのカラー
uniform vec4 u_EdgeColor;
// エッジの輝度
uniform float u_EdgeColorIntensity;

void main(void) {
    // 元画像のテクスチャを取得
    vec4 color = texture(u_RenderTexture, v_TexCoord);
    // マスク用テクスチャのタイリングとオフセットを加える
    vec2 uv = v_TexCoord * vec2(1.0, -1.0) * u_Tilling + u_Offset;
    float mask = texture(u_MaskTexture, uv).r;
    // エッジの抽出
    float edge = smoothstep(u_Threshold, u_Threshold * (1.0 + u_EdgeWidth), mask);
    // エッジのカラーを加算
    color += u_EdgeColor * edge * u_EdgeColorIntensity;
    // 消失する範囲を求める(maskがu_Treasholdよりも小さければ０になる）
    float cutoff = step(mask, u_Threshold * (1.0 + u_EdgeWidth));
    // 消失する部分は黒くなる
    color *= cutoff;
    // 最終カラーの出力
    out_FragColor = vec4(color.rgb, 1.0);
}
