#include "PopShishimai.h"
#include "EnemyShishimai.h"
#include "Military.h"

PopShishimai::PopShishimai( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopShishimai::~PopShishimai( ) {
}

void PopShishimai::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyShishimai( _pos ) ) );
		_pop = true;
	}
}