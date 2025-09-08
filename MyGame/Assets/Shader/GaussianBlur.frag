#version 330
layout(location = 0) out vec4 out_FragColor;
// �e�N�X�`�����W
in vec2 v_TexCoord;

// �u���[�̕��� ������(1.0, 0.0), �c����(0.0, 1.0)
uniform vec2 u_Direction;
// �e�N�X�`�����W�ł̂P�e�N�Z���̃T�C�Y
uniform vec2 u_TexelSize;

// �����_�[�^�[�Q�b�g
uniform sampler2D u_RenderTexture;

void main(void) {
    // �K�E�V�A���u���[�̏d��
    const float[5] weights = float[](
      0.17158221, 0.15839034, 0.12459426, 0.08351803, 0.04770625
    );
    // ���E�i�܂��͏㉺�j��9�s�N�Z���̉��d���ϒl�����߂�
    vec4 col = texture(u_RenderTexture, v_TexCoord) * weights[0];
    for (int i = 1; i < 5; ++i) {
        vec2 offset = u_TexelSize * i * u_Direction;
        col += texture(u_RenderTexture, v_TexCoord + offset) * weights[i];
        col += texture(u_RenderTexture, v_TexCoord - offset) * weights[i];
    }
    out_FragColor = vec4(col.rgb, 1.0f);
}