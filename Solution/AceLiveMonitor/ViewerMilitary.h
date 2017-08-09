#pragma once
#include "Image.h"


class ViewerMilitary {
public:
	ViewerMilitary( ImagePtr impact );
	virtual ~ViewerMilitary( );
public:
	void draw( ) const;
	void drawEnemyies( ) const;
	void drawImpacts( ) const;
private:
	ImagePtr _enemy_small;
	ImagePtr _enemy_midium;
	ImagePtr _enemy_wide;
	ImagePtr _enemy_boss;
	ImagePtr _impact;
};

