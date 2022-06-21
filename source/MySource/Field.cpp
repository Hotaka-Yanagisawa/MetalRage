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
	//�L���[�u�̐���
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

//�g�k����]���ړ�
void Field::Draw()
{
	// 3D�̍��W�ϊ��̊�{�͍s��ł̌v�Z���s���B
	// �Ⴆ�΃��f�����������������A��]���������A�ړ����������ꍇ�A
	// ���ꂼ��̕ϊ��s����쐬����K�v������B�i����炷�ׂĂ���x�ɍs���ϊ��͎����ō�邵���Ȃ��j
	// ���ꂼ��̕ϊ��s����|�����킹���s�񂪍ŏI�I�ȃ��[���h�ϊ��s��ƂȂ�B
	// ���̎��A�|���Z�̏��Ԃ��ӎ����Ȃ��ƈӐ}���Ȃ����ʂƂȂ�̂Œ��ӂ��K�v�B
	// ��{�I�ɂ͊g�k*��]*�ړ��̏��ԂŌv�Z���s���Ƃ悢�B
	// DirectX�͍����珇�Ԃɏ���������B
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z) *
		(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)));

	m_pCube->Draw();
}