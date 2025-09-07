#include <GSgame.h>
#include <imgui/imgui.h>
#include <GSstandard_shader.h>
#include <GSeffect.h>

#include "Screen.h"
#include "GameSystem/InputSystem/GamepadInput.h"
#include "GameSystem/InputSystem/InputSystem.h"

#include "Scene/SceneManager.h"
#include "Scene/Scenes/TitleScene.h"
#include "Scene/Scenes/LoadScene.h"
#include "Scene/Scenes/GamePlayScene.h"
#include "Scene/Scenes/ResultScene.h"

// ゲームクラス
class MyGame : public gslib::Game {
public:
    MyGame() :gslib::Game{ Screen::ScreenWidth, Screen::ScreenHeight, Screen::fullScreen }{};

private:
    GamepadInput gamePad_;
    SceneManager sceneManager_;

    void start() override {
#if !_DEBUG
        gsHideMouseCursor();
#endif
        //シェーダーの初期化（絶対に入れなさいよ）
        gsInitDefaultShader();
        // エフェクトの初期化
        gsInitEffect();
        //インプットシステム起動
        InputSystem::Initialize(&gamePad_);
        sceneManager_.Add(SceneIndex::TitleScene, new TitleScene());
        sceneManager_.Add(SceneIndex::LoadScene, new LoadScene());
        sceneManager_.Add(SceneIndex::GamePlayScene, new GamePlayScene());
        sceneManager_.Add(SceneIndex::ResultScene, new ResultScene());
        sceneManager_.Change(SceneIndex::GamePlayScene);
    }

    void update(float delta_time) override {
        sceneManager_.Update(delta_time);

#if _DEBUG
        debug(delta_time);
#endif

    }

    void draw() override {
        sceneManager_.Draw();
    }

    //強制終了処理
    bool is_running()override {
        return !InputSystem::ForceQuit();
    }

    void end() override {
        sceneManager_.Clear();
        gsStopAllEffects();
        gsFinishEffect();
    }

    void debug(float delta_time) {
        sceneManager_.Debug(delta_time);
        DebugInput();
    }

    void DebugInput()
    {
        ImGui::Begin("Input");
        ImGui::Value("A", InputSystem::ButtonIsPress(InputSystem::Button::A));
        ImGui::Value("B", InputSystem::ButtonIsPress(InputSystem::Button::B));
        ImGui::Value("X", InputSystem::ButtonIsPress(InputSystem::Button::X));
        ImGui::Value("Y", InputSystem::ButtonIsPress(InputSystem::Button::Y));
        ImGui::Value("Up", InputSystem::ButtonIsPress(InputSystem::Button::Up));
        ImGui::Value("Down", InputSystem::ButtonIsPress(InputSystem::Button::Down));
        ImGui::Value("Left", InputSystem::ButtonIsPress(InputSystem::Button::Left));
        ImGui::Value("Right", InputSystem::ButtonIsPress(InputSystem::Button::Right));
        ImGui::Value("LShoulder", InputSystem::ButtonIsPress(InputSystem::Button::LShoulder));
        ImGui::Value("RShoulder", InputSystem::ButtonIsPress(InputSystem::Button::RShoulder));
        ImGui::Value("LTrigger", InputSystem::LeftTriggerWeight());
        ImGui::Value("RTrigger", InputSystem::RightTriggerWeight());
        ImGui::SliderFloat2("LeftStick", InputSystem::LeftStick(), -1, 1);
        ImGui::SliderFloat2("RightStick", InputSystem::RightStick(), -1, 1);
        ImGui::End();
    }
};

int main() {
    return MyGame().run();
}
