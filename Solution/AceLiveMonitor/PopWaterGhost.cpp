#include "PopWaterGhost.h"
#include "EnemyWaterGhost.h"
#include "Military.h"
#include "Property.h"

const int POP_RANGE = 300;

PopWaterGhost::PopWaterGhost( const Vector& pos ) :
Pop( pos ) {
	_max_pop_time = Property::getTask( )->getData( "WaterGhost_POP_TIME" );
	_count = _max_pop_time;
}


PopWaterGhost::~PopWaterGhost( ) {
}

void PopWaterGhost::update( ) {
	//プレイヤーが近くにきたら沸く
	if ( !_enemy.expired( ) ) {
		return;
	}
	if ( _count > _max_pop_time ) {
		if ( isInRangePlayer( POP_RANGE ) ) {
			EnemyPtr enemy = EnemyPtr( new EnemyWaterGhost( getPos( ) ) );
			Military::getTask( )->popUp( enemy );
			_enemy = enemy;
			_count = 0;
		}
	}
	_count++;
}