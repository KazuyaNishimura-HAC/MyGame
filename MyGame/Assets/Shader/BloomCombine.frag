#version 330
layout(location = 0) out vec4 out_FragColor;
in vec2 v_TexCoord;

// �V�[���̃e�N�X�`��
uniform sampler2D u_BaseTexture;
// �u���[�e�N�X�`��
uniform sampler2D u_BlurTexture1;
uniform sampler2D u_BlurTexture2;
uniform sampler2D u_BlurTexture3;
uniform sampler2D u_BlurTexture4;
// �u���[�����ʂ̋���
uniform float u_BloomIntensity = 1.0;


// �g�[���}�b�s���O
vec3 ACESFilm(vec3 x) {
    x *= 0.6;
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((x*(a*x+b))/(x*(c*x+d)+e), 0.0, 1.0);
}

// �K���}�J���[��Ԃ��烊�j�A�J���[��Ԃɕϊ�
vec3 GammaToLinearSpace(vec3 color) {
    return pow(color, vec3(2.2));
}

// ���j�A�J���[��Ԃ���K���}�J���[��Ԃɕϊ�
vec3 LinearToGammaSpace(vec3 color) {
    return pow(color, vec3(1.0/2.2));
}

void main(void) {
    // �V�[���̃J���[���擾
    vec4 col = texture(u_BaseTexture, v_TexCoord);
    // ���j�A�J���[��Ԃɕϊ�
    col.rgb = GammaToLinearSpace(col.rgb);
    // �u���[���̃J���[������
    vec4 bloom = vec4(0.0);
    bloom += texture(u_BlurTexture1, v_TexCoord);
    bloom += texture(u_BlurTexture2, v_TexCoord);
    bloom += texture(u_BlurTexture3, v_TexCoord);
    bloom += texture(u_BlurTexture4, v_TexCoord);
    // �V�[���̃J���[�ƃu���[���̃J���[������
    col += bloom * u_BloomIntensity;
    // �g�[���}�b�s���O
    col.rgb = ACESFilm(col.rgb);
    // �K���}�J���[��Ԃɕϊ����Ȃ��Ă����v�I(glEnable(GL_FRAMEBUFFER_SRGB);�����邽��)
    out_FragColor = vec4(col.rgb, 1.0);
}