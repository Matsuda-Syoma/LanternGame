#include "GameMain.h"
#include "../Utility/LoadSounds.h"
#include <math.h>
#include "../Utility/InputControl.h"
#include "../Utility/UserData.h"
#include "Title.h"

GameMain::GameMain()
{
	SetFontSize(32);
/*******************画像読み込み*******************/
	BackGround::LoadImages();
	Bomb::LoadImages();
	Particle::LoadImages();
	Tornado::LoadImages();
	ComboEnd::LoadImages();
	AddScore::LoadImages();
	hiscore = (int)UserData::LoadData(1);		// ハイスコア読み込み
	//BGMをループしながら再生する
	PlaySoundMem(Sounds::BGM_GMain, DX_PLAYTYPE_BACK);

/*******************初期化*******************/
	textdisp = new TextDisp;
	textdisp->LoadText(0);
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
		while (1)
		{
			// 初期値
			float length = 65535;
			bool ret = false;
			Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
			
			// 氷を見る
			for (int j = 0; j < GM_MAX_ICEFLOOR; j++)
			{
				// 自分以外なら
				if (j != i)
				{
					// 距離を計算
					length = GetLength(stage[j]->GetLocation(), spawnloc);
					// 360より短いならだめ:フラグon
					if (length < 360) {
						ret = true;
						break;
					}
				}
			}
			// フラグ0ffなら座標指定してるーぷぬける
			if (!ret) 
			{
				stage[i]->SetLocation(spawnloc);
				break;
			}
		}
	}

	conveyor = new Conveyor * [GM_MAX_CONVEYOR];
	{
		for (int i = 0; i < GM_MAX_CONVEYOR; i++)
		{
			conveyor[i] = nullptr;
		}
		for (int i = 0; i < GM_MAX_CONVEYOR; i++)
		{
			conveyor[i] = new Conveyor;
		}
		for (int i = 0; i < GM_MAX_CONVEYOR; i++)
		{
			conveyor[i]->SetLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
			conveyor[i]->Update();
		}
	}
	player->Init();

	// 兵士の初期化
	soldier = new Soldier * [GM_MAX_ENEMY_SOLDIER];
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		soldier[i] = nullptr;
	}

	// 兵士の作成
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		soldier[i] = new Soldier;
		while (1)
		{
			Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
			if (1080 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
				powf((spawnloc.x - player->GetLocation().x), 2) +
				powf((spawnloc.y - player->GetLocation().y), 2))))
			{
				soldier[i]->SetLocation(spawnloc);
				break;
			}
		}
	}

	// 爆弾の初期化
	bomb = new Bomb * [GM_MAX_ENEMY_BOMB];
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		bomb[i] = nullptr;
	}

	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		bomb[i] = new Bomb;
		while (1)
		{
			Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
			if (1080 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
				powf((spawnloc.x - player->GetLocation().x), 2) +
				powf((spawnloc.y - player->GetLocation().y), 2))))
			{
				bomb[i]->SetLocation(spawnloc);
				bomb[i]->SetMoveToLocation(spawnloc);
				bomb[i]->SetMode(GetRand(4) + 1);
				break;
			}
		}
	}

	// 爆発判定の初期化
	explosion = new Explosion * [GM_MAX_EFFECT_EXPLOSION];
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++)
	{
		explosion[i] = nullptr;
	}

	// 背景の初期化(マップサイズ/64を正の無限大へ丸めて、二倍にする。そのあと二乗する)
	background = new BackGround * [(int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2 + 2, 2)];
	for (int i = 0; i < (int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2 + 2, 2); i++)
	{
		background[i] = nullptr;
	}

	// 背景の生成(2次元配列で座標を決め、1次元配列に順番で配置)
	int backnum = 0;
	for (int i = 1; i < (int)ceil(GM_MAX_MAPSIZE / 64.f) * 2;i++)
	{
		for (int j = 1; j < (int)ceil(GM_MAX_MAPSIZE / 64.f) * 2; j++)
		{
			background[backnum] = new BackGround(
				Vector2D((i - (float)ceil(GM_MAX_MAPSIZE / 64.f)) * 64
					   , (j - (float)ceil(GM_MAX_MAPSIZE / 64.f)) * 64));
			backnum++;
		}
	}

	// パーティクルの初期化
	particle = new Particle * [GM_MAX_PARTICLE];
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		particle[i] = nullptr;
	}

	// プレイヤーの位置に炎を出現
	SpawnParticle(1, player, true, Vector2D(player->GetLocation().x + 15, player->GetLocation().y)
								 , Vector2D(player->GetLocation().x + 15, player->GetLocation().y), 1.0);

	// 吸い込むギミックの初期化
	tornado = new Tornado * [GM_MAX_TORNADO];
	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		tornado[i] = nullptr;
	}

	// 吸い込むギミックの生成
	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		tornado[i] = new Tornado;
	}
	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		while (1)
		{
			// 初期値
			float length = 65535;
			bool ret = false;
			Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));

			// 吸い込みを見る
			for (int j = 0; j < GM_MAX_TORNADO; j++)
			{
				// 自分以外なら
				if (j != i)
				{
					// 距離を計算
					length = GetLength(tornado[j]->GetLocation(), spawnloc);
					// 360より短いなら:フラグon
					if (length < 420) {
						ret = true;
						break;
					}
				}
			}
			for (int j = 0; j < GM_MAX_ICEFLOOR; j++)
			{
					// 距離を計算
				length = GetLength(stage[j]->GetLocation(), spawnloc);
				// 360より短いなら:フラグon
				if (length < 420) {
					ret = true;
					break;
				}
			}
			// フラグ0ffなら座標指定してるーぷぬける
			if (!ret)
			{
				tornado[i]->SetLocation(spawnloc);
				break;
			}
		}
	}

	// コンボ初期化
	comboend = new ComboEnd * [GM_MAX_COMBOEND];
	for (int i = 0; i < GM_MAX_COMBOEND; i++)
	{
		comboend[i] = nullptr;
	}

	// スコア表示の初期化
	addscore = new AddScore * [GM_MAX_ADDSCORE];
	for (int i = 0; i < GM_MAX_ADDSCORE; i++)
	{
		addscore[i] = nullptr;
	}

	/*******************画像読み込み*******************/
	lifeimage = LoadGraph("Resources/images/lifebar.png", 0);
	lifematchimage = LoadGraph("Resources/images/match.png", 0);
	closemapimage = LoadGraph("Resources/images/warning.png", 0);
	hukidasiimage = LoadGraph("Resources/images/hukidasi.png", 0);
	LoadDivGraph("Resources/images/number.png", 10, 10, 1, 64, 64, numimage);
	LoadDivGraph("Resources/images/alphabet.png", 26, 7, 4, 64, 64, alphabetimage);
	resultimage = LoadGraph("Resources/images/result.png", 0);
	highscoreimage = LoadGraph("Resources/images/highscore.png", 0);
	blackimage = LoadGraph("Resources/images/black.png", 0);
	
}

