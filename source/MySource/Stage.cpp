#include "Stage.h"

//StageBase→継承→Stage1,2,3....

Stage::Stage()
	: m_ppFields(NULL)
	, m_nFieldNum(0)
{
}

Stage::~Stage()
{
	Uninit();
}

void Stage::Start()
{
	struct FieldSetting
	{
		Float3 pos;
		Float3 size;
	};

	FieldSetting settings[] =
	{
		{ Float3(0,-0.5f,0),
		  Float3(30,1,30),},

		{ Float3(10, 0.5f,10),
		  Float3(10,1,10),},

		  { Float3(5, 0.5f,5),
		  Float3(10,1,10),},
	};

	// 初期データからフィールドの数を計算
	m_nFieldNum = sizeof(settings) / sizeof(settings[0]);
	// ポインタを格納する配列を作成
	m_ppFields = new Field*[m_nFieldNum];
	// それぞれの配列にフィールドをメモリ確保
	for (int i = 0; i < m_nFieldNum; i++)
	{
		m_ppFields[i] = new Field(settings[i].size);
		m_ppFields[i]->SetPos(settings[i].pos);
		m_ppFields[i]->Init();
	}

	//※クラスを配列でメモリ確保する際は
	//規定のコンストラクタ（引数の無いコンストラクタ）が必要。
	//どうしても引数付きのコンストラクタを配列で呼び出したい場合は、
	//ポインタを格納する配列を確保し、
	//配列一つ一つの要素にメモリ確保を行うことで
	//引数付きコンストラクタを呼び出すやり方がある。
}

void Stage::Uninit()
{
	if (m_ppFields != NULL)
	{
		for (int i = 0; i < m_nFieldNum; i++)
		{
			//個別に削除
			delete m_ppFields[i];
		}
		//配列を削除
		delete[] m_ppFields;
		m_ppFields = NULL;
	}
}

void Stage::Update()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Update();
	}
}

void Stage::Draw()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Draw();
	}
}

Field *Stage::GetField(int index)
{
	if (index < m_nFieldNum)
	{
		return m_ppFields[index];
	}
	return NULL;
}

