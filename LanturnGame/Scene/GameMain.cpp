#include "GameMain.h"
#include "../Utility/LoadSounds.h"
#include <math.h>
#include "../Utility/InputControl.h"
#include "../Utility/UserData.h"
#include "Title.h"

GameMain::GameMain()
{
	SetFontSize(32);
	Sounds::LoadSounds();
	BackGround::LoadImages();
	Bomb::LoadImages();
	Particle::LoadImages();
	hiscore = (int)UserData::LoadData(1);
	player = new Player;

	stage = new Stage * [GM_MAX_ICEFLOOR];
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		stage[i] = nullptr;
	}
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		stage[i] = new Stage;
	}
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		stage[i]->SetLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
	}
	player->Init();

	soldier = new Soldier * [GM_MAX_ENEMY_SOLDIER];
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		soldier[i] = nullptr;
	}
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		soldier[i] = new Soldier;
		//soldier[i]->DMGflg(true);
	}
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		soldier[i]->SetLocation(Vector2D((float)(100 + GetRand(200) * 2), (float)(100 + GetRand(200) * 2)));
	}

	bomb = new Bomb * [GM_MAX_ENEMY_BOMB];
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		bomb[i] = nullptr;
	}


	explosion = new Explosion * [GM_MAX_EFFECT_EXPLOSION];
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		explosion[i] = nullptr;
	}

	background = new BackGround * [(int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2, 2) + 1];
	for (int i = 0; i < (int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2, 2) + 1; i++) {
		background[i] = nullptr;
	}
	int backnum = 0;
	for (int i = 0; i < (int)ceil(GM_MAX_MAPSIZE / 64.f) * 2;i++) {
		for (int j = 0; j < (int)ceil(GM_MAX_MAPSIZE / 64.f) * 2; j++) {
			background[backnum] = new BackGround(Vector2D((i - (float)ceil(GM_MAX_MAPSIZE / 64.f)) * 64, (j - (float)ceil(GM_MAX_MAPSIZE / 64.f)) * 64));
			backnum++;
		}
	}

	particle = new Particle * [GM_MAX_PARTICLE];
	for (int i = 0; i < GM_MAX_PARTICLE; i++) {
		particle[i] = nullptr;
	}
	SpawnParticle(1, player, true, Vector2D(player->GetLocation().x + 5, player->GetLocation().y)
								 , Vector2D(player->GetLocation().x + 5, player->GetLocation().y), 0.5);

	lifeimage = LoadGraph("Resources/images/lifebar.png", 0);
	lifematchimage = LoadGraph("Resources/images/match.png", 0);
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{

	if (resultflg == false) {

		/*soldier->GetMapSize(MapSize);
		soldier->Upadate(player->GetLocation());*/
		player->GetMapSize(MapSize);
		player->Update();
		//for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		//	if (bomb[i] != nullptr) {
		//		if (player->HitSphereInLine(bomb[i]->GetLocation(), bomb[i]->GetRadius())) {
		//			bomb[i]->SetExpFlg(true);
		//		}
		//	}
		//}
		for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
		{
			if (soldier[i] != nullptr)
			{
				soldier[i]->Upadate(player->GetLocation());
				soldier[i]->GetMapSize(MapSize);
				soldier[i]->SetVelocity(1);
			}
			else
			{
				if ((game_frametime % 120) == 0)
				{
					soldier[i] = new Soldier;
					Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
					if (640 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
						powf((spawnloc.x - player->GetLocation().x), 2) +
						powf((spawnloc.y - player->GetLocation().y), 2))))
					{
						soldier[i]->SetLocation(spawnloc);
						break;
					}
				}
			}
		}

		Vector2D ee = 0;
		float eel = 65535;
		int chek = -1;


		
		for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
		{
			//兵隊同士の当たり判定
			for (int j = 0; j < GM_MAX_ENEMY_SOLDIER; j++)
			{
				if (i != j)
				{
					// nullptrじゃないなら距離を見る
					if (soldier[i] != nullptr && soldier[j] != nullptr) {

						// 距離が短いなら変数を保存する
						if (eel > soldier[i]->direction(soldier[j]->GetLocation())) {
							chek = j;
							eel = soldier[i]->direction(soldier[j]->GetLocation());
						}
					}
				}
			}
			if (chek != -1)
			{
				if (eel < 80)
				{
					ee = (soldier[chek]->GetLocation() - soldier[i]->GetLocation());
					ee /= eel;
					soldier[i]->SetVelocity(ee);
					break;
				}
			}
			//兵隊と爆弾の当たり判定
			for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
			{
					// nullptrじゃないなら距離を見る
					if (soldier[i] != nullptr && bomb[j] != nullptr) {

						// 距離が短いなら変数を保存する
						if (eel > soldier[i]->direction(bomb[j]->GetLocation())) {
							chek = j;
							eel = soldier[i]->direction(bomb[j]->GetLocation());
						}
					}
			}
			if (chek != -1)
			{
				if (eel < 80)
				{
						ee = (bomb[chek]->GetLocation() - soldier[i]->GetLocation());
						ee /= eel;
						soldier[i]->SetVelocity(ee);
						break;
				}
			}
		}

		for (int i = 0; i < GM_MAX_PARTICLE; i++) {

			// パーティクルがnullptrじゃないなら
			if (particle[i] != nullptr) {
				particle[i]->Update();
				if (!particle[i]->Getflg()) {
					particle[i] = nullptr;
					delete particle[i];
				}
			}
		}


		// 敵の数を見る
		SE_HitFlg = false;
		for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {

			// 敵がnullptrじゃないなら
			if (bomb[i] != nullptr) {

				// プレイヤーとの距離を見る
				// プレイヤーと320離れていたら
				if (240 < bomb[i]->GetLength(player->GetLocation()) && bomb[i]->GetMode() == 2) {
					bomb[i]->SetMode(GetRand(4) + 1);
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
								if(bomb[i]->GetMode() != 3) {
									if (length > bomb[j]->GetLength(bomb[i]->GetLocation())) {
										temp = j;
										length = bomb[j]->GetLength(bomb[i]->GetLocation());
									}
								}
							}
						}
						else if (bomb[j] == nullptr) {
							temp = -1;
							length = 65535;
						}
					}
					if (temp != -1) {
						// 距離が長いなら
						if (length > 80) {
							vvec = (bomb[temp]->GetLocation() - bomb[i]->GetLocation());
							vvec /= length;
							bomb[i]->SetVelocity(vvec);
							break;
						}
						// 距離が近いなら
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
						// 距離が近いなら
						if (length < 72) {
							vvec = (bomb[i]->GetLocation() - bomb[temp]->GetLocation());
							vvec /= length;
							bomb[i]->SetVelocity(vvec);
							break;
						}
					}
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

					// ランダム移動
				case 4:
					length = bomb[i]->GetLength(bomb[i]->GetMoveToLocation());
					if (length > 16) {
						vvec = (bomb[i]->GetMoveToLocation() - bomb[i]->GetLocation());
						vvec /= length;
						bomb[i]->SetVelocity(vvec);
					}
					else {
						bomb[i]->SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
					}
					if (fabsf(bomb[i]->GetMoveToLocation().x) - MapSize + 32 > 0 || fabsf(bomb[i]->GetMoveToLocation().y) - MapSize + 32 > 0) {
						bomb[i]->SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
					}
					break;

					// プレイヤーと対称の動き
				case 5:
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
						// 距離が近いなら
						if (length < 72) {
							vvec = (bomb[i]->GetLocation() - bomb[temp]->GetLocation());
							vvec /= length;
							bomb[i]->SetVelocity(vvec);
							break;
						}
					}
					length = bomb[i]->GetLength(player->GetLocation() * -1);
					if (length > 16) {
						bomb[i]->SetMoveToLocation(player->GetLocation() * -1);
						vvec = (bomb[i]->GetMoveToLocation() - bomb[i]->GetLocation());
						vvec /= length;
						bomb[i]->SetVelocity(vvec);

					}
					else {
						bomb[i]->SetVelocity(NULL);
					}
					break;
				}
				// 敵の更新
				bomb[i]->GetMapSize(MapSize);
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
						SE_HitFlg = true;
						bomb[i]->SetExpFlg(true);
						//if (bomb[i]->GetMode() == 3) {
							vvec = (bomb[i]->GetLocation() - player->GetLocation());
							length = bomb[i]->GetLength(player->GetLocation());
							vvec /= length;
							bomb[i]->SetKnockBack(vvec, 50);
							SpawnParticle(0, nullptr, false, bomb[i]->GetLocation(), player->GetLocation(), 0.5f);
							SetCameraShake(7);

						//}
					}
				}
				// 敵のフラグが0なら
				if (!bomb[i]->GetFlg()) {
					// 爆発を発生して敵をnullptrにしてループを抜ける
					SpawnExplosion(bomb[i]->GetLocation());
					SpawnParticle(2, nullptr, false, bomb[i]->GetLocation(), bomb[i]->GetLocation(), 2.5f);
					PlaySoundMem(Sounds::SE_Explosion, DX_PLAYTYPE_BACK, true);
					combo += 1;
					ui_combo_framecount = 25;
					score += (combo * 100);
					SetCameraShake(GetRand(8) + 4);
					bomb[i] = nullptr;
					delete bomb[i];
					// break;
					continue;
				}
			}
			// スポーン仮
			else {
				if (!comboflg) {
					if (i < MaxEnemyBomb) {
						bomb[i] = new Bomb;
						while (1) {
							Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
							if (640 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
								powf((spawnloc.x - player->GetLocation().x), 2) +
								powf((spawnloc.y - player->GetLocation().y), 2))))
							{
								bomb[i]->SetLocation(spawnloc);
								bomb[i]->SetMoveToLocation(spawnloc);
								//bomb[i]->SetMode(GetRand(4) + 1);
								bomb[i]->SetMode(5);
								break;
							}
						}
					}
				}
			}
		}

		comboflg = false;
		for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {

			if (explosion[i] != nullptr) {
				comboflg = true;
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
				//兵隊と爆発の当たり判定
				for (int j = 0; j < GM_MAX_ENEMY_SOLDIER; j++)
				{
					if (soldier[j] != nullptr)
					{
						if (explosion[i]->HitSphere(soldier[j]))
						{
							PlaySoundMem(Sounds::SE_DeleteSoldier, DX_PLAYTYPE_BACK);
							//soldier[j]->DMGflg(false);
								soldier[j] = nullptr;
								delete soldier[j];
								break;
						}
					}
				}

				if (!explosion[i]->Getflg()) {
					explosion[i] = nullptr;
					delete explosion[i];
				}
			}

		}

		// 兵隊とプレイヤーの当たり判定
		for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
		{
			if (soldier[i] != nullptr)
			{
				if (soldier[i]->HitSphere(player))
				{
					if (player->GetFlg() == false) {
						life--;
						hitmoment = true;
						player->SetFlg(true);
						PlaySoundMem(Sounds::SE_CatchiPlayer, DX_PLAYTYPE_BACK);
						soldier[i] = nullptr;
						soldier[i]->finalize();
					}
					else//無敵状態なら兵隊が反発する
					{
						ev = (soldier[i]->GetLocation() - player->GetLocation());
						l = soldier[i]->direction(player->GetLocation());
						ev /= l;
						soldier[i]->Knockback(ev, 50);
					}
				}
				else if (!soldier[i]->HitSphere(player) && hitmoment == true) {
					hitmoment = false;
				}
			}
		}

		// 効果音のフラグがたっているなら
		if (SE_HitFlg) {
			// 一度もなっていないなら
			if (!SE_NewHitFlg) {
				PlaySoundMem(Sounds::SE_Hit, DX_PLAYTYPE_BACK);
				SE_NewHitFlg = true;
			}
		}
		// フラグがたっていないならフラグを下げる
		else {
			SE_NewHitFlg = false;
		}

		// コンボのフラグがたっていないならコンボ数を0する
		if (!comboflg) {
			combo = 0;
		}
		// 0以上ならコンボ継続時間を下げる
		if (ui_combo_framecount > 0) {
			ui_combo_framecount--;
		}
		// マップが最小サイズより大きいならマップを小さくする
		if (MapSize > GM_MIN_MAPSIZE) {
			MapSize -= MapCloseSpeed / 10;
		}
		// マップサイズで敵の最大スポーン数を変える
		MaxEnemyBomb = (int)(GM_MAX_ENEMY_BOMB * (MapSize / GM_MAX_MAPSIZE));
		// ゲームのフレームを増やす
		game_frametime++;
		// カメラアップデート
		CameraUpdate();
		// 残機が0ならリザルトフラグを立てる
		if (life == 0) {
			resultflg = true;
		}

	}
	// リザルトフラグがたっているなら
	else {
		//if (InputControl::GetButtonDown(XINPUT_BUTTON_B)) {
		//	life = 3;
		//	resultflg = false;

		//}
		// 一回だけ動く
		if (!resultnewflg) {
			// 最大スコアよりスコアが大きいなら保存する
			if (score > hiscore) {
				UserData::SaveData(1, (float)score);
			}
			resultnewflg = true;
		}
		// Aボタンでタイトルに戻る
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A)) {
			return new Title;

		}
	}

	return this;

}

