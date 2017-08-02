#include "PopCrocoSnake.h"
#include "EnemyCrocoSnake.h"
#include "Military.h"


PopCrocoSnake::PopCrocoSnake( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopCrocoSnake::~PopCrocoSnake( ) {
}

void PopCrocoSnake::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyCrocoSnake( _pos ) ) );
		_pop = true;
	}
}
