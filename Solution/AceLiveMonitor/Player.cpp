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
#include "Debug.h"
#include "SynchronousData.h"
#include "Magazine.h"
#include "Impact.h"

//画像サイズ
static const int PLAYER_FOOT = 7;
//速度
static const int MAX_SPEED = 20;
static const int MOVE_SPEED = 7;
static const int BRAKE_ACCEL = 1;
static const int JUMP_POWER = -10;
static const int BLOW_POWER = -30;
//攻撃関係
static const int CHARGE_PHASE_COUNT = 25;
static const int MAX_CHARGE_COUNT = CHARGE_PHASE_COUNT * 4 - 1;
static const int BURST_TIME = 60;
static const int MAX_HP = 16;
//アニメーション
static const int PLAYER_ANIM_WAIT_COUNT = 12;
static const int PLAYER_ANIM_WIDTH_NUM = 10;
static const int PLAYER_FLASH_WAIT_TIME = 2;
//カウント
static const int MAX_DAMEGE_COUNT = 20;
static const int MAX_BACK_COUNT = 6;
static const int MAX_UNRIVALED_COUNT = 45;
static const int MAX_DEAD_ACTCOUNT = 120;
static const int MAX_IMPACT_COUNT = 30;

Player::Player( int player_id, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_over_charge_time( -1 ),
_id( 0 ),
_money( 0 ),
_toku( 0 ),
_charge_count( 0 ),
_unrivaled_count( MAX_UNRIVALED_COUNT ),
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
	case ACTION_BLOW_AWAY:
		actOnBlowAway( );
		break;
	case ACTION_DAED:
		actOnDead( );
		break;
	}
	actOnCamera( );
	updateState( );
	_unrivaled_count++;
}

