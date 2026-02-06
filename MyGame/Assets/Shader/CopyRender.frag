#version 330
layout(location = 0) out vec4 out_FragColor;

// テクスチャ座標
in vec2 v_TexCoord;

// レンダーテクスチャ 
uniform sampler2D u_BaseTexture;


void main(void) {
    // テクスチャカラーをそのまま出力
    out_FragColor = texture(u_BaseTexture, v_TexCoord);
    //α値は1.0固定
    out_FragColor = vec4(out_FragColor.rgb,1.0);
}
