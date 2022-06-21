#include "Field.h"

Field::Field(Float3 size)
{
	m_Scale = size;
}

Field::~Field()
{
	Uninit();
}


void Field::Init()
{
	//キューブの生成
	m_pCube = new Cube();
	m_pCube->SetPos(m_pos.x, m_pos.y, m_pos.z);
	m_pCube->SetScale(1);
}


void Field::Uninit()
{
	if (m_pCube != nullptr)
	{
		delete m_pCube;
		m_pCube = NULL;
	}
}


void Field::Update()
{

}

//拡縮→回転→移動
void Field::Draw()
{
	// 3Dの座標変換の基本は行列での計算を行う。
	// 例えばモデルを小さくしたい、回転させたい、移動させたい場合、
	// それぞれの変換行列を作成する必要がある。（これらすべてを一度に行う変換は自分で作るしかない）
	// それぞれの変換行列を掛け合わせた行列が最終的なワールド変換行列となる。
	// この時、掛け算の順番を意識しないと意図しない結果となるので注意が必要。
	// 基本的には拡縮*回転*移動の順番で計算を行うとよい。
	// DirectXは左から順番に処理をする。
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z) *
		(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)));

	m_pCube->Draw();
}