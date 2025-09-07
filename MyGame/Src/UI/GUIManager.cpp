#include "GUIManager.h"
#include "GUI.h"

#include <string>
#include <imgui/imgui.h>

GUIManager::~GUIManager()
{
    Clear();
}

void GUIManager::Update(float deltaTime, float scaledDeltaTime)
{
    for (auto gui : gui_)
    {
        //ゲーム速度に影響されるか
        float time = gui->TimeScaled() ? scaledDeltaTime : deltaTime;
        gui->Update(time);
    }

    for (auto gui : cameraGUI_)
    {
        float time = gui->TimeScaled() ? scaledDeltaTime : deltaTime;
        gui->Update(time);
    }
    Remove();
}

void GUIManager::Draw() const
{
    for (auto gui : gui_)
    {
        gui->Draw();
    }
}

void GUIManager::IndepDraw(int indep) const
{
    if (indep == 0) return;
    for (auto gui : cameraGUI_)
    {
        if (gui->Independent() != indep) continue;
        gui->Draw();
    }
}

void GUIManager::AddGUI(GUI* newGUI)
{
    gui_.push_back(newGUI);
}

void GUIManager::AddCameraGUI(GUI* newGUI,int indep)
{
    newGUI->Independent(indep);
    cameraGUI_.push_back(newGUI);

}

void GUIManager::Remove()
{
    for (auto i = gui_.begin(); i != gui_.end();)
    {
        if ((*i)->end_)
        {
            delete* i;
            i = gui_.erase(i);
        }
        else ++i;
    }

    for (auto i = cameraGUI_.begin(); i != cameraGUI_.end();)
    {
        if ((*i)->end_)
        {
            delete* i;
            i = cameraGUI_.erase(i);
        }
        else ++i;
    }
}

void GUIManager::Clear()
{
    for (auto gui : gui_)
    {
        delete gui;
    }
    gui_.clear();

    for (auto gui : cameraGUI_)
    {
        delete gui;
    }
    cameraGUI_.clear();
}

void GUIManager::Enable(bool enable)
{
    for (auto gui : gui_)
    {
        gui->Enable(enable);
    }
    for (auto gui : cameraGUI_)
    {
        gui->Enable(enable);
    }
}

void GUIManager::Debug()
{
    const std::string buttonText = isAllDraw_ ? "OFF" : "ON";

    ImGui::Begin("UIDebug");
    ImGui::Text("AllDraw");
    ImGui::SameLine();
    if (ImGui::Button(buttonText.c_str(),ImVec2(40,20))) {
        isAllDraw_ = !isAllDraw_;
        Enable(isAllDraw_);
    }
    ImGui::End();
}
