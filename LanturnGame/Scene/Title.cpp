#include "Title.h"
#include "DxLib.h"
#include "../Utility/LoadSounds.h"
#include "../Utility/InputControl.h"
#include "GameMain.h"
#include "Setting.h"
#include "credit.h"

Title::Title()
{
	SetUseASyncLoadFlag(true);
	menuimage[0] = LoadGraph("Resources/images/titlemenu_start.png");
	//menuimage[1] = LoadGraph("Resources/images/titlemenu_setting.png");
	menuimage[1] = LoadGraph("Resources/images/titlemenu_end.png");
	for (int i = 0; i < 2; i++)
	{
		if (menuimage[i] == -1) {
			printfDx("err : menuimage\n");
		}
	}
	cursorimage = LoadGraph("Resources/images/match.png", 0);
	titleimage = LoadGraph("Resources/images/Title.png", 0);
	//LoadDivGraph("Resources/images/Titlename.png", 1, 1, 1, 131, 128, titlenameimage);
	titlenameimag = LoadGraph("Resources/images/Titlename.png",0);
	titlebombimage = LoadGraph("Resources/images/titlebomb.png", 0);
	LoadDivGraph("Resources/images/alphabet.png", 26, 6, 5, 64,64, alphabetimage);
	particle = new Particle * [GM_MAX_PARTICLE];
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		particle[i] = nullptr;
	}
	SetUseASyncLoadFlag(false);
}

Title::~Title()
{
}

AbstractScene* Title::Update()
{
	if (CheckSoundMem(Sounds::BGM_Title) == 0)
	{
		PlaySoundMem(Sounds::BGM_Title, DX_PLAYTYPE_BACK);
	}
	if (InputControl::GetLeftStick().y > 0.8 && !stickonce || InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		if (!isCheck)
		{
			PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
		}
		cursor_menu++;
		// ��ԉ��ɓ��B������A��ԏ�ɂ���
		if (cursor_menu > maxcursor_menu)
		{
			cursor_menu = 0;
		}
	}

	// �J�[�\����ړ�
	if (InputControl::GetLeftStick().y < -0.8 && !stickonce || InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		if (!isCheck)
		{
			PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
		}
		cursor_menu--;
		// ��ԏ�ɓ��B������A��ԉ��ɂ���
		if (cursor_menu < 0)
		{
			cursor_menu = maxcursor_menu;
		}
	}

	// �{�^���������ĂȂ��Ȃ琔�l�X�V
	if (!isCheck) {
		cursor_last = cursor_menu;
	}

	// �J�[�\������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (!isCheck) {
			PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
			isCheck = true;
		}
	}

	// ���ɂ߃J�E���g�X�V
	if (fireanim < maxfireanim) {
		if (isCheck) {
			fireanim++;
		}
	}
	else {
		switch (cursor_last)
		{
		case 0:
			StopSoundMem(Sounds::BGM_Title);
			return new GameMain;
			break;
		case 1:
			return new Credit;
			break;
		default:
			//return new End;
			break;
		}
	}

	if (CheckSoundMem(Sounds::SE_cursor) == 0)
	{
		StopSoundMem(Sounds::SE_cursor);
	}

	if (CheckSoundMem(Sounds::SE_transition) == 0)
	{
		StopSoundMem(Sounds::SE_transition);
	}

	// lerp����
	/*Vector2D qw = (Vector2D(886.00f, 128.0f + (cursor_last * 65.0f)) * (float)clamp(1.0f - (fireanim / 60.0f), 0.0f, 1.0f));
	Vector2D qw2 = (Vector2D(800.0f, 380.0f + (cursor_last * 65.0f)) * (float)clamp((fireanim / 60.0f), 0.0f, 1.0f));
	bombloc = qw + qw2;*/

	bombloc = Vector2D(800.0f, 380.0f + (cursor_last * 65.0f));



	// 60�t���[���Ȃ�p�[�e�B�N���o��
	if (fireanim == 60)
	{
		int ptemp = CreateParticle(3);
		GetParticle(ptemp)->SetLocation(bombloc);
		GetParticle(ptemp)->SetAngle((float)GetRand(360));
		GetParticle(ptemp)->SetScale(2.0f);
		PlaySoundMem(Sounds::SE_Explosion[GetRand(4)], DX_PLAYTYPE_BACK, true);
	}

	if (fireanim > 60 && fireanim % 3 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int ptemp = CreateParticle(3);
			GetParticle(ptemp)->SetLocation(Vector2D((SCREEN_WIDTH / 2) + (GetRand(SCREEN_WIDTH) - (SCREEN_WIDTH / 2))
													,(SCREEN_HEIGHT / 2) + (GetRand(SCREEN_HEIGHT) - (SCREEN_HEIGHT / 2))));
			GetParticle(ptemp)->SetAngle((float)GetRand(360));
			GetParticle(ptemp)->SetScale((GetRand(9) + 1) / 5.0f);
			PlaySoundMem(Sounds::SE_Explosion[GetRand(4)], DX_PLAYTYPE_BACK, true);
		}

		//PlaySoundMem(Sounds::SE_ED_Soldier, DX_PLAYTYPE_BACK);
		PlaySoundMem(Sounds::SE_Explosion[GetRand(4)], DX_PLAYTYPE_BACK, true);
	}

	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		// �p�[�e�B�N����nullptr����Ȃ��Ȃ�
		if (particle[i] != nullptr)
		{
			particle[i]->Update(nullptr);
			if (!particle[i]->Getflg())
			{
				particle[i] = nullptr;
				delete particle[i];
			}
		}
	}
	// �X�e�B�b�N����x������������t���O
	if (fabs(InputControl::GetLeftStick().y) > 0.8)
	{
		stickonce = true;
	}
	else
	{
		stickonce = false;
	}
	return this;
}

