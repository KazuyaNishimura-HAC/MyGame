#ifndef SHADER_ID_H_
#define SHADER_ID_H_
// �V�F�[�_�[
struct Sh {
    enum Name {
        Player,          // �v���C���[
        BloomExtract,    // ���P�x�s�N�Z�����o
        GaussianBlur,    // �K�E�V�A���u���[
        BloomCombine,    // �u���[���G�t�F�N�g����
        Fog,             // �t�H�O
        Dissolve,        //�f�B�]���u
    };
};
#endif