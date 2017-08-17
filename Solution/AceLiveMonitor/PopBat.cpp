#include "PopBat.h"
#include "EnemyBat.h"
#include "Military.h"


PopBat::PopBat( const Vector& pos ) :
Pop( pos ) {
}


PopBat::~PopBat( ) {
}

void PopBat::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyBat( getPos( ) ) ) );
}