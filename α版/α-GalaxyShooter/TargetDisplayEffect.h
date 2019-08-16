//=============================================================================
// �X�e���V���w�b�_�[ [TargetDisplayEffect.h]
// ����� �ђˏt�P
//=============================================================================
#include "Sprite.h"
#include "ScreenEffectBase.h"
#include "TextureLoader.h"
#include "Object.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TRGET_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �X�e���V���̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TargetDisplayEffect : public ScreenEffectBase
{
private:
	Sprite image;
	StaticMeshLoader* staticMeshLoader;

	int playerNumber;
	static LPDIRECT3DTEXTURE9 TargetTexture;			// �e�N�X�`��
	static int cntUI;									// �C���X�^���X�̐��𐔂���
public:

	TargetDisplayEffect();
	~TargetDisplayEffect();
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader *textureLoader, StaticMeshLoader* _staticMeshLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void renderStencilMask(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);	// �X�e���V���}�X�N��`��
	void renderEffectImage(LPDIRECT3DDEVICE9 device);	// �G�t�F�N�g�摜��`��
};
