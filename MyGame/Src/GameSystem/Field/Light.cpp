#include "Light.h"
#include <imgui/imgui.h>

//コンストラクタ
Light::Light(IWorld* world) {
    world_ = world;
    name_ = "Light";
    tag_ = "LightTag";
}

//描画
void Light::Draw() const {
    static float ambient[]{ 0.15f, 0.18f, 0.25f, 1.0f };
    static float diffuse[]{ 0.6f, 0.7f, 0.9f, 1.0f };
    static float specular[]{ 1.0f,1.0f, 1.0f, 1.0f };
    static float position[]{ -100.0f, 100.0f, 100.0f, 1.0f };

    // ImGuiによるパラメータ調整
#if _DEBUG
    ImGui::Begin("Lighting");
    ImGui::ColorEdit4("ambient", ambient, ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("diffuse", diffuse, ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("specular", specular, ImGuiColorEditFlags_Float);
    ImGui::DragFloat4("position", position);
    ImGui::End();
#endif
    //ライトのパラメータ設定
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);

    glEnable(GL_LIGHTING);

    //シャドウマップ用のライトの位置を設定
    GSvector3 shadow_map_light_position{ position[0],position[1],position[2] };
    gsSetShadowMapLightPosition(&shadow_map_light_position);
}
