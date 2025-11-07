#ifndef FIELD_H_
#define FIELD_H_
#include <GStransform.h>
#include "Line.h"
class Field
{
public:
	//Field各面
	struct FieldSurface
	{
		GSvector3 pos;
		GSvector3 normal;
		GSvector3 size;
		GSvector3 collide;
	};
	Field(const GSvector3& position, const GSvector3& size, bool cameraCollide = true);
	GSvector3 ClampPosition(const GSvector3& actorPosition, float radius);
	//衝突してなかったら結果のノーマルが0で渡される
	FieldSurface ClampCameraPosition(Line camera, float radius = 0.5f);
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
	GSvector3 CollisionSize(float radius);

	GStransform transform_;
	bool cameraCollide_{ true };
	GSvector3 normal_[4]{ {0,0,1},{1,0,0},{0,0,-1},{-1,0,0} };
	bool enable_{ true };
	bool dead_{ false };
};

#endif
