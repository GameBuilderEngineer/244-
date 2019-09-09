//===================================================================================================================================
//�yMemoryLine.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/08
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
	currentRenderNum = 0;
	updateTimer = 0;
	colorTimer = 0.0f;
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
void MemoryLine::update(LPDIRECT3DDEVICE9 device, float frameTime,int type)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��

	if (disconnected) {
		lost(frameTime);
	}
	else {
		switch (type)
		{
		case PENTAGON:setLine(device); break;
		case STAR:setStarLine(device,frameTime); break;
		}
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
//�y���`�̃��C���̐ݒ�z
//[�������e]���J�[�W�����������ɐ��`�̃��C���𐶐�����
//[����]�������[�p�C���̃A�N�e�B�u�󋵂Ɋւ�炸�T�_�̊ԂŐ��������
//===================================================================================================================================
void MemoryLine::setStarLine(LPDIRECT3DDEVICE9 device,float frameTime)
{
	for (int i = 0; i < pileNum; i++)
	{
		if (joinTarget[i].getActive() == false)return;//�S�Ă��A�N�e�B�u�łȂ��ꍇ�͏������s��Ȃ�
	}

	renderNum = 0;//�S�̂ŕ`�悷��_�̐���0�Ƃ���B
	//�`�惉�C���̐ݒ�
	for (int i = 0; i < pileNum; i++)
	{
		pointNum[i] = 0;//���C����̓_�̕`�搔��0�ɂ���
		{//�������[���C���̎n�_�ʒu�ƏI�_�ʒu��ݒ肷��
				line[i].start = *joinTarget[i].getPosition();//�ڑ������������[���C���̎n�_�ɂ���
				//���̃������[�p�C���̗v�f��
				int k = UtilityFunction::wrap(i + 2, 0, pileNum);
				//�������[���C���̏I�_�����̃������[���C��
				line[i].end = *joinTarget[k].getPosition();
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
			D3DXVec3Lerp(&pointList[i][n], &line[i].start, &line[i].end, (float)(n + 1) / (float)pointNum[i]);
		}
	}
	updateTimer += frameTime;
	while (updateTimer > UPDATE_TIME)
	{
		if (currentRenderNum < renderNum)
			currentRenderNum++;
		updateTimer -= UPDATE_TIME;
		if (currentRenderNum >= renderNum)
		{
			currentRenderNum = 0;
		}
	}

	if (currentRenderNum > 0)
	{
		renderList = new D3DXVECTOR3[currentRenderNum];
		{//pointList��p����renderList�֒l��ݒ肷��
			int j = 0;
			int k = 0;
			for (int i = 0; i < currentRenderNum; i++)
			{
				if (pointNum[j] > 0)renderList[i] = pointList[j][k];
				k++;
				if (k >= pointNum[j]) {
					k = 0;
					j++;
				}
			}
		}
		//�C���X�^���X�r���{�[�h�̕`�搔�ƕ`��ʒu���̐ݒ�
		billboard.setNumOfRender(device, currentRenderNum, renderList);
		for (int i = 0; i < pileNum; i++)
		{
			if (pointNum[i] <= 0)continue;//�`�搔��0�ȉ��ł���΃X�L�b�v
			delete[]pointList[i];//�`�悷��_�̃��X�g�̍폜
		}
	}

	SAFE_DELETE_ARRAY(renderList);//�S�̂̃������[���C���̓_�̈ʒu��񃊃X�g���폜

	colorTimer += frameTime*4;
	float sinValue = sinf(colorTimer);
	float cosValue = cosf(colorTimer);
	D3DXCOLOR changeCol = D3DXCOLOR(sinValue,sinValue,sinValue,sinValue);
	changeColor(device, changeCol);

}
//===================================================================================================================================
//�y�`�惉�C���̐ݒ�z
//[�������e]�������[���C����ݒ肷��
//[����]�������[�p�C���̃A�N�e�B�u�󋵂ɉ����ĂT�_�̊ԂŐ��������
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

			//utility::Polar3D lineStart = UtilityFunction::fromRectangular3D(line[i].start);
			//utility::Polar3D lineEnd = UtilityFunction::fromRectangular3D(line[i].end);
			//
			//D3DXMATRIX xRotation;
			//D3DXMATRIX yRotation;
			//D3DXMATRIX rotation;
			//D3DXMatrixRotationX(&xRotation, lineStart.theta);
			//D3DXMatrixRotationY(&yRotation, -lineStart.phi + D3DX_PI / 2);
			//D3DXMatrixMultiply(&rotation, &xRotation, &yRotation);
			//
			//float rate = (float)(n + 1) / (float)pointNum[i];
			//
			//utility::Polar3D lerpPolar = lineStart;
			//
			//float deltaTheta = lineEnd.theta - lineStart.theta;
			////if (deltaTheta < 0)deltaTheta *= -1;
			//float deltaPhi = lineEnd.phi - lineStart.phi;
			//
			//
			//
			//if (deltaPhi > D3DX_PI)
			//{
			//		deltaPhi -= 2*D3DX_PI;
			//}
			//if (deltaPhi < -D3DX_PI)
			//{
			//		deltaPhi += 2*D3DX_PI;
			//}
			//
			//lerpPolar.phi = deltaPhi;
			//
			//lerpPolar.theta	= UtilityFunction::lerp(0,deltaTheta, rate);
			//
			//pointList[i][n] = UtilityFunction::fromTransformationPolar3D(lerpPolar.radius, lerpPolar.theta, lerpPolar.phi);
			//D3DXVec3TransformCoord(&pointList[i][n], &pointList[i][n], &rotation);

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
				if(pointNum[j] >0)renderList[i] = pointList[j][k];
				k++;
				if (k >= pointNum[j]) {
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
		resetCurrentRenderNum();
		for (int i = 0; i < pileNum; i++)
		{
			line[i].start = D3DXVECTOR3(0, 0, 0);
			line[i].end = D3DXVECTOR3(0, 0, 0);
			//if (pointNum[i] > 0)delete[] pointList[i];
			pointNum[i] = 0;//���C����̓_�̕`�搔��0�ɂ���
		}
		billboard.setNumOfRender(NULL, 0, renderList);
		billboard.offRender();
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
//�y����_�ƍł��߂��ʒu�z
//===================================================================================================================================
D3DXVECTOR3 MemoryLine::calculationNearPoint(D3DXVECTOR3 point)
{
	D3DXVECTOR3 result;
	float minDistance = THICKNESS;
	for (int i = 0; i < pileNum; i++)
	{
		if (!joinTarget[i].getActive())continue;//�ڑ������A�N�e�B�u�łȂ��ꍇ�X�L�b�v

		D3DXVECTOR3 nearPoint = nearestPointOnLine(line[i].start, line[i].end, point);//���C����̍ł��߂��_���Z�o
		float distance = D3DXVec3Length(&(point - nearPoint));//�ł��߂��_�Ƃ̋����𑪒肷��

		//0�Ԃ͕K���A�N�e�B�u�ł���A����ɑ������K�v������B
		if (i == 0)
		{
			minDistance = distance;
			result = nearPoint;
		}
		else if (distance < minDistance) {
			minDistance = distance;//���߂�������
			result = nearPoint;
		}
	}

	return result;
}

//===================================================================================================================================
//�y�Փ˔���z
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

//===================================================================================================================================
//(�ؑ�)�F�̐ؑ�
//===================================================================================================================================
void MemoryLine::changeColor(LPDIRECT3DDEVICE9 device, D3DXCOLOR color)
{
	D3DXCOLOR* colorList = new D3DXCOLOR[renderNum];
	for (int i = 0; i < renderNum; i++)
	{
		colorList[i] = color;
	}
	billboard.setColorBuffer(device, renderNum, colorList);
	SAFE_DELETE_ARRAY(colorList);
}


//===================================================================================================================================
//�ysetter�z
//===================================================================================================================================
void MemoryLine::resetCurrentRenderNum()
{
	currentRenderNum = 0;
}

//===================================================================================================================================
//�ygetter�z
//===================================================================================================================================
bool MemoryLine::getDisconnected()
{
	return disconnected;
}