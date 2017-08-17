#include "PopFlog.h"
#include "EnemyFlog.h"
#include "Military.h"


PopFlog::PopFlog( const Vector& pos ) :
Pop( pos ) {
}


PopFlog::~PopFlog( ) {
}

void PopFlog::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyFlog( getPos( ) ) ) );
}