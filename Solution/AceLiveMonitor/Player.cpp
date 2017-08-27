#include "Player.h"
#include "Device.h"
#include "Armoury.h"
#include "ace_define.h"
#include "Family.h"
#include "MapStreet.h"
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
#include "Monmotaro.h"
#include "ShotPlayer.h"
#include "Office.h"

#include <assert.h>

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

Player::Player( PLAYER player, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_over_charge_time( -1 ),
_player( player ),
_id( -1 ),
_money( 0 ),
_toku( 0 ),
_charge_count( 0 ),
_unrivaled_count( MAX_UNRIVALED_COUNT ),
_monmo( MonmotaroPtr( ) ),
_action( ACTION_WAIT ),
_entry_gamble( false ) {
	setRadius( 25 );
	setDir( DIR_RIGHT );
}

Player::~Player( ) {
}

void Player::act( ) {
	if ( _id < 0 ) {
		actOnCamera( );
		return;
	}

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
	case ACTION_CALL:
		actOnCall( );
		break;
	}
	actOnCamera( );
	updateState( );
	_unrivaled_count++;

	if ( _monmo ) {
		Monmotaro::Target target;
		target.id  = _id;
		target.radius = getRadius( );
		target.attack = ( _action == ACTION_ATTACK );
		target.pos = getPos( );
		target.dir = getDir( );
		_monmo->setTarget( target );
		_monmo->update( );
		if ( _monmo->isFinished( ) ) {
			_monmo = MonmotaroPtr( );
		}
	}
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
	ShotPlayerPtr shot( new ShotPlayer( _player, getPos( ), getDir( ), power ) );
	shot->setArea( getArea( ) );
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
	if ( getArea( ) != AREA_EVENT ) {
		x += family->getCameraPosX( );
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
		//ひるみ中でも移動できるようにする
		setAction( ACTION_WAIT );
	}
}


void Player::actOnBlowAway( ) {
	Vector pos = getPos( );
	if ( pos.y < -GRAPH_SIZE ) {
		setPos( Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, -GRAPH_SIZE ) );
		setAction( ACTION_WAIT );
		setVec( Vector( ) );
		return;
	}
	setVec( Vector( getVec( ).x, BLOW_POWER ) );
}

void Player::actOnDead( ) {
	int act_count = getActCount( );
	int chip_size = getChipSize( );
	AREA area = getArea( );
	if ( act_count == MAX_DEAD_ACTCOUNT ) {
		if ( area == AREA_EVENT ) {
			//イベントで倒れたら、爆発する
			Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, chip_size / 2 ), area, chip_size * 2 ) ) );
		}
	}
	if ( act_count > MAX_DEAD_ACTCOUNT + MAX_IMPACT_COUNT ) {
		if ( getArea( ) == AREA_EVENT ) {
			//メインの画面中央上部に移動
			setArea( AREA_STREET );
			MapEvent::getTask( )->setEvent( EVENT_NONE );
			Military::getTask( )->createBoss( );
			setPos( Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, chip_size ) );
			Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, chip_size / 2 ), getArea( ), chip_size * 2 ) ) );
		}
		if ( act_count < MAX_DEAD_ACTCOUNT + MAX_IMPACT_COUNT * 2 ) {
			setVec( Vector( 0, -GRAVITY ) );
		}
	}

}

void Player::actOnCall( ) {
	if ( !_monmo ) {
		setAction( ACTION_WAIT );
		return;
	}

	if ( _monmo->getAction( ) == Monmotaro::ACTION_MOVE ) {
		setAction( ACTION_WAIT );
	}
}

