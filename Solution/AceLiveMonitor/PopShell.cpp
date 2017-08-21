#include "PopShell.h"
#include "EnemyShell.h"
#include "Military.h"


PopShell::PopShell( const Vector& pos ) :
Pop( pos ) {
}


PopShell::~PopShell( ) {
}

void PopShell::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyShell( getPos( ) ) ) );
}
