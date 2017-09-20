#include "PopFaceAndHand.h"
#include "EnemyFaceAndHand.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 600;
const Vector FOOT = Vector( 0, -100, 0 );

PopFaceAndHand::PopFaceAndHand( const Vector& pos ) : 
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopFaceAndHand::~PopFaceAndHand( ) {
}

void PopFaceAndHand::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyFaceAndHand( getPos( ) + FOOT ) ) );
			_count = 0;
		}
	}
	_count++;
}