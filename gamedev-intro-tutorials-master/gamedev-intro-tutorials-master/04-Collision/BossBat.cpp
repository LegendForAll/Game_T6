#include "BossBat.h"

void BossBat::LoadResource()
{
	//load resource zombie
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BOSSBAT, L"Resource\\sprites\\Bosses\\VAMPIRE_BAT.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DEAD, L"Resource\\sprites\\Effect\\DEAD.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texBoss = textures->Get(ID_TEX_BOSSBAT);


	sprites->Add(301, 0, 0, 100, 46, texBoss);		//boss static


	sprites->Add(302, 100, 0, 200, 32, texBoss);		//boss fly
	sprites->Add(303, 200, 0, 300, 32, texBoss);


	LPDIRECT3DTEXTURE9 texdead = textures->Get(ID_TEX_DEAD);
	//dead object
	sprites->Add(6000, 0, 0, 42, 44, texdead);
	sprites->Add(6001, 42, 0, 84, 44, texdead);
	sprites->Add(6002, 84, 0, 128, 44, texdead);

	LPANIMATION ani;
	CAnimations * animations = CAnimations::GetInstance();

	ani = new CAnimation(100);		//boss static
	ani->Add(301);
	animations->Add(BOSSBAT_STATIC, ani);


	ani = new CAnimation(100);		//boss fly
	ani->Add(302);
	ani->Add(303);
	animations->Add(BOSSBAT_FLY, ani);

	ani = new CAnimation(100);		//Dead
	ani->Add(6000);
	ani->Add(6001);
	ani->Add(6002);
	animations->Add(BOSSBAT_DIE, ani);

	this->AddAnimation(BOSSBAT_STATIC);
	this->AddAnimation(BOSSBAT_FLY);
	this->AddAnimation(BOSSBAT_DIE);
}