void Player::actOnWaiting( ) {
	//デバイスのスティック入力があった場合、action_walk
	if ( !isStanding( ) ) {
		setAction( ACTION_FLOAT );
		return;
	}
	Vector vec = getVec( );
	if ( fabs( vec.x ) > 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	DevicePtr device( Device::getTask( ) );
	if ( abs( device->getDirX( _id ) ) > 50 ) {
		setAction( ACTION_WALK );
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		setAction( ACTION_ATTACK );
		return;
	}
	if ( device->getDirY( _id ) > 0 ) {
		setAction( ACTION_CHARGE );
		return;
	}
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		setAction( ACTION_FLOAT );
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
		setAction( ACTION_FLOAT );
		return;
	}
	if ( device->getDirX( _id ) * vec.x < 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	if ( device->getDirX( _id ) == 0 ) {
		setAction( ACTION_WAIT );
		return;
	}

	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		setAction( ACTION_FLOAT );
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
		setAction( ACTION_FLOAT );
		return;
	}
	if ( ( int )vec.x == 0 ) {
		setAction( ACTION_WAIT );
	}
	DevicePtr device( Device::getTask( ) );
	if ( device->getDirX( ) * vec.x > 0 ) {
		setAction( ACTION_WALK );
	}
	if ( isStanding( ) && device->getPush( _id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		setAction( ACTION_FLOAT );
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
		setAction( ACTION_WAIT );
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
		setAction( ACTION_ATTACK );
	}
}

void Player::actOnAttack( ) {
	int power = ( _charge_count / CHARGE_PHASE_COUNT ) + 1;
	ShotPtr shot( new Shot( getPos( ), getDir( ), power ) );
	shot->setState( getState( ) );
	Armoury::getTask( )->add( shot );
	setAction( ACTION_WAIT );
	_charge_count = 0;
}

void Player::actOnCharge( ) {
	DevicePtr device( Device::getTask( ) );
	if ( !isStanding( ) ) {
		setAction( ACTION_FLOAT );
		return;
	}
	if ( device->getPush( _id ) & BUTTON_A ) {
		setAction( ACTION_ATTACK );
		return;
	}
	if ( device->getDirY( _id ) <= 0 ) {
		if ( device->getDirX( _id ) == 0 ) {
			setAction( ACTION_WAIT );
			return;
		} else {
			setAction( ACTION_WALK );
			return;
		}
		Vector vec = getVec( );
		if ( device->getPush( _id ) & BUTTON_C ) {
			vec.y = JUMP_POWER;
			setVec( vec );
			setAction( ACTION_FLOAT );
			return;
		}
	}
	_charge_count++;
	if ( _charge_count > MAX_CHARGE_COUNT ) {
		_charge_count = 0;
		_over_charge_time = getActCount( );
		setAction( ACTION_OVER_CHARGE );
	}
}

void Player::actOnOverCharge( ) {
	if ( _over_charge_time < 0 ) {
		setAction( ACTION_WAIT );
		return;
	}

	if ( getActCount( ) - _over_charge_time > BURST_TIME ) {
		setAction( ACTION_WAIT );
		_over_charge_time = -1;
	}
}

void Player::actOnCamera( ) {
	FamilyConstPtr family( Family::getTask( ) );
	int x = 0;
	if ( getState( ) != STATE_EVENT ) {
		x += ( int )family->getCameraPos( );
	}
	Vector pos = getPos( );
	Vector vec = getVec( );
	double radius = getRadius( );
	if ( pos.x + vec.x - radius < x ) {
		pos.x = x + radius;
		vec.x = 0;
		setPos( pos );
		setVec( vec );
	}
	if ( getPos( ).x + getVec( ).x + getRadius( ) > x + SCREEN_WIDTH ) {
		pos.x = ( x + SCREEN_WIDTH ) - radius;
		vec.x = 0;
		setPos( pos );
		setVec( vec );
	}
}

void Player::actOnDamege( ) {
	int act_count = getActCount( );
	if ( act_count >= MAX_DAMEGE_COUNT ) {
		setAction( ACTION_WAIT );
		return;
	}
	if ( act_count > MAX_BACK_COUNT ) {
		setVec( Vector( 0, getVec( ).y ) );
	}
	if ( act_count > MAX_DAMEGE_COUNT / 2 ) {
		Vector vec = getVec( );
		//ひるみ中でも移動できるようにする
		DevicePtr device( Device::getTask( ) );
		char dir_x = device->getDirX( _id );
		if ( dir_x < -50 ) {
			vec.x = -MOVE_SPEED;
		}
		if ( dir_x > 50 ) {
			vec.x = MOVE_SPEED;
		}
		if ( dir_x == 0 ) {
			vec.x = 0;
		}
		setVec( vec );
	}
}


void Player::actOnBlowAway( ) {
	Vector pos = getPos( );
	if ( pos.y < -GRAPH_SIZE ) {
		setPos( Vector( Family::getTask( )->getCameraPos( ) + SCREEN_WIDTH / 2, -GRAPH_SIZE ) );
		setAction( ACTION_WAIT );
		setVec( Vector( ) );
		return;
	}
	setVec( Vector( getVec( ).x, BLOW_POWER ) );
}

void Player::actOnDead( ) {
	int act_count = getActCount( );
	int chip_size = getChipSize( );
	STATE state = getState( );
	if ( act_count == MAX_DEAD_ACTCOUNT ) {
		if ( state == STATE_EVENT ) {
			//イベントで倒れたら、爆発する
			Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, chip_size / 2 ), state, chip_size * 2 ) ) );
		}
	}
	if ( act_count > MAX_DEAD_ACTCOUNT + MAX_IMPACT_COUNT ) {
		if ( getState( ) == STATE_EVENT ) {
			//メインの画面中央上部に移動
			setState( STATE_MAIN );
			MapEvent::getTask( )->setType( MapEvent::TYPE_TITLE );
			setPos( Vector( Family::getTask( )->getCameraPos( ) + SCREEN_WIDTH / 2, chip_size ) );
			Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, chip_size / 2 ), getState( ), chip_size * 2 ) ) );
		}
		if ( act_count < MAX_DEAD_ACTCOUNT + MAX_IMPACT_COUNT * 2 ) {
			setVec( Vector( 0, -GRAVITY ) );
		}
	}

}

