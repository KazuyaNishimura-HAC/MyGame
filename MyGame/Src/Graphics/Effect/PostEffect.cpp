#include "PostEffect.h"
#include "../Shader/Shader.h"
#include "../Shader/RenderTexture.h"
#include "../../AssetID/Graphics.h"

PostEffect& PostEffect::Instance()
{
    static PostEffect instance;
    return instance;
}

PostEffect::PostEffect()
{
	
}

PostEffect::~PostEffect()
{
}

void PostEffect::Load()
{
    CreateRender();
    LoadShader();
}

void PostEffect::Bloom(GSuint n, float intensity, GScolor col)
{
    // �u���[���̋�����ݒ�
    bloomIntencity_ = intensity;

    // �P�x�̍������������o��
    bloomExtract(n, col);
    // �K�E�V�A���u���[�łڂ���
    gaussianBlur(Rt::BloomExtract, { width_ / 4.0f, height_ / 4.0f }, Rt::BlurH1, Rt::BlurV1);
    gaussianBlur(Rt::BlurV1, { width_ / 8.0f, height_ / 8.0f }, Rt::BlurH2, Rt::BlurV2);
    gaussianBlur(Rt::BlurV2, { width_ / 16.0f, height_ / 16.0f }, Rt::BlurH3, Rt::BlurV3);
    gaussianBlur(Rt::BlurV3, { width_ / 32.0f, height_ / 32.0f }, Rt::BlurH4, Rt::BlurV4);
    // �u���[���̍���
    bloomCombine(n);
    // ������̌��ʂ�\��
    RenderTexture::BindRenderTextureEx(Rt::BloomCombine, 0, 0);
    // �����_�[�^�[�Q�b�g�`��
    RenderTexture::DrawRender(Rt::BloomCombine);
}

void PostEffect::Fog(GSuint n, GScolor col)
{
    // �V�F�[�_�[��L���ɂ���
    gsBeginShader(Sh::Fog);
    gsBeginRenderTarget(n);
    // ���摜�e�N�X�`���̐ݒ�
    gsSetShaderParamTexture("u_RenderTexture", 0);
    gsBindRenderTargetTextureEx(Rt::BloomCombine, 0, 0);
    // �f�v�X�o�b�t�@�e�N�X�`���̐ݒ�
    gsSetShaderParamTexture("u_DepthTexture", 1);
    gsBindRenderTargetDepthEx(n, 1);
    // z�o�b�t�@�p�����[�^�̐ݒ�
    GSvector4 zparams = zBufferParams(0.3f, 1000.0f);
    gsSetShaderParam4f("u_ZBufferParams", &zparams);
    // �t�H�O�̃J���[�̐ݒ�
    gsSetShaderParam4f("u_FogColor", &col);
    // �t�H�O�̊J�n�ʒu�̐ݒ�
    gsSetShaderParam1f("u_FogStart", fogStart_);
    // �t�H�O�̏I���ʒu�̐ݒ�
    gsSetShaderParam1f("u_FogEnd", fogEnd_);
    // �����_�[�^�[�Q�b�g��`��
    gsDrawRenderTargetEx(n);
    gsEndRenderTarget();
    // �e�N�X�`���̃o�C���h����
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    gsUnbindRenderTargetDepthEx(n, 1);
    // �V�F�[�_�[�𖳌��ɂ���
    gsEndShader();
}

void PostEffect::Dissolve(GSuint n, GSuint m)
{
    // �V�F�[�_�[�L����
    gsBeginShader(Sh::Dissolve);
    // ���摜
    gsSetShaderParamTexture("u_RenderTexture", 0);
    gsBindRenderTargetTextureEx(n, 0, 0);
    // �}�X�N�e�N�X�`���̐ݒ�
    gsSetShaderParamTexture("u_MaskTexture", 1);
    gsBindTextureEx(m, 1);
    // UV���W�̃^�C�����O
    gsSetShaderParam2f("u_Tilling", &tilling_);
    // UV���W�̃I�t�Z�b�g
    gsSetShaderParam2f("u_Offset", &offset_);
    // �f�B�]���u���邵�����l
    gsSetShaderParam1f("u_Threshold", threshold_);
    // �G�b�W�̕�
    gsSetShaderParam1f("u_EdgeWidth", edge_width_);
    // �G�b�W�̃J���[
    gsSetShaderParam4f("u_EdgeColor", &edge_color_);
    // �G�b�W�̋P�x
    gsSetShaderParam1f("u_EdgeColorIntensity", edge_color_intensity_);
    // �����_�[�^�[�Q�b�g��`��
    gsDrawRenderTargetEx(n);
    // �e�N�X�`���̃o�C���h����
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    gsUnbindTextureEx(m, 1);
    // �V�F�[�_�[�𖳌��ɂ���
    gsEndShader();
}

