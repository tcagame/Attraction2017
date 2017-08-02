#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopCrocoSnake : public Pop {
public:
	PopCrocoSnake( const Vector& pos );
	virtual ~PopCrocoSnake( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

