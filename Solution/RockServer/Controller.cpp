#include "Controller.h"
#include "Drawer.h"
#include "define.h"
#include "Command.h"
#include "StatusDrawer.h"
#include "StatusSender.h"

const int STATUS_FLAME_X = 5;
const int STATUS_FLAME_Y = 5;
const int STATUS_FLAME_WIDTH = SCREEN_WIDTH - STATUS_FLAME_X * 2;
const int STATUS_FLAME_HEIGHT = 250;
const int WIDTH_BRANK = STATUS_FLAME_WIDTH / 10;
const int HEIGHT_BRANK = STATUS_FLAME_HEIGHT / 5;


Controller::Controller( ) {
}


Controller::~Controller( ) {
}

void Controller::initialize( ) {
	_command = CommandPtr ( new Command );
	_status_sender = StatusSenderPtr( new StatusSender );
	_status_drawer = StatusDrawerPtr( new StatusDrawer( _status_sender ) );
}

void Controller::update( ) {
	Drawer::getTask( )->flip( );
	drawFlame( );
	_command->update( );
	_status_drawer->draw( );
	_command->draw( );
}

void Controller::drawFlame( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
}