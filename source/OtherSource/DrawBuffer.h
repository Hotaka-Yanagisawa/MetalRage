///////////////////////////////////////
//DrawBuffer.h
//-------------------------------------
//�`��
//-------------------------------------
//�쐬�ҁF���򔿋M
//-------------------------------------
//2020/10/07 ���Ƃō쐬
///////////////////////////////////////
#ifndef __DRAW_BUFFER_H_
#define __DRAW_BUFFER_H_

#include "DirectX.h"

class DrawBuffer
{
public:
	DrawBuffer();
	~DrawBuffer();
	
	//DirectX��Buffer�ɗ��߂����_�������Ƃɕ`��s���B
	//���_�̏��͑��₵���茸�炵���肷�邱�Ƃ��o����B
	//���̂��߁A�����Œ��_�ׂ̍�������������K�v������B
	////////////////////////////////////////
	//�����P�F�`��ɕK�v�Ȓ��_�̃f�[�^
	//�����Q�F�������̒��_�̃f�[�^�T�C�Y
	//�����R�F�`�悷�钸�_�̐�
	//�����S�F���_�o�b�t�@�̏����������\��
	////////////////////////////////////////
	HRESULT CreateVertexBuffer(void* pVtx, UINT size, UINT count, bool isWrite = false);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	//���ۂ̃��f���͓������_�����L���ĎO�p�`��`�悷�邱�Ƃ������B
	//�����ŎO�p�`��`�悷��ۂɁA���ڒ��_���w�肷��̂ł͂Ȃ��A
	//�C���f�b�N�X�i�Q�Ɣԍ��j��p���ĕ`�悷��B
	//���_�o�b�t�@�݂̂ŕ`�悷������f�[�^�ʂ��y���Ȃ�
	//��P�����F
	//��Q�����F
	HRESULT CreateIndexBuffer(const long* pIdx, UINT count);

	void Write(void* pData);

	//�o�b�t�@�̕`��   ��P�����F�|���S���̕`����@
	void Draw(D3D11_PRIMITIVE_TOPOLOGY primitive);

private:
	// ���_�o�b�t�@
	ID3D11Buffer* m_pVertexBuffer;
	// ���_�̃f�[�^�T�C�Y
	UINT m_vtxSize;
	// ���_�̐�
	UINT m_vtxCount;

	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* m_pIndexBuffer;
	//�C���f�b�N�X�̐�
	UINT m_idxCount;
	//
};


#endif // !__DRAW_BUFFER_H_

