#include "DirectX.h"
#include "FBX/FBXLoader.h"
#include "Texture.h"
#include "Input.h"
#include "Shader.h"
//#include "Defines.h"
#include "Camera.h"
#include "Player.h"
#include "Collision.h"
#include "Object.h"
#include "Enemy.h"
#include "Collider.h"
#include "HP.h"
#include "Billboard.h"
#include "ParallelProjection.h"
#include "Controller.h"
#include "MySound.h"
#include "Cube.h"
#include "Model.h"


//#include "DrawBuffer.h"
//#include "Cube.h"
//#include "Model.h"
//#include "Cylinder.h"
//#include "Stage.h"
//#include "Line.h"
//#include "Sphere.h"
//#include "PolyLine.h"
#include "Scene.h"

// ---グローバル変数
bool g_bFillFlag = true;

//Camera* g_pCamera;
//Collision *g_pCollision;

HRESULT ErrorBox(HRESULT hr, const char* message)
{
	MessageBox(NULL, message, "Error", MB_OK);
	return hr;
}

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	
	//fbxsdkの初期化
	ggfbx::Initialize();
	// DirectX
	hr = InitDX(hWnd, width, height, false);
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to DirectX."); }
	// キーボード
	hr = InitKeyboard();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }
	// シェーダ
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }

	CSound::InitSound();
	// ---ゲームで使うオブジェクトの初期化
	Cube::InitTexture();
	Billboard::InitTexture();
	ParallelProjection::InitTexture();
	Enemy::PointsInit();
	Model::LoadModel("Assets/Model/mech/mech.fbx");

	Scene::GetInstance()->Init();

	return hr;
}

void Uninit()
{
	Cube::UninitTexture();
	Billboard::UninitTexture();
	ParallelProjection::UninitTexture();
	CSound::UninitSound();
	SHADER->Uninit();
	UninitKeyboard();
	UninitDX();
	ggfbx::Terminate();
}

void Update()
{
	UpdateKeyboard();
	PAD->Update();

	//if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_BACK) || IsKeyTrigger('T'))
	if (IsKeyTrigger('T'))
	{
		g_bFillFlag ^= true;
	}
		ChangeFill(g_bFillFlag);

	Scene::GetInstance()->Update();
}

void Draw()
{
	BeginDrawDX();

	Scene::GetInstance()->Draw();

	DrawKeyboard();
	EndDrawDX();
}
// EOF