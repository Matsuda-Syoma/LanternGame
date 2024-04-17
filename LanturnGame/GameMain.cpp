#include "GameMain.h"
#include "common.h"
#include "LoadSounds.h"

GameMain::GameMain()
{
	Sounds::LoadSounds();
	player = new Player;
	soldier = new Soldier;
	bomb = new Bomb * [GM_MAX_ENEMY_BOMB];
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		bomb[i] = nullptr;
	}
	for (int i = 0; i < 50; i++) {
		bomb[i] = new Bomb;
	}
	for (int i = 0; i < 50; i++) {
		bomb[i]->SetLocation(Vector2D(8 * (i + 1) + GetRand(64), 100 + GetRand(80) * 2));
	}

	explosion = new Explosion * [GM_MAX_EFFECT_EXPLOSION];
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		explosion[i] = nullptr;
	}

}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	player->Update();
	soldier->Upadate(player->GetLocation());
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
			}
			// 敵と敵の距離を見る
			int temp = -1;
			float length = 65535;
			Vector2D vvec = 0;

			switch (bomb[i]->GetMode()) {
			case 0:
				break;

				// 敵同士集まる
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

				// プレイヤーから逃げる
			case 2:
				length = bomb[i]->GetLength(player->GetLocation());
				vvec = (bomb[i]->GetLocation() - player->GetLocation());
				vvec /= length;
				bomb[i]->SetVelocity(vvec);
				break;

				// プレイヤーを追いかける
			case 3:
				length = bomb[i]->GetLength(player->GetLocation());
				if (length > 80) {
					vvec = (player->GetLocation() - bomb[i]->GetLocation());
					vvec /= length;
					bomb[i]->SetVelocity(vvec);
				}
				else {
					bomb[i]->SetVelocity(NULL);
				}
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
					if (bomb[i]->GetMode() == 3) {
						vvec = (bomb[i]->GetLocation() - player->GetLocation());
						length = bomb[i]->GetLength(player->GetLocation());
						vvec /= length;
						bomb[i]->SetKnockBack(vvec,50);
					}
				}
			}
			// 敵のフラグが0なら
			if (!bomb[i]->GetFlg()) {
				// 爆発を発生して敵をnullptrにしてループを抜ける
				SpawnExplosion(bomb[i]->GetLocation());
				PlaySoundMem(Sounds::SE_Explosion, DX_PLAYTYPE_BACK, true);
				ratio += 1;
				ui_ratio_framecount = 25;
				score += (ratio * 100);
				bomb[i] = nullptr;
				delete bomb[i];
				break;
			}
		}
	}

	ratioflg = false;
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {

		if (explosion[i] != nullptr) {
			ratioflg = true;
			explosion[i]->Update();
			// プレイヤーと爆発の当たり判定
			if (explosion[i]->HitSphere(player) && hitmoment == false) {
				if (player->GetFlg() == false) {
					life--;
					hitmoment = true;
					player->SetFlg(true);
				}
			}
			else if (!explosion[i]->HitSphere(player) && hitmoment == true) {
				hitmoment = false;
			}

			if (!explosion[i]->Getflg()) {
				explosion[i] = nullptr;
				delete explosion[i];
			}
		}

	}

	if (!ratioflg) {
		ratio = 0;
	}
	game_frametime++;
	if (ui_ratio_framecount > 0) {
		ui_ratio_framecount--;
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

	soldier->Draw(player->GetLocation());

	player->Draw(0);
	

	DrawFormatString(640, 10, 0xffffff, "%06d", score);

	if (ratioflg) {
		SetFontSize(16 + ((1 + (ui_ratio_framecount)) + (ratio / 2)));
		DrawFormatString(720, 10, GetColor(255, 255, 255 - (25 * ratio)), "%dx", ratio);
	}
	SetFontSize(16);

	if (life > 0) {
		DrawFormatString(10, 10, 0xffffff, "life : %d", life);
	}
	else {
		DrawString(10, 10, "GameOver", 0xffffff);
	}
	
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
