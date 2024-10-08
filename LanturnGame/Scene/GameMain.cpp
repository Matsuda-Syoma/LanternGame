﻿#include "GameMain.h"
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
	//ComboEnd::LoadImages();
	AddScore::LoadImages();

	// ハイスコア読み込み
	hiscore = (int)UserData::LoadData(UserData::Type::HISCORE);		// ハイスコア読み込み

	
	/*******************初期化*******************/
	textdisp = new TextDisp;
	textdisp->LoadText(0);
	description = new Description;

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

	//// パーティクルの初期化
	particle = new Particle * [GM_MAX_PARTICLE];
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		particle[i] = nullptr;
	}


	CreateObject(new Player);

	for (int i = 0; i < GM_MAX_ENEMY_BOMB; i++)
	{
		int temp = CreateObject(new Bomb);
		static_cast<CharaBase*>(object[temp])->SpawnEvent();
		Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
		object[temp]->SetLocation(spawnloc);
	}

	for (int i = 0; i < GM_MAX_ENEMY_SOLDIER; i++)
	{
		int temp = CreateObject(new Soldier);
		//static_cast<CharaBase*>(object[temp])->SpawnEvent();
		Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
		object[temp]->SetLocation(spawnloc);
	}

	int gimmicknum = 0;

	for (int i = 0; i < GM_MAX_TORNADO; i++)
	{
		int temp = CreateObject(new Tornado);
		Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
		object[temp]->SetLocation(spawnloc);
		gimmicknum++;
	}

	for (int i = 0; i < GM_MAX_ICEFLOOR; i++)
	{
		int temp = CreateObject(new Stage);
		Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
		object[temp]->SetLocation(spawnloc);
		gimmicknum++;
	}

	for (int i = 0; i < GM_MAX_CONVEYOR; i++)
	{
		int temp = CreateObject(new Conveyor);
		Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 1.5) - MapSize, (float)GetRand((int)MapSize * 1.5) - MapSize));
		object[temp]->SetLocation(spawnloc);
		gimmicknum++;
	}

	for (int i = 0; i < gimmicknum; i++)
	{
	}

	camera = new CameraManager();


	if (particle[0] != nullptr)
	{
		particle[0]->SetVisible(false);
	}

	/*******************画像読み込み*******************/
	lifeimage[0] = LoadGraph("Resources/images/life0.png", 0);
	lifeimage[1] = LoadGraph("Resources/images/life1.png", 0);
	lifeimage[2] = LoadGraph("Resources/images/life2.png", 0);
	lifeimage[3] = LoadGraph("Resources/images/life3.png", 0);
	lifeimage[4] = LoadGraph("Resources/images/life4.png", 0);
	//lifeimage = LoadGraph("Resources/images/lifebar.png", 0);
	lifematchimage = LoadGraph("Resources/images/match.png", 0);
	lifematchimage_2 = LoadGraph("Resources/images/match_2.png", 0);
	closemapimage = LoadGraph("Resources/images/warning.png", 0);
	hukidasiimage = LoadGraph("Resources/images/hukidasi.png", 0);
	LoadDivGraph("Resources/images/number.png", 10, 10, 1, 64, 64, numimage);
	//LoadDivGraph("Resources/images/alphabet_2.png", 26, 7, 4, 64, 64, alphabetimage);
	LoadDivGraph("Resources/images/alphabet.png", 26, 6, 5, 64, 64, alphabetimage);
	resultimage = LoadGraph("Resources/images/result.png", 0);
	highscoreimage = LoadGraph("Resources/images/result.png", 0);
	//highscoreimage = LoadGraph("Resources/images/highscore.png", 0);
	blackimage = LoadGraph("Resources/images/black.png", 0);
	crackimage = LoadGraph("Resources/images/crack1.png", 0);
	sootimage = LoadGraph("Resources/images/soot.png", 0);
	
}

// デストラクタ
GameMain::~GameMain()
{

}

