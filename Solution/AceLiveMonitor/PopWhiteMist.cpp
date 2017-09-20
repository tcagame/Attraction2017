#include "PopWhiteMist.h"
#include "EnemyWhiteMist.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 300;

PopWhiteMist::PopWhiteMist( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopWhiteMist::~PopWhiteMist( ) {
}

void PopWhiteMist::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyWhiteMist( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}