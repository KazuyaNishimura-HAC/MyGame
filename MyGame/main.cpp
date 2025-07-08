#include <GSgame.h>
#include "Screen.h"
#include "Camera.h"
#include "InputSystem/GamepadInput.h"
#include "InputSystem/InputSystem.h"

// �Q�[���N���X
class MyGame : public gslib::Game {
public:
    MyGame() :gslib::Game{ Screen::ScreenWidth, Screen::ScreenHeight, Screen::fullScreen}{};

public:
    Camera* camera_;
    
private:
    GamepadInput gamePad_;

    void start() override {
#if !_DEBUG
        gsHideMouseCursor();
#endif
        //���b�V���ǂݍ���
        gsLoadMesh(0, "Assets/Model/patti.msh");
        gsLoadTexture(0, "Assets/SkyBox/default.dds");

        camera_ = new Camera(nullptr,0);
        //�C���v�b�g�V�X�e���N��
        InputSystem::Initialize(&gamePad_);
    }

    void update(float delta_time) override {

        camera_->Update(delta_time);
    }

    void draw() override {
        //�o�b�t�@�N���A�i�F�Ɛ[�x�j
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera_->Draw();
        gsDrawSkyboxCubemap(0);
        draw_grid3D();
        // ���b�V���̕`��
        gsDrawMesh(0);
    }

    //�����I������
    bool is_running()override {
        return true;
    }
    // �O���b�h���̕`��
    void draw_grid3D() {
        //���C�e�B���O����
        glDisable(GL_LIGHTING);
        // �f�v�X�e�X�g���� 
        glDisable(GL_DEPTH_TEST);
        for (float g = -100.0f; g <= 100.0f; g += 1.0f) {
            // xz����
            glColor3f(0.3f, 0.0f, 0.0f);	// ���F
            glBegin(GL_LINES);
            glVertex3f(g, 0.0f, -100.0f);
            glVertex3f(g, 0.0f, 100.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-100.0f, 0.0f, g);
            glVertex3f(100.0f, 0.0f, g);
            glEnd();
            // xy����
            glColor3f(0.2f, 0.2f, 0.2f);	// �O���[
            glBegin(GL_LINES);
            glVertex3f(g, -100.0f, 0.0f);
            glVertex3f(g, 100.0f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-100.0f, g, 0.0f);
            glVertex3f(100.0f, g, 0.0f);
            glEnd();

        }
        // ������`��
        glColor3f(1.0f, 0.0f, 0.0f);	// �ԐF
        glBegin(GL_LINES);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);
        glEnd();
        // ������`��
        glColor3f(0.0f, 1.0f, 0.0f);	// �ΐF
        glBegin(GL_LINES);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
        glEnd();
        // z����`��
        glColor3f(0.0f, 0.0f, 1.0f);	// �F
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
        glEnd();
        // ���ɖ߂�
        glColor3f(1.0f, 1.0f, 1.0f);
        //���C�e�B���O�L��
        glEnable (GL_LIGHTING);
        // �f�v�X�e�X�g�L��
        glEnable(GL_DEPTH_TEST);
    }

};

int main() {
    return MyGame().run();
}