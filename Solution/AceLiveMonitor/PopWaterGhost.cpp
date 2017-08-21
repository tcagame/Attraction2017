#include "PopWaterGhost.h"
#include "EnemyWaterGhost.h"
#include "Military.h"


PopWaterGhost::PopWaterGhost( const Vector& pos ) :
Pop( pos ) {
}


PopWaterGhost::~PopWaterGhost( ) {
}

void PopWaterGhost::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyWaterGhost( getPos( ) ) ) );
}
