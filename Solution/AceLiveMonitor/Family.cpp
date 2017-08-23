#include "Family.h"
#include "Player.h"
#include "Application.h"
#include "SynchronousData.h"
#include "Device.h"
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
		_player[ i ] = PlayerPtr( new Player( INIT_PLAYER_POS[ i ] ) );
	}
	double camera_pos = 0.0;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		camera_pos += _player[ i ]->getPos( ).x;
	}
	_camera_pos = camera_pos * 0.25 - SCREEN_WIDTH / 2;
	_set_device = 0;
}

void Family::update( ) {
	bool update_camera = true;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ]->update( );
		if ( _player[ i ]->getArea( ) != AREA_EVENT ) {
			//キャラクターが右端にいる場合、カメラのポジションを変えない
			if ( ( _camera_pos - SCREEN_WIDTH / 2 ) + SCROLL_BUFFER > _player[ i ]->getPos( ).x ) {
				update_camera = false;
			}
		}
	}
	if ( update_camera ) {
		updateCameraPos( );
	}

	// 同期データ
	setSynchronousData( );

	// device
	updateSetDevice( );
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
	double camera_pos = 0;
	//プレイヤーの平均を出すための値
	double pos_ratio = CAMERA_MAIN_RATIO;
	//プレイヤーの位置の合計を出す
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( _player[ i ]->getArea( ) == AREA_EVENT ) {
			pos_ratio = CAMERA_EVENT_RATIO;
			continue;
		}
		camera_pos += _player[ i ]->getPos( ).x;
	}

	//平均を計算
	camera_pos = camera_pos * pos_ratio - SCREEN_WIDTH / 2;

	//左に行く場合抜ける
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

void Family::setSynchronousData( ) const {
	unsigned char TYPE[ 4 ] = {
		SynchronousData::TYPE_TAROSUKE,
		SynchronousData::TYPE_TAROJIRO,
		SynchronousData::TYPE_GARISUKE,
		SynchronousData::TYPE_TAROMI  ,
	};

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerConstPtr player = getPlayer( i );
		player->setSynchronousData( TYPE[ i ], ( int )getCameraPos( ) );
	}
}

void Family::updateSetDevice( ) {
	DevicePtr device( Device::getTask( ) );
	if ( !( _set_device < MAX_PLAYER ) ) {
		return;
	}

	// デバイスが接続されていなかったら、キーボードで全プレイヤーを操作できるようにする
	int device_num = device->getDeviceNum( );
	if ( device_num < 1 ) {
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			_player[ i ]->setDeviceId( 0 );
		}
		_set_device = MAX_PLAYER;
	}

	for ( int i = 0; i < device_num; i++ ) {
		if ( device->getButton( i ) &&
			 !isSettingDevice( i ) ) {
			_player[ _set_device ]->setDeviceId( i );
			_set_device++;
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
