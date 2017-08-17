#include "PopMoth.h"
#include "EnemyMoth.h"
#include "Military.h"


PopMoth::PopMoth( const Vector& pos ) :
Pop( pos ) {
}


PopMoth::~PopMoth( ) {
}

void PopMoth::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyMoth( getPos( ) ) ) );
}