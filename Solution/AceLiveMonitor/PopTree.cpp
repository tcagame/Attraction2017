#include "PopTree.h"
#include "EnemyTree.h"
#include "Military.h"

PopTree::PopTree( const Vector& pos ) :
Pop( pos ),
_pop( false ) {
}


PopTree::~PopTree( ) {
}

void PopTree::update( ) {
	if ( !_pop ) {
		if ( isInScreen( ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyTree( getPos( ) ) ) );
		}
	}
}