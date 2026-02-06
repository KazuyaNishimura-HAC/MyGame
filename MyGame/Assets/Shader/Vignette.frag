#version 330
//出力カラー
layout(location = 0) out vec4 out_FragColor;
//テクスチャ座標
in vec2 v_TexCoord;

// シーンのテクスチャ
uniform sampler2D u_BaseTexture;
//値設定
uniform float u_VignetteIntensity = 0.5;
uniform float u_VignetteRadius  = 0.75;
uniform float u_VignetteSoftness = 0.25;
uniform vec3 u_VignetteColor = vec3(0.0,0.0,0.0);

void main(void)
{
    // シーンのカラーを取得
    vec4 sceneColor = texture(u_BaseTexture, v_TexCoord);
    // 画面中心 (0.5, 0.5) からの距離
    vec2 center = vec2(0.5,0.5);
    float dist = distance(v_TexCoord, center);
    // 滑らかなビネットマスク
    float vignette = smoothstep(u_VignetteRadius,u_VignetteRadius + u_VignetteSoftness,dist);

    //カラー設定
    vec3 vignetteColor = mix(sceneColor.rgb,u_VignetteColor,vignette);
    
    // 指定範囲で暗くする
    vec3 finalColor = mix(sceneColor.rgb,vignetteColor,u_VignetteIntensity);
    //最終カラーを出力（透明度はそのまま）
    out_FragColor = vec4(finalColor, 1.0);
}
