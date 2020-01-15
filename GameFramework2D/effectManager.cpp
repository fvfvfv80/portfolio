
#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"
effectManager::effectManager()
{
}
effectManager::~effectManager()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־��� ���͸� �˻��ϸ鼭 �����Ѵ�
	vIter = _vTotalEffects.begin();

	for (vIter; vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (vArrIter; vArrIter != mIter->second.end(); ++vArrIter)
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);

				}
				mIter->second.clear();
			}
			else
			{
				++mIter;
			}
		}
	}
}
void effectManager::update(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���͸� �˻��ϸ鼭 ������Ʈ �Ѵ�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���͸� �˻��ϸ鼭 �����Ѵ�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}

//����Ʈ�߰�(����ƮŰ��, �̹����̸�, �̹�������ũ��, �̹�������ũ��, ����Ʈ����ũ��, ����Ʈ����ũ��, FPS, ����ð�, ���۰���)
void effectManager::addEffect(string effectName, const char* imageName, int imageWidth, int imageHeight,
	int effectWidth, int effectHeight, int fps, float elapsed, int buffer)
{
	image* img;
	arrEffects vEffectBuffer;	//����Ʈ ����
	arrEffect mArrEffect;		//Ű���� ���� ����Ʈ ��� STL���� �� map�� ��

	//��ϵ� �̹����� �Ŵ����� �̹� ������
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	//������
	else
	{
		//�̹��� ���
		img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
	}

	//���͸�ŭ ������ ���;ȿ� �־��ִ� �κ�
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsed);
	}

	//����Ʈ ���۸� �ʿ� ����
	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));

	//Ű ���� ���۸� ���� ���� �ٽ� ��Ż�ʿ� �־���
	_vTotalEffects.push_back(mArrEffect);
}

//����Ʈ �÷���(����ƮŰ��, ����Ʈ ��Ʈ�� x��ġ, ����Ʈ ��Ʈ�� y��ġ)
void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���͸� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���������� ���� ������~ �Ѿ
			if (!(mIter->first == effectName)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� �����Ų��
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
