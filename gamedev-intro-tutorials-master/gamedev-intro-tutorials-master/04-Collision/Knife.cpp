#include "Knife.h"

void Knife::LoadResource()
{
	//load resource
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_KNIFE, L"Resource\\sprites\\Sub_weapons\\KNIFE.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texKnife = textures->Get(ID_TEX_KNIFE);

	CSprites * sprites = CSprites::GetInstance();
	sprites->Add(300, 0, 0, 32, 18, texKnife);


	LPANIMATION ani;
	CAnimations * animations = CAnimations::GetInstance();

	ani = new CAnimation(100);		//whip knife
	ani->Add(300, 90);
	animations->Add(WP_KNIFE_STAND, ani);

	ani = new CAnimation(100);		//whip knife
	ani->Add(300, 90);
	animations->Add(WP_KNIFE_SIT, ani);

	this->AddAnimation(WP_KNIFE_STAND);
	this->AddAnimation(WP_KNIFE_SIT);
}

void Knife::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (!isvisible)
	{
		l = x;
		t = y;
		r = l + KNIFE_BBOX_WIDTH;
		b = t + KNIFE_BBOX_HEIGHT;
	}
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coObjectStatic, vector<LPGAMEOBJECT>* coObjectEnemy)
{
	CGameObject::Update(dt);
	x += dx;
}

void Knife::Render(float xViewport, float yViewport)
{
	this->X_view = x - xViewport;
	this->Y_view = y - yViewport;
	int alpha = 255;

	this->SetState(this->state);

	//animation whip left or right
	this->isLeft = nx > 0 ? false : true;

	//choose animation whip stand or sit
	this->ani = isStand ? 0 : 1;

	animations[ani]->Render(x - xViewport, y - yViewport, alpha, isLeft);

	//Render boundingBox at end frame of currentAnimation
	RenderBoundingBox();
}


void Knife::SetCurrentPosSimon(float _xSimon, float _ySimon, int _nx, bool _isStand)
{
	this->x = _xSimon + 20.0f;
	this->y = _ySimon + 15.0f;
	this->nx = _nx;
	this->isStand = _isStand;
}

void Knife::SetPositionLR(float _x, float _y, bool _isStand, int _isLeft)
{
	//position whip vs simon
	//this->curX = _isLeft  == 1 ? _x - 15.0f : _x - 75.0f;
	this->curY = !(isStand) ? _y + 16.5f : _y;

	//Set speed
	if (isStand)
	{
		this->state = WP_KNIFE_STAND;
	}
	else
	{
		this->state = WP_KNIFE_SIT;
	}

	//this->isLeft = _isLeft == 1 ? true : false;

	//theo phan tich da tao ra whip tren viewport
	//_x, _y la toa do viewport cua simon
	this->SetPosition(curX, curY);
	this->isStand = isStand;
}

void Knife::UpdateLimit(float xViewport, float yViewport)
{
	if (this->x - xViewport < 0.0f)
	{
		this->SetInvisible(true);
		this->SetDead(true);
	}
	else if (this->x - (xViewport + SCREEN_WIDTH) > 0.0f)
	{
		this->SetInvisible(true);
		this->SetDead(true);
	}
}

void Knife::SetState(int state)
{
	CGameObject::SetState(state);
	if (this->state == WP_KNIFE_STAND || this->state == WP_KNIFE_SIT)
	{
		this->vx = this->GetNX() == 1 ? KNIFE_SPEED : -KNIFE_SPEED;
	}
}
