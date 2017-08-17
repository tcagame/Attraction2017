#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopCrocoSnake : public Pop {
public:
	PopCrocoSnake( const Vector& pos );
	virtual ~PopCrocoSnake( );
protected:
	void create( );
};

