#pragma once
#include <stdio.h>
#include <crtdbg.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//�x����\��
#pragma warning(disable:4305)
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4111)
//�}�N����`
#ifdef _DEBUG
#define APP_NAME (LPSTR)"Galaxy Shooter ver.��-Debug-"
#define DEBUG_NAME (LPSTR)"DebugWindow"
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define APP_NAME (LPSTR)"Galaxy Shooter ver.��"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#endif // _DEBUG
#define SAFE_DELETE(p) {if(p){delete(p);(p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[](p);(p)=NULL;}}
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}
#define MFAIL(code,string) if(FAILED(code)){MessageBox(0,string,"error",MB_OK);return E_FAIL;}
#define MFALSE(code,string) if(!(code)) {MessageBox(0,string,"error",MB_OK);return E_FAIL;}
#define MSG(text) MessageBox(0,text,0,MB_OK);

struct Vertex3D
{
	D3DXVECTOR3 coord;
};
struct Vertex2D
{
	D3DXVECTOR2 coord;
};
struct UV
{
	D3DXVECTOR2 coord;
};
struct Line
{
	D3DXVECTOR3 start;
	D3DXVECTOR3 end;
};

class Base
{
public:
	//�p������
	static void postureControl(D3DXQUATERNION* quaternion, D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection, float t);
	//�C�ӎ����^��ԉ�]
	static void anyAxisRotationSlerp(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float radian, float t);
	//�C�ӎ���]
	static void anyAxisRotation(D3DXQUATERNION* quaternion,D3DXVECTOR3 axis, float degree);
	//��̃x�N�g���̂Ȃ��p���v�Z
	static bool formedRadianAngle(float* out, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	//�X���b�v�֐�(���˃x�N�g��L�̃x�N�g��N�ɔ�����x�N�g��������ł������B�j
	D3DXVECTOR3 slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
	//�Q�̈ʒu�x�N�g���Ԃ̋������v�Z����
	float between2VectorLength(D3DXVECTOR3 position1, D3DXVECTOR3 position2);
	//�Q�̈ʒu�x�N�g���Ԃ̋����̌v�Z�ɉ����A
	//�ʒu�P����ʒu�Q�Ɍ������i1��2�j�x�N�g�����쐬����(�m����1)
	float between2VectorDirection(D3DXVECTOR3* out, D3DXVECTOR3 position1, D3DXVECTOR3 position2);
	//���_�o�b�t�@�ւ̃R�s�[
	void copyVertexBuffer(unsigned size, void *sorce, IDirect3DVertexBuffer9 *buffer);
	//����_�Ƃ̐�����ōł��߂��_�����߂�
	D3DXVECTOR3 nearestPointOnLine(D3DXVECTOR3 start,D3DXVECTOR3 end,D3DXVECTOR3 point);
};

//�v���g�^�C�v�錾
void initializeDirectory(char* root);
void setRootDirectory();
void setDataDirectory();
void setVisualDirectory();
void setShaderDirectory();
void setSoundDirectory();