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
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);		// �����蔻��p�ɃX�t�B�A�����
	chinginMax = INITIAL_NUM_CHINGIN;							// �����`���M������ݒ�
	chingin = (Chingin**)malloc(sizeof(Chingin*) * chinginMax);	// �|�C���^�z��m��
	if (chingin == NULL)
	{
		MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"),
			TEXT("SystemError"), MB_OK);
		PostQuitMessage(0);
	}
	ZeroMemory(chingin, sizeof(Chingin*) * INITIAL_NUM_CHINGIN);// �z���null���Z�b�g����
	
	numOfUse = 0;
	renderList = NULL;

	// �����G�t�F�N�g������
	chinginEffect.initialize(device, _textureLoader, effect);

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UI_REVIVAL_GAUGE));
}

//=============================================================================
// �I������
//=============================================================================
void ChinginManager::uninitialize(void)
{
	for (int i = 0; i < chinginMax; i++)
	{
		if (chingin[i] != NULL) { SAFE_DELETE(chingin[i]) }
	}
	free(chingin);
}


//=============================================================================
// �X�V����
//=============================================================================
void ChinginManager::update(Sound* _sound, float frameTime)
{
	// �����G�t�F�N�g�̍X�V
	chinginEffect.update(frameTime);

	// �g�p���̃`���M���̋������X�V����
	for (int i = 0; i < chinginMax; i++)
	{
		if (chingin[i] == NULL) { continue; }

		chingin[i]->setSpeed(moveSpeed(*chingin[i]->getPosition(), *chingin[i]->getTarget()->getPosition()));
		chingin[i]->setPosition(*chingin[i]->getPosition() + *chingin[i]->getSpeed());

		D3DXMatrixIdentity(chingin[i]->getMatrixWorld());
		D3DXMatrixTranslation(chingin[i]->getMatrixWorld(),
			chingin[i]->getPosition()->x, chingin[i]->getPosition()->y, chingin[i]->getPosition()->z);

		// �v���C���[�ɓ��������烁�������
		if (chingin[i]->getCollider()->collide(
			chingin[i]->getTarget()->bodyCollide.getCenter(), chingin[i]->getTarget()->bodyCollide.getRadius(),
			*chingin[i]->getMatrixWorld(), *chingin[i]->getTarget()->getMatrixWorld()))
		{

			// �����G�t�F�N�g����
			chinginEffect.generateChinginEffect(1, *chingin[i]->getTarget()->getPosition(), chingin[i]->getTarget()->upVec());

			// �T�E���h�̍Đ�
			_sound->play(soundNS::TYPE::SE_CHINGIN, soundNS::METHOD::PLAY);

			SAFE_DELETE(chingin[i])
			numOfUse--;
		}
	}

#if 1	// �`���M��������g���Ă��Ȃ��^�C�~���O(=�|�C���^�z�񂪑S��null)�Ŕz������T�C�Y����
	if (numOfUse == 0 && chinginMax > INITIAL_NUM_CHINGIN)
	{
		chinginMax = INITIAL_NUM_CHINGIN;
		Chingin** temp = (Chingin**)realloc(chingin, sizeof(Chingin*) * INITIAL_NUM_CHINGIN);
		if (temp == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"),
				TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		chingin = temp;
	}
#endif
}


//=============================================================================
// �`�揈��
//=============================================================================
void ChinginManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃`���M�����C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	int renderIndex = 0;
	for (int i = 0; i < chinginMax; i++)
	{
		if (chingin[i] == NULL) { continue; }

		renderList[renderIndex++] = *chingin[i]->getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	instancingProcedure.render(device, view, projection, cameraPosition);

	// �����G�t�F�N�g�̕`��
	chinginEffect.render(device, view, projection, cameraPosition);

}


//=============================================================================
// �`���M���̈ړ���ݒ�
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
void ChinginManager::generateChingin(int num, D3DXVECTOR3 setPosition, Player* target)
{
	int newIndex = 0;	// �V�K�����`���M���C���X�^���X�̐�

	for (int i = 0; i < chinginMax; i++)
	{
		if (newIndex == num) { break; }
		if (chingin[i] != NULL) { continue; }

		chingin[i] = new Chingin;
		newIndex++;

		// �p�����[�^�ݒ�
		chingin[i]->setPosition(setPosition);
		chingin[i]->setTarget(target);
		chingin[i]->setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(chingin[i]->getMatrixWorld());
		numOfUse++;

		//----------------------------------------------------------------------------
		// �|�C���^�z��̗v�f���𒴂��ă`���M�����m�ۂ��ꂽ�ꍇ�ɔz�񎩑̂��m�ۂ�����
		//----------------------------------------------------------------------------
		static const int ADDITIONAL_NUM_CHINGIN = 200;	// �ǉ��v�f��
		if (i == chinginMax - 1 && newIndex == num)
		{
			chinginMax += ADDITIONAL_NUM_CHINGIN;
			Chingin** temp = (Chingin**)realloc(chingin, sizeof(Chingin*) * chinginMax);
			if (temp == NULL)
			{
				MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"),
					TEXT("SystemError"), MB_OK);
				PostQuitMessage(0);
			}
			chingin = temp;

			// �V�K�m�ە��̃�������null���Z�b�g����
			ZeroMemory(&chingin[i + 1], sizeof(Chingin*) * ADDITIONAL_NUM_CHINGIN);
		}
	}
}


//void ChinginManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

