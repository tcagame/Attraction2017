#include "PopGhost.h"
#include "EnemyGhost.h"
#include "Military.h"

PopGhost::PopGhost( const Vector& pos ) :
Pop( pos ) {
}

PopGhost::~PopGhost( ) {
}

void PopGhost::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyGhost( getPos( ) ) ) );
}
