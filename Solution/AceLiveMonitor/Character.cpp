#include "Character.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"
#include "World.h"
#include "Map.h"

const int MAX_SPEED_Y = 16;
const int MAX_ACT_COUNT = 0xfffffff;

Character::Character( const Vector& pos, const int chip_size, const int power, bool mass ) :
_pos( pos ),
_standing( false ),
_chip_size( chip_size ),
_act_count( 0 ),
_power( power ),
_mass( mass ),
_radius( chip_size / 3 ),
_area( AREA_STREET ) {
}


Character::~Character( ) {
}

void Character::update( ) {
	act( );

	_act_count = ( _act_count + 1 ) % MAX_ACT_COUNT;
	_standing = false;

	updateMass( );
	updateDir( );

	_pos += _vec;

}

void Character::updateMass( ) {
	if ( !_mass ) {
		return;
	}

	_vec.y += GRAVITY;

	if ( _vec.y > MAX_SPEED_Y ) {
		_vec.y = MAX_SPEED_Y;
	}
	if ( _vec.y < -MAX_SPEED_Y ) {
		_vec.y = -MAX_SPEED_Y;
	}
	MapPtr map = World::getTask( )->getMap( _area );
	//è„
	if ( _vec.y < 0 ) {
		unsigned char obj = map->getObject( _pos + Vector( 0, _vec.y - _radius * 2 ) );
		if ( obj == OBJECT_BLOCK ) {
			_pos.y = ( ( int )( _pos.y + _vec.y - _radius * 2 ) / OBJECT_CHIP_SIZE + 1 ) * OBJECT_CHIP_SIZE - GRAVITY / 2 + _radius * 2;
			_vec.y = 0;
		}
	}
	//â∫
	if ( _vec.y > 0 ) {
		unsigned char obj = map->getObject( _pos + Vector( 0, _vec.y ) );
		if ( obj == OBJECT_BLOCK || obj == OBJECT_ONEWAY ) {
			_standing = true;
			_pos.y = ( ( int )( _pos.y + _vec.y ) / OBJECT_CHIP_SIZE ) * OBJECT_CHIP_SIZE - GRAVITY / 2;
			_vec.y = 0;
		}
	}
	//ç∂ë§
	if ( _vec.x < 0 ) {
		if ( map->getObject( _pos + Vector( _vec.x, 0 ) ) == OBJECT_BLOCK ) {
			_pos.x = ( ( int )( _pos.x + _vec.x ) / OBJECT_CHIP_SIZE + 1 ) * OBJECT_CHIP_SIZE;
			_vec.x = 0;
			_dir = DIR_LEFT;
		}
	}
	//âEë§
	if ( _vec.x > 0 ) {
		if ( map->getObject( _pos + Vector( _vec.x, 0 ) ) == OBJECT_BLOCK ) {
			_pos.x = ( ( int )( _pos.x + _vec.x ) / OBJECT_CHIP_SIZE ) * OBJECT_CHIP_SIZE - 1;
			_vec.x = 0;
			_dir = DIR_RIGHT;
		}
	}
}

void Character::damage( int force ) {
	// ë¶éÄÇ…Ç≥ÇπÇÈ
	if ( force < 0 ) {
		force = _power;
	}

	// çUåÇóÕï™å∏ÇÁÇ∑
	_power -= force;
	if ( _power < 0 ) {
		_power = 0;
	}
}


DIR Character::getDir( ) const {
	 return _dir;
}

Vector Character::getVec( ) const{
	return _vec;
}

Vector Character::getPos( ) const{
	return _pos;
}

void  Character::setVec( const Vector& vec ) {
	_vec = vec;
}

void  Character::setPos( const Vector& pos ) {
	_pos = pos;
}

void Character::setDir( DIR dir ) {
	_dir = dir;
}

int Character::getPower( ) const {
	return _power;
}

void Character::setPower( int power ) {
	_power = power;
}

bool Character::isStanding( ) const {
	return _standing;
}

bool Character::isMass( ) const {
	return _mass;
}

AREA Character::getArea( ) const {
	return _area;
}

void Character::updateDir( ) {
	if ( _vec.x < 0 ) {
		_dir = DIR_LEFT;
	}
	if ( _vec.x > 0 ) {
		_dir = DIR_RIGHT;
	}
}

int Character::getActCount( ) const {
	return _act_count;
}

int Character::getChipSize( ) const {
	return _chip_size;
}

Vector Character::getOverlappedPos( ) const {
	return _pos + Vector( 0, -_radius );
}

bool Character::isOverlapped( CharacterConstPtr target ) const {
	if ( _area != target->getArea( ) || _power <= 0 ) {
		return false;
	}
	Vector self = getOverlappedPos( );
	Vector nonself = target->getOverlappedPos( );
	double length = ( self - nonself ).getLength( );
	double radius = getOverlappedRadius( ) + target->getOverlappedRadius( );
	return ( length < radius );
}

void Character::setOverlappedRadius( int radius ) {
	_radius = radius;
}

double Character::getOverlappedRadius( ) const {
	return _radius;
}

void Character::setActCount( int count ) {
	_act_count = count;
}

void Character::setArea( AREA area ) {
	_area = area;
}

ViewerDebug::Data::Circle Character::getDebugDataCircle( ) const {
	ViewerDebug::Data::Circle circle;
	circle.pos = getOverlappedPos( );
	circle.radius = getOverlappedRadius( );

	if ( getArea( ) == AREA_STREET ) {
		circle.pos.y += VIEW_STREET_Y;
		circle.pos.x -= Family::getTask( )->getCameraPosX( );
	}
	return circle;
}

void Character::shiftPos( int map_width ) {
	if ( _area == AREA_EVENT ) {
		return;
	}
	_pos.x -= map_width;
}


bool Character::isOutRange( ) const {
	if ( getArea( ) == AREA_EVENT ) {
		return false;
	}
	return getPos( ).x - Family::getTask( )->getCameraPosX( ) < -GRAPH_SIZE;
}
