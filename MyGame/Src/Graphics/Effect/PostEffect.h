#ifndef POSTEFFECT_H_
#define POSTEFFECT_H_
#include "../../Screen.h"
class PostEffect
{
public:
    static PostEffect& Instance();
	PostEffect();
	~PostEffect();
    void Load();
	void Bloom(GSuint n, GScolor col);
    void SetIntensity(float intensity);
	void Fog(GSuint n, GScolor col);
	void Dissolve(GSuint n, GSuint m);
	void MargeShader(GSuint n, GSuint m);
private:
	const float width_ = Screen::ScreenWidth;
	const float height_ = Screen::ScreenHeight;
	void CreateRender();
	void LoadShader();

    void bloomExtract(GSuint n, GScolor col);
    void bloomCombine(GSuint n);
    // �K�E�V�A���u���[
    // source : ���摜�̃����_�[�^�[�Q�b�g
    // size   : �k���o�b�t�@�̃T�C�Y
    // blur_h : ���������u���[�p�̃����_�[�^�[�Q�b�g
    // blur_v : ���������u���[�p�̃����_�[�^�[�Q�b�g
    void gaussianBlur(GSuint source, GSvector2 size, GSuint blur_h, GSuint blur_v);

    GSvector4 zBufferParams(float near, float far);

    // �e�N�Z����臒l
    float bloomThreshold_{ 0.01f };
    // �G�t�F�N�g�̋���
    float bloomIntencity_{ 0.35f };
    // �G�t�F�N�g�J���[
    GScolor bloomColor_{ 1.0f,1.0f,1.0f,1.0f };
    // �t�H�O�̃J���[
    GScolor fogColor_{ 1.0f, 1.0f, 1.0f, 1.0f };
    // �t�H�O�̊J�n�ʒu
    float fogStart_{ 500.0f };
    // �t�H�O�̏I���ʒu
    float fogEnd_{ 1500.0f };

    // UV���W�̃^�C�����O
    GSvector2 tilling_{ 1.0f, 1.0f };
    // UV���W�̃I�t�Z�b�g
    GSvector2 offset_{ 0.0f, 0.0f };
    // �f�B�]���u���邵�����l
    float threshold_{ 0.0f };
    // �G�b�W�̕�
    float edge_width_{ 0.0f };
    // �G�b�W�̃J���[
    GScolor edge_color_{ 1.0f, 1.0f, 1.0f, 1.0f };
    // �G�b�W�̋P�x
    float edge_color_intensity_{ 1.0f };
};

#endif