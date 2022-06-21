#include "MoveState.h"
#include "../Object.h"
#include "../Enemy.h"

void MoveState::Init(Enemy *obj)
{
	
}

void MoveState::Update(Enemy *obj, HierarchyEnemyState * parent)
{
	//�ړI�n�ɒ������玟�̖ړI�n�̔ԍ��̐ݒ�
	if (fabsf(obj->m_MovePoint.x - obj->m_Parent->GetTranslate().x) +
		fabsf(obj->m_MovePoint.z - obj->m_Parent->GetTranslate().z) < 1)
	{
		obj->m_nPointNum = rand() % (19*19);
		if (obj->m_nPointNum > 19 * 19 - 1)
		{
			obj->m_nPointNum = 0;
		}
	}
	//���݂̖ړI�n�ݒ�
	obj->m_MovePoint = obj->m_decidedPoints[obj->m_nPointNum / 19][obj->m_nPointNum % 19];

	//�ړI�n�Ɍ����Ĉړ��ʂ̐ݒ�
	float Rad = atan2f(obj->m_MovePoint.z - obj->m_Parent->GetTranslate().z,
					   obj->m_MovePoint.x - obj->m_Parent->GetTranslate().x);

	obj->m_Parent->GetTransform()->Move.x = cosf(Rad) * 0.1f;
	obj->m_Parent->GetTransform()->Move.y = -0.1f;
	obj->m_Parent->GetTransform()->Move.z = sinf(Rad) * 0.1f;

	//�ړI�n�̈ʒu���玩���i�G�l�~�[�j�̊p�x���Z�o
	float moveRad = atan2f(
		obj->m_MovePoint.z - obj->m_Parent->GetTranslate().z,
		obj->m_MovePoint.x - obj->m_Parent->GetTranslate().x);
	
	obj->m_Parent->SetRotate(Float3(0, 90 * 3.14f / 180.0f - moveRad, 0));
}