// デストラクタ
GameMain::~GameMain()
{
	Bomb::DeleteImages();
	Explosion::DeleteImages();
	Particle::DeleteImages();
	BackGround::DeleteImages();
	AddScore::DeleteImages();
}

/********************ゲームの更新処理********************/
AbstractScene* GameMain::Update()
{
	// 文字の表示
	textdisp->Update();
	if (resultflg == false && !textdisp->GetFlg() && countdownflg == false) {

		// 曲が鳴っていないなら鳴らす
		if (CheckSoundMem(Sounds::BGM_GMain) == 0)
		{
			PlaySoundMem(Sounds::BGM_GMain, DX_PLAYTYPE_BACK);
			ChangeVolumeSoundMem(150, Sounds::BGM_GMain);
		}

		// プレイヤーの更新
		player->GetMapSize(MapSize);
		player->Update();
		
		// スコア表示の更新
		for (int i = 0; i < GM_MAX_ADDSCORE; i++)
		{
			// nullptrじゃないなら見る
			if (addscore[i] != nullptr)
			{
				// 更新処理
				addscore[i]->Update(player->GetLocation());

				// フラグがたっていないなら消す
				if (!addscore[i]->GetFlg())
				{
					addscore[i] = nullptr;
					delete addscore[i];
				}
			}
		}


		// 吸い込むギミックの更新
		for (int i = 0; i < GM_MAX_TORNADO; i++)
		{
			// nullptrじゃないなら見る
			if (tornado[i] != nullptr)
			{
				// 更新処理
				tornado[i]->Update();
			}
		}

		// 兵士の更新
		for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
		{
			// nullptrじゃないなら見る
			if (soldier[i] != nullptr)
			{
				// 更新処理
				soldier[i]->Upadate(player->GetLocation());
				soldier[i]->GetMapSize(MapSize);
				soldier[i]->SetVelocity(1);
			}
			else
			{
				// 兵士のスポーン
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
					if (soldier[i] != nullptr && soldier[j] != nullptr)
					{

						// 距離が短いなら変数を保存する
						if (eel > soldier[i]->direction(soldier[j]->GetLocation()))
						{
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
					if (soldier[i] != nullptr && bomb[j] != nullptr)
					{
						// 距離が短いなら変数を保存する
						if (eel > soldier[i]->direction(bomb[j]->GetLocation()))
						{
							chek = j;
							eel = soldier[i]->direction(bomb[j]->GetLocation());
						}
					}
			}
			if (chek != -1)
			{
				if (eel < 80)
				{
						ee = (soldier[i]->GetLocation() - bomb[chek]->GetLocation());
						ee /= eel;
						soldier[i]->SetVelocity(ee);
						break;
				}
			}
		}

		for (int i = 0; i < GM_MAX_PARTICLE; i++)
		{
			// パーティクルがnullptrじゃないなら
			if (particle[i] != nullptr)
			{
				particle[i]->Update();
				if (!particle[i]->Getflg())
				{
					particle[i] = nullptr;
					delete particle[i];
				}
			}
		}


		// 敵の数を見る
		SE_HitFlg = false;
		for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
		{
			// 敵がnullptrじゃないなら
			if (bomb[i] != nullptr)
			{
				// プレイヤーとの距離を見る
				// プレイヤーと320離れていたら
				if (240 < bomb[i]->GetLength(player->GetLocation()) && bomb[i]->GetMode() == 2)
				{
					bomb[i]->SetMode(GetRand(4) + 1);
				}
				// 敵と敵の距離を見る
				int temp = -1;
				float length = 65535;
				Vector2D vvec = 0;

				switch (bomb[i]->GetMode())
				{
				case 0:
					break;

					// 敵同士集まる
				case 1:

					for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
					{
						// 自分以外なら
						if (j != i)
						{
							// nullptrじゃないなら距離を見る
							if (bomb[j] != nullptr)
							{
								// 距離が短いなら変数を保存する
								if(bomb[i]->GetMode() != 3)
								{
									if (length > bomb[j]->GetLength(bomb[i]->GetLocation()))
									{
										temp = j;
										length = bomb[j]->GetLength(bomb[i]->GetLocation());
									}
								}
							}
						}
						else if (bomb[j] == nullptr)
						{
							temp = -1;
							length = 65535;
						}
					}
					if (temp != -1)
					{
						// 距離が長いなら
						if (length > 80)
						{
							vvec = (bomb[temp]->GetLocation() - bomb[i]->GetLocation());
							vvec /= length;
							bomb[i]->SetVelocity(vvec);
							break;
						}

						// 距離が近いなら
						else if (length < 72)
						{
							vvec = (bomb[i]->GetLocation() - bomb[temp]->GetLocation());
							vvec /= length;
							bomb[i]->SetVelocity(vvec);
							break;
						} 
						else 
						{
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
					for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
					{

						// 自分以外なら
						if (j != i)
						{

							// nullptrじゃないなら距離を見る
							if (bomb[j] != nullptr)
							{

								// 距離が短いなら変数を保存する
								if (length > bomb[j]->GetLength(bomb[i]->GetLocation()))
								{
									temp = j;
									length = bomb[j]->GetLength(bomb[i]->GetLocation());
								}
							}
						}
						else if (bomb[j] == nullptr)
						{
							temp = -1;
							length = 65535;
						}
					}
					if (temp != -1)
					{
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
					else
					{
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
					else
					{
						bomb[i]->SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
					}
					if (fabsf(bomb[i]->GetMoveToLocation().x) - MapSize + 32 > 0 || fabsf(bomb[i]->GetMoveToLocation().y) - MapSize + 32 > 0) {
						bomb[i]->SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
					}
					break;

					// プレイヤーと対称の動き
				case 5:
					for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
					{
						// 自分以外なら
						if (j != i)
						{
							// nullptrじゃないなら距離を見る
							if (bomb[j] != nullptr)
							{
								// 距離が短いなら変数を保存する
								if (length > bomb[j]->GetLength(bomb[i]->GetLocation()))
								{
									temp = j;
									length = bomb[j]->GetLength(bomb[i]->GetLocation());
								}
							}
						}

						else if (bomb[j] == nullptr)
						{
							temp = -1;
							length = 65535;
						}
					}

					if (temp != -1)
					{
						// 距離が近いなら
						if (length < 72)
						{
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
					else
					{
						bomb[i]->SetVelocity(NULL);
					}
					break;
				}

				// 敵の更新
				bomb[i]->GetMapSize(MapSize);
				bomb[i]->Update();
				// 敵のフラグが1なら
				if (bomb[i]->GetFlg())
				{
					// 爆発の数を見る
					for (int j = 0; j < GM_MAX_EFFECT_EXPLOSION; j++)
					{
						// 爆発がnullptrじゃないなら
						if (explosion[j] != nullptr)
						{
							// 敵と爆発の当たり判定
							if (bomb[i]->HitSphere(explosion[j]))
							{
								// 敵のフラグを切って爆発のループを抜ける
								bomb[i]->SetFlg(false);
								break;
							}
						}
					}

					// 敵とプレイヤーの当たり判定
					if (bomb[i]->HitSphere(player))
					{
							vvec = (bomb[i]->GetLocation() - player->GetLocation());
							length = bomb[i]->GetLength(player->GetLocation());
							vvec /= length;
							if (!bomb[i]->GetExpFlg())
							{
								bomb[i]->SetKnockBack(vvec, 20);
							}
							else
							{
								bomb[i]->SetKnockBack(vvec, 50);
							}
							SE_HitFlg = true;
							bomb[i]->SetExpFlg(true);
							SpawnParticle(0, nullptr, false, bomb[i]->GetLocation(), player->GetLocation(), 0.5f);
							SetCameraShake(7);
					}
				}

				// 敵のフラグが0なら
				if (!bomb[i]->GetFlg())			
				{
					// 爆発を発生して敵をnullptrにしてループを抜ける
					SpawnExplosion(bomb[i]->GetLocation());
					SpawnParticle(3, nullptr, false, bomb[i]->GetLocation(), Vector2D(bomb[i]->GetLocation().x + (GetRand(1) - 0.5f), bomb[i]->GetLocation().y + (GetRand(1) - 0.5f)), 1.5f);
					PlaySoundMem(Sounds::SE_Explosion[GetRand(4)], DX_PLAYTYPE_BACK, true);
					combo += 1;
					ui_combo_framecount = 25;
					score += (combo * 100);
					SpawnAddScore(bomb[i]->GetLocation(), (combo * 100));
					SetCameraShake(GetRand(8) + 4);
					bomb[i] = nullptr;
					delete bomb[i];
					continue;
				}
			}

			// スポーン仮
			else
			{
				if (!comboflg)
				{
					if (i < MaxEnemyBomb)
					{
						bomb[i] = new Bomb;
						while (1)
						{
							Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
							if (1080 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
								powf((spawnloc.x - player->GetLocation().x), 2) +
								powf((spawnloc.y - player->GetLocation().y), 2))))
							{
								bomb[i]->SetLocation(spawnloc);
								bomb[i]->SetMoveToLocation(spawnloc);
								bomb[i]->SetMode(GetRand(4) + 1);
								break;
							}
						}
					}
				}
			}
		}

		comboflg = false;
		for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++)
		{
			if (explosion[i] != nullptr)
			{
				comboflg = true;
				explosion[i]->Update();
				// プレイヤーと爆発の当たり判定
				if (explosion[i]->HitSphere(player) && hitmoment == false)
				{
					if (player->GetFlg() == false)
					{
						life--;
						hitmoment = true;
						player->SetFlg(true);
					}
				}
				else if (!explosion[i]->HitSphere(player) && hitmoment == true)
				{
					hitmoment = false;
				}
				//兵隊と爆発の当たり判定
				for (int j = 0; j < GM_MAX_ENEMY_SOLDIER; j++)
				{
					if (soldier[j] != nullptr)
					{
						if (explosion[i]->HitSphere(soldier[j]))
						{
							//PlaySoundMem(Sounds::SE_DeleteSoldier, DX_PLAYTYPE_BACK);
							soldier[j]->SetDMGflg(false);
							//StopSoundMem(Sounds::SE_DeleteSoldier);
							
						}
						if (soldier[j]->ChekDLflg() == true)
						{
							soldier[j] = nullptr;
							delete soldier[j];
							break;
						}
					}
				}

				if (!explosion[i]->Getflg())
				{
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
					if (player->GetFlg() == false && soldier[i]->ChekhitFlg() == true)
					{
						/*life--;*/
						hitmoment = true;
						//player->SetFlg(true);
						player->SetHitSoldier(true);
						PlaySoundMem(Sounds::SE_CatchiPlayer, DX_PLAYTYPE_BACK);
						soldier[i]->SetDMGflg(false);
						if (CheckSoundMem(Sounds::SE_CatchiPlayer) == 0)
						{
							StopSoundMem(Sounds::SE_CatchiPlayer);
						}
					}
					else//無敵状態なら兵隊が反発する
					{
						ev = (soldier[i]->GetLocation() - player->GetLocation());
						l = soldier[i]->direction(player->GetLocation());
						ev /= l;
						soldier[i]->Knockback(ev, 50);
					}
				}
				else if (!soldier[i]->HitSphere(player) && hitmoment == true)
				{
					hitmoment = false;
				}
				if (soldier[i]->ChekDLflg() == true)
				{
					soldier[i] = nullptr;
					delete soldier[i];
					break;
				}
			}
		}
		//氷の床の当たり判定
		player->SetIceFlg(false);
		for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
		{
			if (stage[i]->HitSphere(player))
			{
				if (player->GetIceFlg() == false)
				{
					player->SetIceFlg(true);
				}
			}
		}

		
		//コンベアの当たり判定
		player->SetConFlg(false);
		for (int i = 0; i < GM_MAX_CONVEYOR; i++)
		{
			conveyor[i]->Update();
			if (conveyor[i]->HitSphere(*player))
			{
				player->SetLocation(Vector2D(player->GetLocation().x + 2, player->GetLocation().y));
				/*if (player->GetConFlg() == false) {
					player->SetConFlg(true);
				}*/
			}
		}
		// Velocity初期化
		player->SetVelocity(NULL);
		for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
		{
			if (bomb[i] != nullptr)
			{
				bomb[i]->SetEXVelocity(NULL);
			}
		}

		// 吸い込みギミックの判定
		for (int i = 0; i < GM_MAX_TORNADO; i++)
		{
			if (tornado[i] != nullptr)
			{
				// プレイヤーが当たっているなら
				if (tornado[i]->HitSphere(player))
				{
					float length = GetLength(player->GetLocation(), tornado[i]->GetLocation());
					Vector2D vvec = (tornado[i]->GetLocation() - player->GetLocation());
					vvec /= length;
					player->SetVelocity(vvec * 2);
				}
			}

			for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
			{
				if (bomb[j] != nullptr)
				{
					if (tornado[i]->HitSphere(bomb[j]))
					{
						float length = GetLength(bomb[j]->GetLocation(), tornado[i]->GetLocation());
						Vector2D vvec = (tornado[i]->GetLocation() - bomb[j]->GetLocation());
						vvec /= length;
						bomb[j]->SetEXVelocity(vvec);
					}
				}
			}
		}

		for (int i = 0; i < GM_MAX_COMBOEND; i++)
		{
			if (comboend[i] != nullptr)
			{
				comboend[i]->Update();
				if (!comboend[i]->GetFlg())
				{
					comboend[i] = nullptr;
					delete comboend[i];
				}
			}
		}

		// 効果音のフラグがたっているなら
		if (SE_HitFlg)
		{
			// 一度もなっていないなら
			if (!SE_NewHitFlg)
			{
				PlaySoundMem(Sounds::SE_Hit, DX_PLAYTYPE_BACK);
				SE_NewHitFlg = true;
			}
		}
		// フラグがたっていないならフラグを下げる
		else {
			SE_NewHitFlg = false;
		}

		// コンボのフラグがたっていないならコンボ数を0する
		if (!comboflg)
		{
			if (combo != 0)
			{
				SpawnParticle(2, player, false, Vector2D(0.f,10.f), Vector2D(0.f, 10.f), 2.f);

				// ここに効果音

				oldcombo = combo;
				for (int i = 0; i < GM_MAX_COMBOEND; i++)
				{
					if (comboend[i] == nullptr)
					{
						comboend[i] = new ComboEnd(oldcombo);
						break;
					}
				}
				// 何か効果音
			}
			combo = 0;
		}

		// 0以上ならコンボ継続時間を下げる
		if (ui_combo_framecount > 0)
		{
			ui_combo_framecount--;
		}

		// マップサイズの変更
		ChangeMapSize();

		// マップサイズで敵の最大スポーン数を変える
		MaxEnemyBomb = (int)(GM_MAX_ENEMY_BOMB * (MapSize / GM_MAX_MAPSIZE));

		// ゲームのフレームを増やす
		game_frametime++;

		// カメラアップデート
		CameraUpdate();


		// 残機が0ならリザルトフラグを立てる

		if (life == 0)
		{
			
				player->SetPFlg(false);
		}

	}
	// 残機が０になったら
	if(player->GetPFlg() == false && resultflg == false){
		StopSoundMem(Sounds::BGM_GMain);
		r_cun++;
		alpha += 3;

		switch (r_cun)
		{
		case(0):
			break;
		case(130):
			resultflg = true;
			break;
		default:
			break;
		}
	}

	// カウントダウン（３秒）
	if (countdownflg == true && !textdisp->GetFlg())
	{
		c_cun++;
		switch (c_cun)
		{
		case(1):
		case(60):
		case(120):
			countdown--;
			countsize = 3.0;
			PlaySoundMem(Sounds::SE_CntDown, DX_PLAYTYPE_BACK);
			break;
		case(180):
			countdown--;
			countsize = 2.5;
			countdownflg = false;
			break;
		default:
			break;
		}

		if (countsize >= 2.0)
		{
			countsize -= 0.1;
		}

	}
	// １秒間「START」表示
	else if (countdown == 0)
	{
		c_cun++;
		switch (c_cun)
		{
		case(240):
			countdown = 4;
			break;
		}

		if (countsize >= 1.5)
		{
			countsize -= 0.1;
		}
	}

	// フェードアウト
	if (alpha > 0 && resultflg == true)
	{
		alpha -= 10;
	}

	// リザルトフラグがたっているなら
	if (resultflg == true)
	{
		//if (InputControl::GetButtonDown(XINPUT_BUTTON_B)) {
		//	life = 3;
		//	resultflg = false;

		// 一回だけ動く
		if (!resultnewflg)
		{
			// 最大スコアよりスコアが大きいなら保存する
			if (score > hiscore)
			{
				UserData::SaveData(1, (float)score);
				highscoreflg = true;
			}
			resultnewflg = true;
		}
		// Aボタンでタイトルに戻る
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			return new Title;
		}
	}

	return this;

}

void GameMain::Draw() const
{

	// 背景
	for (int i = 0; i < (int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2, 2); i++)
	{
		if (background[i] != nullptr)
		{
			background[i]->Draw(player->GetLocation() + +(float)Camerashake);
		}
	}
	// マップの範囲
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	DrawBoxAA(MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)), -MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), GM_MAX_MAPSIZE + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) + 16, MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), 0x000000, true);
	DrawBoxAA(-MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)), -MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), -GM_MAX_MAPSIZE + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) - 16, MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), 0x000000, true);
	DrawBoxAA(-MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) - (16 + (GM_MAX_MAPSIZE - MapSize)), MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)), MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) + (16 + (GM_MAX_MAPSIZE - MapSize)), GM_MAX_MAPSIZE + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)) + 16, 0x000000, true);
	DrawBoxAA(-MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) - (16 + (GM_MAX_MAPSIZE - MapSize)),-MapSize + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)),MapSize + (-player->GetLocation().x + (SCREEN_WIDTH / 2)) + (16 + (GM_MAX_MAPSIZE - MapSize)), -GM_MAX_MAPSIZE + (-player->GetLocation().y + (SCREEN_HEIGHT / 2)) - 16, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

	//ギミック(氷)
    for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		// nullptrじゃないなら
		if (stage[i] != nullptr)
		{
			stage[i]->Draw(player->GetLocation() + +(float)Camerashake);
		}
	}

	//ギミック(コンベア)
    for (int i = 0; i < GM_MAX_CONVEYOR; i++)
	{
		if (conveyor[i] != nullptr)
		{
			conveyor[i]->Draw(player->GetLocation() + +(float)Camerashake);
		}
	}

	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		// nullptrじゃないなら
		if (tornado[i] != nullptr)
		{
			// 画面中なら描画
			if (1040 > fabsf(sqrtf(
				powf((tornado[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((tornado[i]->GetLocation().y - player->GetLocation().y), 2))))
			{
				tornado[i]->Draw(player->GetLocation() + (float)Camerashake);
			}
		}
	}

	// 爆弾
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		// nullptrじゃないなら
		if (bomb[i] != nullptr)
		{
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
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++)
	{
		// nullptrじゃないなら
		if (explosion[i] != nullptr)
		{
			// 画面中なら描画
			if (800 > fabsf(sqrtf(
				powf((explosion[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((explosion[i]->GetLocation().y - player->GetLocation().y), 2))))
			{
				explosion[i]->Draw(player->GetLocation() + (float)Camerashake);
			}
		}
	}
	

	// プレイヤー
	player->Draw(Camerashake);

	
	// パーティクル
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		// 敵がnullptrじゃないなら
		if (particle[i] != nullptr)
		{
			particle[i]->Draw(player->GetLocation());
		}
	}
	
	for (int i = 0; i < GM_MAX_ADDSCORE; i++)
	{
		// 敵がnullptrじゃないなら
		if (addscore[i] != nullptr)
		{
			addscore[i]->Draw(player->GetLocation());
		}
	}

	// コンボ
	DrawCombo();
	for (int i = 0; i < GM_MAX_COMBOEND; i++)
	{
		if (comboend[i] != nullptr)
		{
			comboend[i]->Draw();
		}
	}

	DrawCloseMap();

	DrawRotaGraph(SCREEN_WIDTH - 128, 328, 1.0, 0.0, lifeimage, true);
	for (int i = 0; i < life; i++)
	{
		DrawRotaGraph(SCREEN_WIDTH - 180 + (24 * i), 360, 1.0, 0.0, lifematchimage, true);
	}

	// ミニマップ
	DrawBox(SCREEN_WIDTH - 128 - 104, 128 - 104, SCREEN_WIDTH - 128 + 104, 128 + 104, 0x004400, true);
	DrawBox(SCREEN_WIDTH - 128 - (GM_MAX_MAPSIZE / 16), 128 - (GM_MAX_MAPSIZE / 16), SCREEN_WIDTH - 128 + (GM_MAX_MAPSIZE / 16), 128 + (GM_MAX_MAPSIZE / 16), 0x8844ff, true);
	DrawBoxAA(SCREEN_WIDTH - 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), SCREEN_WIDTH - 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 0x88ff88, true);

	// ミニマップ(爆弾)
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		if (bomb[i] != nullptr)
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (bomb[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (bomb[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2, 8, 0x7f2244, true);
		}
	}

	// ミニマップ(兵士)
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		if (soldier[i] != nullptr)
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (soldier[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (soldier[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2.5, 8, 0xff0000, true);
		}
	}

	// ミニマップ(ギミック(氷)
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		if (bomb[i] != nullptr)
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (stage[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (stage[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 8, 8, 0x004488, true);
		}
	}	

	/*//ミニマップ(ギミック(コンベア))
	for (int i = 0; i < GM_MAX_CONVEYOR; i++) {
		if (bomb[i] != nullptr) {
			DrawBoxAA(SCREEN_WIDTH - 128 + (conveyor[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (conveyor[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 8, 8, 0x004488, true);
		}
	}*/
	// ミニマップ(ギミック(氷)
	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		if (tornado[i] != nullptr)
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (tornado[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (tornado[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 12, 8, 0x800000, true);
		}
	}

	// ミニマップ(プレイヤー)
	DrawCircleAA(SCREEN_WIDTH - 128 + (player->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (player->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2, 8, 0x8888ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	// リザルトじゃないなら
	if (resultflg == false)
	{
		DrawFormatString(560, 10, 0xffffff, "%06d", hiscore);
		DrawFormatString(560, 40, 0xffffff, "%06d", score);
		//DrawFormatString(320, 25, 0xffffff, "%02dmin %02dsec", game_frametime / 3600,(game_frametime / 60) % 60);
	}
	// リザルトなら
	else
	{
		if (highscoreflg == true)
		{
			DrawGraph(0, 0, highscoreimage, true);
		}
		else {
			DrawGraph(0, 0, resultimage, true);
		}
		
		char res[] = "result\0";
		for (int i = 0; i < sizeof(res); i++)
		{
			int chr = res[i] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 420) + 56 * i, 300, 1.0, 0.0, alphabetimage[chr], true);
		}
		char res_2[] = "title with a button\0";
		for (int i = 0; i < sizeof(res_2); i++)
		{
			int chr = res_2[i] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 480) + 22 * i, 440, 0.6, 0.0, alphabetimage[chr], true);
		}

		int bufscore = score;
		for (int i = 0; i < 6; i++)
		{
			DrawRotaGraph((SCREEN_WIDTH - 180) - (40 * i), 380, 1.0, 0.0, numimage[bufscore % 10], true);
			bufscore /= 10;
		}
	}

	// カウントダウン（数字）
	if (countdownflg == true && countdown < 4)
	{
		DrawRotaGraph(SCREEN_WIDTH / 2, 260, countsize, 0.0, numimage[countdown], true);
	}
	// カウントダウン（START）
	else if (countdown == 0)
	{
		char res3[] = "start\0";
		for (int i = 0; i < sizeof(res3); i++)
		{
			int chr = res3[i] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 750) + 56 * i, 270, countsize, 0.0, alphabetimage[chr], true);
		}
	}

	textdisp->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, blackimage, false);
	//画像透かし終わり
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

void GameMain::Game()
{
}

// 爆発のスポーン
void GameMain::SpawnExplosion(Vector2D loc)
{
	for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++)
	{
		if (explosion[i] == nullptr)
		{
			explosion[i] = new Explosion;
			explosion[i]->SetLocation(loc);
			break;
		}
	}
}

// パーティクルのスポーン(種類、親、ループ可か、スポーン座標、向く座標、大きさ
void GameMain::SpawnParticle(int type, SphereCollider * root, bool loop, Vector2D loc, Vector2D loc2, float scale)
{
	for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
	{
		if (particle[j] == nullptr)
		{
			particle[j] = new Particle();
			particle[j]->Init(type, root, loop, scale);
			if (root != nullptr)
			{
				particle[j]->SetRootLocation(loc);
			}
			particle[j]->SetLocation(loc);
			particle[j]->SetAngle(loc, loc2);
			break;
		}
	}
}

// カメラ更新
void GameMain::CameraUpdate()
{
	if (CamerashakeCount > 0)
	{
		Camerashake = (int)round((double)CamerashakeCount / 2);
		if (CamerashakeCount % 2 == 0)
		{
			Camerashake *= -1;
		}
		CamerashakeCount--;
	}
}

void GameMain::SetCameraShake(int _i)
{
	CamerashakeCount = _i;
}

void GameMain::SetMapSize(float f)
{
	MapSize = f;
}

void GameMain::ChangeMapSize()
{
	if (game_frametime % 900 > 550 && game_frametime % 900 <= 750)
	{
		if (game_frametime % 900 == 551)
		{
			PlaySoundMem(Sounds::SE_MapClose, DX_PLAYTYPE_BACK);
		}
		if (MapSize > GM_MIN_MAPSIZE)
		{
			SetMapSize(MapSize - 0.75f);

			if (MapSize < GM_MIN_MAPSIZE)
			{
				SetMapSize(GM_MIN_MAPSIZE);
			}
		}
		else
		{
			SetMapSize(GM_MIN_MAPSIZE);
		}
	}
}

void GameMain::DrawCombo() const
{
	int OldSize = GetFontSize();
	// コンボフラグがたっているなら描画
	if (comboflg)
	{
		SetFontSize(OldSize + ((1 + (ui_combo_framecount)) + (combo / 2)));
		char buf[4];
		int StrLen = snprintf(buf, 4, "%d", combo);
		int StrWidth = GetDrawStringWidth(buf, StrLen);
		int CenterX = (int)((0 + ((SCREEN_WIDTH - 0) / 2)) - (StrWidth / 2));
		DrawFormatString(CenterX, SCREEN_HEIGHT / 2, GetColor(255, 255, 255 - (25 * combo)), "%d", combo);
	}
	SetFontSize(OldSize);
}

void GameMain::DrawCloseMap() const
{
	//int OldSize = GetFontSize();
	//if (game_frametime % 200 > 100) {
	//SetFontSize(48 + (game_frametime % 100) /10);
	//char buf[8] = {"Warning"};
	//int StrLen = strlen(buf);
	//int StrWidth = GetDrawStringWidth(buf, StrLen);
	//int CenterX = (int)((0 + ((SCREEN_WIDTH - 0) / 2)) - (StrWidth / 2));
	//DrawFormatStringF(CenterX, (SCREEN_HEIGHT / 2) - 120, GetColor(255, 64, 64), "%s", buf);
	//}
	//SetFontSize(OldSize);
	int OldDrawMode;
	int OldDrawParam;
	GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (game_frametime % 150) * 4);
	if (MapSize > GM_MIN_MAPSIZE)
	{
		if (game_frametime % 900 > 450 && game_frametime % 900 <= 550)
		{
			DrawRotaGraph((SCREEN_WIDTH / 2) + GetRand(3) - 2, (SCREEN_HEIGHT / 2) - 120, 1.0, 0.0, closemapimage, true);
			DrawBoxAA((SCREEN_WIDTH / 2) - 105, (SCREEN_HEIGHT / 2) - 85,
					  (SCREEN_WIDTH / 2) + 105, (SCREEN_HEIGHT / 2) - 65, 0x000000, true);
			DrawBoxAA((SCREEN_WIDTH / 2) - (float)(game_frametime % 150) + 100, (SCREEN_HEIGHT / 2) - 80, 
					  (SCREEN_WIDTH / 2) + (float)(game_frametime % 150) - 100, (SCREEN_HEIGHT / 2) - 70, 0xffffff, true);
		}
	}
	SetDrawBlendMode(OldDrawMode, OldDrawParam);
}

// 爆発のスポーン
void GameMain::SpawnAddScore(Vector2D loc, int _score)
{
	for (int i = 0; i < GM_MAX_ADDSCORE; i++)
	{
		if (addscore[i] == nullptr)
		{
			addscore[i] = new AddScore(loc, _score);
			break;
		}
	}
}