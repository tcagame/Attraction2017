#include "Monmotaro.h"
#include "SynchronousData.h"
#include "Family.h"
#include "Player.h"
#include "ShotMonmotaro.h"
#include "Armoury.h"
#include "Sound.h"

//‘¬“x
const int ENTRY_SPEED = 5;
const int MAX_SPEED = 18;
const int MOVE_SPEED = 6;

//Á‚¦‚éŽžŠÔ
const int FADE_OUT_TIME = 30 * 60;

//”O—Í
const int SHOT_POWER = 1;

const int WAIT_ANIM_TIME = 3;
const int FADE_IN_OUT_TIME = WAIT_ANIM_TIME * 8;
const Vector LEAVE_POS[ 2 ] {
	Vector(  32, -64 ),
	Vector( -32, -64 )
};

Monmotaro::Monmotaro( const Vector& pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, 1, false ),
_tracking( -1 ),
_action( ACTION_HIDE ) {
	setOverlappedRadius( 36 );
}

Monmotaro::~Monmotaro( ) {
}

void Monmotaro::act( ) {
	switch ( _action ) {
	case ACTION_HIDE:
		actOnHide( );
		break;
	case ACTION_ENTRY:
		actOnEntry( );
		break;
	case ACTION_FADE_IN:
		actOnFadeIn( );
		break;
	case ACTION_MOVE:
		actOnMove( );
		break;
	case ACTION_FADE_OUT:
		actOnFadeOut( );
		break;
	}
	setSynchronousData( );
}

void Monmotaro::actOnHide( ) {
	FamilyPtr family( Family::getTask( ) );

	setVec( Vector( ) );
	setPos( Vector( family->getCameraPosX( ), 0 ) );

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player( family->getPlayer( i ) );
		if ( player->getAction( ) == Player::ACTION_CALL ) {
			_tracking = i;
			setAction( ACTION_ENTRY );
		}
	}
}

void Monmotaro::actOnEntry( ) {
	FamilyPtr family( Family::getTask( ) );
	PlayerPtr player( family->getPlayer( _tracking ) );
	Vector vec = ( player->getPos( ) - getPos( ) ).normalize( ) * ENTRY_SPEED;
	setVec( vec );
	if ( ( getPos( ) - player->getPos( ) ).getLength( ) < getOverlappedRadius( ) + player->getOverlappedRadius( ) ) {
		DIR dir = player->getDir( );
		setDir( dir );
		setPos( player->getPos( ) + LEAVE_POS[ dir ] );
		setAction( ACTION_FADE_IN );
		setVec( Vector( ) );
	}
}

void Monmotaro::actOnFadeIn( ) {
	if ( getActCount( ) > FADE_IN_OUT_TIME ) {
		setAction( ACTION_MOVE );
		setVec( Vector( ) );
	}
}

void Monmotaro::actOnMove( ) {
	FamilyPtr family( Family::getTask( ) );
	PlayerPtr player( family->getPlayer( _tracking ) );
	DIR dir = player->getDir( );
	Vector target_pos = player->getPos( ) + LEAVE_POS[ dir ];
	Vector vec = ( target_pos - getPos( ) ).normalize( ) * MOVE_SPEED;
	if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	if ( vec.getLength2( ) > ( target_pos - getPos( ) ).getLength2( ) ) {
		vec = ( target_pos - getPos( ) );
	}
	setVec( vec );
	if ( getActCount( ) > FADE_OUT_TIME ) {
		setAction( ACTION_FADE_OUT );
		setActCount( 0 );
	}
	if ( player->getAction( ) == Player::ACTION_ATTACK ) {
		for ( int i = 0; i < 2; i++ ) {
			Vector pos( getPos( ) );
			int chip_size = getChipSize( );
			int random = rand( );
			pos.x += random % ( chip_size / 2 ) * ( getDir( ) == DIR_RIGHT ? 1 : -1 );
			pos.y += sin( PI2 / random * getActCount( ) ) * ( chip_size / 2 );
			Sound::getTask( )->playSE( "yokai_se_27.wav" );
			ShotMonmotaroPtr shot( ShotMonmotaroPtr( new ShotMonmotaro( ( PLAYER )_tracking, pos, getDir( ), SHOT_POWER ) ) );
			Armoury::getTask( )->add( shot );
		}
	}
}

void Monmotaro::actOnFadeOut( ) {
	if ( getActCount( ) > FADE_IN_OUT_TIME ) {
		setAction( ACTION_HIDE );
	}
}

void Monmotaro::damage( int force ) {
	if ( force < 0 ) {
		_action = ACTION_FADE_OUT;
	}
}

void Monmotaro::setAction( ACTION action ) {
	_action = action;
	setActCount( 0 );
}

Monmotaro::ACTION Monmotaro::getAction( ) const {
	return _action;
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
	case ACTION_ENTRY:
		{
			const int ANIM[ ] = { 0, 1, 2, 1 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_FADE_IN:
		{
			const int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_MOVE:
		{
			const int ANIM[ ] = { 3, 4, 5, 6, 5, 4 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_FADE_OUT:
		{
			const int ANIM[ ] = { 23, 22, 21, 20, 19, 18, 17, 16, 16 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	pattern += ( _tracking * 16 * 2 );
	data->addObject( area, type, pattern, attribute, x, y );
}

