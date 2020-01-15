#pragma once
#include "animation.h" //�ִϸ��̼� Ŭ���� �߰�
//==================================================================
//		## image ## (�̹��� Ŭ����)
//==================================================================

class image
{
public:

	//�̹��� �ε� ��Ÿ��
	enum IMAGE_LOADKIND
	{
		LOAD_RESOURCE = 0,	//���ҽ��� �ε�
		LOAD_FILE,			//���Ϸκ��� �ε�
		LOAD_EMPTY,			//�׳� ����
		LOAD_END
	};

	//�̹��� ���� ����ü
	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP	hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;	//���� ������ X
		int		currentFrameY;	//���� ������ Y
		int		maxFrameX;		//�ִ� ������ X
		int		maxFrameY;		//�ִ� ������ Y
		int		frameWidth;		//������ ����ũ��
		int		frameHeight;	//������ ����ũ��
		BYTE	loadType;
		RECT	boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� ��θ�

	BOOL			_tran;			//���� ����ֳ� ����?
	COLORREF		_transColor;	//���� �÷�Ű

	BLENDFUNCTION	_blendFunc;		//���� ���带 ���� ����
	LPIMAGE_INFO	_blendImage;	//���� ���带 ����ϱ� ���� �̹��� ����

public:
	image(void);
	~image(void);

	//�� ��Ʈ�� �����

	//�ʱ�ȭ �Լ�
	//�ƹ��͵� ���� �� ��Ʈ�� ����
	HRESULT init(int width, int height);

	//���ҽ��� ���� �о����
	HRESULT init(const DWORD resID, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� ���� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� + ������ ���� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//������ (�����Լ�)
	void release(void);

	//���� ����
	void setTransColor(BOOL trans, COLORREF transColor);

	//����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//���� ����
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	
	//������ ���ķ���
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//���� ����
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//�ִ� ����
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniRenderAlpha(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//DC���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//��ǥ x ����
	inline void setX(float x) { _imageInfo->x = x; }
	//��ǥ x ���
	inline float getX(void) { return _imageInfo->x; }
	//��ǥ y ����
	inline void setY(float y) { _imageInfo->y = y; }
	//��ǥ y ���
	inline float getY(void) { return _imageInfo->y; }

	//��ǥ���� x, y
	inline void setCenter(float x, float y) {
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//�̹��� ���α���
	inline int getWidth(void) { return _imageInfo->width; }
	//�̹��� ���α���
	inline int getHeight(void) { return _imageInfo->height; }

	//�ٿ�� �ڽ�(�浹üũ)
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_imageInfo->x - (_imageInfo->width / 2)),
			int(_imageInfo->y - (_imageInfo->height / 2)),
			int(_imageInfo->x + (_imageInfo->width / 2)),
			int(_imageInfo->y + (_imageInfo->height / 2)) };
		return rc;
	}
	//�����ӹٿ�� �ڽ�(�浹üũ)
	inline RECT frameBoundingBox(void)
	{
		RECT rc = { int(_imageInfo->x),
			int(_imageInfo->y),
			int(_imageInfo->x + _imageInfo->frameWidth),
			int(_imageInfo->y + _imageInfo->frameHeight) };
		return rc;
	}

	//������ x �����ϱ�
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	//������ y �����ϱ�
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	
	//�ƽ������� x ���
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	//�ƽ������� y ���
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
	//������ x ���
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	//������ y ���
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	//������ ���α��� ���
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	//������ ���α��� ���
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
};
