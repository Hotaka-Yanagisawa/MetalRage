#include "Cube.h"
#include "Shader.h"
#include "Object.h"

Cube::Cube()
{

	Vertex vtx[] =
	{
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//前左上
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//前右上
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//前左下
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//前右下
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//後右上
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//後左上
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//後右下
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//後左下

		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{0,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{1,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{1,0} },
		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{0,0} },
	};
	//頂点バッファ作るときUV用に３６個の頂点を使うとテクスチャを綺麗に貼れる

	//インデックスデータ
	long idx[] = {
		0,1,2, 1,3,2,	// 手前
		1,4,3, 4,6,3,	// 右
		4,5,6, 5,7,6,	// 奥
		5,0,7, 0,2,7,	// 左
		9,8,10, 8,11,10,	// 上
		2,3,7, 3,6,7	// 下
	
	};

	//バッファの作成
	//m_buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));

	//m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}

Cube::Cube(Float3 pos, Float3 size)
{
	m_pos = pos;
	m_Scale = size;

	Vertex vtx[] =
	{
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//前左上
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//前右上
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//前左下
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//前右下
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//後右上
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//後左上
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//後右下
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//後左下

		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{0,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{1,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{1,0} },
		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{0,0} },
	};
	//頂点バッファ作るときUV用に３６個の頂点を使うとテクスチャを綺麗に貼れる

	//インデックスデータ
	long idx[] = {
		0,1,2, 1,3,2,	// 手前
		1,4,3, 4,6,3,	// 右
		4,5,6, 5,7,6,	// 奥
		5,0,7, 0,2,7,	// 左
		9,8,10, 8,11,10,	// 上
		2,3,7, 3,6,7	// 下
		
	};

	//バッファの作成
	m_buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));

	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}

Cube::~Cube()
{

}

void Cube::SetScale(Float3 newScale)
{
	m_Scale = newScale;

	Vertex vtx[] =
	{
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//前左上
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//前右上
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//前左下
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//前右下
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//後右上
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//後左上
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//後右下
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//後左下

		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{0,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{1,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{1,0} },
		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{0,0} },
	};
	//頂点バッファ作るときUV用に３６個の頂点を使うとテクスチャを綺麗に貼れる

	//インデックスデータ
	long idx[] = {
		0,1,2, 1,3,2,	// 手前
		1,4,3, 4,6,3,	// 右
		4,5,6, 5,7,6,	// 奥
		5,0,7, 0,2,7,	// 左
		9,8,10, 8,11,10,	// 上
		2,3,7, 3,6,7	// 下
		
	};
	//バッファの作成
	m_buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));

	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}




void Cube::Draw()
{
	SHADER->SetTexture(m_pTexture[1]);
	FigureBase::Draw();
}
