#include "StatusDrawer.h"
#include "Drawer.h"
#include "define.h"
#include "StatusSender.h"
#include "Device.h"

const int STATUS_FLAME_X = 5;
const int STATUS_FLAME_Y = 5;
const int BOX_HEIGHT = 30;
const int BOX_WIDTH[ StatusDrawer::MAX_TAG ] {
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
const int STATUS_FLAME_HEIGHT = BOX_HEIGHT * ( ROCK_PLAYER_NUM + 1 );
const char* NAME[ ROCK_PLAYER_NUM ] = {
	"TAROSUKE",
	"TAROJIRO",
	"GARISUKE",
	"TAROMI"
};
const int DEVICE_FLAME_X = 5;
const int DEVICE_FLAME_Y = STATUS_FLAME_Y + STATUS_FLAME_HEIGHT + 10;
const int DEVICE_FLAME_WIDTH = 150;
const int DEVICE_FLAME_HEIGHT = 30;
const int RESET_TIME = 60;

StatusDrawer::StatusDrawer( StatusSenderConstPtr status_sender ) :
_status_sender( status_sender ) {
}


StatusDrawer::~StatusDrawer( ) {

}

void StatusDrawer::draw( ) const {
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
}

void StatusDrawer::drawFlame( ) const {
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

void StatusDrawer::drawDeviceNum( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	//flame
	drawer->drawLine( DEVICE_FLAME_X, DEVICE_FLAME_Y, DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y );
	drawer->drawLine( DEVICE_FLAME_X, DEVICE_FLAME_Y + DEVICE_FLAME_HEIGHT, DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y + DEVICE_FLAME_HEIGHT);

	drawer->drawLine( DEVICE_FLAME_X, DEVICE_FLAME_Y, DEVICE_FLAME_X, DEVICE_FLAME_Y + DEVICE_FLAME_HEIGHT );
	drawer->drawLine( DEVICE_FLAME_X + 100, DEVICE_FLAME_Y, DEVICE_FLAME_X + 100, DEVICE_FLAME_Y + DEVICE_FLAME_HEIGHT );
	drawer->drawLine( DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y, DEVICE_FLAME_X + DEVICE_FLAME_WIDTH, DEVICE_FLAME_Y + DEVICE_FLAME_HEIGHT );
	//device num 表示
	int sx = STATUS_FLAME_X + 5;
	int sy = STATUS_FLAME_Y + BOX_HEIGHT * 5 + 20;
	drawer->drawString( sx, sy, "Device Num   %d", Device::getTask( )->getDeviceNum( ) );
}

void StatusDrawer::drawPlayer( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_PLAYER; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "PLAYER" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, NAME[ i ] );
	}
}

void StatusDrawer::drawDeviceDir( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_DEVICE_DIR; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "DEVICE DIR" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		int dir_x = _status_sender->getData( ).player[ i ].device_x;
		int dir_y = _status_sender->getData( ).player[ i ].device_y;
		drawer->drawString( sx, sy, "X:%d Y:%d", dir_x, dir_y );
	}
}

void StatusDrawer::drawDeviceButton( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_DEVICE_BUTTON; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "DEVICE BUTTON" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%s", BToS( _status_sender->getData( ).player[ i ].device_button ).c_str( ) );
	}
}

void StatusDrawer::drawState( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_STATE; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "STATE" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		std::string state = "\0";
		switch ( _status_sender->getData( ).player[ i ].state ) {
		case STATE_NONE:
			state = "NONE";
			break;
		case STATE_ENTRY:
			state = "ENTRY";
			break;
		case STATE_STREET_1:
			state = "道中1";
			break;
		case STATE_STREET_2:
			state = "道中2";
			break;
		case STATE_STREET_3:
			state = "道中3";
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

void StatusDrawer::drawContinue( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_CONTINUE; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "CONTINUE" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", _status_sender->getData( ).player[ i ].continue_num );
	}
}

void StatusDrawer::drawToku( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_TOKU; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "TOKU" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", _status_sender->getData( ).player[ i ].toku );
	}
}

void StatusDrawer::drawItem( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_ITEM; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "ITEM" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%s", BToS( _status_sender->getData( ).player[ i ].item ).c_str( ) );
	}
}

void StatusDrawer::drawMoney( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_MONEY; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "MONEY" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", _status_sender->getData( ).player[ i ].money );
	}
}

void StatusDrawer::drawPower( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	int sx = STATUS_FLAME_X + 5;
	for ( int i = 0; i < TAG_POWER; i++ ) {
		sx += BOX_WIDTH[ i ];
	}
	int sy = STATUS_FLAME_Y + 10;
	drawer->drawString( sx, sy, "POWER" );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		sy += BOX_HEIGHT;
		drawer->drawString( sx, sy, "%d", _status_sender->getData( ).player[ i ].power );
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