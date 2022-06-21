#include "DrawBuffer.h"


DrawBuffer::DrawBuffer()
	: m_pVertexBuffer(NULL)
	, m_vtxSize(0)
	, m_vtxCount(0)
	, m_pIndexBuffer(NULL)
	, m_idxCount(0)
{

}

DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

HRESULT DrawBuffer::CreateVertexBuffer(void* pVtx, UINT size, UINT count, bool isWrite)
{
	// 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {}; //右これで構造体の中身を０で初期化
	// バッファの大きさ
	bufDesc.ByteWidth = size * count;
	// バッファの使用方法
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;				//DYNAMICだとバッファを実行中にも変更できる
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//書き込み可能にする
	}
	else
	{
		bufDesc.Usage = D3D11_USAGE_DEFAULT;	
	}
	//バッファの利用先
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// --- バッファの初期値を設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	// 初期化に使うデータの置き場所の指定
	subResource.pSysMem = pVtx;

	// 頂点バッファの作成
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();//DirectXで使うものを一括で管理するものコンテキストだと描画全般を担当
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVertexBuffer);

	// --- そのほかの情報を設定
	if (SUCCEEDED(hr))	// 初期化が成功していたら
	{
		m_vtxSize = size;
		m_vtxCount = count;
	}
	return hr;
}


HRESULT DrawBuffer::CreateIndexBuffer(const long* pIdx, UINT count)
{
	//バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = sizeof(long) * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	//インデックスバッファの生成
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIndexBuffer);

	// --- そのほかの情報を設定
	if (SUCCEEDED(hr))	// 初期化が成功していたら
	{
		m_idxCount = count;
	}
	return hr;
}

//バッファの書き込み
void DrawBuffer::Write(void * pData)
{
	HRESULT hr;
	ID3D11DeviceContext* pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(m_pVertexBuffer, 0 ,D3D11_MAP_WRITE_DISCARD, 0 , &mapResource);

	// ↑Map関数で書き込みOKであれば実行
	if (SUCCEEDED(hr))
	{
		memcpy_s(mapResource.pData, m_vtxSize * m_vtxCount, pData, m_vtxSize * m_vtxCount);
	}

	//書き込み終了
	pContext->Unmap(m_pVertexBuffer, 0);
}



void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext = GetContext();
	// 頂点一つ当たりの大きさ
	UINT stride = m_vtxSize;
	// 頂点データの読み取り開始位置
	UINT offset = 0;

	// プリミティブの設定
	// TriangleList...頂点を３つずつに区切って描画
	// 例）　[0,1,2] [3,4,5]
	// TriangleStrip...参照場所を一つずつずらしながら描画
	// 例）　[0,1,2] [1,2,3] [2,3,4]
	pContext->IASetPrimitiveTopology(primitive);

	//描画に使用するバッファの設定
	//第１引数：GPUへの割り当て先
	//第２引数：頂点バッファの数
	//第３引数：頂点バッファ
	//第４引数：頂点のサイズ
	//第５引数：読み取り開始位置
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//描画
	//インデックスバッファの有無で描画処理が若干異なる
	if (m_idxCount > 0)
	{
		//描画に使用するインデックスバッファを設定
		// インデックス一つ当たりの大きさ 4byte = 32bit 2byte = 16bit
		pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//インデックスバッファを使用して描画
		pContext->DrawIndexed(m_idxCount, 0, 0);
	}
	else
	{
		//頂点バッファのみで描画
		pContext->Draw(m_vtxCount, 0);
	}
	
}