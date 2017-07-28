#include "TableDrawer.h"
#include "Drawer.h"
#include "define.h"
#include "StatusSender.h"
#include "Device.h"
#include "Command.h"
#include "Application.h"
#include "Log.h"

const int STATUS_FLAME_X = 5;
const int STATUS_FLAME_Y = 5;
const int BOX_HEIGHT = 30;
const int STATUS_FLAME_HEIGHT = BOX_HEIGHT * ( ROCK_PLAYER_NUM + 1 );

const int COMMAND_WIDTH = 400;
const int COMMAND_X = SCREEN_WIDTH - COMMAND_WIDTH - 10;
const int COMMAND_Y = SCREEN_HEIGHT - BOX_HEIGHT - 10;

const int LOG_WIDTH = 400;
const int LOG_HEIGHT = 400;
const int LOG_X = SCREEN_WIDTH - LOG_WIDTH - 10;
const int LOG_Y = SCREEN_HEIGHT - LOG_HEIGHT - 50;

const int MESSAGE_X = LOG_X + 10;
const int MESSAGE_Y = LOG_Y + LOG_HEIGHT - BOX_HEIGHT;

const int DEVICE_FLAME_X = 5;
const int DEVICE_FLAME_Y = STATUS_FLAME_Y + STATUS_FLAME_HEIGHT + 10;
const int DEVICE_FLAME_WIDTH = 150;

const int CONNECT_WIDTH = 300;
const int CONNECT_X = STATUS_FLAME_X;
const int CONNECT_Y = STATUS_FLAME_Y + DEVICE_FLAME_Y + BOX_HEIGHT + 50;

const int RESET_TIME = 60;

const int BOX_WIDTH[ TableDrawer::MAX_TAG ] {
	100, //プレイヤー名
	150, //Device Dir
	150, //Device Button
	100, //State
	100, //Continue
	100, //Toku
	150, //Item
	100, //Money
	100, //Power
};
const char* NAME[ ROCK_PLAYER_NUM ] = {
	"TAROSUKE",
	"TAROJIRO",
	"GARISUKE",
	"TAROMI"
};

TableDrawerPtr TableDrawer::getTask( ) {
	return std::dynamic_pointer_cast< TableDrawer >( Application::getInstance( )->getTask( getTag( ) ) );
}


TableDrawer::TableDrawer( ) {
}


TableDrawer::~TableDrawer( ) {

}

void TableDrawer::update( ) {
	Drawer::getTask( )->flip( );
	drawFlame( );
	drawDeviceNum( );
	drawPlayer( );
	drawDeviceDir( );
	drawDeviceButton( );
	drawState( );
	drawContinue( );
	drawToku( );
	drawItem( );
	drawMoney( );
	drawPower( );
	drawCommand( );
	drawLog( );
	drawConnect( );
}

void TableDrawer::drawFlame( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int vertical_sx = STATUS_FLAME_X;
	for ( int i = 0; i < MAX_TAG; i++ ) {
		for ( int j = 0; j < ROCK_PLAYER_NUM; j++ ) {
			drawer->drawLine( vertical_sx, STATUS_FLAME_Y, vertical_sx, STATUS_FLAME_Y + STATUS_FLAME_HEIGHT ); // 縦ライン
		}
		vertical_sx += BOX_WIDTH[ i ];
	}
	drawer->drawLine( vertical_sx, STATUS_FLAME_Y, vertical_sx, STATUS_FLAME_Y + STATUS_FLAME_HEIGHT ); // 最後の縦ライン
	int frame_right = vertical_sx;
	int horizontal_sy = STATUS_FLAME_Y;
	for ( int i = 0; i < ROCK_PLAYER_NUM + 1; i++ ) {
		drawer->drawLine( STATUS_FLAME_X, horizontal_sy, frame_right, horizontal_sy ); // 横ライン
		horizontal_sy += BOX_HEIGHT;
	}
	drawer->drawLine( STATUS_FLAME_X, horizontal_sy, frame_right, horizontal_sy ); // 横ライン
}

void TableDrawer::drawDeviceNum( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	//flame
	drawer->drawLine( DEVICE_FLAME_X, DEVICE_FLAME_Y, DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y );
	drawer->drawLine( DEVICE_FLAME_X, DEVICE_FLAME_Y + BOX_HEIGHT, DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y + BOX_HEIGHT );

	drawer->drawLine( DEVICE_FLAME_X, DEVICE_FLAME_Y, DEVICE_FLAME_X, DEVICE_FLAME_Y + BOX_HEIGHT );
	drawer->drawLine( DEVICE_FLAME_X + 100, DEVICE_FLAME_Y, DEVICE_FLAME_X + 100, DEVICE_FLAME_Y + BOX_HEIGHT );
	drawer->drawLine( DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y, DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y + BOX_HEIGHT );
	//device num 表示
	int sx = STATUS_FLAME_X + 5;
	int sy = STATUS_FLAME_Y + BOX_HEIGHT * 5 + 20;
	drawer->drawString( sx, sy, "Device Num   %d", Device::getTask( )->getDeviceNum( ) );
}

void TableDrawer::drawPlayer( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_PLAYER; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "PLAYER" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d:%s", i, NAME[ i ] );
	}
}

void TableDrawer::drawDeviceDir( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_DEVICE_DIR; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "DEVICE DIR" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		int dir_x = status_sender->getData( ).player[ i ].device_x;
		int dir_y = status_sender->getData( ).player[ i ].device_y;
		drawer->drawString( sx, sy, "X:%d Y:%d", dir_x, dir_y );
	}
}

