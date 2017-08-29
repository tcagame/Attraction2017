#include "ViewerStatus.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"

const int HP_GRAPH_HEIGHT = 16;
const int HP_GRAPH_WIDTH = 8;

ViewerStatus::ViewerStatus( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_status_flame = drawer->createImage( "UI/status_plate.png" );
	_status_ui = drawer->createImage( "UI/ui.png" );
}

ViewerStatus::~ViewerStatus( ) {
}

void ViewerStatus::draw( PLAYER player, int sx, int sy ) const {
	_status_flame->setPos( sx, sy );
	_status_flame->draw( );

	FamilyPtr family(Family::getTask());
	PlayerPtr p = family->getPlayer( player );

	drawPower( p->getPower( ), sx, sy );
	drawMoney( p->getMoney( ), sx, sy );
	drawVirtue( p->getVirtue( ), sx, sy );
}

void ViewerStatus::drawPower( int power, int sx, int sy ) const {
	int tw = HP_GRAPH_WIDTH * power;
	_status_ui->setRect( 0, 256, tw, HP_GRAPH_HEIGHT );
	sx += 160;
	sy +=  50;
	_status_ui->setPos( sx, sy );
	_status_ui->draw( );
}

void ViewerStatus::drawMoney( int money,  int sx, int sy ) const {
	sx += 160;
	sy += 105;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawString( sx, sy, "%15d", money );
}

void ViewerStatus::drawVirtue( int virtue, int sx, int sy ) const {
	sx += 280;
	sy += 180;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawString( sx, sy, "%2d", virtue);
}