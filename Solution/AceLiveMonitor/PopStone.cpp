#include "PopStone.h"
#include "EnemyStone.h"
#include "Military.h"


PopStone::PopStone( const Vector& pos ) :
Pop( pos ) {
}


PopStone::~PopStone( ) {
}

void PopStone::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyStone( getPos( ) ) ) );
}