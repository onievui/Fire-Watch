#pragma once
#include "FieldObject.h"


/// <summary>
/// テントクラス
/// </summary>
class Tent : public FieldObject {

public:
	Tent();

public:
	void initialize() override;
	void update() override;
	void draw() override;
	void clickEvent() override;

private:

};

