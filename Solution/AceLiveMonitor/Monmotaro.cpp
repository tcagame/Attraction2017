#include "Monmotaro.h"
#include "SynchronousData.h"
#include "Family.h"
#include "Player.h"
#include "ShotMonmotaro.h"
#include "Armoury.h"
#include "Sound.h"
#include <assert.h>

const int FADEIN_COUNT = 30;
const int FADEOUT_COUNT = 30;

//”O—Í
const int SHOT_POWER = 1;
const int WAIT_ANIM_TIME = 3;
const int OFFSET_X = -60;
const int OFFSET_Y = -80;

const double ACCEL_SPEED = 0.5;
const double MAX_SPEED = 8.0;

Monmotaro::Monmotaro( ) :
Character( Vector( 0, 1000 ), NORMAL_CHAR_GRAPH_SIZE, 1, false ),
_action( ACTION_HIDE ) {
}

Monmotaro::~Monmotaro( ) {
}

void Monmotaro::appear( PlayerPtr player ) {
	_capture_power = player->getPower( );
	if ( _capture_power <= 0 ) {
		return;
	}
	_player= player;
	setAction( ACTION_APPEAR );
	setVec( Vector( ) );
}

void Monmotaro::act( ) {

	switch ( _action ) {
	case ACTION_HIDE:
		actOnHide( );
		break;
	case ACTION_APPEAR:
		actOnAppear( );
		break;
	case ACTION_FADEIN:
		actOnFadeIn( );
		break;
	case ACTION_MOVE:
		actOnMove( );
		break;
	case ACTION_FADEOUT:
		actOnFadeOut( );
		break;
	}
}

void Monmotaro::actOnHide( ) {
}

void Monmotaro::actOnAppear( ) {
	if ( _player->isStanding( ) ) {
		setPos( _player->getPos( ) + Vector( OFFSET_X, OFFSET_Y ) );
		setVec( Vector( ) );
		setAction( ACTION_FADEIN );
	}
}

void Monmotaro::actOnFadeIn( ) {
	if ( getActCount( ) >= FADEIN_COUNT ) {
		setAction( ACTION_MOVE );
		setVec( Vector( ) );
	}
}

void Monmotaro::actOnFadeOut( ) {
	if ( getActCount( ) >= FADEOUT_COUNT ) {
		setAction( ACTION_HIDE );
		setVec( Vector( ) );
	}
}

void Monmotaro::actOnMove( ) {
	setArea( _player->getArea( ) );
	
	if ( _capture_power < _player->getPower( ) ) {
		_capture_power = _player->getPower( );
	}
	if ( _capture_power > _player->getPower( ) ) {
		setAction( ACTION_FADEOUT );
	}

	Vector target_pos = _player->getPos( ) + Vector( OFFSET_X, OFFSET_Y );
	Vector speed = ( target_pos - getPos( ) ).normalize( ) * ACCEL_SPEED;
	Vector vec = getVec( ) + speed;
	if ( vec.getLength( ) > MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	setVec( vec );

	static int n = 0;
	n++;

	if ( n % 20 == 0 ) {
		ShotMonmotaroPtr shot( ShotMonmotaroPtr( new ShotMonmotaro( _player->getPlayer( ), getPos( ), DIR_RIGHT, SHOT_POWER ) ) );
		Armoury::getTask( )->add( shot );
	}
}

void Monmotaro::setAction( ACTION action ) {
	_action = action;
	setActCount( 0 );
}

void Monmotaro::setSynchronousData( ) {
	int camera_pos = Family::getTask( )->getCameraPosX( );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}

	unsigned char type = SynchronousData::TYPE_MONMOTARO;
	int pattern = 0;
	switch ( _action ) {
	case ACTION_HIDE:
		return;
	case ACTION_FADEIN:
		{
			const int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			int idx = getActCount( ) * anim_num / FADEIN_COUNT;
			if ( idx > anim_num - 1 ) idx = anim_num - 1; 
			pattern = ANIM[ idx ];
		}
		break;
	case ACTION_FADEOUT:
		{
			const int ANIM[ ] = { 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			int idx = getActCount( ) * anim_num / FADEOUT_COUNT;
			if ( idx > anim_num - 1 ) idx = anim_num - 1; 
			pattern = ANIM[ idx ];
		}
		break;
	case ACTION_MOVE:
		{
			const int ANIM[ ] = { 8, 9, 10, 11 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	}
	unsigned char attribute = SynchronousData::ATTRIBUTE_REVERSE;
	
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, pattern, attribute, x, y );
}

