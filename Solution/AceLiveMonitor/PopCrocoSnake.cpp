#include "PopCrocoSnake.h"
#include "EnemyCrocoSnake.h"
#include "Military.h"


PopCrocoSnake::PopCrocoSnake( const Vector& pos ) :
Pop( pos ) {
}


PopCrocoSnake::~PopCrocoSnake( ) {
}

void PopCrocoSnake::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyCrocoSnake( getPos( ) ) ) );
}
