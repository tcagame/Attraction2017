#include "PopWhiteMist.h"
#include "EnemyWhiteMist.h"
#include "Military.h"

PopWhiteMist::PopWhiteMist( const Vector& pos ) :
Pop( pos ) {
}

PopWhiteMist::~PopWhiteMist( ) {
}

void PopWhiteMist::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyWhiteMist( getPos( ) ) ) );
}