void Title::Draw() const
{
	// �^�C�g���摜�̕`��
	DrawGraph(0, 0, titleimage,true);

	// �^�C�g������`��
	DrawRotaGraph(980, 180, 1.5, 0.0, titlenameimag, true);

	// ���l���ꎞ�ۑ�
	int OldBlendMode, OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, max(255 - (int)(clamp((fireanim / 30.0f), 0.0f, 1.0f) * 511.0f), 0));
	
	// �^�C�g�����̔��e��`��
	DrawRotaGraph(800, 380 + (cursor_last * 65), 1.0, 0.0, titlebombimage, true);

	SetDrawBlendMode(OldBlendMode, OldBlendParam);

	// Start�̕`��
	if (cursor_last == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, max(255 - (int)(clamp(((fireanim - 60.0f) / (float)(maxfireanim - 60.0f)), 0.0f, 1.0f) * 511.0f), 0));
	}
	char chr_start[] = "start";
	for (int i = 0; i < sizeof(chr_start); i++)
	{
		int chr = chr_start[i] - 'a';
		DrawRotaGraph(880 + 48 * i, 380, 1.0, 0.0, alphabetimage[chr], true);
	}
	SetDrawBlendMode(OldBlendMode, OldBlendParam);

	// End�̕`��
	if (cursor_last == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, max(255 - (int)(clamp(((fireanim - 60.0f) / (float)(maxfireanim - 60.0f)), 0.0f, 1.0f) * 511.0f), 0));
	}

	char chr_end[] = "end";
	for (int i = 0; i < sizeof(chr_end); i++)
	{
		int chr = chr_end[i] - 'a';
		DrawRotaGraph(880 + 48 * i, 445, 1.0, 0.0, alphabetimage[chr], true);
	}
	SetDrawBlendMode(OldBlendMode, OldBlendParam);

	// ���e�̕`��
	if (fireanim < 60)
	{
		if (fireanim % 14 > 7)
		{
			SetDrawBright(255, 0, 0);// �ԈȊO�Â�����
		}
		DrawRotaGraphF(bombloc.x, bombloc.y, 1.5, 0.0, titlebombimage, true);
		SetDrawBright(255, 255, 255);// �S�F�Â����Ȃ��i�f�t�H���g�j
	}


	// �p�[�e�B�N���̕`��
	for (int i = 0; i < GM_MAX_PARTICLE; i++)
	{
		// �G��nullptr����Ȃ��Ȃ�
		if (particle[i] != nullptr)
		{
			particle[i]->Draw();
		}
	}
}


int Title::CreateParticle(int type)
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

Particle* Title::GetParticle(int _num)
{
	return particle[_num];
}