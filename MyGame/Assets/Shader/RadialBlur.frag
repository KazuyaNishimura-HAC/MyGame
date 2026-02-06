#version 330
layout(location = 0) out vec4 out_FragColor;
// テクスチャ座標
in vec2 v_TexCoord;

//中心座標
uniform vec2 u_Center= vec2(0.5,0.5);
//ブラー強度
uniform float u_BlurIntensity = 0.5;
//サンプル数
uniform int u_SampleCount = 8;

// レンダーターゲット
uniform sampler2D u_BaseTexture;

void main(void) {
    //放射ベクトル
    vec2 dir = v_TexCoord - u_Center;
    vec2 offset = vec2(0.0);
    vec4 color = vec4(0.0);
    //強度設定
    float intensity = u_BlurIntensity * length(dir);
    
    for(int i = 0;i < u_SampleCount; ++i){
        float t = float(i) / float(u_SampleCount);
        offset = dir * t * intensity;
        color += texture(u_BaseTexture,v_TexCoord - offset);
    }
    color /= u_SampleCount;
    out_FragColor = vec4(color.rgb, 1.0f);
}
