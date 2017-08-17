#include "PopOneEyeSnake.h"
#include "EnemyOneEyeSnake.h"
#include "Military.h"

PopOneEyeSnake::PopOneEyeSnake( const Vector& pos ) :
Pop( pos ) {
}


PopOneEyeSnake::~PopOneEyeSnake( ) {
}

void PopOneEyeSnake::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyOneEyeSnake( getPos( ) ) ) );
}