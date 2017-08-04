#include "Family.h"
#include "Player.h"
#include "Application.h"
#include <assert.h>

const int CAMERA_SCROLL_SPEED = 8;
const int SCROLL_BUFFER = SCREEN_WIDTH / 10;

const Vector INIT_PLAYER_POS[ ACE_PLAYER_NUM ] = {
	Vector( SCREEN_WIDTH / 2 + 150, NORMAL_CHAR_GRAPH_SIZE ),
	Vector( SCREEN_WIDTH / 2 + 250, NORMAL_CHAR_GRAPH_SIZE ),
	Vector( SCREEN_WIDTH / 2 + 350, NORMAL_CHAR_GRAPH_SIZE ),
	Vector( SCREEN_WIDTH / 2 + 450, NORMAL_CHAR_GRAPH_SIZE )
};

FamilyPtr Family::getTask( ) {
	return std::dynamic_pointer_cast< Family >( Application::getInstance( )->getTask( getTag( ) ) );
}


Family::Family( ) {
}


Family::~Family( ) {
}

void Family::initialize( ) {
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ] = PlayerPtr( new Player( i, INIT_PLAYER_POS[ i ] ) );
	}
	double camera_pos = 0.0;
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		camera_pos += _player[ i ]->getPos( ).x;
	}
	_camera_pos = camera_pos * 0.25 - SCREEN_WIDTH / 2;
}

void Family::update( ) {
	bool update_camera = true;
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		_player[ i ]->update( );
		if ( ( _camera_pos - SCREEN_WIDTH / 2 ) + SCROLL_BUFFER > _player[ i ]->getPos( ).x ) {
			update_camera = false;
		}
	}
	if ( update_camera ) {
		updateCameraPos( );
	}
}

PlayerConstPtr Family::getPlayer( int player_id ) const {
	assert( player_id < ACE_PLAYER_NUM );
	assert( player_id >= 0 );
	return _player[ player_id ];
}

PlayerPtr Family::getPlayer( int player_id ) {
	assert( player_id < ACE_PLAYER_NUM );
	assert( player_id >= 0 );
	return _player[ player_id ];
}

void Family::updateCameraPos( ) {
	double camera_pos = 0;
	//�v���C���[�̈ʒu�̍��v���o��
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		if ( _player[ i ]->getState( ) == Character::STATE_EVENT ) {
			continue;
		}
		camera_pos += _player[ i ]->getPos( ).x;
	}
	//�v���C���[�̕��ς��o�����߂̒l
	double pos_ratio = 0.25;
	if ( isExistancePlayerEvent( ) ) {
		pos_ratio = 1.0 / ( ACE_PLAYER_NUM - 1 );
	}

	//���ς��v�Z
	camera_pos = camera_pos * pos_ratio - SCREEN_WIDTH / 2;

	//���ɍs���ꍇ������
	if ( _camera_pos - camera_pos > 0 ) {
		return;
	}

	if ( _camera_pos - camera_pos > CAMERA_SCROLL_SPEED ) {
		_camera_pos -= CAMERA_SCROLL_SPEED;
	}
	if ( _camera_pos - camera_pos < -CAMERA_SCROLL_SPEED ) {
		_camera_pos += CAMERA_SCROLL_SPEED;
	}
	if ( fabs( _camera_pos - camera_pos ) < CAMERA_SCROLL_SPEED ) {
		_camera_pos = camera_pos;
	}
}

double Family::getCameraPos( ) const {
	return _camera_pos;
}

bool Family::isExistancePlayerEvent( ) const {
	bool result = false;
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		if ( _player[ i ]->getState( ) == Character::STATE_EVENT ) {
			result = true;
			break;
		}
	}
	return result;
}
