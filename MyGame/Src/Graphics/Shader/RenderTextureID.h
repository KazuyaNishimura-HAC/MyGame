#ifndef RENDER_TEXTURE_ID_H_
#define RENDER_TEXTURE_ID_H_
// �����_�[�^�[�Q�b�g
struct Rt {
    enum Name {
        BaseScene,   // �V�[��
        FinalScene,  // �ŏI���
        BloomExtract,// ���P�x�e�N�Z�����o
        BlurH1,	    // ���������u���[(1/4�k���o�b�t�@)
        BlurV1,	    // ���������u���[(1/4�k���o�b�t�@)
        BlurH2,	    // ���������u���[(1/8�k���o�b�t�@)
        BlurV2,	    // ���������u���[(1/8�k���o�b�t�@)
        BlurH3,	    // ���������u���[(1/16�k���o�b�t�@)
        BlurV3,	    // ���������u���[(1/16�k���o�b�t�@)
        BlurH4,	    // ���������u���[(1/32�k���o�b�t�@)
        BlurV4,	    // ���������u���[(1/32�k���o�b�t�@)
        BloomCombine,// �u���[���G�t�F�N�g����
    };
};


#endif