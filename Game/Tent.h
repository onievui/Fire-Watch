#pragma once
#include "FieldObject.h"


/// <summary>
/// �e���g�N���X
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

