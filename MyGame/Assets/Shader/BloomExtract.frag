#version 330
layout(location = 0) out vec4 out_FragColor;

// �e�N�X�`�����W
in vec2 v_TexCoord;

// �����_�[�e�N�X�`�� 
uniform sampler2D u_RenderTexture;
// �P�x�̂������l
uniform float u_BloomThreshold = 1.0f;

// �u���[���J���[�i�f�t�H���j
uniform vec4 u_BloomColor = vec4(1.0f,1.0f,1.0f,1.0f);

// �K���}�J���[��Ԃ��烊�j�A�J���[��Ԃɕϊ�
vec3 GammaToLinearSpace(vec3 color) {
    return pow(color, vec3(2.2));
}


void main(void) {
    // �����_�[�e�N�X�`���̃J���[���擾
    vec4 color = texture(u_RenderTexture, v_TexCoord);
    // ���j�A�J���[��Ԃɕϊ�
    color.rgb = GammaToLinearSpace(color.rgb);
    // �e�N�Z���̋P�x�����߂�
    float luminance = dot(color.rgb, vec3(0.33, 0.34, 0.33));
    // �w�肵���P�x�̈ȏ�̃s�N�Z�������c��
    luminance = max(0.0, luminance - u_BloomThreshold);
    // sign�̓v���X�̒l�̏ꍇ��1.0,�[���̏ꍇ��0.0�ƂȂ�̂ŁA�������l�ȉ��͍��ɂȂ�
    color.rgb *= sign(luminance);
    // �����ɃJ���[����Z
    color.rgb *= u_BloomColor.rgb * u_BloomColor.a;
    // �ŏI�J���[�̏o��
    out_FragColor = vec4(color.rgb, 1.0);
}