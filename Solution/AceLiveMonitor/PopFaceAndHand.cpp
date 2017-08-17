#include "PopFaceAndHand.h"
#include "EnemyFaceAndHand.h"
#include "Military.h"

PopFaceAndHand::PopFaceAndHand( const Vector& pos ) : 
Pop( pos ) {
}

PopFaceAndHand::~PopFaceAndHand( ) {
}

void PopFaceAndHand::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyFaceAndHand( getPos( ) ) ) );
}