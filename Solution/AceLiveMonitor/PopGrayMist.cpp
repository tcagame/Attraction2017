#include "PopGrayMist.h"
#include "EnemyGrayMist.h"
#include "Military.h"

PopGrayMist::PopGrayMist( const Vector& pos ) :
Pop( pos ) {
}

PopGrayMist::~PopGrayMist( ) {
}

void PopGrayMist::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyGrayMist( getPos( ) ) ) );
}