#ifndef __CAMERA_H__
#define __CAMERA_H__

//DirectX���񋟂��Ă��鐔�w�n�̃��C�u����
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
	//XMMATRIX...�s��p�̌^
	DirectX::XMMATRIX m_viewMat;

	Float3 m_look;
	//�x��Č������̒����_
	Float3 m_latePos;
	Float3 m_lateLook;
	Float3 m_up;
	float m_angle;
	float m_near;
	float m_far;
	// --- �ɍ��W
	//XZ����ł̊p�x(0����-Z�̈ʒu)
	float m_xzAngle;
	//XZ���ŉ�]�����p�x�i0���Ő����j
	float m_yAngle;
	//���S����̋���
	float m_radius;

	Transform *m_pTarget;
	int m_nTime;
};

#endif // !__CAMERA_H__