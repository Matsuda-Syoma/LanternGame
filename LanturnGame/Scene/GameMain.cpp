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
	Tornado::LoadImages();
	ComboEnd::LoadImages();
	AddScore::LoadImages();

	// ハイスコア読み込み
	hiscore = (int)UserData::LoadData(UserData::Type::HISCORE);		// ハイスコア読み込み

	// BGMをループしながら再生する
	PlaySoundMem(Sounds::BGM_GMain, DX_PLAYTYPE_BACK);

	/*******************初期化*******************/
	textdisp = new TextDisp;
	textdisp->LoadText(0);
	player = new Player;
	

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
			while (1)
			{
				// 初期値
				float length = 65535;
				bool ret = false;
				Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
				Vector2D center = (Vector2D((float)((int)MapSize) - 1500, (float)((int)MapSize) - 1500));

				// コンベアを見る
				for (int j = 0; j < GM_MAX_CONVEYOR; j++)
				{
					// 自分以外なら
					if (j != i)
					{
						// 距離を計算
						length = GetLength(conveyor[j]->GetLocation(), spawnloc);
						// 360より短いならだめ:フラグon
						if (length < 500) {
							ret = true;
							break;
						}
					}

					length = GetLength(center, spawnloc);
					if (length > 600) {
							ret = true;
							break;
					}
				}
				if (!ret)
				{
					conveyor[i]->SetLocation(spawnloc);
					conveyor[i]->Update();
					break;
				}
			}

		}
	}

	conveyor_y = new Conveyor_y * [GM_MAX_CONVEYOR_Y];
	{
		for (int i = 0; i < GM_MAX_CONVEYOR_Y; i++)
		{
			conveyor_y[i] = nullptr;
		}
		for (int i = 0; i < GM_MAX_CONVEYOR_Y; i++)
		{
			conveyor_y[i] = new Conveyor_y;
		}
		for (int i = 0; i < GM_MAX_CONVEYOR_Y; i++)
		{
			while (1)
			{
				// 初期値
				float length = 65535;
				bool ret = false;
				bool rat = false;
				Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
				Vector2D center = (Vector2D((float)((int)MapSize) - 1500, (float)((int)MapSize) - 1500));

				// コンベアを見る
				for (int j = 0; j < GM_MAX_CONVEYOR_Y; j++)
				{
					// 自分以外なら
					if (j != i)
					{
						// 距離を計算
						length = GetLength(conveyor_y[j]->GetLocation(), spawnloc);
						// 360より短いならだめ:フラグon
						if (length < 600) {
							ret = true;
							break;
						}
					}
					for (int j = 0; j < GM_MAX_CONVEYOR; j++)
					{
						// 距離を計算
						length = GetLength(conveyor[j]->GetLocation(), spawnloc);
						// 360より短いなら:フラグon
						if (length < 800) {
							ret = true;
							break;
						}
					}
					length = GetLength(center, spawnloc);
					if (length > 900) {
							rat = true;
							break;
					}
				}
				if (!ret)
				{
					if (!rat) {
						conveyor_y[i]->SetLocation(spawnloc);
						conveyor_y[i]->Update();
						break;
					}
				}
				
			}

		}
	}
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
			for (int j = 0; j < GM_MAX_CONVEYOR; j++)
			{
				// 距離を計算
				length = GetLength(conveyor[j]->GetLocation() + 300, spawnloc);
				// 360より短いなら:フラグon
				if (length < 500) {
					ret = true;
					break;
				}
			}
			for (int j = 0; j < GM_MAX_CONVEYOR_Y; j++)
			{
				// 距離を計算
				length = GetLength(conveyor_y[j]->GetLocation() + 300, spawnloc);
				// 360より短いなら:フラグon
				if (length < 500) {
					ret = true;
					break;
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

	// 爆弾を設定数初期化する
	for (int i = 0; i < MaxSpawnEnemyBomb; i++)
	{
		bomb[i] = new Bomb;
		bomb[i]->Init(C_ExpSize);
		while (1)
		{
			// プレイヤーから距離が遠かったらスポーン
			Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
			if (1080 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
				powf((spawnloc.x - player->GetLocation().x), 2) +
				powf((spawnloc.y - player->GetLocation().y), 2))))
			{
				bomb[i]->SetLocation(spawnloc);
				bomb[i]->SetMoveToLocation(spawnloc);
				bomb[i]->SetMode(RandType(GetRand(99)) + 1);
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
	for (int i = 1; i < (int)ceil(GM_MAX_MAPSIZE / 64.f) * 2; i++)
	{
		for (int j = 1; j < (int)ceil(GM_MAX_MAPSIZE / 64.f) * 2; j++)
		{
			background[backnum] = new BackGround(
				Vector2D((i - (float)ceil(GM_MAX_MAPSIZE / 64.f))
					, (j - (float)ceil(GM_MAX_MAPSIZE / 64.f))));
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
	SpawnParticle(1, player, true,
		Vector2D(player->GetLocation().x + 15, player->GetLocation().y), 0.f, 1.0, 0.f);

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
			for (int j = 0; j < GM_MAX_CONVEYOR; j++)
			{
				// 距離を計算
				length = GetLength(conveyor[j]->GetLocation() + 300, spawnloc);
				// 800より短いなら:フラグon
				if (length < 600) {
					ret = true;
					break;
				}
			}
			for (int j = 0; j < GM_MAX_CONVEYOR_Y; j++)
			{
				// 距離を計算
				length = GetLength(conveyor_y[j]->GetLocation() + 300, spawnloc);
				// 360より短いなら:フラグon
				if (length < 600) {
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
	crackimage = LoadGraph("Resources/images/crack1.png", 0);
	sootimage = LoadGraph("Resources/images/soot.png", 0);
	
}

// デストラクタ
GameMain::~GameMain()
{
	Bomb::DeleteImages();
	Explosion::DeleteImages();
	BackGround::DeleteImages();
	AddScore::DeleteImages();
}

/********************ゲームの更新処理********************/
AbstractScene* GameMain::Update()
{
	// 文字の表示
	textdisp->Update();
	//スコア描画の中心の値を求める
	ScoreCenter = GetDrawStringWidth("%d,", score) / 2;

		

	// リザルトじゃない かつ カウントダウンが終わっているとき
	if (resultflg == false && !textdisp->GetFlg() && countdownflg == false) {

		
		//ポーズ画面
		if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
		{
				PauseFlg = !PauseFlg;
		}
		// 曲が鳴っていないなら鳴らす
		if (player->GetPlayerFlg() == true && CheckSoundMem(Sounds::BGM_GMain) == 0)
		{
			PlaySoundMem(Sounds::BGM_GMain, DX_PLAYTYPE_BACK);
		}
		if(!PauseFlg)
		{
		// プレイヤーの更新
		player->GetMapSize(MapSize);
		player->Update();
		Camera = player->GetLocation();
		Camera += (float)Camerashake;

		// プレイヤーが生きている&兵士が当たってないとき
		if (player->GetPlayerFlg() && !player->GetHitSoldier())
		{
			// 炎を表示する
			particle[0]->SetVisible(true);
			switch (player->GetDirection())
			{
			case 0:
			case 4:
				// プレイヤーの位置に煙を出現
				SpawnParticle(4, nullptr, false,
					Vector2D(player->GetLocation().x + 15.f, player->GetLocation().y - 10.f),
					(float)GetRand(30) - 15.f, (GetRand(4) + 1) / 10.f, (float)(GetRand(1) + 1.f));
				particle[0]->SetRootLocation(Vector2D(15, -15));
				break;
			case 1:
			case 5:
				// プレイヤーの位置に煙を出現
				SpawnParticle(4, nullptr, false,
					Vector2D(player->GetLocation().x - 15.f, player->GetLocation().y - 10.f),
					(float)GetRand(30) - 15.f, (GetRand(4) + 1) / 10.f, (float)(GetRand(1) + 1.f));
				particle[0]->SetRootLocation(Vector2D(-15, -15));
				break;
			case 2:
			case 6:
				// プレイヤーの位置に煙を出現
				SpawnParticle(4, nullptr, false,
					Vector2D(player->GetLocation().x + 15.f, player->GetLocation().y - 10.f),
					(float)GetRand(30) - 15.f, (GetRand(4) + 1) / 10.f, (float)(GetRand(1) + 1.f));
				particle[0]->SetRootLocation(Vector2D(15, -15));
				break;
			case 3:
			case 7:
				// プレイヤーの位置に煙を出現
				SpawnParticle(4, nullptr, false,
					Vector2D(player->GetLocation().x - 15.f, player->GetLocation().y - 10.f),
					(float)GetRand(30) - 15.f, (GetRand(4) + 1) / 10.f, (float)(GetRand(1) + 1.f));
				particle[0]->SetRootLocation(Vector2D(-15, -15));
				break;
			default:
				break;
			}
		}
		else
		{
			// 炎を表示しない
			particle[0]->SetVisible(false);
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
				if( 0 < life)
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
								// 距離が短いなら変数を保存する(3じゃないとき)
								if (bomb[i]->GetMode() != 3)
								{
									if (length > bomb[j]->GetLength(bomb[i]->GetLocation()))
									{
										temp = j;
										length = bomb[j]->GetLength(bomb[i]->GetLocation());
									}
								}
							}
						}
						// 空ならデータを初期化
						else if (bomb[j] == nullptr)
						{
							temp = -1;
							length = 65535;
						}
					}

					// -1以外なら見る
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
						// 距離が間なら動かない
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
						// 空ならデータを初期化
						else if (bomb[j] == nullptr)
						{
							temp = -1;
							length = 65535;
						}
					}
					// -1以外なら見る
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

					// 距離が間なら動かない
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
						// 次に行く座標をランダム指定
						bomb[i]->SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
					}

					if (fabsf(bomb[i]->GetMoveToLocation().x) - MapSize + 32 > 0 || fabsf(bomb[i]->GetMoveToLocation().y) - MapSize + 32 > 0) {
						// 次に行く座標がマップ外なら再度指定
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
						// 空ならデータを初期化
						else if (bomb[j] == nullptr)
						{
							temp = -1;
							length = 65535;
						}
					}

					// -1以外なら見る
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

					if (length > 16) 
					{
						// プレイヤーと対象の対称に座標指定
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
						// プレイヤーと爆弾のベクトル取得
							vvec = (bomb[i]->GetLocation() - player->GetLocation());
							length = bomb[i]->GetLength(player->GetLocation());
							vvec /= length;

							// 点火してないなら
							if (!bomb[i]->GetExpFlg())
							{
								// プレイヤーの速度*20飛ばす
								bomb[i]->SetKnockBack(vvec, (int)max(5, player->GetNormalSpeed() * 20.0f));
							}

							// 点火しているなら
							else
							{
								// プレイヤーの速度*50飛ばす
								bomb[i]->SetKnockBack(vvec, (int)max(5, player->GetNormalSpeed() * 50.0f));
							}
							// 効果音フラグ立てる
							SE_HitFlg = true;
							// 点火フラグ立てる
							bomb[i]->SetExpFlg(true);
							SpawnParticle(0, nullptr, false, bomb[i]->GetLocation(), 90.0f - Normalize(bomb[i]->GetLocation() , player->GetLocation()), 0.5f, 0.f);
							for (int j = 0; j < 7; j++)
							{
								if (10 >= bomb[i]->hitcheck())
								{
									SpawnParticle(5, nullptr, false, bomb[i]->GetLocation(), (GetRand(60) - 30) - Normalize(bomb[i]->GetLocation(), player->GetLocation()), 0.1f, GetRand(5) + 10.f);
									bomb[i]->hitset();
								}
							}

							SetCameraShake(7);
					}
				}

				// 敵のフラグが0なら
				if (!bomb[i]->GetFlg())
				{
					// 爆発を発生して敵をnullptrにしてループを抜ける
					SpawnExplosion(bomb[i]->GetLocation());
					botime = 8;
					SpawnParticle(3, nullptr, false, bomb[i]->GetLocation(), (float)GetRand(360), C_ExpSize / 6.6667f, 0.f);
					PlaySoundMem(Sounds::SE_Explosion[GetRand(4)], DX_PLAYTYPE_BACK, true);
					combo += 1;
					ui_combo_framecount = 25;
					// スコア加算
					score += (((10 * C_ExpSize) * combo) * (int)(1 + (game_frametime / 3600)));
					SpawnAddScore(bomb[i]->GetLocation(), ((10 * C_ExpSize) * combo));
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
					if (i < MaxSpawnEnemyBomb)
					{
						bomb[i] = new Bomb;
						bomb[i]->Init(C_ExpSize);
						while (1)
						{
							Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
							if (1080 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
								powf((spawnloc.x - player->GetLocation().x), 2) +
								powf((spawnloc.y - player->GetLocation().y), 2))))
							{
								bomb[i]->SetLocation(spawnloc);
								bomb[i]->SetMoveToLocation(spawnloc);
								bomb[i]->SetMode(RandType(GetRand(99)) + 1);
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
					if (player->GetHitFlg() == false)
					{
						life--;
						hitmoment = true;
						player->KnockBack(explosion[i]->GetLocation());

						player->SetHitFlg(true);
						player->SetDamageDirectionFlg(true);

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
						if (explosion[i]->HitSphere(soldier[j]) && soldier[j]->CheckMode() == 1)
						{
							soldier[j]->SetMode(3);
						}
						if (soldier[j]->CheckDLflg() == true)
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
					if (player->GetHitFlg() == false && soldier[i]->CheckMode() == 1)
					{
						life--;
						hitmoment = true;
						player->SetHitFlg(true);
						player->SetHitSoldier(true);
						soldier[i]->SetMode(2);
						for (int c = 0; c < GM_MAX_ENEMY_SOLDIER; c++)
						{
							if (soldier[i] != soldier[c])
							{
								soldier[c]->SetMode(0);
							}
						}

					}
				}
				else if (!soldier[i]->HitSphere(player) && hitmoment == true)
				{
					hitmoment = false;
				}
				if (soldier[i]->CheckDLflg() == true)
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
			if (conveyor[i] != nullptr) {


				conveyor[i]->Update();
				if (conveyor[0]->HitSphere(*player))
				{
					player->SetLocation(Vector2D(player->GetLocation().x + CONVEYOR_SPEED, player->GetLocation().y));

				}
				if (conveyor[1]->HitSphere(*player))
				{
					player->SetLocation(Vector2D(player->GetLocation().x - CONVEYOR_SPEED, player->GetLocation().y));

				}

				for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
				{
					if (bomb[j] != nullptr)
					{
						if (conveyor[0]->HitSphere(*bomb[j]))
						{
							bomb[j]->SetLocation(Vector2D(bomb[j]->GetLocation().x + CONVEYOR_SPEED, bomb[j]->GetLocation().y));
						}
						if (conveyor[1]->HitSphere(*bomb[j]))
						{
							bomb[j]->SetLocation(Vector2D(bomb[j]->GetLocation().x - CONVEYOR_SPEED, bomb[j]->GetLocation().y));
						}
					}
				}
				for (int j = 0; j < GM_MAX_ENEMY_SOLDIER; j++)
				{
					if (soldier[j] != nullptr)
					{
						if (conveyor[0]->HitSphere(*soldier[j]))
						{
							soldier[j]->SetLocation(Vector2D(soldier[j]->GetLocation().x + CONVEYOR_SPEED, soldier[j]->GetLocation().y));
						}
						if (conveyor[1]->HitSphere(*soldier[j]))
						{
							soldier[j]->SetLocation(Vector2D(soldier[j]->GetLocation().x - CONVEYOR_SPEED, soldier[j]->GetLocation().y));
						}
					}
				}
			}
		}

		player->SetConFlg(false);
		for (int i = 0; i < GM_MAX_CONVEYOR_Y; i++)
		{
			conveyor_y[i]->Update();
			if (conveyor_y[0]->HitSphere(*player))
			{
				player->SetLocation(Vector2D(player->GetLocation().x, player->GetLocation().y - CONVEYOR_SPEED));

			}
			if (conveyor_y[1]->HitSphere(*player))
			{
				player->SetLocation(Vector2D(player->GetLocation().x, player->GetLocation().y + CONVEYOR_SPEED));

			}
			

			for (int j = 0; j < GM_MAX_ENEMY_BOMB; j++)
			{
				if (bomb[j] != nullptr) {
					if (conveyor_y[0]->HitSphere(*bomb[j]))
					{
						bomb[j]->SetLocation(Vector2D(bomb[j]->GetLocation().x, bomb[j]->GetLocation().y - CONVEYOR_SPEED));
					}
					if (conveyor_y[1]->HitSphere(*bomb[j]))
					{
						bomb[j]->SetLocation(Vector2D(bomb[j]->GetLocation().x, bomb[j]->GetLocation().y + CONVEYOR_SPEED));
					}
				}
			}
				for (int j = 0; j < GM_MAX_ENEMY_SOLDIER; j++)
				{
				if (soldier[j] != nullptr){
				if (conveyor_y[0]->HitSphere(*soldier[j]))
				{
					soldier[j]->SetLocation(Vector2D(soldier[j]->GetLocation().x, soldier[j]->GetLocation().y - CONVEYOR_SPEED));
				}
				if (conveyor_y[1]->HitSphere(*soldier[j]))
				{
					soldier[j]->SetLocation(Vector2D(soldier[j]->GetLocation().x, soldier[j]->GetLocation().y + CONVEYOR_SPEED));
				}
				}
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
					player->SetVelocity(vvec);
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
						bomb[j]->SetEXVelocity(vvec * 0.8f);
					}
				}
			}
		}

		// スコア表示の更新
		for (int i = 0; i < GM_MAX_ADDSCORE; i++)
		{
			// nullptrじゃないなら見る
			if (addscore[i] != nullptr)
			{
				// 更新処理
				addscore[i]->Update(Camera);

				// フラグがたっていないなら消す
				if (!addscore[i]->GetFlg())
				{
					addscore[i] = nullptr;
					delete addscore[i];
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

				// ここに効果音
				//PlaySoundMem(Sounds::SE_ComboEnd, DX_PLAYTYPE_BACK);
				oldcombo = combo;
				for (int i = 0; i < GM_MAX_COMBOEND; i++)
				{
					if (comboend[i] == nullptr)
					{
						//comboend[i] = new ComboEnd(oldcombo);
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

		if (botime > 0)
		{
			botime--;
		}

		// マップサイズの変更
		ChangeMapSize();

		// マップサイズで敵の最大スポーン数を変える
		MaxSpawnEnemyBomb = (int)(C_MaxEnemyBomb * max(-0.5 + ((MapSize) / (GM_MAX_MAPSIZE)) * 1.5, 0.2));

		// ゲームのフレームを増やす
		game_frametime++;

		Vector2D cDistance;

		bool CameraFlg = false;
		for (int i = 0; i < GM_MAX_EFFECT_EXPLOSION; i++)
		{
			if (explosion[i] != nullptr)
			{

				CameraFlg = true;
				cDistance = Vector2D(explosion[i]->GetLocation().x - Camera.x
									,explosion[i]->GetLocation().y - Camera.y);

				// 爆発-カメラのX座標の長さが元の数値より小さいなら保存
				if (cDistance.x < cMin.x)
				{
					cMin.x = cDistance.x;
				}

				// 爆発-カメラのX座標の長さが元の数値より大きいなら保存
				if (cDistance.x >= cMax.x)
				{
					cMax.x = cDistance.x;
				}

				// 爆発-カメラのY座標の長さが元の数値より小さいなら保存
				if (cDistance.y < cMin.y)
				{
					cMin.y = cDistance.y;
				}

				// 爆発-カメラのY座標の長さが元の数値より大きいなら保存
				if (cDistance.y >= cMax.y)
				{
					cMax.y = cDistance.y;
				}

			}

		}


		if (CameraOutCnt > 0)
		{
			CameraDistance = 0.0f;
			if (cMin.x != 0.0 || cMin.y != 0.0)
			{
				float CameraDistanceTemp = (GetLength(Camera, Camera - cMin) / 1200.0f) * min((CameraOutCnt / 90.0f), 1.0f);
				CameraDistance = CameraDistanceTemp;
			}
			if (cMax.x != 0.0 || cMax.y != 0.0)
			{
				float CameraDistanceTemp = (GetLength(Camera, Camera - cMax) / 1200.0f) * min((CameraOutCnt / 90.0f), 1.0f);
				if (CameraDistance < CameraDistanceTemp)
				{
					CameraDistance = CameraDistanceTemp;
				}
			}
			if (CameraDistance > 1.5f)
			{
				CameraDistance = 1.5f;
			}
			if (cMin.x != 0.0)
			{
				Camera.x += (cMin.x / 2.0f) * min((CameraOutCnt / 90.0f), 1.0f);
			}
			if (cMin.y != 0.0)
			{
				Camera.y += (cMin.y / 2.0f) * min((CameraOutCnt / 90.0f), 1.0f);
			}
			if (cMax.x != 0.0)
			{
				Camera.x += (cMax.x / 2.0f) * min((CameraOutCnt / 90.0f), 1.0f);
			}
			if (cMax.y != 0.0)
			{
				Camera.y += (cMax.y / 2.0f) * min((CameraOutCnt / 90.0f), 1.0f);
			}
			Vector2D qw = (Camera * (float)(1.0f - (CameraDistance / DISTANCE_MAX)));
			Vector2D qw2 = (0 * (float)(CameraDistance / DISTANCE_MAX));
			Camera = qw + qw2;
			
		}
		else
		{
			cMin = 0;
			cMax = 0;
			CameraDistance = 0.0f;
		}
		if (CameraFlg)
		{
			if (CameraOutCnt < 120)
			{
				CameraOutCnt += 5;
			}

		}
		else
		{
			if (CameraOutCnt > 0)
			{
				CameraOutCnt--;
			}
		}
		// カメラアップデート
		CameraUpdate();

		// 残機が0ならプレイヤーフラグをfalseにする
		if (life <= 0)
		{
			player->SetPlayerFlg(false);
		}

	}
	}
	
	// 残機が０になったら
	if (player->GetPlayerFlg() == false && resultflg == false) {
		StopSoundMem(Sounds::BGM_GMain);
		result_cnt++;

		if (result_cnt == 1) {
			// プレイヤーが兵隊に捕まっていなかったら
			if (player->GetHitSoldier() == false)
			{
				crack_alpha = 255;
				soot_alpha = 255;
			}
		}
		if (200 <= result_cnt)
		{
			resultflg = true;
		}

		// リザルトに遷移するまでフェードアウト
		if (result_cnt > 100)
		{
			fadeout_alpha += 3;
		}

	}

	// カウントダウン（３秒）
	if (countdownflg == true && !textdisp->GetFlg())
	{
		cnt++;
		switch (cnt)
		{
		case(1):
		case(60):
		case(120):
			countdown--;
			countsize = 3.0;
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
		cnt++;
		switch (cnt)
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

	// プレイヤーが爆発に当たった かつ ダメージ演出が表示されていなかったら
	if (player->GetIDamageDirectionFlg() == true && crackflg == false)
	{
		crack_alpha = 200;
		soot_alpha = 255 - life * 51;	// 残りライフに応じて薄さを変える
		crackflg = true;
	}

	// ダメージ演出が表示されている かつ プレイヤーが生きていたら
	if (crackflg == true && player->GetPlayerFlg() == true)
	{
		// ダメージ演出を少しずつ薄くする

		if (crack_alpha > 0)
		{
			crack_alpha -= 1;
		}

		if (soot_alpha > 0 && crack_alpha <= soot_alpha)
		{
			soot_alpha -= 1;
		}

		if (crack_alpha == 0)
		{
			crackflg = false;
		}

	}

	// フェードアウト
	if (fadeout_alpha > 0 && resultflg == true)
	{
		fadeout_alpha -= 10;
	}

	// リザルトフラグがたっているなら
	if (resultflg == true)
	{

		if (CheckSoundMem(Sounds::BGM_Title) == 0)
		{
			PlaySoundMem(Sounds::BGM_Title, DX_PLAYTYPE_BACK);
		}

		// 一回だけ動く
		if (!resultnewflg)
		{
			// 最大スコアよりスコアが大きいなら保存する
			if (score > hiscore)
			{
				UserData::SaveData(UserData::Type::HISCORE, 0, (float)score);
				highscoreflg = true;
			}
			resultnewflg = true;
		}
		// Aボタンでタイトルに戻る
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
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
			background[i]->Draw(Camera, CameraDistance);
		}
	}

	//ギミック(氷)
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		// nullptrじゃないなら
		if (stage[i] != nullptr)
		{
			stage[i]->Draw(Camera, CameraDistance);
		}
	}

	//ギミック(コンベア)
	for (int i = 0; i < GM_MAX_CONVEYOR; i++)
	{
		if (conveyor[i] != nullptr)
		{
			conveyor[0]->Draw(Camera, CameraDistance);
			conveyor[1]->Draw_left(Camera, CameraDistance);
		}
	}

	for (int i = 0; i < GM_MAX_CONVEYOR_Y; i++)
	{
			conveyor_y[0]->Draw(Camera, CameraDistance);
			conveyor_y[1]->Draw_up(Camera, CameraDistance);
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
				tornado[i]->Draw(Camera, CameraDistance);
			}
		}
	}

	// マップの範囲
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	float Scale = (float)(1 - ((CameraDistance / DISTANCE_MAX) / DISTANCE_NUM));
	DrawBoxAA((float)((MapSize * Scale) + (-Camera.x + (SCREEN_WIDTH / 2))), (float)(-(MapSize * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2))), (float)((GM_MAX_MAPSIZE * Scale) + (-Camera.x + (SCREEN_WIDTH / 2)) + 16), (float)((MapSize * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2))), 0x000000, true);
	DrawBoxAA((float)(-(MapSize * Scale) + (-Camera.x + (SCREEN_WIDTH / 2))), (float)(-(MapSize * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2))), (float)(-(GM_MAX_MAPSIZE * Scale) + (-Camera.x + (SCREEN_WIDTH / 2)) - 16), (float)((MapSize * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2))), 0x000000, true);
	DrawBoxAA((float)(-(MapSize * Scale) + (-Camera.x + (SCREEN_WIDTH / 2)) - (16 + (GM_MAX_MAPSIZE - MapSize))), (float)((MapSize * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2))), (float)((MapSize * Scale) + (-Camera.x + (SCREEN_WIDTH / 2)) + (16 + (GM_MAX_MAPSIZE - MapSize))), (float)((GM_MAX_MAPSIZE * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2)) + 16), 0x000000, true);
	DrawBoxAA((float)(-(MapSize * Scale) + (-Camera.x + (SCREEN_WIDTH / 2)) - (16 + (GM_MAX_MAPSIZE - MapSize))), (float)(-(MapSize * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2))), (float)((MapSize * Scale) + (-Camera.x + (SCREEN_WIDTH / 2)) + (16 + (GM_MAX_MAPSIZE - MapSize))), (float)(-(GM_MAX_MAPSIZE * Scale) + (-Camera.y + (SCREEN_HEIGHT / 2)) - 16), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 爆弾
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		// nullptrじゃないなら
		if (bomb[i] != nullptr)
		{
			// 画面中なら描画
			if (720 > fabsf(sqrtf(
				powf((bomb[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((bomb[i]->GetLocation().y - player->GetLocation().y), 2))) || CameraOutCnt)
			{
				bomb[i]->Draw(Camera, CameraDistance);
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
				explosion[i]->Draw(Camera, CameraDistance);
			}
		}
	}


	// プレイヤー
	player->Draw(Camera, CameraDistance);

	// 兵士
	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		// nullptrじゃないなら
		if (soldier[i] != nullptr)
		{
			// 画面中なら描画
			if (1720 > fabsf(sqrtf(
				powf((soldier[i]->GetLocation().x - player->GetLocation().x), 2) +
				powf((soldier[i]->GetLocation().y - player->GetLocation().y), 2))))
			{
				soldier[i]->Draw(Camera, CameraDistance);
			}
		}
	}

	// パーティクル
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		// 敵がnullptrじゃないなら
		if (particle[i] != nullptr)
		{
			particle[i]->Draw(Camera, CameraDistance);
		}
	}

	for (int i = 0; i < GM_MAX_ADDSCORE; i++)
	{
		// 敵がnullptrじゃないなら
		if (addscore[i] != nullptr)
		{
			addscore[i]->Draw(Camera, CameraDistance);
		}
	}

	// コンボ
	for (int i = 0; i < GM_MAX_COMBOEND; i++)
	{
		if (comboend[i] != nullptr)
		{
			comboend[i]->Draw();
		}
	}
	DrawCloseMap();

	// 爆弾に当たったときのダメージ演出
	if (crackflg == true || life == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, crack_alpha);
		DrawGraph(0, 0, crackimage, true);	// ヒビ
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, soot_alpha);
		DrawGraph(0, 0, sootimage, true);	// 煤
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}


	DrawRotaGraph(SCREEN_WIDTH - 128, 328, 1.0, 0.0, lifeimage, true);

	//残り体力の表示
	DrawRotaGraph(SCREEN_WIDTH - 128, 328, 1.0, 0.0, lifeimage, true);
	for (int i = 0; i < life; i++)
	{
		DrawRotaGraph(SCREEN_WIDTH - 180 + (24 * i), 360, 1.0, 0.0, lifematchimage, true);
	}
	
	int bcnt = 0;
	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		if (bomb[i] != nullptr)
		{
			bcnt++;
		}
	}

	// ミニマップ
	DrawBox(SCREEN_WIDTH - 128 - 104, 128 - 104, SCREEN_WIDTH - 128 + 104, 128 + 104, 0x004400, true);
	DrawBox(SCREEN_WIDTH - 128 - (GM_MAX_MAPSIZE / 16), 128 - (GM_MAX_MAPSIZE / 16), SCREEN_WIDTH - 128 + (GM_MAX_MAPSIZE / 16), 128 + (GM_MAX_MAPSIZE / 16), 0x8844ff, true);
	DrawBoxAA(SCREEN_WIDTH - 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), SCREEN_WIDTH - 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 0x88ff88, true);


	// ミニマップ(ギミック(氷)
	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		if (stage[i] != nullptr)
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (stage[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (stage[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 8, 8, 0x004488, true);
		}
	}

	//ミニマップ(ギミック(コンベア))
	for (int i = 0; i < GM_MAX_CONVEYOR; i++)
	{
		if (conveyor[i] != nullptr)
		{
			DrawBoxAA(SCREEN_WIDTH - 128 + (conveyor[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
				128 + (conveyor[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
				SCREEN_WIDTH - 128 + (conveyor[i]->GetSize(2) / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
				128 + (conveyor[i]->GetSize(3) / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 0x004488, true);
		}
	}

	for (int i = 0; i < GM_MAX_CONVEYOR_Y; i++)
	{
		if (conveyor_y[i] != nullptr)
		{
			DrawBoxAA(SCREEN_WIDTH - 128 + (conveyor_y[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
				128 + (conveyor_y[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
				SCREEN_WIDTH - 128 + (conveyor_y[i]->GetSize(2) / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
				128 + (conveyor_y[i]->GetSize(3) / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 0x004488, true);
		}
	}
	// ミニマップ(ギミック(竜巻)
	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		if (tornado[i] != nullptr)
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (tornado[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (tornado[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 12, 8, 0x800000, true);
		}
	}

	BlackOutDraw();

	// ミニマップ(プレイヤー)
	DrawCircleAA(SCREEN_WIDTH - 128 + (player->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (player->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2, 8, 0x8888ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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
		if (soldier[i] != nullptr && (soldier[i]->CheckMode() == 1 || soldier[i]->CheckMode() == 0))
		{
			DrawCircleAA(SCREEN_WIDTH - 128 + (soldier[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 128 + (soldier[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 2.5, 8, 0xff0000, true);
		}
	}
	// リザルトじゃないなら
	if (resultflg == false)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(SCREEN_WIDTH - 233, 400, SCREEN_WIDTH - 23, 530, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		char chr_score[] = "score";
		for (int i = 0; i < sizeof(chr_score); i++)
		{
			int chr = chr_score[i] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 190) + 33 * i, 440, 0.6, 0.0, alphabetimage[chr], true);
		}

		if (score == 0)
		{
			DrawRotaGraph(SCREEN_WIDTH - 125, 490, 0.6, 0.0, numimage[0], true);
		}

		//スコアの表示
		int bufscore = score;
		int num = 0;
		while (bufscore > 0)
		{
			num++;
			bufscore /= 10;
		}
		bufscore = score;
		for (int s = 0; s < num; s++)
		{
			DrawRotaGraph((SCREEN_WIDTH - 140 + (26 * num) / 2) - (26 * s), 490, 0.6, 0.0, numimage[bufscore % 10], true);
			bufscore /= 10;
		}

	}
	// リザルトなら
	else
	{
		DrawGraph(0, 0, blackimage, false);

		// ハイスコアだったら
		if (highscoreflg == true)
		{
			DrawGraph(0, 0, highscoreimage, true);
			char newrecord[] = "new record";
			for (int ne = 0; ne < sizeof(newrecord); ne++)
			{
				int chr = newrecord[ne] - 'a';
				SetDrawBright(255, 255, 0);
				DrawRotaGraph((SCREEN_WIDTH - 360) + 18 * ne, 220, 0.4, 0.0, alphabetimage[chr], true);
				SetDrawBright(255, 255, 255);
			}
		}
		else {
			DrawGraph(0, 0, resultimage, true);
		}

		char result[] = "result\0";
		for (int re = 0; re < sizeof(result); re++)
		{
			int chr = result[re] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 400) + 50 * re, 150, 1.0, 0.0, alphabetimage[chr], true);
		}
		char highscore[] = "high score";
		for (int hi = 0; hi < sizeof(highscore); hi++)
		{
			int chr = highscore[hi] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 360) + 20 * hi, 390, 0.5, 0.0, alphabetimage[chr], true);
		}
		char press[] = "press a";
		for (int pr = 0; pr < sizeof(press); pr++)
		{
			int chr = press[pr] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 340) + 22 * pr, 580, 0.6, 0.0, alphabetimage[chr], true);
		}

		int bufhiscore = hiscore;
		int hi_num = 0;
		while (bufhiscore > 0)
		{
			hi_num++;
			bufhiscore /= 10;
		}
		bufhiscore = hiscore;
		for (int h = 0; h < hi_num; h++)
		{
			DrawRotaGraph((SCREEN_WIDTH - 290 + (28 * hi_num) / 2) - (28 * h), 440, 0.6, 0.0, numimage[bufhiscore % 10], true);
			bufhiscore /= 10;
		}

		int bufscore = score;
		int num = 0;
		while (bufscore > 0)
		{
			num++;
			bufscore /= 10;
		}
		bufscore = score;
		for (int s = 0; s < num; s++)
		{
			DrawRotaGraph((SCREEN_WIDTH - 300 + (40 * num) / 2) - (40 * s), 270, 1.0, 0.0, numimage[bufscore % 10], true);
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
		char start[] = "start";
		for (int i = 0; i < sizeof(start); i++)
		{
			int chr = start[i] - 'a';
			DrawRotaGraph((SCREEN_WIDTH - 750) + 56 * i, 270, countsize, 0.0, alphabetimage[chr], true);
		}
	}

	textdisp->Draw();
	if (PauseFlg)
	{
		DrawPause();
	}


	// フェードアウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeout_alpha);
	DrawGraph(0, 0, blackimage, false);
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
			explosion[i]->Init(C_ExpSize);
			explosion[i]->SetLocation(loc);
			break;
		}
	}
}

// パーティクルのスポーン(種類、親、ループ可か、スポーン座標、向く座標、大きさ
int GameMain::SpawnParticle(int type, SphereCollider* root, bool loop, Vector2D loc, float angle, float scale, float speed)
{
	int num = -1;
	for (int j = 0; j < GM_MAX_PARTICLE; j++)
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
			particle[j]->SetAngle(angle);
			particle[j]->SetSpeed(speed);
			num = j;
			break;
		}
	}
	return num;
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
	if (game_frametime % 1200 > 900 && game_frametime % 1200 <= 1100)
	{
		if (game_frametime % 1200 == 901)
		{
			PlaySoundMem(Sounds::SE_MapClose, DX_PLAYTYPE_BACK);
			for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
			{
				// 敵がnullptrじゃないなら
				if (bomb[i] != nullptr)
				{
					bomb[i]->SetMode(RandType(GetRand(99)) + 1);
				}
			}
		}
		if (MapSize > GM_MIN_MAPSIZE)
		{
			SetMapSize(MapSize - 0.5f);

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

void GameMain::DrawCloseMap() const
{
	int OldDrawMode;
	int OldDrawParam;
	GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (game_frametime % 100) * 4);
	char res[] = "area closing\0";
	
	if (MapSize > GM_MIN_MAPSIZE)
	{
		if (game_frametime % 1200 > 800 && game_frametime % 1200 <= 900)
		{
			for (int i = 0; i < sizeof(res); i++)
			{
				//+(20 * (digit - 2)) - (i * 20)
				int chr = res[i] - 'a';
				DrawRotaGraph((SCREEN_WIDTH / 2) - (32 * (((sizeof(res) - 2) / 2))) + (i * 32) + GetRand(3) - 2, (SCREEN_HEIGHT / 2) - 120, 0.8, 0.0, alphabetimage[chr], true);
			}
			DrawBoxAA((SCREEN_WIDTH / 2) - 105, (SCREEN_HEIGHT / 2) - 85,
				(SCREEN_WIDTH / 2) + 105, (SCREEN_HEIGHT / 2) - 65, 0x000000, true);
			DrawBoxAA((SCREEN_WIDTH / 2) - (float)(game_frametime % 100) + 100, (SCREEN_HEIGHT / 2) - 80,
				(SCREEN_WIDTH / 2) + (float)(game_frametime % 100) - 100, (SCREEN_HEIGHT / 2) - 70, 0xffffff, true);
		}
	}
	SetDrawBlendMode(OldDrawMode, OldDrawParam);
}

// スコア増加画像のスポーン
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

void GameMain::BlackOutDraw() const
{
	int OldDrawMode;
	int OldDrawParam;
	GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)max(((botime / 8.) * 63.), 0));
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xffffff, true);
	SetDrawBlendMode(OldDrawMode, OldDrawParam);
}

void GameMain::DrawPause() const
{
	char res[] = "pause\0";

	for (int i = 0; i < sizeof(res); i++)
	{
		//+(20 * (digit - 2)) - (i * 20)
		int chr = res[i] - 'a';
		DrawRotaGraph((SCREEN_WIDTH / 2) - (80 * (((sizeof(res) - 2) / 2))) + (i * 80), (SCREEN_HEIGHT / 2) - 120, 1.6, 0.0, alphabetimage[chr], true);
	}
}