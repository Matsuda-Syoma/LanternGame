#include "InputControl.h"
#include "Dxlib.h"

// �ÓI�����o�ϐ���`
bool InputControl::now_button[16] = {};
bool InputControl::old_button[16] = {};
float InputControl::trigger[2] = {};
Vector2D InputControl::stick[2] = {};

// ���͋@�\ : �X�V����

void InputControl::Update() 
{
	// XInput�R���g���[���[�̓��͒l��擾����
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);

	// �{�^�����͒l�̍X�V
	for (int i = 0; i < 16; i++) {
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	// �g���K�[���͒l�̍X�V(0.0f����1.0f�ɔ͈͂𐧌�����)
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	// ���X�e�B�b�N���͒l�̍X�V(-1.0f����1.0f�ɔ͈͂𐧌�����)
	if(input_state.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
	}
	else 
	{
		stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
	}
	if(input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = -((float)input_state.ThumbLY / (float)SHRT_MIN);
	}

	// �E�X�e�B�b�N���͒l�̍X�V(-1.0f����1.0f�ɔ͈͂𐧌�����)
	if (input_state.ThumbRX > 0.0f)
	{
		stick[1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state.ThumbRY > 0.0f)
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = -((float)input_state.ThumbRY / (float)SHRT_MIN);
	}
}

// �{�^���擾 : �����Ă��
bool InputControl::GetButton(int button)
{
	return CheckButtonRange(button) && (now_button[button] && old_button[button]);
}

// �{�^���擾 : �������u��
bool InputControl::GetButtonDown(int button)
{
	return CheckButtonRange(button) && (now_button[button] && !old_button[button]);
}

// �{�^���擾 : �������u��
bool InputControl::GetButtonUp(int button)
{
	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
}

// ���g���K�[�擾
float InputControl::GetLeftTrigger()
{
	return trigger[0];
}

// �E�g���K�[�擾
float InputControl::GetRightTrigger()
{
	return trigger[1];
}

// ���X�e�B�b�N�擾
Vector2D InputControl::GetLeftStick()
{
	return stick[0];
}

// �E�X�e�B�b�N�擾
Vector2D InputControl::GetRightStick()
{
	return stick[1];
}

// �{�^���z��͈̓`�F�b�N
bool InputControl::CheckButtonRange(int button)
{
	return (0 <= button && button < 16);
}