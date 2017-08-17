#include "PopNoNeckGhost.h"
#include "EnemyNoNeckGhost.h"
#include "Military.h"

PopNoNeckGhost::PopNoNeckGhost( const Vector& pos ) :
Pop( pos ) {
}


PopNoNeckGhost::~PopNoNeckGhost( ) {
}

void PopNoNeckGhost::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyNoNeckGhost( getPos( ) ) ) );
}