#include "Description.h"
#include "DxLib.h"
#include "Utility/InputControl.h"
#include "DxLib.h"

#define PI 3.1415926535897932384626433832795f
#define thousand 2000

Description::Description()
{
	//‰æ‘œ‚ğ•Ï”‚É•Û‘¶
	ignited = LoadGraph("Resources/images/ignited.png");
	touchbomb = LoadGraph("Resources/images/touch.png");
	bakuhatu = LoadGraph("Resources/images/explosion.png");
	chain = LoadGraph("Resources/images/chain.png");

	touchsoldier = LoadGraph("Resources/images/touchsoldier.png");
	be_pursued = LoadGraph("Resources/images/be_pursued.png");

	sankaku = LoadGraph("Resources/images/sankaku.png");


	//•Ï”‚Ì‰Šú‰»
	Movepng = 0;
	MovepngMax = 0;

}

Description::~Description()
{

}

void Description::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if(MovepngMax < 6000)
		MovepngMax += thousand;
	}
	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (MovepngMax > 0)
		MovepngMax -= thousand;
	}*/
	if (Movepng != MovepngMax)
	{
		if (Movepng < MovepngMax)
		{
			Movepng += 100;
		}
		/*if (Movepng > MovepngMax)
		{
			Movepng -= 100;
		}*/
	}
}

void Description::Draw()
{
	DrawBox(10, 10, 1270, 340, 0xffffff, true);

	//‰æ‘œ‚Ì•`‰æ
	DrawRotaGraph((980 - (thousand * 0)) + Movepng, 170, 0.7, 0.0, touchbomb, TRUE);
	DrawRotaGraph((300 - (thousand * 0)) + Movepng, 170, 0.7, 0.0, ignited, TRUE);
	DrawRotaGraph((980 - (thousand * 1)) + Movepng, 170, 0.7, 0.0, be_pursued, TRUE);
	DrawRotaGraph((300 - (thousand * 1)) + Movepng, 170, 0.7, 0.0, touchsoldier, TRUE);
	DrawRotaGraph((640 - (thousand * 2)) + Movepng, 170, 0.7, 0.0, chain, TRUE);
}