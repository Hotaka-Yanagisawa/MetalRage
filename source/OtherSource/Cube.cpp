#include "Cube.h"
#include "Shader.h"
#include "Object.h"

Cube::Cube()
{

	Vertex vtx[] =
	{
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//�O����
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//�O�E��
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//�O����
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//�O�E��
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//��E��
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//�㍶��
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//��E��
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//�㍶��

		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{0,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{1,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{1,0} },
		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{0,0} },
	};
	//���_�o�b�t�@���Ƃ�UV�p�ɂR�U�̒��_���g���ƃe�N�X�`�����Y��ɓ\���

	//�C���f�b�N�X�f�[�^
	long idx[] = {
		0,1,2, 1,3,2,	// ��O
		1,4,3, 4,6,3,	// �E
		4,5,6, 5,7,6,	// ��
		5,0,7, 0,2,7,	// ��
		9,8,10, 8,11,10,	// ��
		2,3,7, 3,6,7	// ��
	
	};

	//�o�b�t�@�̍쐬
	//m_buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));

	//m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}

Cube::Cube(Float3 pos, Float3 size)
{
	m_pos = pos;
	m_Scale = size;

	Vertex vtx[] =
	{
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//�O����
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//�O�E��
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//�O����
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//�O�E��
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//��E��
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//�㍶��
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//��E��
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//�㍶��

		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{0,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{1,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{1,0} },
		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{0,0} },
	};
	//���_�o�b�t�@���Ƃ�UV�p�ɂR�U�̒��_���g���ƃe�N�X�`�����Y��ɓ\���

	//�C���f�b�N�X�f�[�^
	long idx[] = {
		0,1,2, 1,3,2,	// ��O
		1,4,3, 4,6,3,	// �E
		4,5,6, 5,7,6,	// ��
		5,0,7, 0,2,7,	// ��
		9,8,10, 8,11,10,	// ��
		2,3,7, 3,6,7	// ��
		
	};

	//�o�b�t�@�̍쐬
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
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//�O����
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//�O�E��
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//�O����
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f, -m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//�O�E��
		{{ m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,0} },	//��E��
		{{-m_Scale.x*0.5f, m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,0} },	//�㍶��
		{{ m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {0,1} },	//��E��
		{{-m_Scale.x*0.5f,-m_Scale.y*0.5f,  m_Scale.z*0.5f}, {1,1,1,1}, {1,1} },	//�㍶��

		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{0,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f,-m_Scale.z*0.5f},{1,1,1,1},{1,1} },
		{ { m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{1,0} },
		{ {-m_Scale.x*0.5f, m_Scale.y*0.5f, m_Scale.z*0.5f},{1,1,1,1},{0,0} },
	};
	//���_�o�b�t�@���Ƃ�UV�p�ɂR�U�̒��_���g���ƃe�N�X�`�����Y��ɓ\���

	//�C���f�b�N�X�f�[�^
	long idx[] = {
		0,1,2, 1,3,2,	// ��O
		1,4,3, 4,6,3,	// �E
		4,5,6, 5,7,6,	// ��
		5,0,7, 0,2,7,	// ��
		9,8,10, 8,11,10,	// ��
		2,3,7, 3,6,7	// ��
		
	};
	//�o�b�t�@�̍쐬
	m_buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));

	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}




void Cube::Draw()
{
	SHADER->SetTexture(m_pTexture[1]);
	FigureBase::Draw();
}
