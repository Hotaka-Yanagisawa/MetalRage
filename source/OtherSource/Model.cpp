#include "Model.h"
#include "Shader.h"
#include "Object.h"

FBXPlayer Model::m_fbx;
Model::Model()
	:m_pBuffer(NULL)
{
}

Model::~Model()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
	}
}

bool Model::LoadModel(const char* pFilePath)
{
	HRESULT hr;
	//モデルファイルの読み込み
	hr = m_fbx.LoadModel(pFilePath);

	if (FAILED(hr))
	{ return false; }

	return true;
}

void Model::Create()
{
	//モデルのメッシュの数だけ、頂点バッファ作成
	int meshNum = m_fbx.GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];

	for (int i = 0; i < meshNum; ++i)
	{
		//メッシュごとに頂点バッファ
		m_pBuffer[i].CreateVertexBuffer(m_fbx.GetVertexData(i), m_fbx.GetVertexSize(i), m_fbx.GetVertexCount(i));

		//インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(m_fbx.GetIndexData(i), m_fbx.GetIndexCount(i));
	}
}

void Model::Draw()
{
	if (m_fbx.IsPlay()) SHADER->Bind(VS_ANIMATION, PS_UNLIT);
	
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(
			m_Parent->GetTransform()->Scale.x * 0.002f,
			m_Parent->GetTransform()->Scale.y * 0.002f,
			m_Parent->GetTransform()->Scale.z * 0.002f)
		* DirectX::XMMatrixRotationX(m_Parent->GetTransform()->Rotate.x)
		* DirectX::XMMatrixRotationY(m_Parent->GetTransform()->Rotate.y)
		* DirectX::XMMatrixRotationZ(m_Parent->GetTransform()->Rotate.z)
		* DirectX::XMMatrixTranslation(
			m_Parent->GetTransform()->Translate.x,
			m_Parent->GetTransform()->Translate.y,
			m_Parent->GetTransform()->Translate.z)
	);
	
	int meshNum = m_fbx.GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		if (m_fbx.IsPlay()) SHADER->SetAnimation(m_fbx.GetAnimeMatrix(i), m_fbx.GetAnimeMatrixNum(i));

		SHADER->SetTexture(m_fbx.GetTexture(i));

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	SHADER->Bind(VS_WORLD, PS_PHONG);
	//int meshNum = m_fbx.GetMeshNum();
	//for (int i = 0; i < meshNum; ++i)
	//{
	//	SHADER->SetTexture(m_fbx.GetTexture(i));
	//	m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//}
}
