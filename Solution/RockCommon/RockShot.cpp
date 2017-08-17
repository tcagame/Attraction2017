#include "RockShot.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int ACTIVE_COUNT = 150;
const int MOVE_SPEED = 3;
const Vector FOOT( 0, 30, 0 ); // ƒvƒŒƒCƒ„[‚Ì‘«Œ³‚©‚ç‚Ì‚‚³

RockShot::RockShot( const int id_, const Vector& pos, const Vector& dir ) :
RockCharacter( pos + FOOT, DOLL_NONE, 32, 32, false, false ),
_id( id_ ),
_out_range( false ),
_finished( false ) {
	setVec( dir * MOVE_SPEED );
}

RockShot::~RockShot( ) {
}

void RockShot::act( ) {
	if ( getActCount( ) > ACTIVE_COUNT ) {
		_out_range = true;
	}
	if ( _out_range ) {
		actOutRange( );
	}
}

void RockShot::actOutRange( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _id );
	Vector diff = ( ( player->getPos( ) + FOOT ) - getPos( ) );
	if ( diff.getLength2( ) > 1 ) {
		setVec( diff.normalize( ) * MOVE_SPEED );
	} else {
		_finished = true;
	}
}

double RockShot::getAnimTime( ) const {
	return 0;
}

bool RockShot::isfinished( ) const {
	return _finished;
}