#pragma once

class Object;

class Component
{
public:
	Component() {}
	virtual ~Component() {}
	//�e�A�j
	virtual void Start() {}
	virtual void Uninit() { delete this; }
	virtual void Update() {}
	virtual void Draw() {}

	//�������Ă��鎞�̏���
	virtual void OnCollision(Object *) {}
	//*************�݌v��****************************
	//�����������̏���
	//Object�ɂ����std::Vector<Object *>��ǉ�����
	//A��B�Ɠ������Ă��鎞��
	//find(B)��A������Vector<Object *>��B�̃A�h���X��
	//�������ꍇ�͏������s��Ȃ��B�Ȃ�������s��
	//A��B���������ĂȂ�������
	//find(B)�ŃA�h���X���������ꍇReMove����
	//************************************************
	virtual void OnCollisionEnter(Object *) {}

	Object *m_Parent = nullptr;
	bool m_bRemove = false;
};
