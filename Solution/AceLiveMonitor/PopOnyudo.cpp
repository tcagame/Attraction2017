#include "PopOnyudo.h"
#include "EnemyOnyudo.h"
#include "Military.h"

PopOnyudo::PopOnyudo( const Vector& pos ) :
Pop( pos ) {
}

PopOnyudo::~PopOnyudo( ) {
}

void PopOnyudo::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyOnyudo( getPos( ) ) ) );
}