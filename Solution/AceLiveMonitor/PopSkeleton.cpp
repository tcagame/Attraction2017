#include "PopSkeleton.h"
#include "EnemySkeleton.h"
#include "Military.h"

PopSkeleton::PopSkeleton( const Vector& pos ) :
Pop( pos ) {
}

PopSkeleton::~PopSkeleton( ) {
}

void PopSkeleton::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemySkeleton( getPos( ) ) ) );
}