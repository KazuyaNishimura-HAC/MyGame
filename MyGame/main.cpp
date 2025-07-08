#include <GSgame.h>
#include "Screen.h"
#include "Camera.h"
#include "InputSystem/GamepadInput.h"
#include "InputSystem/InputSystem.h"

// ゲームクラス
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
        //メッシュ読み込み
        gsLoadMesh(0, "Assets/Model/patti.msh");
        gsLoadTexture(0, "Assets/SkyBox/default.dds");

        camera_ = new Camera(nullptr,0);
        //インプットシステム起動
        InputSystem::Initialize(&gamePad_);
    }

    void update(float delta_time) override {

        camera_->Update(delta_time);
    }

    void draw() override {
        //バッファクリア（色と深度）
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera_->Draw();
        gsDrawSkyboxCubemap(0);
        draw_grid3D();
        // メッシュの描画
        gsDrawMesh(0);
    }

    //強制終了処理
    bool is_running()override {
        return true;
    }
    // グリッド線の描画
    void draw_grid3D() {
        //ライティング無効
        glDisable(GL_LIGHTING);
        // デプステスト無効 
        glDisable(GL_DEPTH_TEST);
        for (float g = -100.0f; g <= 100.0f; g += 1.0f) {
            // xz平面
            glColor3f(0.3f, 0.0f, 0.0f);	// 茶色
            glBegin(GL_LINES);
            glVertex3f(g, 0.0f, -100.0f);
            glVertex3f(g, 0.0f, 100.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-100.0f, 0.0f, g);
            glVertex3f(100.0f, 0.0f, g);
            glEnd();
            // xy平面
            glColor3f(0.2f, 0.2f, 0.2f);	// グレー
            glBegin(GL_LINES);
            glVertex3f(g, -100.0f, 0.0f);
            glVertex3f(g, 100.0f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-100.0f, g, 0.0f);
            glVertex3f(100.0f, g, 0.0f);
            glEnd();

        }
        // ｘ軸を描画
        glColor3f(1.0f, 0.0f, 0.0f);	// 赤色
        glBegin(GL_LINES);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);
        glEnd();
        // ｙ軸を描画
        glColor3f(0.0f, 1.0f, 0.0f);	// 緑色
        glBegin(GL_LINES);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
        glEnd();
        // z軸を描画
        glColor3f(0.0f, 0.0f, 1.0f);	// 青色
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
        glEnd();
        // 白に戻す
        glColor3f(1.0f, 1.0f, 1.0f);
        //ライティング有効
        glEnable (GL_LIGHTING);
        // デプステスト有効
        glEnable(GL_DEPTH_TEST);
    }

};

int main() {
    return MyGame().run();
}