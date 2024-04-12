#include "GameMain.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player;

	bomb = new Bomb * [GM_MAX_ENEMY_BOMB];
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		bomb[i] = nullptr;
	}
	for (int i = 0; i < 5; i++) {
		bomb[i] = new Bomb;
	}
	for (int i = 0; i < 5; i++) {
		bomb[i]->SetLocation(Vector2D(80 * (i + 1), 100));
	}

	explosion = new Explosion * [GM_MAX_EFFECT_EXPLOSION];
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		explosion[i] = nullptr;
	}

	//explosion[0] = new Explosion;
	//explosion[0]->SetLocation(bomb[0]->GetLocation());

}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{

	player->Update();
	// 敵の数を見る
	clsDx();
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {

		// 敵がnullptrじゃないなら
		if (bomb[i] != nullptr) {
			int temp = -1;
			float length = 65535;
			for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++) {
				if (j != i) {
					if (bomb[j] != nullptr) {
						if (length > bomb[j]->SetMinBomb(bomb[i]->GetLocation())) {
							temp = j;
							length = bomb[j]->SetMinBomb(bomb[i]->GetLocation());
						}
					}
				}
			}
			printfDx("%d -> %d\n",i,temp);
			// 敵の更新
			bomb[i]->Update();

			// 敵のフラグが1なら
			if (bomb[i]->GetFlg()) {

				// 爆発の数を見る
				for (int j = 0; j < GM_MAX_EFFECT_EXPLOSION; j++) {

					// 爆発がnullptrじゃないなら
					if (explosion[j] != nullptr) {

						// 敵と爆発の当たり判定
						if (bomb[i]->HitSphere(explosion[j])) {

							// 敵のフラグを切って爆発のループを抜ける
							bomb[i]->SetFlg(false);
							break;

						}
					}
				}

				// 敵とプレイヤーの当たり判定
				if (bomb[i]->HitSphere(player)) {
					bomb[i]->SetExpFlg(true);
				}
			}
			// 敵のフラグが0なら
			if (!bomb[i]->GetFlg()) {
				// 爆発を発生して敵をnullptrにしてループを抜ける
				SpawnExplosion(bomb[i]->GetLocation());
				bomb[i] = nullptr;
				delete bomb[i];
				break;
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

void GameMain::SpawnExplosion(Vector2D loc) {
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		if (explosion[i] == nullptr) {
			explosion[i] = new Explosion;
			explosion[i]->SetLocation(loc);
			break;
		}
	}
}
