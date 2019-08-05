//-----------------------------------------------------------------------------
// �`���M������ [Chingin.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/8/1
//-----------------------------------------------------------------------------
#include "ChinginManager.h"


//=============================================================================
// ����������
//=============================================================================
void ChinginManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		chingin[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		chingin[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(chingin[i].getMatrixWorld());
		chingin[i].getCollider()->initialize(device, chingin[i].getPosition(), sphere);
		chingin[i].setUse(false);
	}
	
	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UI_MISSILE));
}


//=============================================================================
// �X�V����
//=============================================================================
void ChinginManager::update(float frameTime, Player* player)
{
	// �g�p���̃`���M���̋������X�V����
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		if (chingin[i].getUse() == false) { continue; }

		chingin[i].setSpeed(moveSpeed(*chingin[i].getPosition(), *player->getPosition()));
		chingin[i].setPosition(*chingin[i].getPosition() + *chingin[i].getSpeed());

		D3DXMatrixIdentity(chingin[i].getMatrixWorld());
		D3DXMatrixTranslation(chingin[i].getMatrixWorld(),
			chingin[i].getPosition()->x, chingin[i].getPosition()->y, chingin[i].getPosition()->z);

		// �v���C���[�ɓ���������I��
		if (chingin[i].getCollider()->collide(
			player->bodyCollide.getCenter(), player->bodyCollide.getRadius(),
			*chingin[i].getMatrixWorld(), *player->getMatrixWorld()))
		{
			chingin[i].setUse(false);
			numOfUse--;
		}
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void ChinginManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃`���M�����C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (chingin[i].getUse() == false) { continue; }

		renderList[i] = *chingin[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	instancingProcedure.render(device, view, projection, cameraPosition);
}


//=============================================================================
// �`���M���̑��x��ݒ�
//=============================================================================
D3DXVECTOR3 ChinginManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
{
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveDirection = targetPosition - position;
	//float distance = D3DXVec3Length(&moveDirection);
	//float magneticeForce = (target.amount*amount) / distance;
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	speed += moveDirection * 2.0f;// ���̂ւ�͂܂��K��

	return speed;
}


//=============================================================================
// �`���M���𔭐�������
//=============================================================================
void ChinginManager::generateChingin(int num, D3DXVECTOR3 positionToGenerate)
{
	int cnt = 0;
	D3DXVECTOR3 newPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		if (chingin[i].getUse()) { continue; }
		
		if (cnt < num)
		{
			newPosition.x = positionToGenerate.x + rand() % 20;
			newPosition.y = positionToGenerate.y + rand() % 20;
			newPosition.z = positionToGenerate.z + rand() % 20;
			chingin[i].setPosition(newPosition);

			chingin[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			D3DXMatrixIdentity(chingin[i].getMatrixWorld());
			chingin[i].setUse(true);
			numOfUse++;
		}
		cnt++;
	}
}


//void ChinginManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

