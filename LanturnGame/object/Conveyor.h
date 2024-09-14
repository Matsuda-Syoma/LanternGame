#pragma once
#include "Object.h"

class GameMain;
class CameraManager;

class Conveyor : public Object
{
private:
    int angle = 0;      // 0:右 1:下 2:左 3:上
    int images;
    int finalimage[3];
    float width = 128.0f;
    float height = 512.0f;
    int scroll;
public:
    Conveyor();
    ~Conveyor();

    void Initialize(GameMain* _g, int _obj_pos) override;
    void Finalize() override {};
    void Update(GameMain* _g) override;
    void Draw(CameraManager* camera)const override;
    void SetAngle(int i);
    void Hit(Object* _obj) override {};                         // 当たった時の処理
};
