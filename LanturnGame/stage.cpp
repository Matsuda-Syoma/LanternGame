#include"stage.h"
#include"Dxlib.h"
#include"common.h"

stage::stage() {

	
}

stage::~stage() {
	
}

void stage::Update() {

}

void stage::Draw() const {
	DrawBox(IcefloorR_x,IcefloorR_y,IcefloorL_x,IcefloorL_y, 0xff2255,FALSE);
}