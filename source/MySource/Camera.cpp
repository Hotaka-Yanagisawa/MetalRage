#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Defines.h"
#include "Controller.h"
#include "Transform.h"
#include "Controller.h"

Camera::Camera()
	: m_pos(0,0,-5)
	, m_look(0,0,0)
	, m_lateLook(0,0,0)
	, m_latePos(m_pos)
	, m_up(0,1,0)
	, m_angle(100.0f)
	, m_near(0.5f)
	, m_far(500.0f)
	, m_xzAngle(0.0f)
	, m_yAngle(28.0f)
	, m_radius(2.0f)
	, m_pTarget(nullptr)
	, m_ScreenWidth(SCREEN_WIDTH)
	, m_CameraNum(0)
	, m_ConNum(0)
	, m_nTime(0)
{

}

Camera::~Camera()
{

}

void Camera::Init()
{
	if (m_ConNum == 1)
		m_xzAngle = 180.0f;
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	if (m_pTarget != nullptr)
	{
		m_look = m_pTarget->Translate;
		m_look.y += 1.0f;
	}
	const float RAD = 3.141519f / 180.0f;
	const float SPD = 2.0f;

	if (PAD->IsRTriggerPress(m_ConNum))
	{
		m_look.x += cosf((m_xzAngle)* RAD) * 1;
		m_look.z += sinf((m_xzAngle)* RAD) * 1;
	}
	if (PAD->IsLTriggerPress(m_ConNum))
	{
		m_look.x -= cosf((m_xzAngle)* RAD) * 1;
		m_look.z -= sinf((m_xzAngle)* RAD) * 1;
	}
	
	if (PAD->IsRStickLeft(m_ConNum))	m_xzAngle += SPD;
	if (PAD->IsRStickRight(m_ConNum))	m_xzAngle -= SPD;
	if (PAD->IsRStickDown(m_ConNum))
	{
		m_yAngle += SPD/8.0f;
		if (m_yAngle >= 60.0f)	m_yAngle = 59.0f;
	}
	if (PAD->IsRStickUp(m_ConNum))
	{
		m_yAngle -= SPD/8.0f;
		if (m_yAngle <= -30.0f)	m_yAngle = -29.0f;
	}
//#ifndef DEB
	if (IsKeyPress('E'))
	{
		m_look.x += cosf((m_xzAngle)* RAD) * 1;
		m_look.z += sinf((m_xzAngle)* RAD) * 1;
	}
	if (IsKeyPress('Q'))
	{
		m_look.x -= cosf((m_xzAngle)* RAD) * 1;
		m_look.z -= sinf((m_xzAngle)* RAD) * 1;
	}


	if (IsKeyPress(VK_LEFT))	m_xzAngle += 1.0f;
	if (IsKeyPress(VK_RIGHT))	m_xzAngle -= 1.0f;
	if (IsKeyPress(VK_DOWN))
	{
		m_yAngle += 1.0f;
		if (m_yAngle >= 60.0f)	m_yAngle = 59.0f;
	}
	if (IsKeyPress(VK_UP))
	{
		m_yAngle -= 1.0f;
		if (m_yAngle <= -30.0f)	m_yAngle = -29.0f;
	}
//#endif

	// 揺らし
	if (m_nTime > 0)
	{
		m_nTime--;
		m_lateLook.x += ((m_nTime % 7 - 3) * 5) * 0.001f;
		m_lateLook.y += (m_nTime + 1 % 3 * 2) * 0.001f;
		m_lateLook.z += ((m_nTime % 7 - 3) * 5) * 0.001f;
	}

	//カメラ位置計算
	float xzRad = m_xzAngle * 3.141592f / 180.0f;  //πはラジアン角の180度　度の180で割ることにより１となりラジアンに変換
	float yRad  = m_yAngle  * 3.141592f / 180.0f;

	m_pos.x =  cos(yRad) * sin(xzRad) * m_radius;
	m_pos.z =  cos(yRad) * -cos(xzRad)  * m_radius;
	m_pos.y =  sin(yRad) * m_radius;

	//原点中心（0,0,0）で回転するのではなく、
	//注視点を中心に回転させる
	//これとSetLookでplayerを追跡するカメラにできる ver2
	m_pos.x += m_look.x;
	m_pos.y += m_look.y;
	m_pos.z += m_look.z;

	//遅れ表現
	//本来移動させたい距離よりも短い距離を移動させる ver3
	Float3 move(m_look.x - m_lateLook.x, m_look.y - m_lateLook.y, m_look.z - m_lateLook.z);
	float late = 0.2f;
	move.x *= late;
	move.y *= late;
	move.z *= late;
	m_lateLook.x += move.x;
	m_lateLook.y += move.y;
	m_lateLook.z += move.z;

	m_move = Float3 ((m_pos.x - m_latePos.x)*late, (m_pos.y - m_latePos.y)*late, (m_pos.z - m_latePos.z)*late);
	//m_move.x *= late;
	//m_move.y *= late;
	//m_move.z *= late;
	m_latePos.x +=m_move.x;
	m_latePos.y +=m_move.y;
	m_latePos.z +=m_move.z;
}

void Camera::Bind()
{
	//カメラのパラメータをShaderに渡す
	m_viewMat = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(m_latePos.x,  m_latePos.y,  m_latePos.z,  0),
											  DirectX::XMVectorSet(m_lateLook.x, m_lateLook.y, m_lateLook.z, 0),
											  DirectX::XMVectorSet(m_up.x,   m_up.y,   m_up.z,   0));

	SHADER->SetView(m_viewMat);
	//画角（広いといろんなものが視界に移る、
	//狭いと拡大したような絵になる。）
	//画角が狭いほど、３D感が薄れ、奥行きが
	//分かりづらくなる　→２Dに近づく
	SHADER->SetProjection(DirectX::XMMatrixPerspectiveFovLH(m_angle * 3.141592f / 180.0f,
														   m_ScreenWidth / SCREEN_HEIGHT, m_near, m_far));

	//カメラの座標をシェーダに設定
	SHADER->SetPSCameraPos(m_pos.DXFloat3());

	EnableZBuffer(true);
}

void Camera::Bind2D()
{
	//2Dはカメラの座標系への変換を省略できる
	//MatrixIdentityは単位行列を生成する
	//1, 0, 0, 0
	//0, 1, 0, 0
	//0, 0, 1, 0
	//0, 0, 0, 1
	SHADER->SetView(DirectX::XMMatrixIdentity());
	// 2Dの表示方法を平行投影と呼ぶ
	// 3Dの表示方法を透視投影と呼ぶ
	SHADER->SetProjection(
		//2Dの原点が指定できる平行投影行列を作成
		//今回は画面左上を原点に指定
		DirectX::XMMatrixOrthographicOffCenterLH(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, m_near, m_far));

	EnableZBuffer(false);
}

//void Camera::SetLook(Float3 look)
//{
//	m_look = look;
//}

//アニメーション敵の数で割る
