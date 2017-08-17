#include "PopGhoul.h"
#include "EnemyGhoul.h"
#include "Military.h"


PopGhoul::PopGhoul( const Vector& pos ) :
Pop( pos ) {
}


PopGhoul::~PopGhoul( ) {
}

void PopGhoul::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyGhoul( getPos( ) ) ) );
}