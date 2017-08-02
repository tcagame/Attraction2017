#include "PopArcher.h"
#include "EnemyArcher.h"
#include "Military.h"

PopArcher::PopArcher( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopArcher::~PopArcher( ) {
}

void PopArcher::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyArcher( _pos ) ) );
		_pop = true;
	}
}