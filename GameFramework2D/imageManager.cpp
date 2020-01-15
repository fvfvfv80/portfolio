#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager(void)
{
}
imageManager::~imageManager(void)
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

//�¾�
HRESULT	imageManager::init(void)
{
	return S_OK;
}

//������
void imageManager::release(void)
{
	deleteAll();
}

//Ű�� �����Ͽ� ���̹��� �߰�
image* imageManager::addImage(string strKey, int width, int height)
{
	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//Ű�� �����Ͽ� ���ҽ�ID�� �̹��� �߰�
image* imageManager::addImage(string strKey, const DWORD resID, int width, int height, BOOL trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(resID, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//Ű�� �����Ͽ� ���Ϸ� �̹��� �߰�
image* imageManager::addImage(string strKey, const char* fileName, int x, int y, int width, int height, BOOL trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(fileName, (float)x, (float)y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img)
		return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//Ű�� �����Ͽ� ���Ϸ� �̹��� �߰�
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img)
			return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//���Ϸ� �̹����߰� (Ű���� ���� �̸�)
image* imageManager::addImage(int width, int height, const char* fileName, BOOL trans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� Ű���� ���� �̸����� �����Ѵ�.
	string strFileName = fileName;
	if (!getFileName(strFileName))
	{
		//�̸� ������ ���� �ϸ� NULL ����
		return NULL;
	}

	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strFileName);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strFileName, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img)
			return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű ���� �̹����� �����ϴ� �� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����Ѵٸ� �߰����� �ʰ� ���� �Ѵ�.
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹��� ���� �ϰ� �̹����� ����� ������ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img)
			return NULL;
	}

	//������ �̹��� Map ����Ʈ�� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//�̹��� ã��
image* imageManager::findImage(string strKey)
{
	//�ش� Ű�� �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�ش� Ű���� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

//����
BOOL imageManager::deleteImage(string strKey)
{
	//�ش� Ű�� �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�ش� Ű���� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();

		//�޸�����
		SAFE_DELETE(key->second);

		//�ʸ���Ʈ���� ����
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//��ü ����
BOOL imageManager::deleteAll(void)
{
	//�� ��ü�� ���鼭 �����.
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//�������� �ݺ��ڸ� �������� �ʴ´�.
		if (iter->second != NULL)
		{
			iter->second->release();
			delete iter->second;
			iter = _mImageList.erase(iter);
		}
		else
		{
			//�ݺ��� ����
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}

//�̹��� ��� �̸��� �����̸����� �˻�
BOOL imageManager::getFileName(string& strFile)
{
	if (strFile.empty()) return FALSE;

	//String ������ ��ġ ��
	size_t pos;

	// ��� ¥����
	//�ڿ��� ���� '/' ���ڸ����� ���� ã�� pos �� ����
	pos = strFile.find_first_of("/");

	//ã�Ҵٸ�..
	if (pos != string::npos)
	{
		//©�� ����
		strFile = strFile.substr(pos + 1, strFile.length());
	}
	else //�� ã�Ҵٸ�... '\' �� ã�´�
	{
		//�ٽ� ã�´�/
		pos = strFile.find_last_of("\\");

		if (pos != string::npos)
		{
			//©�� ����
			strFile = strFile.substr(pos + 1, strFile.length());
		}
	}

	// Ȯ���� ¥����
	pos = strFile.find(".");

	if (pos != string::npos) strFile = strFile.substr(0, pos);
	else return FALSE;

	return TRUE;
}

//���� (������ �̹����� Ű �� �ʿ�)
//�Ϲ� ����
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//�����ӷ���
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, frameX, frameY);
}

//���� ����
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
	image* img = findImage(strKey);
	
	if (img) img->frameAlphaRender(hdc, destX, destY, frameX, frameY, alpha);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}