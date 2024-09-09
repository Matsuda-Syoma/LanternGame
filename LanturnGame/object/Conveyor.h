#pragma once
#include "Object.h"

class GameMain;
class CameraManager;

class Conveyor : public Object
{
private:
    int images;
    int finalimage[3];
    float width = 1024.0f;
    float height = 256.0f;
    int scroll;
public:
    Conveyor();
    ~Conveyor();

    void Initialize(GameMain* _g, int _obj_pos) override;
    void Finalize() override {};
    void Update(GameMain* _g) override;
    void Draw(CameraManager* camera)const override;
    void Hit(Object* _obj) override {};                         // 当たった時の処理
};
