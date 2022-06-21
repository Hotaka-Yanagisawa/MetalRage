#include "Collision.h"
#include "Object.h"
#include "Collider2D.h"
#include "Enemy.h"
#include "State/PatrolState.h"
#include "State/DiscoveryState.h"

Collision::Collision()
{
}

Collision::~Collision()
{
	Uninit();
}

bool Collision::Init()
{
	return true;
}

void Collision::Uninit()
{
}

void Collision::Update()
{
	int ShiftNum = -1;
	// ���X�g����
	for (auto A : COLLIDER_LIST)
	{
		++ShiftNum;
		int continueNum = ShiftNum + 1;
		for (auto B : COLLIDER_LIST)
		{
			if (continueNum > 0)
			{
				continueNum--;
				continue;
			}
			// �l�p�`���m�̓����蔻��
			// 2D�ł�3D�ł�
			// ���S�܂ł̋��� < �����̑傫���𑫂����킹�����͕ς��Ȃ��B
			// �v�Z���鎲�������邾��
			Float3 aPos = (*A).m_Parent->GetTranslate();
			Float3 bPos = (*B).m_Parent->GetTranslate();
			Float3 aScale = (*A).m_Parent->GetScale();
			Float3 bScale = (*B).m_Parent->GetScale();

			Float3 distance(
				fabsf(bPos.x - aPos.x),
				fabsf(bPos.y - aPos.y),
				fabsf(bPos.z - aPos.z)
			);

			bool hitX = distance.x < (aScale.x + bScale.x) * 0.5f;
			bool hitY = distance.y < (aScale.y + bScale.y) * 0.5f;
			bool hitZ = distance.z < (aScale.z + bScale.z) * 0.5f;

			// �����蔻��̌���
			if (hitX && hitY && hitZ)
			{
				for (auto i : A->m_Parent->ComponentList) i->OnCollision(B->m_Parent);
				for (auto j : B->m_Parent->ComponentList) j->OnCollision(A->m_Parent);
			}
		}
	}
	ShiftNum = -1;
	
	// ���X�g����
	for (auto A : COLLIDER2D_LIST)
	{
		if (A->m_Parent->GetType() != PLAYER) continue;
		for (auto B : COLLIDER2D_LIST)
		{
			Fan fan;
			fan.Position.x = B->m_Parent->GetTransform()->Translate.x;
			fan.Position.y = B->m_Parent->GetTransform()->Translate.z;
			fan.Length = 20;
			fan.FanDegree = 360;
			fan.RotateDegree = 180;
			Float2 point;
			point.x = A->m_Parent->GetTransform()->Translate.x;
			point.y = A->m_Parent->GetTransform()->Translate.z;
		
			if (IsCollidingFanAndPoint(fan, point))
			{
				if (B->m_Parent->GetType() == ENEMY)
				{
					//B->m_Parent->GetComponent<Enemy>()->CreateBullet();
					if (B->m_Parent->GetComponent<Enemy>()->GetHierarchyState() != DiscoveryState::GetInstance())
					{
						B->m_Parent->GetComponent<Enemy>()->SetHierarchyState(DiscoveryState::GetInstance());
					}
					B->m_Parent->GetComponent<Enemy>()->m_Placemark.SetColor(Float4(1, 0, 0, 1));
				}
			}
			else
			{
				if (B->m_Parent->GetComponent<Enemy>()->GetHierarchyState() != PatrolState::GetInstance())
				{
					B->m_Parent->GetComponent<Enemy>()->SetHierarchyState(PatrolState::GetInstance());
				}
				B->m_Parent->GetComponent<Enemy>()->m_Placemark.SetColor(Float4(0, 1, 0, 1));

			}
		}	
	}
}

bool Collision::IsCollidingFanAndPoint(Fan fan, Float2 point)
{
	const float RAD = 3.141519f / 180.0f;

	// �_�Ɛ�̃x�N�g��
	Float2 vec_fan_to_point = {
		point.x - fan.Position.x,
		point.y - fan.Position.y
	};

	// �x�N�g���̒����Z�o
	float vec_length = sqrtf((vec_fan_to_point.x * vec_fan_to_point.x) + (vec_fan_to_point.y * vec_fan_to_point.y));

	// �x�N�g���Ɛ�̋����̔�r
	if (fan.Length < vec_length)
	{
		// �������Ă��Ȃ�
		return false;
	}

	// �~�ʂ̕����x�N�g�������߂�
	float rotate_rad = fan.RotateDegree * RAD;
	Float2 fan_dir =
	{
		1.0f,
		0.0f
	};

	// �x�N�g������]������
	Float2 rotate_fan_dir
	{
		fan_dir.x * cosf(rotate_rad) + fan_dir.y * -sinf(rotate_rad),
		fan_dir.x * sinf(rotate_rad) + fan_dir.y * cosf(rotate_rad)
	};

	// ��Ɠ_�̃x�N�g����P�ʃx�N�g���ɂ���
	Float2 normal_fan_to_point = {
		vec_fan_to_point.x / vec_length,
		vec_fan_to_point.x / vec_length
	};

	// ���όv�Z
	float dot = normal_fan_to_point.x * rotate_fan_dir.x + normal_fan_to_point.y * rotate_fan_dir.y;

	// ��͈̔͂�cos�ɂ���
	float fan_cos = cosf((fan.FanDegree / 2.0f) * RAD);

	// �_����͈͓̔��ɂ��邩���r����
	if (fan_cos > dot)
	{
		// �������ĂȂ�
		return false;
	}

	return true;
}

void Collision::Register(Collider * pA, Collider * pB)
{
	//if (m_registerNum > MAX_COLLISION_REGISTER) return;

	//m_pList[m_registerNum][0] = pA;
	//m_pList[m_registerNum][1] = pB;
	//++m_registerNum;
}

void Collision::Push(Collider * pDynamic, Collider * pStatic)
{
	Float3 dPos  = pDynamic->m_Parent->GetTranslate();
	Float3 sPos  = pStatic->m_Parent->GetTranslate();
	Float3 dSize = pDynamic->m_Parent->GetScale();
	Float3 sSize = pStatic->m_Parent->GetScale();
	Float3 dMove = pDynamic->m_Parent->GetMove();
	
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
			pDynamic->m_Parent->SetTranslate(dPos);
			//�S�Ă̈ړ��ʂ�0�ɂ��Ă��܂��ƁA
			//���̃I�u�W�F�N�g�Ɖ����o���̌v�Z��
			//����ۂɈړ��ʂ��������ƂɂȂ�̂ŁA
			//�ړ��ʂ�0�ɂ��Ȃ���΂Ȃ�Ȃ���������0�ɂ���B
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
			pDynamic->m_Parent->SetMove(dMove);
			break;
		}
	}


}