/********************ゲームの更新処理********************/
AbstractScene* GameMain::Update()
{
	//// 文字の表示
	textdisp->Update();

	// BGMをループしながら再生する
	if (CheckSoundMem(Sounds::BGM_GMain) == 0)
	{
		PlaySoundMem(Sounds::BGM_GMain, DX_PLAYTYPE_BACK);
	}
	//操作方法の説明画像の描画
	description->Update();

	//// リザルトじゃない かつ カウントダウンが終わっているとき
	if (resultflg == false && !textdisp->GetFlg() && countdownflg == false) 
	{

		//	// マップサイズの変更
		ChangeMapSize();

		//	// マップサイズで敵の最大スポーン数を変える
		MaxSpawnEnemyBomb = (int)(C_MaxEnemyBomb * max(-0.5 + ((MapSize) / (GM_MAX_MAPSIZE)) * 1.5, 0.2));

		//	// ゲームのフレームを増やす
		game_frametime++;

		// 残機が０になったら
		if (static_cast<Player*>(GetPlayer())->GetPlayerFlg() == false && resultflg == false) {
			StopSoundMem(Sounds::BGM_GMain);
			result_cnt++;

			if (result_cnt == 1) {
				// プレイヤーが兵隊に捕まっていなかったら
				if (static_cast<Player*>(GetPlayer())->GetHitSoldier() == false)
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



		//////////// オブジェクトの処理 ////////////

		for (int i = 0; i < GM_MAX_OBJECT; i++)
		{
			if (object[i] != nullptr)
			{
				object[i]->Update(this);
				if (object[i] == nullptr)
				{
					continue;
				}
				for (int j = 0; j < GM_MAX_OBJECT; j++)
				{
					if (object[j] != nullptr)
					{
						if (!object[j]->GetBoxCol())
						{
							if (i != j && object[i]->SphereCollider::HitSphere(object[j]))
							{
								object[i]->Hit(object[j]);
								object[j]->Hit(object[i]);
							}
						}
						if (object[j]->GetBoxCol())
						{
							if (i != j && object[i]->SphereCollider::HitBox(*object[j]))
							{
								object[i]->Hit(object[j]);
								object[j]->Hit(object[i]);
							}
						}
					}
				}
			}
		}

		// オブジェクトがあるか確認
		comboflg = false;
		for (int i = 0; i < GM_MAX_OBJECT; i++)
		{
			if (object[i] != nullptr)
			{
				// 爆発の確認
				if (object[i]->GetType() == Object::TYPE::_EXPLOSION)
				{
					comboflg = true;
					camera->SetInOutFlg(true);
					camera->SetObjectDistance(object[i]->GetLocation(), 0);
				}
			}
		}

		if (comboflg)
		{


		}
		else
		{
			camera->SetInOutFlg(false);
			combocount = 0;
			int bombcnt = 0;
			int soldercnt = 0;
			for (int i = 0; i < GM_MAX_OBJECT; i++)
			{
				if (object[i] != nullptr)
				{
					// 爆弾の確認
					if (object[i]->GetType() == Object::TYPE::_BOMB)
					{
						bombcnt++;
					}

					// 兵隊の確認
					if (object[i]->GetType() == Object::TYPE::_SOLDIER)
					{
						soldercnt++;
					}
				}
			}
			for (int i = 0; i < GM_MAX_ENEMY_BOMB - bombcnt; i++)
			{
				int temp = CreateObject(new Bomb);
				static_cast<CharaBase*>(object[temp])->SpawnEvent();
				Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
				object[temp]->SetLocation(spawnloc);

			}

			for (int i = 0; i < GM_MAX_ENEMY_SOLDIER - soldercnt; i++)
			{
				int temp = CreateObject(new Soldier);
				Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
				object[temp]->SetLocation(spawnloc);

			}
		}

		//////////// パーティクルの処理 ////////////

		for (int i = 0; i < GM_MAX_PARTICLE; i++)
		{
			// パーティクルがnullptrじゃないなら
			if (particle[i] != nullptr)
			{
				particle[i]->Update(this);
			}
		}


		if (scoresize > 0.6)
		{
			scoresize -= 0.02;
		}
	}

	//////////// スタートの処理 ////////////

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

	// フェードアウト
	if (fadeout_alpha > 0 && resultflg == true)
	{
		fadeout_alpha -= 10;
	}

	// リザルトフラグがたっているなら
	if (resultflg == true)
	{
		StopSoundMem(Sounds::BGM_GMain);

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

	camera->Update(this);
	return this;

}

void GameMain::Draw() const
{
	// 背景
	for (int i = 0; i < (int)pow((int)ceil(GM_MAX_MAPSIZE / 64.f) * 2, 2); i++)
	{
		if (background[i] != nullptr)
		{
			background[i]->Draw(camera);
		}
	}

	// マップの範囲
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	float Scale = (float)(1 - ((camera->GetDistance() / DISTANCE_MAX) / 1.385));
	DrawBoxAA((float)((MapSize * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))), (float)(-(MapSize * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))), (float)((GM_MAX_MAPSIZE * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + 16), (float)((MapSize * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))), 0x000000, true);
	DrawBoxAA((float)(-(MapSize * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))), (float)(-(MapSize * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))), (float)(-(GM_MAX_MAPSIZE * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) - 16), (float)((MapSize * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))), 0x000000, true);
	DrawBoxAA((float)(-(MapSize * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) - (16 + (GM_MAX_MAPSIZE - MapSize))), (float)((MapSize * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))), (float)((MapSize * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + (16 + (GM_MAX_MAPSIZE - MapSize))), (float)((GM_MAX_MAPSIZE * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) + 16), 0x000000, true);
	DrawBoxAA((float)(-(MapSize * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) - (16 + (GM_MAX_MAPSIZE - MapSize))), (float)(-(MapSize * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))), (float)((MapSize * Scale) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + (16 + (GM_MAX_MAPSIZE - MapSize))), (float)(-(GM_MAX_MAPSIZE * Scale) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) - 16), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawCloseMap();

	for (int i = 0; i < GM_MAX_OBJECT; i++)
	{
		if (object[i] != nullptr)
		{
			switch (object[i]->GetType())
			{
			case Object::TYPE::_TORNADO:
			case Object::TYPE::_ICEFLOOR:
			case Object::TYPE::_CONVEYER:
				object[i]->Draw(camera);
				break;
			default:
				break;
			}
		}
	}
	
	for (int i = 0; i < GM_MAX_OBJECT; i++)
	{
		if (object[i] != nullptr)
		{
			switch (object[i]->GetType())
			{
			case Object::TYPE::_BOMB:
			case Object::TYPE::_EXPLOSION:
			case Object::TYPE::_SOLDIER:
			case Object::TYPE::_ADDSCORE:
				object[i]->Draw(camera);
				break;
			default:
				break;
			}
		}
	}


	object[0]->Draw(camera);

	//残り体力の表示
	DrawRotaGraph(SCREEN_WIDTH - 128, 328, 1.0, 0.0, lifeimage[life], true);

	// パーティクル
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		// nullptrじゃないなら
		if (particle[i] != nullptr)
		{
			particle[i]->Draw(camera);
		}
	}

	//ミニマップ
	DrawBox(SCREEN_WIDTH - 128 - 104, 128 - 104, SCREEN_WIDTH - 128 + 104, 128 + 104, 0x004400, true);
	DrawBox(SCREEN_WIDTH - 128 - (GM_MAX_MAPSIZE / 16), 128 - (GM_MAX_MAPSIZE / 16), SCREEN_WIDTH - 128 + (GM_MAX_MAPSIZE / 16), 128 + (GM_MAX_MAPSIZE / 16), 0x8844ff, true);
	DrawBoxAA(SCREEN_WIDTH - 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 - ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), SCREEN_WIDTH - 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 128 + ((GM_MAX_MAPSIZE / 16) * (MapSize / GM_MAX_MAPSIZE)), 0x88ff88, true);

	for (int i = 0; i < GM_MAX_OBJECT; i++)
	{
		if (object[i] != nullptr)
		{
			if (object[i]->GetType() != Object::TYPE::_ADDSCORE && object[i]->GetType() != Object::TYPE::_CONVEYER)
			{
				DrawCircleAA(SCREEN_WIDTH - 128 + (object[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16)))
										  , 128 + (object[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), object[i]->GetMapRadius() / 16, 8
										  , object[i]->GetMapColor(), true);

			}
			if (object[i]->GetType() == Object::TYPE::_CONVEYER)
			{
				DrawBoxAA(SCREEN_WIDTH - 128 + (object[i]->GetLocation().x / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
										 128 + (object[i]->GetLocation().y / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
						  SCREEN_WIDTH - 128 + ((object[i]->GetLocation().x + static_cast<Conveyor*>(object[i])->GetScale().x) / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))),
										 128 + ((object[i]->GetLocation().y + static_cast<Conveyor*>(object[i])->GetScale().y) / (GM_MAX_MAPSIZE / (GM_MAX_MAPSIZE / 16))), 0x004488, true);
			}
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
			DrawRotaGraph((SCREEN_WIDTH - 195) + 33 * i, 440, 0.8, 0.0, alphabetimage[chr], true);
		}

		if (score == 0)
		{
			// 描画輝度を黄色にセット
			SetDrawBright(255, 255, 0);
			DrawRotaGraph(SCREEN_WIDTH - 125, 490, 0.6, 0.0, numimage[0], true);
			SetDrawBright(255, 255, 255);
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
			// 描画輝度を黄色にセット
			SetDrawBright(255, 255, 0);
			DrawRotaGraph((SCREEN_WIDTH - 140 + (26 * num) / 2) - (26 * s), 490, scoresize, 0.0, numimage[bufscore % 10], true);
			SetDrawBright(255, 255, 255);

			bufscore /= 10;
		}

		//ゲームが始まる前
		if (textdisp->GetFlg())
		{
			textdisp->Draw();
			//description->Draw();
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

	// フェードアウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeout_alpha);
	DrawGraph(0, 0, blackimage, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	

}

void GameMain::Game()
{
}

// パーティクルのスポーン(種類、親、ループ可か、スポーン座標、向く座標、大きさ
int GameMain::CreateParticle(int type)
{
	int num = -1;
	for (int j = 0; j < GM_MAX_PARTICLE; j++)
	{
		if (particle[j] == nullptr)
		{
			particle[j] = new Particle();
			particle[j]->Init(type, j);
			particle[j]->SetRoot(nullptr);
			particle[j]->SetLoop(false);
			particle[j]->SetScale(1.0f);
			particle[j]->SetLocation(0.0f);
			particle[j]->SetAngle(0.0f);
			particle[j]->SetSpeed(0.0f);
			num = j;
			break;
		}
	}
	return num;
}

Particle* GameMain::GetParticle(int _num)
{
	return particle[_num];
}

void GameMain::DeleteParticle(Particle* _particle, int _pos)
{
	if (particle[_pos] != nullptr && _particle != nullptr && _pos >= 0)
	{
		particle[_pos] = nullptr;
		delete particle[_pos];
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

float GameMain::GetMapSize() const
{
	return MapSize;
}

void GameMain::ChangeMapSize()
{
	if (game_frametime % 1200 > 900 && game_frametime % 1200 <= 1100)
	{
		if (game_frametime % 1200 == 901)
		{
			PlaySoundMem(Sounds::SE_MapClose, DX_PLAYTYPE_BACK);
			for (int i = 0; i < GM_MAX_OBJECT; i++)
			{
				if (object[i] != nullptr)
				{
					if (object[i]->GetType() == Object::TYPE::_BOMB)
					{
						static_cast<Bomb*>(object[i])->SetMode(RandType(GetRand(99)) + 1);
					}
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

int GameMain::CreateObject(Object* _object)
{
	for (int i = 0; i < GM_MAX_OBJECT; i++)
	{
		//空いている場所に格納する
		if (object[i] == nullptr)
		{
			object[i] = _object;

			object[i]->Initialize(this, i);
			return i;
			break;
		}
	}
	return -1;
}

void GameMain::DeleteObject(Object* _object, int _pos)
{
	if (object[_pos] != nullptr && _object != nullptr && _pos >= 0)
	{
		object[_pos] = nullptr;
		delete object[_pos];
	}
}

Object* GameMain::GetObject(int _pos)
{
	return object[_pos];
}

Object* GameMain::GetPlayer()
{
	if (object[0] != nullptr)
	{
		return object[0];
	}
	return nullptr;
}

CameraManager* GameMain::GetCamera()
{
	return camera;
}

void GameMain::AddLife(int i)
{
	life += i;
}

int GameMain::GetLife()const
{
	return life;
}

void GameMain::AddGameScore(int i)
{
	score += i;
	scoresize = 0.8;
}

void GameMain::AddCombo(int i)
{
	combocount += i;
}

int GameMain::GetComboCount()const
{
	return combocount;
}

void GameMain::SetResultFlg(bool b)
{
	resultflg = b;
}