void TableDrawer::drawDeviceButton( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_DEVICE_BUTTON; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "DEVICE BUTTON" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%s", BToS( status_sender->getData( ).player[ i ].device_button ).c_str( ) );
	}
}

void TableDrawer::drawState( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_STATE; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "STATE" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		std::string state = "\0";
		switch ( status_sender->getData( ).player[ i ].state ) {
		case STATE_NONE:
			state = "NONE";
			break;
		case STATE_ENTRY:
			state = "ENTRY";
			break;
		case STATE_STREET_1:
			state = "street1";
			break;
		case STATE_STREET_2:
			state = "street2";
			break;
		case STATE_STREET_3:
			state = "street3";
			break;
		case STATE_BOSS:
			state = "BOSS";
			break;
		case STATE_RESULT:
			state = "RESULT";
			break;
		}
		drawer->drawString( sx, sy, "%s", state.c_str( ) );
	}
}

void TableDrawer::drawContinue( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_CONTINUE; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "CONTINUE" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", status_sender->getData( ).player[ i ].continue_num );
	}
}

void TableDrawer::drawToku( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_TOKU; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "TOKU" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", status_sender->getData( ).player[ i ].toku );
	}
}

void TableDrawer::drawItem( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_ITEM; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "ITEM" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%s", BToS( status_sender->getData( ).player[ i ].item ).c_str( ) );
	}
}

void TableDrawer::drawMoney( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_MONEY; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "MONEY" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", status_sender->getData( ).player[ i ].money );
	}
}

void TableDrawer::drawPower( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_POWER; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "POWER" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", status_sender->getData( ).player[ i ].power );
	}
}

std::string TableDrawer::BToS( unsigned char b ) const {
	std::string str;
	for ( int i = 0; i < 8; i++ ) {
		char s[ 2 ] = { ( ( b & ( 1 << i ) ) != 0 ) + '0', '\0' };
		std::string buf = s;
		str = buf + str;
	}
	return str;
}

void TableDrawer::drawCommand( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	CommandPtr command( Command::getTask( ) );
	{//Frame
		drawer->drawLine( COMMAND_X, COMMAND_Y, COMMAND_X + COMMAND_WIDTH, COMMAND_Y );
		drawer->drawLine( COMMAND_X, COMMAND_Y + BOX_HEIGHT , COMMAND_X + COMMAND_WIDTH, COMMAND_Y + BOX_HEIGHT );
		drawer->drawLine( COMMAND_X, COMMAND_Y, COMMAND_X, COMMAND_Y + BOX_HEIGHT );
		drawer->drawLine( COMMAND_X + COMMAND_WIDTH, COMMAND_Y, COMMAND_X + COMMAND_WIDTH, COMMAND_Y + BOX_HEIGHT );
	}
	{//string
		std::string str = "command : " + command->getCommand( );
		drawer->drawString( COMMAND_X + 10, COMMAND_Y + 6, str.c_str( ) );
	}
}

void TableDrawer::drawLog( ) const{
	DrawerPtr drawer( Drawer::getTask( ) );
	LogPtr log( Log::getTask( ) );
	{//frame
		drawer->drawLine( LOG_X, LOG_Y, LOG_X + LOG_WIDTH, LOG_Y );
		drawer->drawLine( LOG_X, LOG_Y + LOG_HEIGHT , LOG_X + LOG_WIDTH, LOG_Y + LOG_HEIGHT );
		drawer->drawLine( LOG_X, LOG_Y, LOG_X, LOG_Y + LOG_HEIGHT );
		drawer->drawLine( LOG_X + LOG_WIDTH, LOG_Y, LOG_X + LOG_WIDTH, LOG_Y + LOG_HEIGHT );
	}
	{//string
		int x = MESSAGE_X;
		int y = MESSAGE_Y;
		for ( int i = 0; i < MESSAGE_COUNT; i++ ) {
			DrawerPtr drawer( Drawer::getTask( ) );
			drawer->drawString( x, y, log->getMessage( i ).c_str( ) );
			y -= BOX_HEIGHT;
		}
	}
}

void TableDrawer::drawConnect( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	ServerPtr server( Server::getTask( ) );
	drawer->drawLine( CONNECT_X, CONNECT_Y, CONNECT_X, CONNECT_Y + BOX_HEIGHT * ( MAX_MACHINE + 1 )  );
	drawer->drawLine( CONNECT_X + CONNECT_WIDTH, CONNECT_Y, CONNECT_X + CONNECT_WIDTH, CONNECT_Y + BOX_HEIGHT * ( MAX_MACHINE + 1 )  );
	drawer->drawLine( CONNECT_X, CONNECT_Y + BOX_HEIGHT * ( MAX_MACHINE + 1 ), CONNECT_X + CONNECT_WIDTH, CONNECT_Y + BOX_HEIGHT * ( MAX_MACHINE + 1 ) );
	int sy = CONNECT_Y;
	drawer->drawLine( CONNECT_X, sy, CONNECT_X + CONNECT_WIDTH, sy );
	drawer->drawString( CONNECT_X + 100, sy + 6, "Connect" );
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( CONNECT_X, sy + 6, server->getMachineIPStr( i ).c_str( ) );
		drawer->drawLine( CONNECT_X, sy, CONNECT_X + CONNECT_WIDTH, sy );
	}
}