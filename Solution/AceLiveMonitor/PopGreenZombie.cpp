#include "PopGreenZombie.h"
#include "EnemyGreenZombie.h"
#include "Military.h"


PopGreenZombie::PopGreenZombie( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopGreenZombie::~PopGreenZombie( ) {
}


void PopGreenZombie::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyGreenZombie( _pos ) ) );
		_pop = true;
	}
}