#include "MemoryLine.h"

MemoryLine::MemoryLine()
{
	line = NULL;
	joinTarget = NULL;
	joinPlayer = NULL;
	pointList = NULL;
	renderList = NULL;

	initialized = false;
	
	pileNum = 0;
	pointNum = NULL;
	renderNum = 0;
}

MemoryLine::~MemoryLine()
{
	SAFE_DELETE_ARRAY(line);
	SAFE_DELETE_ARRAY(pointList);
	SAFE_DELETE_ARRAY(renderList);
	SAFE_DELETE_ARRAY(pointNum);
}

void MemoryLine::initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Player* player)
{
	pileNum = num;
	line = new Line[num];
	for (int i = 0; i < pileNum; i++)
	{
		line[i].start = D3DXVECTOR3(0,0,0);
		line[i].end = D3DXVECTOR3(0, 0, 0);
	}
	pointList = new D3DXVECTOR3*[pileNum];

	//pointList[0] = new D3DXVECTOR3[pileNum];
	//pointList[0][0] = D3DXVECTOR3(0,0,0);

	pointNum = new int[pileNum];

	//���C���̌��ƂȂ郁�����[�p�C���̃Z�b�g
	joinTarget = memoryPile;
	//�������[�p�C����ݒu����v���C���[
	joinPlayer = player;
	
	setLine(device);
	billboard.initialize(device);

	initialized = true;
}

void MemoryLine::unInitialize()
{

}

void MemoryLine::update(LPDIRECT3DDEVICE9 device, float frameTime)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��
	setLine(device);
}

void MemoryLine::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��
	billboard.render(device, view, projection, cameraPosition);
}

void MemoryLine::setLine(LPDIRECT3DDEVICE9 device)
{
	renderNum = 0;
	//�`�惉�C���̐ݒ�
	for (int i = 0; i < pileNum; i++)
	{
		pointNum[i] = 0;
		if (joinTarget[i].getActive())
		{
			line[i].start = *joinTarget[i].getPosition();
			int k = i + 1;
			if (k >= pileNum)k = 0;
			if (joinTarget[k].getActive())
			{
				line[i].end = *joinTarget[k].getPosition();
			}
			else {
				line[i].end = *joinPlayer->getPosition();
			}
		}

		//
		float length = D3DXVec3Length(&(line[i].end - line[i].start));
		pointNum[i] = (int)(length / 1.0f);
		renderNum += pointNum[i];
		if (pointNum[i] <= 0)continue;
		pointList[i] = new D3DXVECTOR3[pointNum[i]];
		for (int n = 0; n < pointNum[i]; n++)
		{
			D3DXVec3Lerp(&pointList[i][n], &line[i].start, &line[i].end, (float)(n+1) / (float)pointNum[i]);
		}
	}

	if (renderNum > 0)
	{
		renderList = new D3DXVECTOR3[renderNum];
		//pointList�֒l��ݒ肷��
		int j = 0;
		int k = 0;
		for (int i = 0;i< renderNum; i++)
		{
			renderList[i] = pointList[j][k];
			k++;
			if (k > pointNum[j]) {
				j++;
				k = 0;
			}
		}
		billboard.setNumOfRender(device, renderNum, renderList);
		for (int i = 0; i < pileNum; i++)
		{
			if (pointNum[i] <= 0)continue;
			delete[]pointList[i];
		}
	}

	SAFE_DELETE_ARRAY(renderList);
}