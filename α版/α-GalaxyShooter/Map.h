//-----------------------------------------------------------------------------
// �}�b�v���� [Map.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/27
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "Ray.h"
#include "BoundingSphere.h"
#include "Planet.h"
#include "Wasuremono.h"
#include <vector>

namespace MapNS
{
	const int SLICES = 8;			// �厲�ɕ��s�ȕ����̕�����
	const int STACKS = 8;			// �厲�ɐ����ȕ����̕�����
}


//*****************************************************************************
// �}�b�v�m�[�h
//*****************************************************************************
class MapNode
{
private:
	// Data
	int number;						// �m�[�h�ԍ�
	static int instanceCount;		// �m�[�h���J�E���^
	D3DXVECTOR3	position;			// ���[���h���W
	D3DXMATRIX worldMatrix;			// ���[���h�}�g���N�X
	int wasuremonoCount;			// �o�E���f�B���O�X�t�B�A���̃��X�����m�̐�

public:
	BoundingSphere boundingSphere;	// �o�E���f�B���O�X�t�B�A

	// Method
	MapNode(void) { instanceCount++; }
	int getInstanceCount(void) { return instanceCount; }	// Getter
	D3DXVECTOR3 getPosition(void) { return position; }
	D3DXMATRIX* getWorldMatrix(void) { return &worldMatrix; }
	void setNumber(int _number) { number = _number; }		// Setter
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setWasuremonoCount(int _set) { wasuremonoCount = wasuremonoCount; }
};


//*****************************************************************************
// �}�b�v
//*****************************************************************************
class Map
{
private:
	LPD3DXMESH sphere;				// �o�E���f�B���O�X�t�B�A�p���`���b�V��
	LPD3DXMESH mapCoodMark;			// �}�b�v�m�[�h���W�}�[�N�p���b�V��
	D3DMATERIAL9 mapCoodMat;		// �}�b�v�m�[�h���W�}�[�N�p�̃}�e���A�����̂P
	D3DMATERIAL9 targetCoodMat;		// �}�b�v�m�[�h���W�}�[�N�p�̃}�e���A�����̂Q
	std::vector<MapNode*> mapNode;	// �}�b�v�m�[�h
	Ray ruler;						// �m�[�h�z�u�ɂ������C

public:
	void initialize(LPDIRECT3DDEVICE9 device, Planet* planet);
	void uninitialize(void);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void createNode(LPDIRECT3DDEVICE9 device);	// �m�[�h����
};
