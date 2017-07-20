#include "Log.h"
#include "define.h"
#include "Drawer.h"

const int LOG_WIDTH = 400;
const int LOG_HEIGHT = 400;
const int LOG_X = SCREEN_WIDTH - LOG_WIDTH - 10;
const int LOG_Y = SCREEN_HEIGHT - LOG_HEIGHT - 50;
const int MESSAGE_HEIGHT = 30;
const int MESSAGE_X = LOG_X + 10;
const int MESSAGE_Y = LOG_Y + LOG_HEIGHT - MESSAGE_HEIGHT;


Log::Log( ) {
	_message = { };
}

Log::~Log( ) {
}

void Log::update( ) {
}

void Log::draw( ) {
	drawFrame( );
	drawString( );
}

void Log::drawFrame( ) const{
	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawLine( LOG_X, LOG_Y, LOG_X + LOG_WIDTH, LOG_Y );
	drawer->drawLine( LOG_X, LOG_Y + LOG_HEIGHT , LOG_X + LOG_WIDTH, LOG_Y + LOG_HEIGHT );
	drawer->drawLine( LOG_X, LOG_Y, LOG_X, LOG_Y + LOG_HEIGHT );
	drawer->drawLine( LOG_X + LOG_WIDTH, LOG_Y, LOG_X + LOG_WIDTH, LOG_Y + LOG_HEIGHT );

}

void Log::drawString( ) const{
	int x = MESSAGE_X;
	int y = MESSAGE_Y;
	for ( int i = 0; i < MESSAGE_COUNT; i++ ) {
		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawString( x, y, _message[ i ].c_str( ) );
		y -= MESSAGE_HEIGHT;
	}
}

void Log::addMessage( std::string message ) {
	for ( int i = 0; i < MESSAGE_COUNT - 1; i++ ) {
		_message[ MESSAGE_COUNT - i - 1 ] = _message[ MESSAGE_COUNT - i - 2 ];
	}
	_message[ 0 ] = message;
}
