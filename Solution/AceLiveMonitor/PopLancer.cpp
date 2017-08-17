#include "PopLancer.h"
#include "EnemyLancer.h"
#include "Military.h"

PopLancer::PopLancer( const Vector& pos ) :
Pop( pos ) {
}


PopLancer::~PopLancer( ) {
}

void PopLancer::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyLancer( getPos( ) ) ) );
}
