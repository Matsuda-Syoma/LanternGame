#pragma once

class stage
{
private:
  

public:
    stage();    //コンストラクタ
    ~stage();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw()const;   //描画処理

};
