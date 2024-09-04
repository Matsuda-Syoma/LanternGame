#pragma once
#include "Object.h"

class GameMain;
class CameraManager;

class Stage : public Object
{
private:
    int images;

public:
    Stage();    //�R���X�g���N�^
    ~Stage();   //�f�X�g���N�^

    void Initialize(GameMain* _g, int _obj_pos) override;
    void Finalize() override {};
    void Update(GameMain* _g) override;
    void Draw(CameraManager* camera)const override;
    void Hit(Object* _obj) override {};                         // �����������̏���
};