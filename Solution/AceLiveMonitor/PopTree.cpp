#include "PopTree.h"
#include "EnemyTree.h"
#include "Military.h"


PopTree::PopTree( const Vector& pos ) :
_pos( pos ),
_pop( false ) {
}


PopTree::~PopTree( ) {
}

void PopTree::update( ) {
	if ( !_pop ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyTree( _pos ) ) );
		_pop = true;
	}
}
