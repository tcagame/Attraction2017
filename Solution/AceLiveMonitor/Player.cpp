#include "Player.h"
#include "Device.h"
#include "Armoury.h"
#include "ace_define.h"
#include "Family.h"
#include "Map.h"
#include "Viewer.h"
#include "ViewerEvent.h"
#include "MapEvent.h"
#include "Military.h"
#include "Enemy.h"
#include "Storage.h"

//画像サイズ
const int PLAYER_FOOT = 7;
//速度
const int MAX_SPEED = 20;
const int MOVE_SPEED = 7;
const int BRAKE_ACCEL = 1;
const int JUMP_POWER = -15;
//攻撃関係
const int CHARGE_PHASE_COUNT = 25;
const int MAX_CHARGE_COUNT = CHARGE_PHASE_COUNT * 4 - 1;
const int BURST_TIME = 60;
//アニメーション
const int PLAYER_ANIM_WAIT_COUNT = 12;
const int PLAYER_ANIM_WIDTH_NUM = 10;
const int DAMEGE_COUNT = 20;

Player::Player( int player_id, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE ),
_charge_count( 0 ),
_damege_count( 0 ),
_over_charge_time( -1 ),
_id( 0 ),
_action( ACTION_WAIT ) {
	setRadius( 25 );
	setDir( DIR_RIGHT );
}

Player::~Player( ) {
}

void Player::act( ) {
	switch ( _action ) {
	case ACTION_WAIT:
		actOnWaiting( );
		break;
	case ACTION_WALK:
		actOnWalking( );
		break;
	case ACTION_BRAKE:
		actOnBreaking( );
		break;
	case ACTION_FLOAT:
		actOnFloating( );
		break;
	case ACTION_ATTACK:
		actOnAttack( );
		break;
	case ACTION_CHARGE:
		actOnCharge( );
		break;
	case ACTION_OVER_CHARGE:
		actOnOverCharge( );
		break;
	case ACTION_DAMEGE:
		actOnDamege( );
		break;
	}
	actOnCamera( );
	updateState( );
}

void Player::actOnWaiting( ) {
	//デバイスのスティック入力があった場合、action_walk
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	Vector vec = getVec( );
	if ( fabs( vec.x ) > 0 ) {
		_action = ACTION_BRAKE;
		return;
	}
	DevicePtr device( Device::getTask( ) );
	if ( abs( device->getDirX( _id ) ) > 50 ) {
		_action = ACTION_WALK;
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
		return;
	}
	if ( device->getDirY( _id ) > 0 ) {
		_action = ACTION_CHARGE;
		return;
	}
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		_action = ACTION_FLOAT;
		vec.y = JUMP_POWER;
	}
	setVec( vec );
	_charge_count -= 2;
	if ( _charge_count < 0 ) {
		_charge_count = 0;
	}
}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	DevicePtr device( Device::getTask( ) );
	Vector vec = getVec( );
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	if ( device->getDirX( _id ) * vec.x < 0 ) {
		_action = ACTION_BRAKE;
		return;
	}
	if ( device->getDirX( _id ) == 0 ) {
		_action = ACTION_WAIT;
		return;
	}

	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		_action = ACTION_FLOAT;
		vec.y = JUMP_POWER;
	}
	if ( device->getDirX( _id ) < -50 ) {
		vec.x = -MOVE_SPEED;
	}
	if ( device->getDirX( _id ) > 50 ) {
		vec.x = MOVE_SPEED;
	}
	setVec( vec );
}

void Player::actOnBreaking( ) {
	Vector vec = getVec( );
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	if ( ( int )vec.x == 0 ) {
		_action = ACTION_WAIT;
	}
	DevicePtr device( Device::getTask( ) );
	if ( device->getDirX( ) * vec.x > 0 ) {
		_action = ACTION_WALK;
	}
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		_action = ACTION_FLOAT;
	}
	if ( vec.x < 0 ) {
		if ( vec.x < -BRAKE_ACCEL ) {
			vec.x += BRAKE_ACCEL;
		} else {
			vec.x = 0;
		}
	}
	if ( vec.x > 0 ) {
		if ( vec.x > BRAKE_ACCEL ) {
			vec.x -= BRAKE_ACCEL;
		} else {
			vec.x = 0;
		}
	}
	setVec( vec );
}

void Player::actOnFloating( ) {
	if ( isStanding( ) ) {
		_action = ACTION_WAIT;
		return;
	}
	DevicePtr device( Device::getTask( ) );
	Vector vec = getVec( );
	// 空中の移動
	int dir_x = device->getDirX( _id );
	//右に移動してるとき
	if ( vec.x >= 0 ) {
		//入力方向が逆
		if ( dir_x < 0 ) {
			if ( vec.x > BRAKE_ACCEL ) {
				vec.x -= BRAKE_ACCEL;
			} else {
				vec.x = 0;
			}
		}
		//入力が同じ
		if ( dir_x > 0 ) {
			vec.x = MOVE_SPEED;
		}
	}

	//左に移動してるとき
	if ( vec.x <= 0 ) {
		//入力方向が逆
		if ( dir_x > 0 ) {
			if ( vec.x < -BRAKE_ACCEL ) {
				vec.x += BRAKE_ACCEL;
			} else {
				vec.x = 0;
			}
		}
		//入力方向が一緒
		if ( dir_x < 0 ) {
			vec.x = -MOVE_SPEED;
		}
	}

	setVec( vec );
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
	}
}

