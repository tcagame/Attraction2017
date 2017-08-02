#include "PopOneEyeSnake.h"
#include "EnemyOneEyeSnake.h"
#include "Military.h"

PopOneEyeSnake::PopOneEyeSnake( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopOneEyeSnake::~PopOneEyeSnake( ) {
}

void PopOneEyeSnake::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyOneEyeSnake( _pos ) ) );
		_pop = true;
	}
}