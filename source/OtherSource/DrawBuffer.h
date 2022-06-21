///////////////////////////////////////
//DrawBuffer.h
//-------------------------------------
//描画
//-------------------------------------
//作成者：柳沢帆貴
//-------------------------------------
//2020/10/07 授業で作成
///////////////////////////////////////
#ifndef __DRAW_BUFFER_H_
#define __DRAW_BUFFER_H_

#include "DirectX.h"

class DrawBuffer
{
public:
	DrawBuffer();
	~DrawBuffer();
	
	//DirectXはBufferに溜めた頂点情報をもとに描画行う。
	//頂点の情報は増やしたり減らしたりすることが出来る。
	//そのため、引数で頂点の細かい情報を教える必要がある。
	////////////////////////////////////////
	//引数１：描画に必要な頂点のデータ
	//引数２：一つ当たりの頂点のデータサイズ
	//引数３：描画する頂点の数
	//引数４：頂点バッファの書き換えが可能か
	////////////////////////////////////////
	HRESULT CreateVertexBuffer(void* pVtx, UINT size, UINT count, bool isWrite = false);

	//インデックスバッファの作成
	//実際のモデルは同じ頂点を共有して三角形を描画することが多い。
	//そこで三角形を描画する際に、直接頂点を指定するのではなく、
	//インデックス（参照番号）を用いて描画する。
	//頂点バッファのみで描画するよりもデータ量が軽くなる
	//第１引数：
	//第２引数：
	HRESULT CreateIndexBuffer(const long* pIdx, UINT count);

	void Write(void* pData);

	//バッファの描画   第１引数：ポリゴンの描画方法
	void Draw(D3D11_PRIMITIVE_TOPOLOGY primitive);

private:
	// 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer;
	// 頂点のデータサイズ
	UINT m_vtxSize;
	// 頂点の数
	UINT m_vtxCount;

	//インデックスバッファ
	ID3D11Buffer* m_pIndexBuffer;
	//インデックスの数
	UINT m_idxCount;
	//
};


#endif // !__DRAW_BUFFER_H_

