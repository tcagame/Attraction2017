#include "Family.h"
#include "Player.h"
#include "Monmotaro.h"
#include "Application.h"
#include "SynchronousData.h"
#include "Device.h"
#include "World.h"
#include "Map.h"
#include "Sound.h"
#include <assert.h>
#include "Military.h"
#include "Storage.h"
#include "Office.h"

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
	}
	
	double camera_pos = 0.0;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		camera_pos += _player[ i ]->getPos( ).x;
	}
	_camera_pos_x = ( int )( camera_pos * 0.25 ) - SCREEN_WIDTH / 2;
	
	_monmotaro = MonmotaroPtr( new Monmotaro );
}

void Family::update( ) {

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		updatePlayer( ( PLAYER )i );
	}
	
	updateCameraPos( );
	_monmotaro->update( );
}

void Family::updatePlayer( PLAYER target ) {
	// プレイヤー更新
	_player[ target ]->update( );
	
	if ( !_player[ target ]->isExist( ) ) {
		return;
	}
		
	//キャラクターが右端にいる場合、カメラのポジションを変えない
	if ( _player[ target ]->getArea( ) == AREA_STREET ) {
		if ( ( _camera_pos_x - SCREEN_WIDTH / 2 ) + SCROLL_BUFFER > _player[ target ]->getPos( ).x ) {
			_updating_camera = false;
		}
	}

	// playerの頭の上で跳ねる
	for ( int j = 0; j < MAX_PLAYER; j++ ) {
		if ( !_player[ j ]->isExist( ) ) {
			continue;
		}
		if ( _player[ j ]->getArea( ) != _player[ target ]->getArea( ) ) {
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
	if ( !isInScrollRange( ) ) {
		return;
	}

	//座標調整
	int map_width = World::getTask( )->getMap( AREA_STREET )->getPageNum( ) * GRAPH_SIZE;
	if ( _camera_pos_x > map_width + SCREEN_WIDTH ) {
		_camera_pos_x -= map_width;
		shiftPos( );
	}
	double total = 0;
	//プレイヤーの平均を出すための値
	int num = 0;
	//プレイヤーの位置の合計を出す
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( _player[ i ]->getArea( ) == AREA_EVENT ) {
			total += _camera_pos_x + SCREEN_WIDTH / 2;
		} else {
			total += _player[ i ]->getPos( ).x;
		}
	}

	//平均を計算
	double camera_pos = total / MAX_PLAYER - SCREEN_WIDTH / 2;

	//左に行く場合抜ける
	if ( _camera_pos_x - camera_pos > 0 ) {
		return;
	}
	if ( fabs( _camera_pos_x - camera_pos ) < CAMERA_SCROLL_SPEED ) {
		_camera_pos_x = ( int )camera_pos;
	}
	if ( _camera_pos_x - camera_pos < -CAMERA_SCROLL_SPEED ) {
		_camera_pos_x += CAMERA_SCROLL_SPEED;
	}
}

int Family::getCameraPosX( ) const {
	return _camera_pos_x;
}

bool Family::isExistOnEvent( ) const {
	bool exist = false;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PLAYER target = ( PLAYER )i;
		if ( _player[ target ]->getArea( ) == AREA_EVENT ) {
			exist = true;
			break;
		}
	}
	return exist;
}

void Family::pushDebugData( ViewerDebug::Data& data ) const {
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( !_player[ i ]->isExist( ) ) {
			continue;
		}
		data.circle.push_back( _player[ i ]->getDebugDataCircle( ) );
	}
	data.message.push_back( "CameraX:" + std::to_string( ( int )_camera_pos_x ) );
}

void Family::shiftPos( ) {
	int map_width = World::getTask( )->getMap( AREA_STREET )->getPageNum( ) * GRAPH_SIZE;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ]->shiftPos( map_width );
	}
	Military::getTask( )->shiftPos( map_width );
	Storage ::getTask( )->shiftPos( map_width );
	Office  ::getTask( )->shiftPos( map_width );
	World   ::getTask( )->shiftPos( map_width );
}

bool Family::isModeVirtue( ) const {
	bool mode_virtue = false;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( _player[ i ]->getMode( ) == Player::MODE_VIRTUE ) {
			mode_virtue = true;
			break;
		}
	}
	return mode_virtue;
}



PlayerPtr Family::getOverlappedPlayer( CharacterConstPtr target ) const {
	PlayerPtr result = PlayerPtr( );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		if ( !_player[ i ]->isExist( ) ) {
			continue;
		}
		if ( _player[ i ]->getArea( ) != target->getArea( ) ) {
			continue;
		}

		if ( _player[ i ]->isOverlapped( target ) ) {
			result = _player[ i ];
			break;
		}
	}
	return result;
}

void Family::setSynchronousData( ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setCameraX( getCameraPosX( ) );

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerConstPtr player = getPlayer( i );
		player->setSynchronousData( ( PLAYER )i, getCameraPosX( ) );
	}

	_monmotaro->setSynchronousData( );
}

bool Family::isInScrollRange( ) const {
	//プレイヤーが2人以上のとき
	//コンソールの画面内に仲間キャラクターが映るときのみスクロール
	//コンソールのプレイヤーが映らなくなる範囲は320から
	//int tmp_x = -1;
	//int right_second = -1;
	//for ( int i = 0; i < MAX_PLAYER; i++ ) {
	//	if ( !_player[ i ]->isExist( ) ) {
	//		continue;
	//	}
	//	if ( _player[ i ]->getPos( ).x
	//}
	return true;
}

void Family::call( PlayerPtr player ) {
	_monmotaro->appear( player );
}