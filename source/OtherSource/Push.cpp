#include "Push.h"
#include "FloatOperator.h"
#include "Object.h"
#include "Player.h"

void Push::Start()
{
}

void Push::OnCollision(Object * obj)
{
	if (obj->GetType() != PLAYER && obj->GetType() != COLLIDER && obj->GetType() != ENEMY) return;
	Float3 dPos = obj->GetTranslate();
	Float3 sPos = m_Parent->GetTranslate();
	Float3 dSize = obj->GetScale();
	Float3 sSize = m_Parent->GetScale();
	Float3 dMove = obj->GetMove();

	//�v�Z�ɕK�v�ȏ��𔲂��o��
	//�ړ��ʂ���ړ�������������߂�
	//���ړ���������͂P��-1�ŕ\��
	Float3 dir(dMove.x > 0 ? 1 : -1, dMove.y > 0 ? 1 : -1, dMove.z > 0 ? 1 : -1);
	//���ۂɓ����蔻��ł߂荞�񂾂̂́A�I�u�W�F�N�g�̍��W�ł͂Ȃ��A
	//�p�������߂荞��ł��邱�Ƃ�����̂ŁA�Ώۂ̊p���v�Z�ŋ��߂�
	Float3 dPoint
	(dPos.x + dir.x * dSize.x * 0.5f, dPos.y + dir.y * dSize.y * 0.5f, dPos.z + dir.z * dSize.z * 0.5f);
	//�ړ��O�̊p�̍��W
	//���̂܂܂̈ړ��ʂňړ��O�̍��W��\�����Ƃ���ƕ��������_�̌v�Z�덷�ɂ��A
	//�ړ��x�N�g���̎n�_���ʂ̓����ɂ��邱�ƂɂȂ�A�ђʂ��ĂȂ��Ɣ��肳���B
	//�����������邽�߂ɁA�ړ��O�̈ʒu�������Ȃ�悤��
	//�v�Z�̎������A�ړ��ʂ�傫������
	Float3 prePoint(dPoint.x - dMove.x * 1.1f, dPoint.y - dMove.y * 1.1f, dPoint.z - dMove.z * 1.1f);
	//�Փ˂��ꂽ���̊p���v�Z
	//�Փ˂��ꂽ���̊p�͈ړ������𔽓]���������Ɍ������đ傫���̔����𑫂��Ƌ��߂���
	Float3 sPoint
	(sPos.x - dir.x * sSize.x * 0.5f, sPos.y - dir.y * sSize.y * 0.5f, sPos.z - dir.z * sSize.z * 0.5f);
	// �ʏ�̈�_����ړ��x�N�g���̎n�_�ƏI�_�֌������x�N�g��(�̒���?)���v�Z����
	Float3 vStart(prePoint.x - sPoint.x, prePoint.y - sPoint.y, prePoint.z - sPoint.z);
	Float3 vEnd(dPoint.x - sPoint.x, dPoint.y - sPoint.y, dPoint.z - sPoint.z);

	//���ꂼ��̖ʂƌv�Z
	//�e�ʂ̖@���x�N�g��
	Float3 Normal[] =
	{
		Float3(-dir.x, 0, 0),	//x�̖�
		Float3(0, -dir.y, 0),	//y�̖�
		Float3(0, 0, -dir.z),	//z�̖ʂƂ������Ƃ��Ǝv����@�p�͎O�̖ʂ̒��_������R��
	};

	for (int i = 0; i < _countof(Normal); i++)
	{
		//�ʂ̖@���Ƃ̓��ς��v�Z
		float dotS = vStart.x * Normal[i].x + vStart.y * Normal[i].y + vStart.z * Normal[i].z;
		float dotE = vEnd.x   * Normal[i].x + vEnd.y   * Normal[i].y + vEnd.z   * Normal[i].z;
		//���ꂼ��̓��ς̌��ʂ����ƕ��̒l�ł���Έړ��x�N�g�����ʂ��ђʂ��Ă���
		//���ƕ��̑g�ݍ��킹���ǂ����͊|���Z�Ŕ���ł���
		//(��*��=�� / ��*��=�� / ��*��=���j
		if (dotS * dotE < 0)
		{
			//�ړ��x�N�g���̕����ɂ߂肱�񂾗ʂ�߂��̂ł͂Ȃ��A�ʂ̕����Ɍ�������
			//�߂�(�߂������͓��ς̒l�Ɠ�����)
			dotE = fabsf(dotE);
			dPos.x += Normal[i].x * dotE;
			dPos.y += Normal[i].y * dotE;
			dPos.z += Normal[i].z * dotE;
			obj->SetTranslate(dPos);

			//�S�Ă̈ړ��ʂ�0�ɂ��Ă��܂��ƁA
			//���̃I�u�W�F�N�g�Ɖ����o���̌v�Z��
			//����ۂɈړ��ʂ��������ƂɂȂ�̂ŁA
			//�ړ��ʂ�0�ɂ��Ȃ���΂Ȃ�Ȃ���������0�ɂ���B
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
	
			obj->SetMove(dMove);
			break;
		}
	}

	if (obj->GetType() == PLAYER)
	{
		if (m_Parent->GetType() == FLOOR && obj->GetTransform()->Move.y == 0)
		{
			obj->GetComponent<Player>()->m_bJump = false;
		}
		if (m_Parent->GetType() == PLAYER && obj->GetTransform()->Move.y == 0)
		{
			obj->GetComponent<Player>()->m_bJump = false;
		}
	}
}
