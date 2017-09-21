#include "PopFaceAndHand.h"
#include "EnemyFaceAndHand.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 600;
const Vector FOOT = Vector( 0, -100, 0 );

PopFaceAndHand::PopFaceAndHand( const Vector& pos ) : 
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "FaceAndHand_POP_TIME" );
	_count = _max_pop_time;
}

PopFaceAndHand::~PopFaceAndHand( ) {
}

void PopFaceAndHand::update( ) {
	//ƒvƒŒƒCƒ„[‚ª‹ß‚­‚É‚«‚½‚ç•¦‚­
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyFaceAndHand( getPos( ) + FOOT ) ) );
			_count = 0;
		}
	}
	_count++;
}