void PostEffect::MargeShader(GSuint n, GSuint m)
{
    // ���摜�e�N�X�`���̐ݒ�
    gsSetShaderParamTexture("u_RenderTexture", 0);
    gsBindRenderTargetTextureEx(n, 0, 0);
    // �����_�[�^�[�Q�b�g��`��
    gsDrawRenderTargetEx(m);
    // �e�N�X�`���̃o�C���h����
    gsUnbindRenderTargetTextureEx(m, 0, 0);
    gsUnbindRenderTargetDepthEx(m, 1);
}

void PostEffect::CreateRender()
{
    // ���V�[���p�̃����_�[�^�[�Q�b�g�̍쐬
    RenderTexture::CreateRenderTarget(Rt::BaseScene, { width_,height_ }, GS_TRUE, GS_TRUE, GS_TRUE);
    // ���P�x���o�V�F�[�_�[�p�̃����_�[�^�[�Q�b�g�̍쐬
    RenderTexture::CreateRenderTarget(Rt::BloomExtract, { width_ / 4,height_ / 4 }, GS_TRUE, GS_FALSE, GS_TRUE);
    // �K�E�V�A���u���[�p�̏k���o�b�t�@���쐬
    RenderTexture::CreateRenderTarget(Rt::BlurH1, { width_ / 4,height_ / 4 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV1, { width_ / 4,height_ / 4 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurH2, { width_ / 8,height_ / 8 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV2, { width_ / 8,height_ / 8 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurH3, { width_ / 16,height_ / 16 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV3, { width_ / 16,height_ / 16 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurH4, { width_ / 32,height_ / 32 }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::BlurV4, { width_ / 32,height_ / 32 }, GS_TRUE, GS_FALSE, GS_TRUE);

    // �u���[�������V�F�[�_�[�p�̃����_�[�^�[�Q�b�g�̍쐬
    RenderTexture::CreateRenderTarget(Rt::BloomCombine, { width_,height_ }, GS_TRUE, GS_FALSE, GS_TRUE);
    RenderTexture::CreateRenderTarget(Rt::FinalScene, { width_,height_ }, GS_TRUE, GS_FALSE, GS_TRUE);

}

void PostEffect::LoadShader()
{
    // �V�F�[�_�[�̓ǂݍ���
    gsLoadShader(Sh::BloomExtract, "Assets/Shader/RenderTexture.vert", "Assets/Shader/BloomExtract.frag");
    gsLoadShader(Sh::GaussianBlur, "Assets/Shader/RenderTexture.vert", "Assets/Shader/GaussianBlur.frag");
    gsLoadShader(Sh::BloomCombine, "Assets/Shader/RenderTexture.vert", "Assets/Shader/BloomCombine.frag");
    gsLoadShader(Sh::Fog, "Assets/Shader/RenderTexture.vert", "Assets/Shader/Fog.frag");
    gsLoadShader(Sh::Dissolve, "Assets/Shader/RenderTexture.vert", "Assets/Shader/Dissolve.frag");

}

void PostEffect::bloomExtract(GSuint n, GScolor col)
{
    // ���P�x�s�N�Z�����o�V�F�[�_�[��L���ɂ���
    gsBeginShader(Sh::BloomExtract);
    // �u���[���̑Ώۂɂ���s�N�Z���̋P�x��ݒ�
    gsSetShaderParam1f("u_BloomThreshold", bloomThreshold_);
    // �u���[���̃J���[��ݒ�
    gsSetShaderParam4f("u_BloomColor", &col);
    // �e�N�X�`���̐ݒ�
    gsSetShaderParamTexture("u_RenderTexture", 0);
    // �P�x���o�p�̃����_�[�^�[�Q�b�g���o�C���h����
    gsBeginRenderTarget(Rt::BloomExtract);
    // �o�C���h
    gsBindRenderTargetTextureEx(n, 0, 0);

    // �����_�[�^�[�Q�b�g�̕`��
    gsDrawRenderTargetEx(Rt::BloomExtract);
    // ���V�[���摜�p�̃e�N�X�`���̃o�C���h����
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    // �����_�[�^�[�Q�b�g�̉���
    gsEndRenderTarget();
    // �V�F�[�_�[�𖳌��ɂ���
    gsEndShader();
}

void PostEffect::bloomCombine(GSuint n)
{
    // �u���[�������p�V�F�[�_�[��L���ɂ���
    gsBeginShader(Sh::BloomCombine);
    gsSetShaderParamTexture("u_BaseTexture", 0);
    gsSetShaderParamTexture("u_BlurTexture1", 1);
    gsSetShaderParamTexture("u_BlurTexture2", 2);
    gsSetShaderParamTexture("u_BlurTexture3", 3);
    //gsSetShaderParamTexture("u_BlurTexture4", 4);
    gsSetShaderParam1f("u_BloomIntensity", bloomIntencity_);
    // �u���[�������p�����_�[�^�[�Q�b�g��`���ɂ���
    gsBeginRenderTarget(Rt::BloomCombine);
    // �o�C���h
    gsBindRenderTargetTextureEx(n, 0, 0);
    // �u���[�e�N�X�`�����o�C���h
    gsBindRenderTargetTextureEx(Rt::BlurV1, 0, 1);
    gsBindRenderTargetTextureEx(Rt::BlurV2, 0, 2);
    gsBindRenderTargetTextureEx(Rt::BlurV3, 0, 3);
    //gsBindRenderTargetTextureEx(Rt_BlurV4, 0, 4);
    // �u���[�������p�����_�[�^�[�Q�b�g��`��
    gsDrawRenderTargetEx(Rt::BloomCombine);
    // �o�C���h����
    gsUnbindRenderTargetTextureEx(n, 0, 0);
    // �u���[�e�N�X�`�����o�C���h����
    gsUnbindRenderTargetTextureEx(Rt::BlurV1, 0, 1);
    gsUnbindRenderTargetTextureEx(Rt::BlurV2, 0, 2);
    gsUnbindRenderTargetTextureEx(Rt::BlurV3, 0, 3);
    //gsUnbindRenderTargetTextureEx(Rt_BlurV4, 0, 4);
    // �����_�[�^�[�Q�b�g�̉����@
    gsEndRenderTarget();
    // �V�F�[�_�[�𖳌��ɂ���
    gsEndShader();
}

void PostEffect::gaussianBlur(GSuint source, GSvector2 size, GSuint blur_h, GSuint blur_v)
{
    // �u���[�e�N�X�`���̃e�N�Z���T�C�Y
    GSvector2 blur_texel_size{ 1.0f / size.x, 1.0f / size.y };
    // �����u���[�̕���
    GSvector2 blur_h_direction{ 1.0f, 0.0f };
    // �����u���[�̕���
    GSvector2 blur_v_direction{ 0.0f, 1.0f };
    // �K�E�V�A���u���[�p�V�F�[�_�[��L���ɂ���
    gsBeginShader(Sh::GaussianBlur);
    // �e�N�Z���T�C�Y�̐ݒ�
    gsSetShaderParam2f("u_TexelSize", &blur_texel_size);
    // �u���[�̕����𐅕������ɂ���
    gsSetShaderParam2f("u_Direction", &blur_h_direction);
    // �e�N�X�`���̐ݒ�
    gsSetShaderParamTexture("u_RenderTexture", 0);
    // ���������u���[�p�̃����_�[�^�[�Q�b�g��`���ɂ���
    gsBeginRenderTarget(blur_h);
    // ���摜�̃e�N�X�`�����o�C���h
    gsBindRenderTargetTextureEx(source, 0, 0);
    // �����_�[�^�[�Q�b�g��`��
    gsDrawRenderTargetEx(blur_h);
    // �e�N�X�`���̉���
    gsUnbindRenderTargetTextureEx(source, 0, 0);
    // �����_�[�^�[�Q�b�g�̉���
    gsEndRenderTarget();

    // �u���[�̕����𐂒������ɂ���
    gsSetShaderParam2f("u_Direction", &blur_v_direction);
    // ���������u���[�p�̃����_�[�^�[�Q�b�g��`���ɂ���
    gsBeginRenderTarget(blur_v);
    // ���������u���[�̃e�N�X�`�����o�C���h
    gsBindRenderTargetTextureEx(blur_h, 0, 0);
    // �����_�[�^�[�Q�b�g��`��
    gsDrawRenderTargetEx(blur_v);
    // �e�N�X�`���̉���
    gsUnbindRenderTargetTextureEx(blur_h, 0, 0);
    // �����_�[�^�[�Q�b�g�̉���
    gsEndRenderTarget();
    // �V�F�[�_�[�𖳌��ɂ���
    gsEndShader();
}

GSvector4 PostEffect::zBufferParams(float near, float far)
{
    float x = 1.0f - (far / near);
    float y = (far / near);
    float z = x / far;
    float w = y / far;
    return GSvector4{ x, y, z, w };
}
