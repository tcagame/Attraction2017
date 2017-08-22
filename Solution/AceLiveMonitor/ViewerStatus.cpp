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

void ViewerStatus::draw( ) const {
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		int sx = i * 320;
		_status_flame->setPos( sx, VIEW_STATUS_Y );
		_status_flame->draw( );
	}
	drawHp( );
	drawMoney( );
	drawToku( );
}

void ViewerStatus::drawHp( ) const {
	//(POWER)
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		int tw = HP_GRAPH_WIDTH * player->getHp( );
		_status_ui->setRect( 0, 256, tw, HP_GRAPH_HEIGHT );
		int sx = i * 320 + 160;
		int sy = VIEW_STATUS_Y + 50;
		_status_ui->setPos( sx, sy );
		_status_ui->draw( );
	}
}

void ViewerStatus::drawMoney( ) const {
	//Money
	FamilyPtr family( Family::getTask( ) );
	DrawerPtr drawer( Drawer::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		int sx = i * 320 + 160;
		int sy = VIEW_STATUS_Y + 105;
		drawer->drawString( sx, sy, "%15d", player->getMoneyNum( ) );
	}
}

void ViewerStatus::drawToku( ) const {
	//Toku
	FamilyPtr family( Family::getTask( ) );
	DrawerPtr drawer( Drawer::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		int sx = i * 320 + 280;
		int sy = VIEW_STATUS_Y + 180;
		drawer->drawString( sx, sy, "%2d", player->getTokuNum( ) );
	}
}