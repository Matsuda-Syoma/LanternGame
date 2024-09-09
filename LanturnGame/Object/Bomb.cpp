#include "Bomb.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include <math.h>
#include "../Scene/GameMain.h"
#include "CameraManager.h"
#include "../Utility/LoadSounds.h"
int Bomb::images[3];
Bomb::Bomb()
{
	type = (int)TYPE::_BOMB;
	speed = 1;
	HitCheck = true;
}
Bomb::~Bomb()
{
}
void Bomb::Initialize(GameMain* _g, int _obj_pos)
{
	CharaBase::Initialize(_g, _obj_pos);

	mode = RandType(GetRand(99)) + 1;
}
void Bomb::Finalize()
{
}
void Bomb::Hit(Object* _obj)
{
	if (static_cast<Object*>(_obj)->GetType() == TYPE::_PLAYER)
	{
		// プレイヤーと爆弾のベクトル取得
		Vector2D vvec = (GetLocation() - _obj->GetLocation());
		float length = GetLength(_obj->GetLocation());
		vvec /= length;

		//触れた瞬間SEを鳴らす
		PlaySoundMem(Sounds::BGM_GMain, DX_PLAYTYPE_BACK);

		// 点火してないなら
		if (!GetExpFlg())
		{
			// プレイヤーの速度*20飛ばす
			SetKnockBack(vvec, (int)max(5, static_cast<Player*>(_obj)->GetNormalSpeed() * 20.0f));
		}

		// 点火しているなら
		else
		{
			// プレイヤーの速度*50飛ばす
			SetKnockBack(vvec, (int)max(5, static_cast<Player*>(_obj)->GetNormalSpeed() * 50.0f));
		}
		// SpawnParticle(0, nullptr, false, bomb[i]->GetLocation(), 90.0f - Normalize(bomb[i]->
		//GetLocation(), player->GetLocation()), 0.5f, 0.f);
		int pt = gamemain->CreateParticle(0);
		gamemain->GetParticle(pt)->SetLocation(location);
		gamemain->GetParticle(pt)->SetAngle(90.0f - Normalize(location, gamemain->GetPlayer()->GetLocation()));
		gamemain->GetParticle(pt)->SetScale(0.5f);

		gamemain->GetCamera()->SetCameraShake(vvec, 1, 10);
		// 点火フラグ立てる
		SetExpFlg(true);
		// 効果音フラグ立てる
		//SE_HitFlg = true;
		//SpawnParticle(0, nullptr, false, bomb[i]->GetLocation(), 90.0f - Normalize(bomb[i]->GetLocation() , player->GetLocation()), 0.5f, 0.f);
		//for (int j = 0; j < 7; j++)
		//{
		//	if (10 >= bomb[i]->hitcheck())
		//	{
		//		SpawnParticle(5, nullptr, false, bomb[i]->GetLocation(), (GetRand(60) - 30) - Normalize(bomb[i]->GetLocation(), player->GetLocation()), 0.1f, GetRand(5) + 10.f);
		//		bomb[i]->hitset();
		//	}
		//}
		//SetCameraShake(7);
	}

	if (static_cast<Object*>(_obj)->GetType() == TYPE::_EXPLOSION)
	{
		flg = false;
	}
	if (static_cast<Tornado*>(_obj)->GetType() == TYPE::_TORNADO)
	{
		float length = GetLength(static_cast<Object*>(_obj)->GetLocation() - GetLocation());
		Vector2D vvec = (static_cast<Object*>(_obj)->GetLocation() - GetLocation());
		vvec /= length;
		SetEXVelocity(vvec * 3.8f);

	}
}
void Bomb::Init(int _expsize)
{
	expsize = _expsize;
}
void Bomb::Update(GameMain* _g)
{
	MapSize = _g->GetMapSize();
	// 敵と敵の距離を見る
	int temp = -1;
	float length = 65535;
	Vector2D vvec = 0;

		// 敵の数を見る
		//SE_HitFlg = false;
	for (int i = 0; i < GM_MAX_OBJECT; i++)
	{
		// 敵がnullptrじゃないなら
		if (_g->GetObjectA(i) != nullptr)
		{
			// 自分以外なら
			if (_g->GetObjectA(i) != this)
			{
				// 自分と同じオブジェクトなら
				if (_g->GetObjectA(i)->GetType() == (TYPE)type)
				{
					// 3以外なら
					if (GetMode() != 3)
					{
						// 距離を測る
						if (length > _g->GetObjectA(i)->GetLength(GetLocation()))
						{
							temp = i;
							length = _g->GetObjectA(i)->GetLength(GetLocation());
						}
					}
				}
			}
			// 空ならデータを初期化
			else if (_g->GetObjectA(i) == nullptr)
			{
				temp = -1;
				length = 65535;
			}
		}
	}
	switch (mode)
	{
	case 0:
		break;

		// 敵同士集まる
	case 1:

		// -1以外なら見る
		if (temp != -1)
		{
			// 距離が長いなら
			if (length > 80)
			{
				vvec = (_g->GetObjectA(temp)->GetLocation() - GetLocation());
				vvec /= length;
				SetVelocity(vvec);
			}

			// 距離が近いなら
			else if (length < 72)
			{
				vvec = (GetLocation() - _g->GetObjectA(temp)->GetLocation());
				vvec /= length;
				SetVelocity(vvec);
			}
			// 距離が間なら動かない
			else
			{
				SetVelocity(NULL);
			}
		}
		break;

		// プレイヤーから逃げる
	case 2:
		length = GetLength(_g->GetPlayer()->GetLocation());
		vvec = (GetLocation() - _g->GetPlayer()->GetLocation());
		vvec /= length;
		SetVelocity(vvec);
		break;

		// プレイヤーを追いかける
	case 3:
		// -1以外なら見る
		if (temp != -1)
		{
			// 距離が近いなら
			if (length < 72) {
				vvec = (GetLocation() - _g->GetObjectA(temp)->GetLocation());
				vvec /= length;
				SetVelocity(vvec);
			}
		}
		length = GetLength(_g->GetPlayer()->GetLocation());
		if (length > 80) {
			vvec = (_g->GetPlayer()->GetLocation() - GetLocation());
			vvec /= length;
			SetVelocity(vvec);
		}

		// 距離が間なら動かない
		else
		{
			SetVelocity(NULL);
		}
		break;

		// ランダム移動
	case 4:
		length = GetLength(GetMoveToLocation());
		if (length > 16) {
			vvec = (GetMoveToLocation() - GetLocation());
			vvec /= length;
			SetVelocity(vvec);
		}
		else
		{
			// 次に行く座標をランダム指定
			SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
		}

		if (fabsf(GetMoveToLocation().x) - MapSize + 32 > 0 || fabsf(GetMoveToLocation().y) - MapSize + 32 > 0) {
			// 次に行く座標がマップ外なら再度指定
			SetMoveToLocation(Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
		}
		break;

		// プレイヤーと対称の動き
	case 5:
		// -1以外なら見る
		if (temp != -1)
		{
			// 距離が近いなら
			if (length < 72)
			{
				vvec = (GetLocation() - _g->GetObjectA(temp)->GetLocation());
				vvec /= length;
				SetVelocity(vvec);
			}
		}

		length = GetLength(_g->GetPlayer()->GetLocation() * -1);

		if (length > 16)
		{
			// プレイヤーと対象の対称に座標指定
			SetMoveToLocation(_g->GetPlayer()->GetLocation() * -1);
			vvec = (GetMoveToLocation() - GetLocation());
			vvec /= length;
			SetVelocity(vvec);

		}
		else
		{
			SetVelocity(NULL);
		}
		break;

	default:
		break;
	}

	//			// 敵のフラグが0なら
	//			if (!bomb[i]->GetFlg())
	//			{
	//				// 爆発を発生して敵をnullptrにしてループを抜ける
	//				SpawnExplosion(bomb[i]->GetLocation());
	//				botime = 8;
	//				SpawnParticle(3, nullptr, false, bomb[i]->GetLocation(), (float)GetRand(360), C_ExpSize / 6.6667f, 0.f);
	//				PlaySoundMem(Sounds::SE_Explosion[GetRand(4)], DX_PLAYTYPE_BACK, true);
	//				combo += 1;
	//				ui_combo_framecount = 25;
	//				// スコア加算
	//				score += (((10 * C_ExpSize) * combo) * (int)(1 + (game_frametime / 3600)));
	//				SpawnAddScore(bomb[i]->GetLocation(), ((10 * C_ExpSize) * combo));
	//				SetCameraShake(GetRand(8) + 4);
	//				bomb[i] = nullptr;
	//				delete bomb[i];
	//				continue;
	//			}
	//		}

	//		// スポーン仮
	//		else
	//		{
	//			if (!comboflg)
	//			{
	//				if (i < MaxSpawnEnemyBomb)
	//				{
	//					bomb[i] = new Bomb;
	//					bomb[i]->Init(C_ExpSize);
	//					while (1)
	//					{
	//						Vector2D spawnloc = (Vector2D((float)GetRand((int)MapSize * 2) - MapSize, (float)GetRand((int)MapSize * 2) - MapSize));
	//						if (1080 * (MapSize / GM_MAX_MAPSIZE) < fabsf(sqrtf(
	//							powf((spawnloc.x - player->GetLocation().x), 2) +
	//							powf((spawnloc.y - player->GetLocation().y), 2))))
	//						{
	//							bomb[i]->SetLocation(spawnloc);
	//							bomb[i]->SetMoveToLocation(spawnloc);
	//							bomb[i]->SetMode(RandType(GetRand(99)) + 1);
	//							break;
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}

	// 点火しているなら
	if (expflg)
	{
		// 速度を変更
		speed = 1.5;
		// 生存時間を下げる
		expcnt--;
		// 0以下になればフラグを切る
		if (expcnt < 0)
		{
			flg = false;
			
		}
	}

	// 爆発処理
	if (!flg)
	{
		int exptemp = gamemain->CreateObject(new Explosion);
		gamemain->GetObjectA(exptemp)->SetLocation(location);

		int pt = gamemain->CreateParticle(3);
		gamemain->GetParticle(pt)->SetLocation(location);
		gamemain->GetParticle(pt)->SetAngle((float)GetRand(360));
		gamemain->GetParticle(pt)->SetScale(8 / 6.6667f);

		gamemain->GetCamera()->SetCameraShake((float)GetRand(360), 10, 5);

		exptemp = gamemain->CreateObject(new AddScore);
		gamemain->GetObjectA(exptemp)->SetLocation(location);
		gamemain->AddCombo(1);
		static_cast<AddScore*>(gamemain->GetObjectA(exptemp))->SetScore(100 * gamemain->GetComboCount());

		gamemain->DeleteObject(this, obj_pos);
	}

	// ノックバックの速度を徐々に遅くする
	if (knockback != 0.0f)
	{
		knockback /= 1.1f;
	}

	// locationに座標を足す
	location += velocity * speed;
	location += knockback;
	location += exvelocity;

	exvelocity = 0.0f;

	// マップ外に出ないようにします
	if (location.x < -MapSize + radius)
	{
		location.x = -MapSize + radius;
	}
	if (location.x >= MapSize - radius)
	{
		location.x = MapSize - radius;
	}
	if (location.y < -MapSize + radius)
	{
		location.y = -MapSize + radius;
	}
	if (location.y >= MapSize - radius)
	{
		location.y = MapSize - radius;
	}
}

