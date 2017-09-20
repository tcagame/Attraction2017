#include "PopGhost.h"
#include "EnemyGhost.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;
const int POP_RANGE = 300;

PopGhost::PopGhost( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}

PopGhost::~PopGhost( ) {
}

void PopGhost::update( ) {
	if ( !_enemy.expired( ) ) {
		return;
	}
	//�v���C���[���߂��ɂ����畦��
	if ( _count > MAX_POP_COUNT ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyGhost( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}