#include "PopBlueMonk.h"
#include "EnemyBlueMonk.h"
#include "Military.h"


PopBlueMonk::PopBlueMonk( const Vector& pos ) :
Pop( pos ) {
}


PopBlueMonk::~PopBlueMonk( ) {
}

void PopBlueMonk::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyBlueMonk( getPos( ) ) ) );
}