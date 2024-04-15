#include "GameMain.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player;

	bomb = new Bomb * [GM_MAX_ENEMY_BOMB];
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		bomb[i] = nullptr;
	}
	for (int i = 0; i < 50; i++) {
		bomb[i] = new Bomb;
	}
	for (int i = 0; i < 50; i++) {
		bomb[i]->SetLocation(Vector2D(64 * (i + 1) + GetRand(64), 100 + GetRand(320) * 2));
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
	clsDx();
	player->Update();
	// 敵の数を見る
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {

		// 敵がnullptrじゃないなら
		if (bomb[i] != nullptr) {

			// プレイヤーとの距離を見る
			// プレイヤーと320離れていたら
			if (240 < bomb[i]->GetLength(player->GetLocation()) && bomb[i]->GetMode() != 3) {
				bomb[i]->SetMode(1);
			}
			else if (240 >= bomb[i]->GetLength(player->GetLocation()) && bomb[i]->GetMode() != 3) {
				bomb[i]->SetMode(2);
				printfDx("!");
			}
			// 敵と敵の距離を見る
			int temp = -1;
			float length = 65535;
			Vector2D vvec = 0;
			switch (bomb[i]->GetMode()) {
			case 0:
				break;
			case 1:

				for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++) {

					// 自分以外なら
					if (j != i) {

						// nullptrじゃないなら距離を見る
						if (bomb[j] != nullptr) {

							// 距離が短いなら変数を保存する
							if (length > bomb[j]->GetLength(bomb[i]->GetLocation())) {
								temp = j;
								length = bomb[j]->GetLength(bomb[i]->GetLocation());
							}
						}
					}
					else if (bomb[j] == nullptr) {
						temp = -1;
						length = 65535;
					}
				}
				if (temp != -1) {
					if (length > 80) {
						vvec = (bomb[temp]->GetLocation() - bomb[i]->GetLocation());
						vvec /= length;
						bomb[i]->SetVelocity(vvec);
						break;
					}
					else if (length < 72) {
						vvec = (bomb[i]->GetLocation() - bomb[temp]->GetLocation());
						vvec /= length;
						bomb[i]->SetVelocity(vvec);
						break;
					}
					else {
						bomb[i]->SetVelocity(NULL);
					}
				}


				break;
			case 2:
				vvec = (bomb[i]->GetLocation() - player->GetLocation());
				length = bomb[i]->GetLength(player->GetLocation());
				vvec /= length;
				bomb[i]->SetVelocity(vvec);
				break;
			case 3:
				break;
			}
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
