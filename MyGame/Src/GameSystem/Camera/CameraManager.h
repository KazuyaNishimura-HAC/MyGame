#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_
#include <vector>
class Camera;
class CameraController;

class CameraManager {
public:
	CameraManager();
	~CameraManager();
	void Update(float deltaTime);
	void ControllerUpdate(float deltaTime);
	void Draw(int id = 0) const;
	void Remove();
	void Clear();
	void Debug();

	int CameraCount();
	void AddCamera(Camera* camera);
	Camera* GetCamera(int id = 0);
	std::vector<Camera*> GetCameras() const;

	void AddController(CameraController* controller);
	CameraController* GetActiveController();
	// ÉRÉsÅ[ã÷é~
	CameraManager(const CameraManager& other) = delete;
	CameraManager& operator=(const CameraManager& other) = delete;
private:
	std::vector<Camera*> cameras_;
	std::vector<CameraController*> controller_;
};

#endif