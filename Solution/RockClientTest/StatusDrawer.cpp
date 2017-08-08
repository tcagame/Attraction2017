#include "StatusDrawer.h"
#include "Application.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"

const int VIEW_PLAYER_X = 50;
const int VIEW_DEVICE_X = VIEW_PLAYER_X + 100;
const int VIEW_BUTTON_X = VIEW_DEVICE_X + 100;
const int VIEW_STATE_X = VIEW_BUTTON_X + 120;
const int VIEW_CONTINUE_X = VIEW_STATE_X + 100;
const int VIEW_TOKU_X = VIEW_CONTINUE_X + 100;
const int VIEW_ITEM_X = VIEW_TOKU_X + 60;
const int VIEW_MONEY_X = VIEW_ITEM_X + 100;
const int VIEW_POWER_X = VIEW_MONEY_X + 60;
const int HEIGHT = 16;

StatusDrawerPtr StatusDrawer::getTask( ) {
	return std::dynamic_pointer_cast< StatusDrawer >( Application::getInstance( )->getTask( getTag( ) ) );
}


StatusDrawer::StatusDrawer( StatusPtr status ) :
_status( status ) {
}


StatusDrawer::~StatusDrawer( ) {
}

void StatusDrawer::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->flip( );
	{//player
		int sx = VIEW_PLAYER_X;
		int sy = 0;
		drawer->drawString( sx, sy, "Player" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, "Player%d", i );
		}
	}
	{//drawDeviceDir
		int sx = VIEW_DEVICE_X;
		int sy = 0;
		drawer->drawString( sx, sy, "DeviceDir" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, "%d : %d", _status->getPlayer( i ).device_x, _status->getPlayer( i ).device_y );
		}
	}
	{//drawDeviceButton
		int sx = VIEW_BUTTON_X;
		int sy = 0;
		drawer->drawString( sx, sy, "DeviceButton" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, BToS( _status->getPlayer( i ).device_button ).c_str( ) );
		}
	}
	{//drawState
		int sx = VIEW_STATE_X;
		int sy = 0;
		drawer->drawString( sx, sy, "State" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, BToS( _status->getPlayer( i ).state ).c_str( ) );
		}
	}
	{//drawContinue
		int sx = VIEW_CONTINUE_X;
		int sy = 0;
		drawer->drawString( sx, sy,  "Continue" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, "%d", _status->getPlayer( i ).continue_num );
		}
	}
	{//drawToku
		int sx = VIEW_TOKU_X;
		int sy = 0;
		drawer->drawString( sx, sy,  "Toku" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, "%d", _status->getPlayer( i ).toku );
		}
	}
	{//drawItem
		int sx = VIEW_ITEM_X;
		int sy = 0;
		drawer->drawString( sx, sy, "Item" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, BToS( _status->getPlayer( i ).item ).c_str( ) );
		}
	}
	{//drawMoney
		int sx = VIEW_MONEY_X;
		int sy = 0;
		drawer->drawString( sx, sy,  "Money" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, "%d", _status->getPlayer( i ).money );
		}
	}
	{//drawPower
		int sx = VIEW_POWER_X;
		int sy = 0;
		drawer->drawString( sx, sy,  "Power" );
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			sy += HEIGHT;
			drawer->drawString( sx, sy, "%d", _status->getPlayer( i ).power );
		}
	}
}

std::string StatusDrawer::BToS( unsigned char b ) const {
	std::string str;
	for ( int i = 0; i < 8; i++ ) {
		char s[ 2 ] = { ( ( b & ( 1 << i ) ) != 0 ) + '0', '\0' };
		std::string buf = s;
		str = buf + str;
	}
	return str;
}