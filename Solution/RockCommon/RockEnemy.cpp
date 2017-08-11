#include "RockEnemy.h"
#include "RockPlayer.h"


RockEnemy::RockEnemy( const Vector& pos, DOLL id, int force, bool mass, bool head ) :
RockCharacter( pos, id, mass ),
_force( 1 ),
_head( true ) {
}


RockEnemy::~RockEnemy( ) {
}

int RockEnemy::getForce( ) const {
	return _force;
}

bool RockEnemy::isHead( ) const {
	return _head;
}

bool RockEnemy::isOverRapped( RockPlayerConstPtr target ) const {
	bool result = false;
	Vector pos = getPos( );
	Vector vec = getVec( );
	Vector target_pos = target->getPos( );
		
	double length = ( target_pos - pos ).getLength2( );
	if ( length < 1 ) {
		// 自分だったら判定しない
		return false;
	}
	if ( length > COLLISION_RANGE * COLLISION_RANGE ) {
		// 離れていたら判定しない
		return false;
	}
	
	double range = target->getRadius( ) + getRadius( );
	{//上下判定
		Vector diff = target_pos - ( pos + Vector( 0, vec.y, 0 ) );
		if ( diff.getLength2( ) < range * range ) {
			result = true;
		}
	}
	{//横判定
		Vector diff = target_pos - ( pos + Vector( vec.x, 0, vec.z ) );
		if ( diff.getLength2( ) < range * range ) {
			result = true;
		}
	}
	return result;
}