void Player::damage( int force ) {
	if ( Debug::getTask( )->isDebug( ) ) {
		return;
	}
	if ( _action == ACTION_DAMEGE ||
		 _action == ACTION_BLOW_AWAY ||
		 _unrivaled_count < MAX_UNRIVALED_COUNT ||
		 isFinished( ) ) {
		return;
	}
	Character::damage( force );
	if ( isFinished( ) ) {
		setAction( ACTION_DAED );
		setVec( Vector( ) );
	} else {
		setAction( ACTION_DAMEGE );
		if ( getDir( ) == DIR_LEFT ) {
			setVec( Vector( 4, 0 ) );
		} else {
			setVec( Vector( -4, 0 ) );
		}
	}
	_unrivaled_count = 0;
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
			cx = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_BLOW_AWAY:
		{
			const int ANIM[ ] = {
				5,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			cx = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ] / PLAYER_ANIM_WIDTH_NUM;
		}
		break;
	case ACTION_DAED:
		{
			const int ANIM[ ] = {
				60, 61, 62, 63, 64, 65, 66, 67, 68
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			int anim = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
			if ( anim >= anim_num ) {
				anim = anim_num - 1;
			}
			cx = ANIM[ anim ] % PLAYER_ANIM_WIDTH_NUM;
			cy = ANIM[ anim ] / PLAYER_ANIM_WIDTH_NUM;
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
	setAction( ACTION_FLOAT );
	Vector vec = getVec( );
	vec.y = JUMP_POWER;
	setVec( vec );
}

void Player::blowAway( ) {
	if ( !Debug::getTask( )->isDebug( ) &&
		 _action != ACTION_DAED ) {
		setAction( ACTION_BLOW_AWAY );
	}
}

int Player::getMoneyNum( ) const {
	return _money;
}

void Player::pickUpMoney( int money ) {
	_money += money;
}

int Player::getTokuNum( ) const {
	return _toku;
}

void Player::pickUpToku( ) {
	_toku++;
}

void Player::setAction( ACTION action ) {
	_action = action;
	setActCount( 0 );
}

void Player::setSynchronousData( unsigned char type, int camera_pos ) const {
	if ( _unrivaled_count < MAX_UNRIVALED_COUNT ) {
		if ( _unrivaled_count / PLAYER_FLASH_WAIT_TIME % 2 == 0 ) {
			return;
		}
	}
	STATE state = getState( );
	int add_sy = 0;
	int add_sx = 0;
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_MAIN ) {
		x -= camera_pos;
		area = AREA_MAIN;
	}

	int pattern = 0;
	switch ( _action ) {
	case ACTION_WAIT:
		{
			const int ANIM[ ] = {
				0,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_WALK:
		{
			const int ANIM[ ] = {
				0, 1, 2, 1, 0, 3, 4, 3
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_BRAKE:
		{
			const int ANIM[ ] = {
				6,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_FLOAT:
		{
			const int ANIM[ ] = {
				5,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_CHARGE:
		{
			const int ANIM[ ] = {
				48, 49, 50, 51, 52, 53, 54
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( _charge_count / ( CHARGE_PHASE_COUNT / 2 ) ) % anim_num ];
		}
		break;
	case ACTION_OVER_CHARGE:
		{
			const int ANIM[ ] = {
				48, 49
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_DAMEGE:
		{
			const int ANIM[ ] = {
				96
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_BLOW_AWAY:
		{
			const int ANIM[ ] = {
				5,
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT ) % anim_num ];
		}
		break;
	case ACTION_DAED:
		{
			const int ANIM[ ] = {
				96, 97, 98, 99, 100, 101, 102, 103, 104
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			int anim = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
			if ( anim >= anim_num ) {
				anim = anim_num - 1;
			}
			pattern = ANIM[ anim ];
		}
		break;
	}


	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}

	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, pattern, attribute, x, y );
	if ( _charge_count > 0 ) {
		const int ANIM[ ] = {
			2, 3, 4, 5, 6, 7, 8, 9, 10, 11
		};
		int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		int phase = ( _charge_count / CHARGE_PHASE_COUNT ) * 2;
		int time = ( getActCount( ) / 2 ) % 2;
		data->addObject( area, SynchronousData::TYPE_CHARGE, ANIM[ phase + time ], attribute, x, y );
	}
}

