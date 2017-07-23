#include "Viewer.h"
#include "Family.h"
#include "Player.h"
#include "Drawer.h"
#include <string>

const int PLAYER_CHIP_SIZE = 64;
const int PLAYER_FOOT = 7;
const int PLAYER_ANIM_WAIT_COUNT = 12;
const int PLAYER_ANIM_WIDTH_NUM = 8;

Viewer::Viewer( FamilyConstPtr family ) :
_family( family ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_family[ 0 ] = drawer->createImage( "Family/tarosuke.png" );
	_image_family[ 1 ] = drawer->createImage( "Family/tarojiro.png" );
	_image_family[ 2 ] = drawer->createImage( "Family/garisuke.png" );
	_image_family[ 3 ] = drawer->createImage( "Family/taromi.png" );
	_player_count = { };
	for ( int i = 0; i < ACE_MAP_NUM; i++ ) {
		char buf[ 256 ];
		sprintf_s( buf, "back_%003d", i );
		std::string numstr = buf;
		std::string path = "MapData/Img/" + numstr + ".png";
		_image_back[ i ] = drawer->createImage( path.c_str( ) );
	}
	for ( int i = 0; i < ACE_MAP_NUM; i++ ) {
		char buf[ 256 ];
		sprintf_s( buf, "front_%003d", i );
		std::string numstr = buf;
		std::string path = "MapData/Img/" + numstr + ".png";
		_image_front[ i ] = drawer->createImage( path.c_str( ) );
	}
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	Drawer::getTask( )->flip( );
	drawStreet( );
	drawFamily( );
}

void Viewer::drawFamily( ) const {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerConstPtr player = _family->getPlayer( i );
		Vector pos = player->getPos( );
		Player::ACTION action = player->getAction( );
		int cx = 0;
		int cy = 0;
		switch ( action ) {
		case Player::ACTION_WAIT:
			{
				const int ANIM[ ] = {
					0,
				};
				int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
				int act_count = player->getActCount( );
				cx = ANIM[ ( act_count / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
				cy = ANIM[ ( act_count / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
			}
			break;
		case Player::ACTION_WALK:
			{
				const int ANIM[ ] = {
					0, 1, 2, 1, 0, 3, 4, 3
				};
				int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
				cx = ANIM[ ( ( int )pos.x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
				cy = ANIM[ ( ( int )pos.x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
			}
			break;
		case Player::ACTION_BRAKE:
			{
				const int ANIM[ ] = {
					6,
				};
				int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
				cx = ANIM[ ( ( int )pos.x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
				cy = ANIM[ ( ( int )pos.x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
			}
			break;
		case Player::ACTION_FLOAT:
			{
				const int ANIM[ ] = {
					5,
				};
				int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
				cx = ANIM[ ( ( int )pos.x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
				cy = ANIM[ ( ( int )pos.x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
			}
			break;
		}
		int tx = cx * PLAYER_CHIP_SIZE;
		int ty = cy * PLAYER_CHIP_SIZE;
		_image_family[ i ]->setRect( tx, ty, PLAYER_CHIP_SIZE, PLAYER_CHIP_SIZE );
		if ( player->getDir( ) == Player::DIR_LEFT ) {
			int sx = (int)pos.x - PLAYER_CHIP_SIZE / 2;
			int sy = (int)pos.y - PLAYER_CHIP_SIZE + PLAYER_FOOT;
			_image_family[ i ]->setPos( sx, sy );
		} else {
			int sx = (int)pos.x - PLAYER_CHIP_SIZE / 2 + PLAYER_CHIP_SIZE;
			int sy = (int)pos.y - PLAYER_CHIP_SIZE + PLAYER_FOOT;
			_image_family[ i ]->setPos( sx, sy, sx - PLAYER_CHIP_SIZE, sy + PLAYER_CHIP_SIZE );
		}
		_image_family[ i ]->draw( );
	}
}

void Viewer::drawStreet( ) const{
	//back
	for ( int i = 0; i < ACE_MAP_SIZE; i++ ) {
		int sx1 = GRAPH_SIZE * i;
		_image_back[ i % ACE_MAP_NUM ]->setPos( sx1, SCREEN_HEIGHT - GRAPH_SIZE );
		_image_back[ i % ACE_MAP_NUM ]->draw( );
	}
	//front
	for ( int i = 0; i < ACE_MAP_SIZE; i++ ) {
		int sx1 = GRAPH_SIZE * i;
		_image_front[ i % ACE_MAP_NUM ]->setPos( sx1, SCREEN_HEIGHT - GRAPH_SIZE );
		_image_front[ i % ACE_MAP_NUM ]->draw( );
	}
}
