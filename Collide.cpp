
#include "Collide.h"

HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);

//レイによる衝突判定　レイが相手メッシュと交差する場合は、pfDistanceに距離を、pvNormalに衝突面の法線を入れてtrueを返す
BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, Object* object, FLOAT* pfDistance, D3DXVECTOR3* pvNormal)
{
	BOOL boHit = false;
	D3DXMATRIX mWorld;
	D3DXVec3Normalize(&vDir, &vDir);

	// レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixInverse(&mWorld, NULL, &object->getMatrixWorld());
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);

	DWORD dwPolyIndex;
	D3DXIntersect(object->getMesh(), &vStart, &vDir, &boHit, &dwPolyIndex, NULL, NULL, pfDistance, NULL, NULL);
	if (boHit)
	{
		//交差しているポリゴンの頂点を見つける
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(object->getMesh(), dwPolyIndex, vVertex);
		D3DXPLANE p;
		//その頂点から平面方程式を得る
		D3DXPlaneFromPoints(&p, &vVertex[0], &vVertex[1], &vVertex[2]);
		//平面方程式の係数が法線の成分
		pvNormal->x = p.a;
		pvNormal->y = p.b;
		pvNormal->z = p.c;

		return true;
	}
	return false;
}

//HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh,DWORD dwPolyIndex,D3DXVECTOR3* pvVertices )
//そのポリゴンの頂点を見つける
HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices)
{
	DWORD i, k;
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum = pMesh->GetNumVertices();
	DWORD dwPolyNum = pMesh->GetNumFaces();
	WORD* pwPoly = NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);

	BYTE *pbVertices = NULL;
	FLOAT* pfVetices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMesh->GetVertexBuffer(&VB);
	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pvVertices[0].x = pfVetices[0];
		pvVertices[0].y = pfVetices[1];
		pvVertices[0].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pvVertices[1].x = pfVetices[0];
		pvVertices[1].y = pfVetices[1];
		pvVertices[1].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pvVertices[2].x = pfVetices[0];
		pvVertices[2].y = pfVetices[1];
		pvVertices[2].z = pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
		VB->Release();
	}
	return S_OK;
}

//VOID RenderRay(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 vStart,D3DXVECTOR3 vDir)
//レイを視認できるようにレイをレンダリングする
VOID RenderRay(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 vStart, D3DXVECTOR3 vDir)
{
	device->SetFVF(D3DFVF_XYZ);
	D3DXVECTOR3 vPnt[2];
	vPnt[0] = vStart;
	vPnt[1] = vDir * 100;
	//vPnt[1].y = vPnt[0].y;

	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	device->SetTransform(D3DTS_WORLD, &mWorld);
	//レイのマテリアル設定　（白に設定）
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Diffuse.a = 255;
	mtrl.Diffuse.r = 255;
	mtrl.Diffuse.g = 255;
	mtrl.Diffuse.b = 255;
	mtrl.Ambient = mtrl.Diffuse;
	device->SetMaterial(&mtrl);
	//レイのレンダリング
	device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vPnt, sizeof(D3DXVECTOR3));
}