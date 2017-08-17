#include "PopGama.h"
#include "EnemyGama.h"
#include "Military.h"

PopGama::PopGama( const Vector& pos ) :
Pop( pos ) {
}

PopGama::~PopGama( ) {
}

void PopGama::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyGama( getPos( ) ) ) );
}