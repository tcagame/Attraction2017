#include "Pop.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "World.h"
#include "Map.h"

const int POP_INTERVAL_COUNT = 600;
const int MAX_PAGE = SCREEN_WIDTH / GRAPH_SIZE;
const int POP_RANGE = SCREEN_WIDTH * 3 / 2;

Pop::Pop( const Vector& pos ) :
_pos( pos ) {
}

Pop::~Pop( ) {
}

Vector Pop::getPos( ) const {
	return _pos;
}

bool Pop::isInScreen( ) const {
	bool in_screen = false;
	int camera_x = Family::getTask( )->getCameraPosX( );
	//ç∂í[ && âEí[
	if ( camera_x - _pos.x < GRAPH_SIZE &&
		 camera_x - _pos.x > -SCREEN_WIDTH - GRAPH_SIZE ) {
		in_screen = true;
	}
	return in_screen;
}

bool Pop::isInRangePlayer( int range ) const {
	Vector right_player_pos = Vector( );
	bool exist = false;
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( !player->isExist( ) ) {
			continue;
		}
		if ( abs( player->getPos( ).x - getPos( ).x ) < range ) {
			exist = true;
			break;
		}
	}
	return exist;
}
