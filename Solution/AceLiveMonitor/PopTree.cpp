#include "PopTree.h"
#include "EnemyTree.h"
#include "Military.h"


PopTree::PopTree( const Vector& pos ) :
Pop( pos ) {
}


PopTree::~PopTree( ) {
}

void PopTree::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyTree( getPos( ) ) ) );
}
