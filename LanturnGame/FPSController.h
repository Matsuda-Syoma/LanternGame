#pragma once
#include"DxLib.h"
#include "common.h"

class FpsController {
private:
    int FrameTime;                              // 1�t���[���̎���(�~���b)
    int WaitTime;                               // �҂�����
    int LastTime, NowTime;                      // �Ō�Ɏ擾�������ԂƁC���̎���
    float Count;                                // �t���[���̃J�E���g
    float Fps;                                  // �\�����邵��FPS�l
    int UpdateTime;                             // �\���l��X�V���鎞��
    int LastUpdate;                             // �Ō�ɕ\���l��X�V��������

    // ������
    void Init(float RefreshRate, int UpdateTime);
public:

    // �R���X�g���N�^
    FpsController(float RefreshRate, int UpdateTime) {
        Init(RefreshRate, UpdateTime);
    }
    FpsController() {
        Init(FRAMERATE, UPDATETIME);
    }

    
    void Wait();        // �҂����Ԃ̌v�Z

   
    float Get();        //FPS�l�̌v�Z

    // �`�揈��
    void Disp() {
        SetFontSize(10);
        DrawFormatString(10, 10, 0xffffff, "fps:%0.1f", Fps);
        SetFontSize(24);
    }
    // ������܂Ƃ߂����
    float All() {
        Get();
        Wait();
        return (Fps);
    }

};



