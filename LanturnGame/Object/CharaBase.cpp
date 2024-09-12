#include "CharaBase.h"
#include "CameraManager.h"
#include "DxLib.h"
#include "../Scene/GameMain.h"
void CharaBase::Update(GameMain* _g)
{
	if (spawnev)
	{
		if (lifetime > 60)
		{
			spawnev = false;
			for (int i = 0; i < 4; i++)
			{
				int temp = gamemain->CreateParticle(4);
				gamemain->GetParticle(temp)->SetLocation(location);
				gamemain->GetParticle(temp)->SetAngle((90 * i) + GetRand(90));
				gamemain->GetParticle(temp)->SetSpeed((GetRand(30) / 10) + 1);
				gamemain->GetParticle(temp)->SetLifeTime(GetRand(30) + 10);
				gamemain->GetParticle(temp)->SetChangeAlphaFlg(true);
			}
		}
	}
	lifetime++;

}

void CharaBase::Draw(CameraManager* camera) const
{
	if (spawnev)
	{
		int OldDrawMode;
		int OldDrawParam;
		GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
		DrawCircleAA(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
					,location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
					,48 * (1 - (camera->GetDistance())), 24, 0xff4444, true);

		SetDrawBlendMode(OldDrawMode, OldDrawParam);

		DrawCircleAA(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
					,location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
					,48 * (1 - (camera->GetDistance())), 24, 0xff0000, false, 3.0f);

		DrawFormatStringF((location.x - 8) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
						, (location.y - 16) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
						, 0xffffff, "!");
	}
}

void CharaBase::SpawnEvent()
{
	spawnev = true;
}
