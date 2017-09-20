#include "PopGrayMist.h"
#include "EnemyGrayMist.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 300;

PopGrayMist::PopGrayMist( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopGrayMist::~PopGrayMist( ) {
}

void PopGrayMist::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyGrayMist( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}