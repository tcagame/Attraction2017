#include "EnemyBat.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 3;
const int MAX_HP = 1;
const int MOVE_SPEED = 2;
const Vector POS( 10, 0 );

EnemyBat::EnemyBat( const Vector& pos ) :
Enemy( pos + POS, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_center( pos ) {
	setRadius( 16 );
}


EnemyBat::~EnemyBat( ) {
}

void EnemyBat::act( ) {
	Vector radius = getPos( ) - _center;
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), 1 / radius.getLength( ) );
	Vector f_pos = mat.multiply( radius );
	Vector rot = ( f_pos + _center ) - getPos( );
	setVec( rot * MOVE_SPEED );
}

void EnemyBat::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
