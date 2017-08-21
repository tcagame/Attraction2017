#include "PopRay.h"
#include "EnemyRay.h"
#include "Military.h"

PopRay::PopRay( const Vector& pos ) :
Pop( pos ) {
}

PopRay::~PopRay( ) {
}

void PopRay::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyRay( getPos( ) ) ) );
}
