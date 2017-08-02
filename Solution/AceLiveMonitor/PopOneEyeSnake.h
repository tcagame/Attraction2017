#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopOneEyeSnake : public Pop {
public:
	PopOneEyeSnake( const Vector& pos );
	virtual ~PopOneEyeSnake( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

