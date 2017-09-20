#include "PopWhiteMist.h"
#include "EnemyWhiteMist.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 200;

PopWhiteMist::PopWhiteMist( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopWhiteMist::~PopWhiteMist( ) {
}

void PopWhiteMist::update( ) {
	//�v���C���[���߂��ɂ����畦��
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyWhiteMist( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}