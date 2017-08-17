#include "PopArcher.h"
#include "EnemyArcher.h"
#include "Military.h"

PopArcher::PopArcher( const Vector& pos ) :
Pop( pos ) {
}


PopArcher::~PopArcher( ) {
}

void PopArcher::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyArcher( getPos( ) ) ) );
}