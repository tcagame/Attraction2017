#include "RockMapStreet.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMapStreetDrawer.h"
#include "Status.h"
#include "MessageSender.h"

const int REMOVE_CAVE_TIME = 300;
const int TELEPORT_MONEY = 50000;
const int TELEPORT_TOKU = 10;

RockMapStreet::RockMapStreet( StatusPtr status ) :
_time( 0 ),
_status( status ) {
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::initialize( ) {
	_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );
}

void RockMapStreet::update( ) {
	switch ( _drawer->getStage( ) ) {
	case STAGE_STREET:
		updateStreet( );
		break;
	case STAGE_CAVE:
		updateCave( );
		break;
	case STAGE_TOKU:
		updateToku( );
		break;
	}
}

void RockMapStreet::updateStreet( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		{//�����֍s����STAGE_CAVE�ֈړ�
			double length = ( Vector( -200, 0, -500 ) - player->getPos( ) ).getLength( );
			if ( length < 100 ) {
				_drawer.reset( );
				_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_CAVE ) );
				family->resetPos( Vector( 0, 10, 0 ) );
			}
		}

		{//���ȏ�̂������W�߂�ƁASTAGE_TOKU�ֈړ�
			Status::Player status = _status->getPlayer( i );
			if ( status.money >= TELEPORT_MONEY ) {
				_drawer.reset( );
				_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_TOKU ) );
				family->resetPos( Vector( 0, 10000, -500 ) );
			}
		}
	}
}

void RockMapStreet::updateCave( ) {
	_time++;
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		if ( _time > REMOVE_CAVE_TIME ) {
			_drawer.reset( );
			_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );
			family->resetPos( Vector( 0, 30, -500 ) );
			_time = 0;
		}
	}
}

void RockMapStreet::updateToku( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		{//���ȏ�̓����W�߂�ƁA���U���g�}�b�v��
			Status::Player status = _status->getPlayer( i );
			if ( status.toku >= TELEPORT_TOKU ) {
				unsigned int state = STATE_RESULT;
				MessageSender::getTask( )->sendMessage( i, Message::COMMAND_STATE, &state );
			}
		}
	}
}