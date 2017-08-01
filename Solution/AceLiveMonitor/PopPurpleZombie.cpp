#include "PopPurpleZombie.h"
#include "EnemyPurpleZombie.h"
#include "Military.h"

PopPurpleZombie::PopPurpleZombie( Vector pos ) :
_pos( pos ),
_pop( false ) {
}


PopPurpleZombie::~PopPurpleZombie( ) {
}

void PopPurpleZombie::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyPurpleZombie( _pos ) ) );
		_pop = true;
	}
}