void Player::damage( int force ) {
	if ( Debug::getTask( )->isDebug( ) ) {
		return;
	}
	if ( _action == ACTION_DAMEGE ||
		 _action == ACTION_BLOW_AWAY ||
		 _action == ACTION_CALL ||
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

int Player::getChargeCount( ) const {
	return _charge_count;
}

void Player::updateState( ) {
	//イベント
	MapStreetPtr map( MapStreet::getTask( ) );
	MapEventPtr map_event( MapEvent::getTask( ) );
	OfficePtr office( Office::getTask( ) );
	MilitaryPtr militaly( Military::getTask( ) );
	FamilyPtr family( Family::getTask( ) );

	EVENT event = map_event->getEvent( );
	if ( event == EVENT_NONE ) {
		bool enter = true;
		unsigned char obj = map->getObject( getPos( ) + getVec( ) );
		switch ( obj ) {
		case OBJECT_EVENT_REDDAEMON:
			event = EVENT_REDDAEMON;
			break;
		case OBJECT_EVENT_FIRE:
			event = EVENT_FIRE;
			break;
		case OBJECT_EVENT_TREE:
			event = EVENT_TREE;
			break;
		case OBJECT_EVENT_ROCK:
			event = EVENT_ROCK;
			break;
		case OBJECT_EVENT_SHOP:
			event = EVENT_SHOP;
			break;
		case OBJECT_EVENT_RYUGU:
			event = EVENT_RYUGU;
			break;
		case OBJECT_EVENT_LAKE:
			event = EVENT_LAKE;
			break;
		default:
			enter = false;
			break;
		}
		//イベントに入るとき
		if ( event != EVENT_NONE ) {
			map_event->setEvent( event );
			if ( event >= EVENT_SHOP ) {
				office->popUpNPC( );
			}
			militaly->createBoss( );
			setArea( AREA_EVENT );
			setPos( Vector( GRAPH_SIZE * 3 / 2, 0 ) );
			setVec( Vector( ) );
		}
	}
	//賭博場に入る
	if ( _entry_gamble && event == EVENT_NONE ) {
		map_event->setEvent( EVENT_GAMBLE );
		office->popUpNPC( );
		setArea( AREA_EVENT );
		setPos( Vector( GRAPH_SIZE * 3 / 2, 0 ) );
		setVec( Vector( ) );
		_entry_gamble = false;
	}
	
	if ( map->getObject( getPos( ) + getVec( ) ) == OBJECT_EVENT_CALL ) {
		map->usedObject( getPos( ) + getVec( ) );
		Monmotaro::Target target;
		target.id  = _id;
		target.radius = getRadius( );
		target.attack = false;
		target.pos = getPos( );
		target.dir = getDir( );
		_monmo = MonmotaroPtr( new Monmotaro( _player, Vector( family->getCameraPosX( ), 0 ), target ) );
		setAction( ACTION_CALL );
		setVec( Vector( ) );
	}

	if ( getArea( ) == AREA_EVENT ) {
		//一ページ目にいたらメインに戻る
		if ( getPos( ).x < GRAPH_SIZE ) {
			setArea( AREA_STREET );
			map_event->setEvent( EVENT_NONE );
			militaly->eraseEventEnemy( );
			Storage::getTask( )->eraseEventItem( );
			setPos( Vector( family->getCameraPosX( ) + SCREEN_WIDTH / 2, 0 ) );
			setVec( Vector( ) );
		}
		//ボスが倒れている場合 && アイテムが無い[退場]
		MapEventPtr map_event( MapEvent::getTask( ) );
		StoragePtr storage( Storage::getTask( ) );
		if ( !Military::getTask( )->getBoss( ) &&
			 !storage->isExistanceEventItem( ) &&
			 map_event->getEvent( ) < EVENT_SHOP ) {
			setArea( AREA_STREET );
			map_event->setEvent( EVENT_NONE );
			militaly->eraseEventEnemy( );
			setPos( Vector( family->getCameraPosX( ) + SCREEN_WIDTH / 2, 0 ) );
			setVec( Vector( ) );
		}
	}
}

bool Player::isOnHead( CharacterPtr target ) const {
	if ( _action != ACTION_FLOAT ) {
		return false;
	}
	Vector self = getPos( ) + Vector( 0, -getChipSize( ) / 2 );
	Vector nonself  = target->getPos( ) + Vector( 0, -target->getChipSize( ) / 2 );
	Vector vec = nonself - self;
	if ( vec.y < 0 ) {
		return false;
	}
	if ( vec.getLength( ) < target->getRadius( ) ) {
		return false;
	}
	if ( getPos( ).x < nonself.x - target->getChipSize( ) / 2 ||
		 getPos( ).x > nonself.x + target->getChipSize( ) / 2 ) {
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
	if ( _action == ACTION_CALL ) {
		return;
	}

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

void Player::setSynchronousData( PLAYER player, int camera_pos ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	// Status
	if ( getArea( ) == AREA_STREET ) {
		data->setStatusState( player, SynchronousData::STATE_PLAY_STREET );
	} else {
		data->setStatusState( player, SynchronousData::STATE_PLAY_EVENT );
	}
	data->setStatusX( player, ( int )getPos( ).x );
	// Object
	if ( _unrivaled_count < MAX_UNRIVALED_COUNT ) {
		if ( _unrivaled_count / PLAYER_FLASH_WAIT_TIME % 2 == 0 ) {
			return;
		}
	}

	AREA area = getArea( );
	unsigned char type;
	switch ( player ) {
	case PLAYER_TAROSUKE: type = SynchronousData::TYPE_TAROSUKE; break;
	case PLAYER_TAROJIRO: type = SynchronousData::TYPE_TAROJIRO; break;
	case PLAYER_GARISUKE: type = SynchronousData::TYPE_GARISUKE; break;
	case PLAYER_TAROMI  : type = SynchronousData::TYPE_TAROMI  ; break;
	};

	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;
	if ( area == AREA_STREET ) {
		x -= camera_pos;
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
	case ACTION_CALL:
		{
			const int ANIM[ ] = {
				64, 65, 66, 67, 68, 69, 70, 71
			};
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			int anim = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
			anim %= anim_num;
			pattern = ANIM[ anim ];
		}
		break;
	}


	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}

	data->addObject( area, type, pattern, attribute, x, y );
	if ( _charge_count > 0 ) {
		const int ANIM[ ] = {
			2, 3, 4, 5, 6, 7, 8, 9, 10, 11
		};
		int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		int phase = ( _charge_count / CHARGE_PHASE_COUNT ) * 2;
		int time = ( getActCount( ) / 2 ) % 2;
		data->addObject( area, SynchronousData::TYPE_SHOT, ANIM[ phase + time ], attribute, x, y );
	}
}

void Player::setDeviceId( int id ) {
	assert( 0 <= id && id < MAX_PLAYER );
	_id = id;
}

int Player::getDeviceId( ) const {
	return _id;
}

MonmotaroConstPtr Player::getMonmotaro( ) const {
	return _monmo;
}

void Player::presentGmblePath( ) {
	_entry_gamble = true;
}
