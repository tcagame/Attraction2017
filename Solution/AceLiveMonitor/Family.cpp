#include "Family.h"
#include "Player.h"
#include "Monmotaro.h"
#include "Application.h"
#include "SynchronousData.h"
#include "Device.h"
#include "Sound.h"
#include <assert.h>

const int CAMERA_SCROLL_SPEED = 8;
const int SCROLL_BUFFER = SCREEN_WIDTH / 10;
const double CAMERA_MAIN_RATIO = 1.0 / MAX_PLAYER;
const double CAMERA_EVENT_RATIO = 1.0 / ( MAX_PLAYER - 1 );

const Vector INIT_PLAYER_POS[ MAX_PLAYER ] = {
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
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ] = PlayerPtr( new Player( ( PLAYER )i, INIT_PLAYER_POS[ i ] ) );
		_state[ i ] = STATE_DEVICE_WAIT;
	}
	_state[ 0 ] = STATE_DEVICE_SYNC;
	_setting_device = 0;

	// �f�o�C�X���ڑ�����Ă��Ȃ�������A�L�[�{�[�h�őS�v���C���[�𑀍�ł���悤�ɂ���
	DevicePtr device = Device::getTask( );
	if ( device->getDeviceNum( ) == 0 ) {
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			_player[ i ]->setDeviceId( 0 );
			_state[ i ] = STATE_PLAY; // �Ƃ肠�����S�L�����o��
		}
		_setting_device = MAX_PLAYER;
	}
	
	_monmo = MonmotaroPtr( new Monmotaro( Vector( ) ) );
	double camera_pos = 0.0;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		camera_pos += _player[ i ]->getPos( ).x;
	}
	_camera_pos_x = camera_pos * 0.25 - SCREEN_WIDTH / 2;
}

void Family::update( ) {

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		switch ( _state[ i ] ) {
		case STATE_DEVICE_WAIT:
			break;
		case STATE_DEVICE_SYNC:
			break;
		case STATE_ENTRY:
			break;
		case STATE_PLAY:
			updatePlay( ( PLAYER )i );
			break;
		case STATE_CONTINUE:
			break;
		}
	}
	
	updateCameraPos( );

	// device
	//updateSettingDevice( );
	//updateCommon( );

	_monmo->update( );

	// �����f�[�^
	setSynchronousData( );
}

void Family::updatePlay( PLAYER target ) {
	// �v���C���[�X�V
	_player[ target ]->update( );
	
	if ( _player[ target ]->getArea( ) == AREA_EVENT ) {
		return;
	}
		
	//�L�����N�^�[���E�[�ɂ���ꍇ�A�J�����̃|�W�V������ς��Ȃ�
	if ( ( _camera_pos_x - SCREEN_WIDTH / 2 ) + SCROLL_BUFFER > _player[ target ]->getPos( ).x ) {
		_updating_camera = false;
	}

	// player�̓��̏�Œ��˂�
	for ( int j = 0; j < MAX_PLAYER; j++ ) {
		if ( _state[ j ] != STATE_PLAY ) {
			continue;
		}
		if ( _player[ j ]->getArea( ) != AREA_STREET ) {
			continue;
		}
		if ( target == j ) {
			continue;
		}
		if ( _player[ target ]->isOverlapped( _player[ j ] ) &&
				_player[ target ]->isOnHead( _player[ j ] ) ) {
			_player[ target ]->bound( );
		}
	}

	
}

PlayerConstPtr Family::getPlayer( int player_id ) const {
	assert( player_id < MAX_PLAYER );
	assert( player_id >= 0 );
	return _player[ player_id ];
}

PlayerPtr Family::getPlayer( int player_id ) {
	assert( player_id < MAX_PLAYER );
	assert( player_id >= 0 );
	return _player[ player_id ];
}

void Family::updateCameraPos( ) {
	bool updating = _updating_camera;
	_updating_camera = true;
	if ( !updating ) {
		return;
	}

	double camera_pos = 0;
	//�v���C���[�̕��ς��o�����߂̒l
	double pos_ratio = CAMERA_MAIN_RATIO;
	//�v���C���[�̈ʒu�̍��v���o��
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( _player[ i ]->getArea( ) == AREA_EVENT ) {
			pos_ratio = CAMERA_EVENT_RATIO;
			continue;
		}
		camera_pos += _player[ i ]->getPos( ).x;
	}

	//���ς��v�Z
	camera_pos = camera_pos * pos_ratio - SCREEN_WIDTH / 2;

	//���ɍs���ꍇ������
	if ( _camera_pos_x - camera_pos > 0 ) {
		return;
	}

	if ( _camera_pos_x - camera_pos > CAMERA_SCROLL_SPEED ) {
		_camera_pos_x -= CAMERA_SCROLL_SPEED;
	}
	if ( _camera_pos_x - camera_pos < -CAMERA_SCROLL_SPEED ) {
		_camera_pos_x += CAMERA_SCROLL_SPEED;
	}
	if ( fabs( _camera_pos_x - camera_pos ) < CAMERA_SCROLL_SPEED ) {
		_camera_pos_x = camera_pos;
	}
}

int Family::getCameraPosX( ) const {
	return ( int )_camera_pos_x;
}

void Family::setSynchronousData( ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setCameraX( getCameraPosX( ) );

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerConstPtr player = getPlayer( i );

		switch ( _state[ i ] ) {
		case STATE_ENTRY:
			data->setStatusState( ( PLAYER )i, SynchronousData::STATE_ENTRY ); 
			break;
		case STATE_CONTINUE:
			data->setStatusState( ( PLAYER )i, SynchronousData::STATE_CONTINUE); 
			break;
		case STATE_PLAY:
			if ( player->getArea( ) == AREA_STREET ) {
				data->setStatusState( ( PLAYER )i, SynchronousData::STATE_PLAY_STREET ); 
			} else {
				data->setStatusState( ( PLAYER )i, SynchronousData::STATE_PLAY_EVENT );
			}
			player->setSynchronousData( ( PLAYER )i, getCameraPosX( ) );
		}

	}
}

void Family::updateSettingDevice( ) {
	if ( !( _setting_device < MAX_PLAYER ) ) {
		return;
	}

	DevicePtr device( Device::getTask( ) );
	int device_num = device->getDeviceNum( );
	for ( int i = 0; i < device_num; i++ ) {
		if ( device->getButton( i ) &&
			 !isSettingDevice( i ) ) {
			_player[ _setting_device ]->setDeviceId( i );
			_setting_device++;
		}
	}
}

bool Family::isSettingDevice( int device_id ) const {
	bool result = false;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( _player[ i ]->getDeviceId( ) == device_id ) {
			result = true;
		}
	}
	return result;
}


MonmotaroConstPtr Family::getMonmotaro( ) const {
	return _monmo;
}


