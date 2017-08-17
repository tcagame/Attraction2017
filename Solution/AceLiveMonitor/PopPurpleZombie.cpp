#include "PopPurpleZombie.h"
#include "EnemyPurpleZombie.h"
#include "Military.h"

PopPurpleZombie::PopPurpleZombie( const Vector& pos ) :
Pop( pos ) {
}


PopPurpleZombie::~PopPurpleZombie( ) {
}

void PopPurpleZombie::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyPurpleZombie( getPos( ) ) ) );
}