void Bomb::Draw(CameraManager* camera) const
{

	// 生存時間が14のあまり7以下なら
	if (expcnt % 14 > 7 && expflg)
	{
		SetDrawBright(255, 0, 0);// 赤以外を暗くする
	}


	int imgnum = 0;

	// 点火しているなら
	if (expflg)
	{
		int OldDrawMode;
		int OldDrawParam;
		GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 63);
		// Alpha値63の爆発範囲の円を描画
		//DrawCircleAA(DrawFromCameraX(location, _distance, loc)
		//	, DrawFromCameraY(location, _distance, loc)
		//	, (15 * (expsize - 2)) * ScaleFromCamera(_distance), 16, 0xffffff, false, 10 * ScaleFromCamera(_distance));
		DrawCircleAA(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
					,location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
					,(15 * (expsize - 2)) * (1 - (camera->GetDistance())), 16, 0xffffff, false, 10 * (1 - (camera->GetDistance() * 2)));
		SetDrawBlendMode(OldDrawMode, OldDrawParam);
		imgnum = 2;
	}

	

	// 敵画像を描画
	DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
				,  location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
				,  (1.0f + (double)(max(45 - expcnt, 0) / 45.0)) * (1 - ((camera->GetDistance() / DISTANCE_NUM) / 1.0f)), 0.0, images[imgnum], true);
	
	SetDrawBright(255, 255, 255);// 全色暗くしない（デフォルト）
}

