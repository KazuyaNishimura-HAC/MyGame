#ifndef GUI_MANAGER_H_
#define GUI_MANAGER_H_

#include <list>
class GUI;

class GUIManager
{
public:
    ~GUIManager();
    void Update(float deltaTime, float scaledDeltaTime);
    void Draw()const;
    void IndepDraw(int indep)const;
    void AddGUI(GUI* newGUI);
    //カメラごとに独立したUI
    void AddCameraGUI(GUI* newGUI,int indep);
    void Remove();
    void Clear();
    void Enable(bool enable);
private:
    std::list<GUI*> gui_;
    std::list<GUI*> cameraGUI_;
};

#endif