void Player::actOnAttack( ) {
	int power = ( _charge_count / CHARGE_PHASE_COUNT ) + 1;
	ShotPtr shot( new Shot( getPos( ), getDir( ), power ) );
	shot->setState( getState( ) );
	Armoury::getTask( )->add( shot );
	_action = ACTION_WAIT;
	_charge_count = 0;
}

void Player::actOnCharge( ) {
	DevicePtr device( Device::getTask( ) );
	if ( !isStanding( ) ) {
		_action = ACTION_FLOAT;
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		_action = ACTION_ATTACK;
		return;
	}
	if ( device->getDirY( _id ) <= 0 ) {
		if ( device->getDirX( _id ) == 0 ) {
			_action = ACTION_WAIT;
			return;
		} else {
			_action = ACTION_WALK;
			return;
		}
		Vector vec = getVec( );
		if ( device->getPush( _id ) & BUTTON_C ) {
			vec.y = JUMP_POWER;
			setVec( vec );
			_action = ACTION_FLOAT;
			return;
		}
	}
	_charge_count++;
	if ( _charge_count > MAX_CHARGE_COUNT ) {
		_charge_count = 0;
		_over_charge_time = getActCount( );
		_action = ACTION_OVER_CHARGE;
	}
}

void Player::actOnOverCharge( ) {
	if ( _over_charge_time < 0 ) {
		_action = ACTION_WAIT;
		return;
	}

	if ( getActCount( ) - _over_charge_time > BURST_TIME ) {
		_action = ACTION_WAIT;
		_over_charge_time = -1;
	}
}

void Player::actOnCamera( ) {
	FamilyConstPtr family( Family::getTask( ) );
	int x = 0;
	if ( getState( ) != STATE_EVENT ) {
		x += ( int )family->getCameraPos( );
	}
	if ( getPos( ).x + getVec( ).x - getRadius( ) < x ) {
		Vector pos( getPos( ) );
		pos.x = x + getRadius( );
		setPos( pos );
		Vector vec( getVec( ) );
		vec.x = 0;
		setVec( vec );
	}
	if ( getPos( ).x + getVec( ).x + getRadius( ) > x + SCREEN_WIDTH ) {
		Vector pos( getPos( ) );
		pos.x = ( x + SCREEN_WIDTH ) - getRadius( );
		setPos( pos );
		Vector vec( getVec( ) );
		vec.x = 0;
		setVec( vec );
	}
}

void Player::actOnDamege( ) {
	if ( _damege_count == 0 ) {
		_action = ACTION_WAIT;
		return;
	}
	_damege_count--;
	if ( _damege_count < DAMEGE_COUNT / 2 ) {
		Vector vec = getVec( );
		//ひるみ中でも移動できるようにする
		DevicePtr device( Device::getTask( ) );
		if ( device->getDirX( _id ) < -50 ) {
			vec.x = -MOVE_SPEED;
		}
		if ( device->getDirX( _id ) > 50 ) {
			vec.x = MOVE_SPEED;
		}
		setVec( vec );
	}
	if ( _damege_count < 0 ) {
		_action = ACTION_WAIT;
		_damege_count = 0;
	}
}


void Player::damage( int force ) {
	if ( _damege_count > 0 ) {
		return;
	}

	_action = ACTION_DAMEGE;
	_damege_count = DAMEGE_COUNT;
	setVec( Vector( ) );
}

Player::ACTION Player::getAction( ) const {
	return _action;
}

