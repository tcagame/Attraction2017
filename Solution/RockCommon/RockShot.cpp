#include "RockShot.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int ACTIVE_COUNT = 150;
const int MOVE_SPEED = 3;
const Vector FOOT( 0, 30, 0 ); // ƒvƒŒƒCƒ„[‚Ì‘«Œ³‚©‚ç‚Ì‚‚³

RockShot::RockShot( const int id_, const Vector& pos, const Vector& dir ) :
RockCharacter( pos + FOOT, DOLL_NONE, 32, 32, false, false ),
_id( id_ ),
_back( false ),
_finished( false ) {
	setVec( dir * MOVE_SPEED );
}

RockShot::~RockShot( ) {
}

void RockShot::act( ) {
	if ( getActCount( ) > ACTIVE_COUNT ) {
		_back = true;
	}
	if ( _back ) {
		actOutBack( );
	}
}

void RockShot::actOutBack( ) {
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

bool RockShot::isFinished( ) const {
	return _finished;
}

bool RockShot::isBack( ) const {
	return _back;
}

void RockShot::setFinished( ) {
	_finished = true;
}

void RockShot::setBack( ) {
	_back = true;
}
