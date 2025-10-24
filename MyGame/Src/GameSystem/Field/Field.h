#ifndef FIELD_H_
#define FIELD_H_
#include <GStransform.h>
class Field
{
public:
	Field(const GSvector3& position, const GSvector3& size, bool cameraCollide = true);
	GSvector3 ClampPosition(const GSvector3& actorPosition, float radius);
	void Draw()const;
	void Enable(bool enable);
	bool Enable()const;
	void Die();
	bool IsDead()const;
	void CameraCollide(bool collide);
	bool CameraCollide()const;

private:
	GSvector3 CollisionExtents(float radius);
	bool IsInside(const GSvector3& dist, const GSvector3& size);
	//Fieldäeñ 
	struct FieldSurface
	{
		GSvector3 pos;
		GSvector3 normal;
		GSvector3 size;
		GSvector3 collide;
	};
	GStransform transform_;
	bool cameraCollide_{ true };
	bool enable_{ true };
	bool dead_{ false };
};

#endif