void GameMain::Draw() const
{

	// 背景
	for (int i = 0; i < (int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2, 2); i++) {
		if (background[i] != nullptr) {
			background[i]->Draw(player->GetLocation() + +(float)Camerashake);
		}
	}

	// マップの範囲
	DrawBoxAA(MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)), -MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) + 16, MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), 0x8844ff, true);
	DrawBoxAA(-MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)), -MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), -MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) - 16, MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), 0x8844ff, true);
	DrawBoxAA(-MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) - 16, MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2))+ 16 , MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)) + 16, 0x8844ff, true);
	DrawBoxAA(-MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) - 16,-MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)),MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) + 16, -MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)) - 16, 0x8844ff, true);

	// 兵士
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		// nullptrじゃないなら
		if (soldier[i] != nullptr)
		{
			// 画面中なら描画
			if (720 > fabsf(sqrtf(
				powf((soldier[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((soldier[i]->GetLocation().y - player->GetLocation().y), 2))))
			{
				soldier[i]->Draw(player->GetLocation() + +(float)Camerashake);
			}
		}
	}

	// 爆弾
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++){
		// nullptrじゃないなら
		if (bomb[i] != nullptr) {
			// 画面中なら描画
			if (720 > fabsf(sqrtf(
				powf((bomb[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((bomb[i]->GetLocation().y - player->GetLocation().y), 2))))
			{
				bomb[i]->Draw(player->GetLocation() + +(float)Camerashake);
			}
		}
	}
	// 爆発
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		// nullptrじゃないなら
		if (explosion[i] != nullptr) {
			// 画面中なら描画
			if (800 > fabsf(sqrtf(
				powf((explosion[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((explosion[i]->GetLocation().y - player->GetLocation().y), 2))))
			{
				explosion[i]->Draw(player->GetLocation() + (float)Camerashake);
			}
		}
	}

	
	// ギミック(氷)
    for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		// nullptrじゃないなら
		if (stage[i] != nullptr)
		{
			stage[i]->Draw(player->GetLocation() + +(float)Camerashake);
		}
	}

	// プレイヤー
	player->Draw(Camerashake);

	
	// パーティクル
	for (int i = 0; i < GM_MAX_PARTICLE; i++) {

		// 敵がnullptrじゃないなら
		if (particle[i] != nullptr) {
			particle[i]->Draw(player->GetLocation());

		}
	}

	// リザルトじゃないなら
	if (resultflg == false) {
		DrawFormatString(560, 10, 0xffffff, "%06d", hiscore);
		DrawFormatString(560, 40, 0xffffff, "%06d", score);
		DrawFormatString(320, 25, 0xffffff, "%02dmin %02dsec", game_frametime / 3600,(game_frametime / 60) % 60);
	}
	// リザルトなら
	else {
		DrawBox(300, 250, 960, 490, 0xffffff, true);
		DrawString(580, 280, "Result", 0x000000);
		//DrawString(500, 460, "--- Restart with B button ---", 0x000000);
		DrawString(380, 460, "--- Title with A button ---", 0x000000);
		DrawFormatString(582, 380, 0x000000, "%06d", score);
	}
	
	// コンボ
	int OldSize = GetFontSize();
	// コンボフラグがたっているなら描画
	if (comboflg) {
		SetFontSize(OldSize + ((1 + (ui_combo_framecount)) + (combo / 2)));
		DrawFormatString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GetColor(255, 255, 255 - (25 * combo)), "x%d", combo);
	}
	SetFontSize(OldSize);

	// 残機が1以上なら
	if (life > 0) {
		DrawFormatString(10, 10, 0xffffff, "life : %d", life);
	}
	else {
		DrawString(10, 10, "GameOver", 0xffffff);
	}
	DrawRotaGraph(128, 32, 1.0, 0.0, lifeimage, true);
	for (int i = 0; i < life; i++) {
		DrawRotaGraph(172 + (24 * i), 32, 1.0, 0.0, lifematchimage, true);
	}

	// ミニマップ
	DrawBox(SCREEN_WIDTH - 128 - 104, 128 - 104, SCREEN_WIDTH - 128 + 104, 128 + 104, 0x004400, true);
	DrawBox(SCREEN_WIDTH - 128 - (GM_MAX_MAPSIZE / 16), 128 - (GM_MAX_MAPSIZE / 16), SCREEN_WIDTH - 128 + (GM_MAX_MAPSIZE / 16), 128 + (GM_MAX_MAPSIZE / 16), 0x8844ff, true);
	//DrawBoxAA(SCREEN_WIDTH - 128 - (104 * (MapSize / GM_MAX_MAPSIZE)), 128 - (104 * (MapSize / GM_MAX_MAPSIZE)), SCREEN_WIDTH - 128 + (104 * (MapSize / GM_MAX_MAPSIZE)), 128 + (104 * (MapSize / GM_MAX_MAPSIZE)), 0x004400, true);
	DrawBoxAA(SCREEN_WIDTH - 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), SCREEN_WIDTH - 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 0x88ff88, true);

	// ミニマップ(爆弾)
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++) {
		if (bomb[i] != nullptr) {
			DrawCircleAA(SCREEN_WIDTH - 128 + (bomb[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (bomb[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2, 8, 0x7f2244, true);
		}
	}

	// ミニマップ(兵士)
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++) {
		if (soldier[i] != nullptr) {
			DrawCircleAA(SCREEN_WIDTH - 128 + (soldier[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (soldier[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2.5, 8, 0xff0000, true);
		}
	}

	// ミニマップ(ギミック(氷)
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++) {
		if (bomb[i] != nullptr) {
			DrawCircleAA(SCREEN_WIDTH - 128 + (stage[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (stage[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 8, 8, 0x004488, true);
		}
	}	
	// ミニマップ(プレイヤー)
	DrawCircleAA(SCREEN_WIDTH - 128 + (player->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (player->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2, 8, 0x8888ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void GameMain::Game()
{
}

// 爆発のスポーン
void GameMain::SpawnExplosion(Vector2D loc) {
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++) {
		if (explosion[i] == nullptr) {
			explosion[i] = new Explosion;
			explosion[i]->SetLocation(loc);
			break;
		}
	}
}

// パーティクルのスポーン(種類、親、ループ可か、スポーン座標、向く座標、大きさ
void GameMain::SpawnParticle(int type, SphereCollider * root, bool loop, Vector2D loc, Vector2D loc2, float scale) {
	for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++) {
		if (particle[j] == nullptr) {
			particle[j] = new Particle();
			particle[j]->Init(type, root, loop, scale);
			if (root != nullptr) {
				particle[j]->SetRootLocation(loc);
			}
			else {
			}
			particle[j]->SetLocation(loc);
			particle[j]->SetAngle(loc, loc2);
			break;
		}
	}
}

// カメラ更新
void GameMain::CameraUpdate() {
	if (CamerashakeCount > 0) {
		Camerashake = (int)round((double)CamerashakeCount / 2);
		if (CamerashakeCount % 2 == 0) {
			Camerashake *= -1;
		}
		CamerashakeCount--;
	}
}

void GameMain::SetCameraShake(int _i) {
	CamerashakeCount = _i;
}

void GameMain::SetMapSize(int i) {
	MapSize = (float)i;
}