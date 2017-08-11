#include "PopGrayMist.h"
#include "EnemyGrayMist.h"
#include "Military.h"

PopGrayMist::PopGrayMist( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}

PopGrayMist::~PopGrayMist( ) {
}

void PopGrayMist::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyGrayMist( _pos ) ) );
		_pop = true;
	}
}