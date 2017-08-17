#include "PopShishimai.h"
#include "EnemyShishimai.h"
#include "Military.h"

PopShishimai::PopShishimai( const Vector& pos ) :
Pop( pos ) {
}


PopShishimai::~PopShishimai( ) {
}

void PopShishimai::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyShishimai( getPos( ) ) ) );
}