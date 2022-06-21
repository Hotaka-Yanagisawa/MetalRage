#ifndef __CAMERA_H__
#define __CAMERA_H__

//DirectXが提供している数学系のライブラリ
#include <DirectXMath.h>
#include "FloatOperator.h"

struct Transform;

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Uninit();
	void Update();

	void Bind();
	void Bind2D();

	void Shaking(int time) { m_nTime = time; }

	Float3 GetPos() { return m_pos; }
	DirectX::XMMATRIX GetView() { return m_viewMat; }
	float GetXzAngle() { return m_xzAngle; }
	float GetYAngle() { return m_yAngle; }
	int GetTime() { return m_nTime; }
	void SetYAngle(float Angle) { m_yAngle = Angle; }
	void SetLook(Float3 look) { m_look = look; }
	void SetTarget(Transform *Target) { m_pTarget = Target; }
	void SetRadius(float num) { m_radius = num; }
	//void SetMove(Float3 move) { m_move = move; }
	float m_ScreenWidth;
	int m_CameraNum;
	int m_ConNum;
	Float3 m_move;
	Float3 m_pos;
private:
	//XMMATRIX...行列用の型
	DirectX::XMMATRIX m_viewMat;

	Float3 m_look;
	//遅れて見た時の注視点
	Float3 m_latePos;
	Float3 m_lateLook;
	Float3 m_up;
	float m_angle;
	float m_near;
	float m_far;
	// --- 極座標
	//XZ軸上での角度(0°で-Zの位置)
	float m_xzAngle;
	//XZ軸で回転した角度（0°で水平）
	float m_yAngle;
	//中心からの距離
	float m_radius;

	Transform *m_pTarget;
	int m_nTime;
};

#endif // !__CAMERA_H__