Chip Player::getChip( ) const {
	Chip chip = Chip( );
	chip.size = NORMAL_CHAR_GRAPH_SIZE;
	int cx = 0;
	int cy = 0;
	switch ( _action ) {
	case ACTION_WAIT:
		{
			const int ANIM[ ] = {
				0,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_WALK:
		{
			const int ANIM[ ] = {
				0, 1, 2, 1, 0, 3, 4, 3
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_BRAKE:
		{
			const int ANIM[ ] = {
				6,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_FLOAT:
		{
			const int ANIM[ ] = {
				5,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_CHARGE:
		{
			const int ANIM[ ] = {
				30, 31, 32, 33, 34, 35, 36
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( _charge_count / ( CHARGE_PHASE_COUNT / 2 ) ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( _charge_count / ( CHARGE_PHASE_COUNT / 2 ) ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_OVER_CHARGE:
		{
			const int ANIM[ ] = {
				38, 39
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_DAMEGE:
		{
			const int ANIM[ ] = {
				63
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( _damege_count / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( _damege_count / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	}

	
	chip.tx = cx * NORMAL_CHAR_GRAPH_SIZE;
	chip.ty = cy * NORMAL_CHAR_GRAPH_SIZE;
	Vector pos = getPos( );
	if ( getDir( ) == DIR_LEFT ) {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	} else {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 - NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	}
	return chip;
}

int Player::getChargeCount( ) const {
	return _charge_count;
}

Chip Player::getChargeChip( ) const {
	if ( !( _charge_count > 0 ) ) {
		return Chip( );
	}

	Chip chip = Chip( );
	Vector pos = getPos( );
	if ( getDir( ) == DIR_LEFT ) {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	} else {
		chip.sx1 = (int)pos.x - NORMAL_CHAR_GRAPH_SIZE / 2 + NORMAL_CHAR_GRAPH_SIZE;
		chip.sy1 = (int)pos.y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_FOOT;
		chip.sx2 = chip.sx1 - NORMAL_CHAR_GRAPH_SIZE;
		chip.sy2 = chip.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	}
	const int ANIM[ ] = {
		2, 3, 4, 5, 6, 7, 8, 9, 10, 11
	};
	int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int phase = ( _charge_count / CHARGE_PHASE_COUNT ) * 2;
	int time = ( getActCount( ) / 2 ) % 2;
	chip.tx = ( ANIM[ phase + time ] % 8 ) * NORMAL_CHAR_GRAPH_SIZE;
	chip.ty = ( ANIM[ phase + time ] / 8 ) * NORMAL_CHAR_GRAPH_SIZE;
	chip.size = NORMAL_CHAR_GRAPH_SIZE;

	return chip;
}

void Player::updateState( ) {
	//イベント
	MapPtr map( Map::getTask( ) );
	MapEventPtr map_event( MapEvent::getTask( ) );
	FamilyPtr family( Family::getTask( ) );
	MapEvent::TYPE event_type = map_event->getType( );
	if ( event_type == MapEvent::TYPE_TITLE ) {
		bool event_obj = true;
		unsigned char obj = map->getObject( getPos( ) + getVec( ) );
		switch ( obj ) {
		case OBJECT_EVENT_REDDEAMON:
			map_event->setType( MapEvent::TYPE_RED_DEMON );
			break;
		case OBJECT_EVENT_FIRE:
			map_event->setType( MapEvent::TYPE_FIRE );
			break;
		case OBJECT_EVENT_TREE:
			map_event->setType( MapEvent::TYPE_TREE );
			break;
		case OBJECT_EVENT_ROCK:
			map_event->setType( MapEvent::TYPE_ROCK );
			break;
		case OBJECT_EVENT_SHOP:
			map_event->setType( MapEvent::TYPE_SHOP );
			break;
		case OBJECT_EVENT_RYUGU:
			map_event->setType( MapEvent::TYPE_RYUGU );
			break;
		case OBJECT_EVENT_LAKE:
			map_event->setType( MapEvent::TYPE_LAKE );
			break;
		default:
			event_obj = false;
			break;
		}
		if ( event_obj ) {
			setState( STATE_EVENT );
			setPos( Vector( GRAPH_SIZE * 3 / 2, 0 ) );
			setVec( Vector( ) );
		}
	}

	if ( getState( ) == STATE_EVENT ) {
		//一ページ目にいたらメインに戻る
		if ( getPos( ).x < GRAPH_SIZE ) {
			setState( STATE_MAIN );
			map_event->setType( MapEvent::TYPE_TITLE );
			setPos( Vector( family->getCameraPos( ) + SCREEN_WIDTH / 2, 0 ) );
			setVec( Vector( ) );
		}
		//ボスが倒れている場合 && アイテムが無い[退場]
		MapEventPtr map_event( MapEvent::getTask( ) );
		StoragePtr storage( Storage::getTask( ) );
		if ( !Military::getTask( )->getBoss( ) &&
			 !storage->isExistanceEventItem( ) &&
			 map_event->getType( ) < MapEvent::TYPE_SHOP ) {
			setState( STATE_MAIN );
			map_event->setType( MapEvent::TYPE_TITLE );
			setPos( Vector( family->getCameraPos( ) + SCREEN_WIDTH / 2, 0 ) );
			setVec( Vector( ) );
		}
	}
}

bool Player::isOnHead( EnemyPtr target ) const {
	if ( _action != ACTION_FLOAT ) {
		return false;
	}
	Vector player = getPos( ) + Vector( 0, -getChipSize( ) / 2 );
	Vector enemy  = target->getPos( ) + Vector( 0, -target->getChipSize( ) / 2 );
	Vector vec = enemy - player;
	if ( vec.y < 0 ) {
		return false;
	}
	if ( vec.getLength( ) < target->getRadius( ) ) {
		return false;
	}
	return true;
}

void Player::bound( ) {
	_action = ACTION_FLOAT;
	Vector vec = getVec( );
	vec.y = JUMP_POWER;
	setVec( vec );
}