bool Bomb::GetFlg() const
{
	return flg;
}

void Bomb::SetFlg(bool b)
{
	this->flg = b;
}

bool Bomb::GetExpFlg() const
{
	return this->expflg;
}

void Bomb::SetExpFlg(bool b)
{
	this->expflg = b;

}

void Bomb::SetVelocity(Vector2D loc)
{
	this->velocity = loc;
}

void Bomb::SetEXVelocity(Vector2D loc)
{
	this->exvelocity = loc;
}

void Bomb::SetMode(int i)
{
	this->mode = i;
}

int Bomb::GetMode()
{
	return this->mode;
}

void Bomb::SetKnockBack(Vector2D vec, int i)
{
	this->knockback = vec * (float)i;
}

void Bomb::LoadImages()
{
	//images = LoadGraph("Resources/images/bomb.png", 0);
	int result = LoadDivGraph("Resources/images/bomb.png", 3, 3, 1, 64, 64, images);
	if (result == -1) {
		printfDx("画像エラー");
	}
}

void Bomb::DeleteImages()
{
	DeleteGraph(*images);
}

void Bomb::hitset()
{
	HitCheck++;
}
int Bomb::hitcheck()
{
	return HitCheck;
}
Object* Bomb::GetInsideBomb()
{
	return this;
}