#include "PopWind.h"
#include "EnemyWind.h"
#include "Military.h"

PopWind::PopWind( const Vector& pos ) :
Pop( pos ) {
}

PopWind::~PopWind( ) {
}

void PopWind::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyWind( getPos( ) ) ) );
}