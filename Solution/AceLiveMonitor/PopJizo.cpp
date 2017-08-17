#include "PopJizo.h"
#include "EnemyJizo.h"
#include "Military.h"

PopJizo::PopJizo( const Vector& pos ) :
Pop( pos ) {
}

PopJizo::~PopJizo( ) {
}

void PopJizo::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyJizo( getPos( ) ) ) );
}