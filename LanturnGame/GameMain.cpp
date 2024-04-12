#include "GameMain.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player;

	bomb = new Bomb * [GM_MAX_ENEMY_BOMB];
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		bomb[i] = nullptr;
	}
	for (int i = 0; i < 15; i++) {
		bomb[i] = new Bomb;
	}
	for (int i = 0; i < 15; i++) {
		bomb[i]->SetLocation(Vector2D(50 * (i + 1), 100));
	}

	explosion = new Explosion * [GM_MAX_EFFECT_EXPLOSION];
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		explosion[i] = nullptr;
	}

	//for (int i = 0; i < 10; i++) {
	//	explosion[i] = new Explosion;
	//}
	//explosion[0] = new Explosion;
	//explosion[0]->SetLocation(bomb[0]->GetLocation());
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{

	player->Update();

	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {

		if (bomb[i] != nullptr) {

			for (int j = 0; j < GM_MAX_EFFECT_EXPLOSION; j++) {

				if (explosion[j] != nullptr) {

					if (bomb[i]->HitSphere(explosion[j])) {

						for (int k = 0; k < GM_MAX_EFFECT_EXPLOSION; k++) {
							if (explosion[k] == nullptr) {
								explosion[k] = new Explosion;
								explosion[k]->SetLocation(bomb[i]->GetLocation());
								bomb[i]->SetFlg(false);
								break;
							}
						}
						if (!bomb[i]->GetFlg()) {
							bomb[i] = nullptr;
							delete bomb[i];
							break;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {

		if (explosion[i] != nullptr) {

			explosion[i]->Update();
			if (!explosion[i]->Getflg()) {
				explosion[i] = nullptr;
				delete explosion[i];
			}
		}
	}
	return this;

}

void GameMain::Draw() const
{
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++){
		if (bomb[i] != nullptr) {
			bomb[i]->Draw(player->GetLocation());
		}
	}
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		if (explosion[i] != nullptr) {
			explosion[i]->Draw(player->GetLocation());
		}
	}

	player->Draw(0);
}

void GameMain::Game()
{
}
