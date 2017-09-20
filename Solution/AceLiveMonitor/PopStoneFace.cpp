#include "PopStoneFace.h"
#include "EnemyStoneFace.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 300;

PopStoneFace::PopStoneFace( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopStoneFace::~PopStoneFace( ) {
}

void PopStoneFace::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyStoneFace( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}