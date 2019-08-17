//===================================================================================================================================
//�yMemoryLine.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/12
//===================================================================================================================================
#include "MemoryLine.h"
#include "UtilityFunction.h"
using namespace memoryLineNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
MemoryLine::MemoryLine()
{
	line = NULL;
	joinTarget = NULL;
	joinPlayer = NULL;
	pointList = NULL;
	renderList = NULL;

	disconnected = false;
	lostTime = 0;

	initialized = false;
	
	pileNum = 0;
	pointNum = NULL;
	renderNum = 0;
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
MemoryLine::~MemoryLine()
{
	SAFE_DELETE_ARRAY(line);
	SAFE_DELETE_ARRAY(pointList);
	SAFE_DELETE_ARRAY(renderList);
	SAFE_DELETE_ARRAY(pointNum);
}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
void MemoryLine::initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Object* player
	,LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
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
	billboard.initialize(device,effect,texture);

	initialized = true;
}

//===================================================================================================================================
//�y�I�������z
//===================================================================================================================================
void MemoryLine::unInitialize()
{

}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void MemoryLine::update(LPDIRECT3DDEVICE9 device, float frameTime)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��

	if (disconnected) {
		lost(frameTime);
	}
	else {
		setLine(device);
	}
}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
void MemoryLine::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��
	billboard.render(device, view, projection, cameraPosition);
}

//===================================================================================================================================
//�y�`�惉�C���̐ݒ�z
//�������[�p�C���̃A�N�e�B�u�󋵂ɉ����ĕϓ�
//===================================================================================================================================
void MemoryLine::setLine(LPDIRECT3DDEVICE9 device)
{
	renderNum = 0;//�S�̂ŕ`�悷��_�̐���0�Ƃ���B
	//�`�惉�C���̐ݒ�
	for (int i = 0; i < pileNum; i++)
	{
		pointNum[i] = 0;//���C����̓_�̕`�搔��0�ɂ���
		{//�������[���C���̎n�_�ʒu�ƏI�_�ʒu��ݒ肷��
			if (joinTarget[i].getActive())
			{//[��������]�ڑ����������[�p�C���̃A�N�e�B�u
				line[i].start = *joinTarget[i].getPosition();//�ڑ������������[���C���̎n�_�ɂ���
				//���̃������[�p�C���̗v�f��
				int k = UtilityFunction::wrap(i+1,0,pileNum);
				//���̃������[���C����
				if (joinTarget[k].getActive())
				{//�������[���C���̏I�_�����̃������[���C��
					line[i].end = *joinTarget[k].getPosition();
				}
				else 
				{//�������[���C���̏I�_���v���C���[
					line[i].end = *joinPlayer->getPosition();
				}
			}
		}

		float length = D3DXVec3Length(&(line[i].end - line[i].start));//���C���̒������Z�o
		pointNum[i] = (int)(length / 1.0f);//���C���̕`��_�����m��
		renderNum += pointNum[i];//�S�̍��v�_���։��Z
		if (pointNum[i] <= 0)continue;//�`�悷��_��0�ȉ��Ȃ�Ύ��̃������[���C����
		pointList[i] = new D3DXVECTOR3[pointNum[i]];//�`�悷��_�̈ʒu����V���ɐ���
		for (int n = 0; n < pointNum[i]; n++)
		{
			//���C�������Ƃɕ�ԌW����p���Ĉʒu�����쐬����B
			//��ԌW��=�`��ԍ�n/�S�̕`�搔
			D3DXVec3Lerp(&pointList[i][n], &line[i].start, &line[i].end, (float)(n+1) / (float)pointNum[i]);
		}
	}

	
	if (renderNum > 0)
	{
		renderList = new D3DXVECTOR3[renderNum];
		{//pointList��p����renderList�֒l��ݒ肷��
			int j = 0;
			int k = 0;
			for (int i = 0; i < renderNum; i++)
			{
				renderList[i] = pointList[j][k];
				k++;
				if (k > pointNum[j]) {
					k = 0;
					j++;
				}
			}
		}
		//�C���X�^���X�r���{�[�h�̕`�搔�ƕ`��ʒu���̐ݒ�
		billboard.setNumOfRender(device, renderNum, renderList);
		for (int i = 0; i < pileNum; i++)
		{
			if (pointNum[i] <= 0)continue;//�`�搔��0�ȉ��ł���΃X�L�b�v
			delete[]pointList[i];//�`�悷��_�̃��X�g�̍폜
		}
	}

	SAFE_DELETE_ARRAY(renderList);//�S�̂̃������[���C���̓_�̈ʒu��񃊃X�g���폜
}

//===================================================================================================================================
//�y�ؒf�z
//===================================================================================================================================
void MemoryLine::disconnect()
{
	disconnected = true;
}

//===================================================================================================================================
//�y�����z
//===================================================================================================================================
void MemoryLine::lost(float frameTime)
{
	if (!disconnected)return;
	lostTime += frameTime;

	if (lostTime > LOST_TIME)
	{
		disconnected = false;
		lostTime = 0;
		renderNum = 0;//�S�̂ŕ`�悷��_�̐���0�Ƃ���B
		for (int i = 0; i < pileNum; i++)
		{
			line[i].start = D3DXVECTOR3(0, 0, 0);
			line[i].end = D3DXVECTOR3(0, 0, 0);
			//if (pointNum[i] > 0)delete[] pointList[i];
			pointNum[i] = 0;//���C����̓_�̕`�搔��0�ɂ���
		}
		billboard.setNumOfRender(NULL, 0, renderList);
	}
}

//===================================================================================================================================
//�y�����v�Z�z
//===================================================================================================================================
float MemoryLine::calculationDistance(D3DXVECTOR3 point)
{
	float result = THICKNESS;
	for (int i = 0; i < pileNum; i++)
	{
		if (!joinTarget[i].getActive())continue;//�ڑ������A�N�e�B�u�łȂ��ꍇ�X�L�b�v
		
		D3DXVECTOR3 nearPoint = nearestPointOnLine(line[i].start, line[i].end, point);//���C����̍ł��߂��_���Z�o
		float distance = D3DXVec3Length(&(point - nearPoint));//�ł��߂��_�Ƃ̋����𑪒肷��
		
		if (i == 0)result = distance;//0�Ԃ͕K���A�N�e�B�u�ł���A����ɑ������K�v������B
		else result = min(result, distance);//���߂�������
	}
	return result;
}

//===================================================================================================================================
//�y�����v�Z�z
//�i�����P�jmeasurementPosition�F����ʒu
//�i�����Q�jradius�F���a
//===================================================================================================================================
bool MemoryLine::collision(D3DXVECTOR3 measurementPosition,float radius)
{
	if (initialized == false)return false;//����������Ă��Ȃ���Δ�Փ�
	if (!joinTarget[0].getActive())return false;//�������[�p�C�����A�N�e�B�u�łȂ���Δ�Փ�
	if (calculationDistance(measurementPosition) > THICKNESS)	return false;
	//����+�Ώۂ̔��a���߂��ʒu�ɂ����ꍇ�Փ�
	else return true;
}