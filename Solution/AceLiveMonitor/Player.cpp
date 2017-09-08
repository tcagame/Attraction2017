#include "Player.h"
#include "Device.h"
#include "Armoury.h"
#include "ace_define.h"
#include "Family.h"
#include "ViewerLive.h"
#include "ViewerEvent.h"
#include "Military.h"
#include "Enemy.h"
#include "Storage.h"
#include "Debug.h"
#include "SynchronousData.h"
#include "Magazine.h"
#include "Impact.h"
#include "ShotPlayer.h"
#include "Office.h"
#include "World.h"
#include "Map.h"
#include "Monmotaro.h"
#include "Sound.h"
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
static const int COOL_TIME = 8;
//アニメーション
static const int PLAYER_ANIM_WAIT_COUNT = 4;
static const int PLAYER_ANIM_WIDTH_NUM = 10;
static const int PLAYER_FLASH_WAIT_TIME = 2;
static const int DEAD_ANIM_NUM = 28;
//カウント
static const int MAX_DAMEGE_COUNT = 20;
static const int MAX_BACK_COUNT = 6;
static const int MAX_UNRIVALED_COUNT = 45;
static const int MAX_DEAD_ACTCOUNT = 120;
static const int MAX_IMPACT_COUNT = 30;

// モーションテーブル
const int MOTION_OFFSET[Player::MAX_ACTION] = {
	0,   // ACTION_ENTRY,
	0,   // ACTION_CONTINUE,
	0,   // ACTION_WAIT,
	32,  // ACTION_WALK,
	1,  // ACTION_BRAKE,
	48,  // ACTION_FLOAT,
	0,   // ACTION_ATTACK,
	64,  // ACTION_CHARGE,
	73,  // ACTION_OVER_CHARGE,
	81,  // ACTION_DAMEGE,
	50,  // ACTION_BLOW_AWAY,
	80,  // ACTION_DAED,
	112, // ACTION_CALL,
};

const int MOTION_NUM[MAX_PLAYER][Player::MAX_ACTION] = {
	{ // たろすけ
		0 , // ACTION_ENTRY,
		0 , // ACTION_CONTINUE,
		17, // ACTION_WAIT,
		16, // ACTION_WALK,
		1 , // ACTION_BRAKE,
		11 , // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		7 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		27, // ACTION_DAED,
		18, // ACTION_CALL,
	},
	{ // たろじろー
		0 , // ACTION_ENTRY,
		0 , // ACTION_CONTINUE,
		21, // ACTION_WAIT,
		12, // ACTION_WALK,
		1 , // ACTION_BRAKE,
		11 , // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		6 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		27, // ACTION_DAED,
		18, // ACTION_CALL,
	},
	{ // ガりすけ
		0 , // ACTION_ENTRY,
		0 , // ACTION_CONTINUE,
		16, // ACTION_WAIT,
		16, // ACTION_WALK,
		1 , // ACTION_BRAKE,
		11 , // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		7 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		27, // ACTION_DAED,
		12, // ACTION_CALL,
	},
	{ // たろみ
		0 , // ACTION_ENTRY,
		0 , // ACTION_CONTINUE,
		16, // ACTION_WAIT,
		16, // ACTION_WALK,
		1 , // ACTION_BRAKE,
		11 , // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		7 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		28, // ACTION_DAED,
		12, // ACTION_CALL,
	}
};

Player::Player( PLAYER player, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_over_charge_time( -1 ),
_player( player ),
_device_id( -1 ),
_money( 100 ),
_virtue( 0 ),
_charge_count( 0 ),
_unrivaled_count( MAX_UNRIVALED_COUNT ),
_action( ACTION_ENTRY ),
_progress_count( 0 ) {
	setRadius( 25 );
	setDir( DIR_RIGHT );
}

Player::~Player( ) {
}

bool Player::isExist( ) const {
	return
		_action != ACTION_ENTRY &&
		_action != ACTION_CONTINUE &&
		_action != ACTION_CALL &&
		_action != ACTION_DAMEGE &&
		_action != ACTION_BLOW_AWAY;
}

int Player::getDeviceId( ) const {
	return _device_id;
}

void Player::updatetDevice( ) {
	DevicePtr device = Device::getTask( );
	if ( _device_id < 0 ) {
		unsigned char button[ MAX_PLAYER ];
		button[ PLAYER_TAROSUKE ] = BUTTON_C;
		button[ PLAYER_TAROJIRO ] = BUTTON_D;
		button[ PLAYER_GARISUKE ] = BUTTON_A;
		button[ PLAYER_TAROMI   ] = BUTTON_B;

		int num = device->getDeviceNum( );
		if ( num == 0 ) {
			num = 1;
		}
		for ( int i = 0; i < num; i++ ) {
			if ( device->getDirY( i ) < 0 && device->getButton( i ) == button[ _player ] ) {
				_device_id = i;
			}
		}
	} else {
		if ( device->getDirY( _device_id ) < 0 &&
			device->getButton( _device_id ) == BUTTON_E + BUTTON_F ) {
			_device_id = -1;
		}
	}
}

void Player::act( ) {
	updatetDevice( );

	switch ( _action ) {
	case ACTION_ENTRY:
		actOnEntry( );
		break;
	case ACTION_CONTINUE:
		{
			Vector pos = getPos( );
			pos.x = Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2;
			setPos( pos );
		}
		break;
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

}

void Player::actOnEntry( ) {
	adjustToCamera( );
	updateProgress( );

	if ( _progress_count >= 100 ) {
		// 再登場のために初期化
		appear( );
		// アイテム初期化
		for ( int i = 0; i < MAX_ITEM; i++ ) {
			_item[ i ] = false;
		}
		_virtue = 0;
	}
}

void Player::appear( ) {
	_action = ACTION_FLOAT;
	setPower( MAX_HP );
	_unrivaled_count = 0;
}

void Player::adjustToCamera( ) {
	Vector pos = getPos( );
	pos.x = Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2;
	pos.y = -100;
	setPos( pos );
}

void Player::updateProgress( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( _device_id ) ) {
		_progress_count += 2;
		if ( _progress_count > 100 ) {
			_progress_count = 100;
		}
	} else {
		_progress_count = 0;
	}
}

void Player::actOnWaiting( ) {
	//デバイスのスティック入力があった場合、action_walk
	SoundPtr sound = Sound::getTask( );
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		return;
	}
	Vector vec = getVec( );
	if ( fabs( vec.x ) > 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	DevicePtr device( Device::getTask( ) );
	if ( abs( device->getDirX( _device_id ) ) > 50 ) {
		setAction( ACTION_WALK );
		return;
	}
	if ( device->getPush( _device_id ) & BUTTON_A &&
		 getActCount( ) > COOL_TIME ) {
		setAction( ACTION_ATTACK );
		return;
	}
	if ( device->getDirY( _device_id ) > 0 ) {
		setAction( ACTION_CHARGE );
		sound->playSE( "yokai_se_21.wav", true );
		return;
	}
	sound->stopSE( "yokai_se_21.wav" );
	sound->stopSE( "yokai_se_22.wav" );
	if ( isStanding( ) && device->getPush( _device_id ) & BUTTON_C ) {
		sound->playSE( "yokai_voice_17.wav" );
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
		Sound::getTask( )->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		return;
	}
	if ( device->getDirX( _device_id ) * vec.x < 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	if ( device->getDirX( _device_id ) == 0 ) {
		setAction( ACTION_WAIT );
		return;
	}

	if ( isStanding( ) && device->getPush( _device_id ) & BUTTON_C ) {
		Sound::getTask( )->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		vec.y = JUMP_POWER;
	}
	if ( device->getDirX( _device_id ) < -50 ) {
		vec.x = -MOVE_SPEED;
	}
	if ( device->getDirX( _device_id ) > 50 ) {
		vec.x = MOVE_SPEED;
	}
	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingSE( "yokai_voice_15.wav" ) ) {
		sound->playSE( "yokai_voice_15.wav" );
	}
	setVec( vec );
}

void Player::actOnBreaking( ) {
	Vector vec = getVec( );
	if ( !isStanding( ) ) {
		Sound::getTask( )->playSE( "yokai_voice_17.wav" );
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
	if ( isStanding( ) && device->getPush( _device_id ) & BUTTON_C ) {
		vec.y = JUMP_POWER;
		Sound::getTask( )->playSE( "yokai_voice_17.wav" );
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
	int dir_x = device->getDirX( _device_id );
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
	if ( device->getPush( _device_id ) & BUTTON_A &&
		 getActCount( ) > COOL_TIME ) {
		setAction( ACTION_ATTACK );
	}
}

void Player::actOnAttack( ) {
	int power = ( _charge_count / CHARGE_PHASE_COUNT ) + 1;
	Sound::getTask( )->playSE( "yokai_se_20.wav" );
	ShotPlayerPtr shot( new ShotPlayer( _player, getPos( ), getDir( ), power ) );
	shot->setArea( getArea( ) );
	Armoury::getTask( )->add( shot );
	setAction( ACTION_WAIT );
	_charge_count = 0;
}

void Player::actOnCharge( ) {
	DevicePtr device( Device::getTask( ) );
	SoundPtr sound = Sound::getTask( );
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		return;
	}
	if ( device->getPush( _device_id ) & BUTTON_A &&
		 getActCount( ) > COOL_TIME ) {
		sound->stopSE( "yokai_se_21.wav" );
		sound->stopSE( "yokai_se_22.wav" );
		setAction( ACTION_ATTACK );
		return;
	}
	if ( device->getDirY( _device_id ) <= 0 ) {
		if ( device->getDirX( _device_id ) == 0 ) {
			setAction( ACTION_WAIT );
			return;
		} else {
			setAction( ACTION_WALK );
			return;
		}
		Vector vec = getVec( );
		if ( device->getPush( _device_id ) & BUTTON_C ) {
			vec.y = JUMP_POWER;
			setVec( vec );
			Sound::getTask( )->playSE( "yokai_voice_17.wav" );
			setAction( ACTION_FLOAT );
			return;
		}
	}
	_charge_count++;
	if ( _charge_count > 75 ) {
		sound->stopSE( "yokai_se_21.wav" );
		if ( !sound->isPlayingSE( "yokai_se_22.wav" ) ) {
			sound->playSE( "yokai_se_22.wav" );
		}
	}
	if ( _charge_count > MAX_CHARGE_COUNT ) {
		_charge_count = 0;
		_over_charge_time = getActCount( );
		sound->stopSE( "yokai_se_22.wav" );
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
			World::getTask( )->setEvent( EVENT_NONE );
			Military::getTask( )->createBoss( );
			Storage::getTask( )->eraseEventItem( );
			setPos( Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, chip_size ) );
			Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, chip_size / 2 ), getArea( ), chip_size * 2 ) ) );
		}
		if ( act_count < MAX_DEAD_ACTCOUNT + MAX_IMPACT_COUNT * 2 ) {
			setVec( Vector( 0, -GRAVITY ) );
		}
	}
}

void Player::actOnCall( ) {
	MonmotaroConstPtr monmo( Family::getTask( )->getMonmotaro( ) );
	
	if ( monmo->getAction( ) == Monmotaro::ACTION_MOVE ) {
		setAction( ACTION_WAIT );
	}
}

void Player::damage( int force ) {
	if ( Debug::getTask( )->isDebug( ) ) {
		return;
	}
	if ( !isExist( ) ||
		 _unrivaled_count < MAX_UNRIVALED_COUNT ||
		 isFinished( ) ) {
		return;
	}

	Character::damage( force );
	SoundPtr sound = Sound::getTask( );
	if ( isFinished( ) ) {
		setAction( ACTION_DAED );
		setVec( Vector( ) );
	} else {
		sound->playSE( "yokai_voice_26.wav" );
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
	WorldPtr world = World::getTask( );
	MapPtr map = world->getMap( AREA_STREET );
	MapPtr map_event = world->getMap( AREA_EVENT );
	OfficePtr office( Office::getTask( ) );
	MilitaryPtr militaly( Military::getTask( ) );
	FamilyPtr family( Family::getTask( ) );
	StoragePtr storage( Storage::getTask( ) );

	EVENT event = world->getEvent( );
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
			world->setEvent( event );
			storage->eraseEventItem( );
			if ( event >= EVENT_SHOP ) {
				office->popUpNPC( );
			}
			if ( event == EVENT_SHOP ) {
				storage->createShopItem( );
			}
			militaly->createBoss( );
			setArea( AREA_EVENT );
			setPos( Vector( GRAPH_SIZE * 3 / 2, 0 ) );
			setVec( Vector( ) );
		}
	}

	if ( map->getObject( getPos( ) + getVec( ) ) == OBJECT_EVENT_CALL ) {
		Sound::getTask( )->playSE( "yokai_voice_06.wav" );
		setAction( ACTION_CALL );
		setVec( Vector( ) );
	}

	if ( getArea( ) == AREA_EVENT ) {
		//一ページ目にいたらメインに戻る
		if ( getPos( ).x < GRAPH_SIZE ) {
			setArea( AREA_STREET );
			world->setEvent( EVENT_NONE );
			militaly->eraseEventEnemy( );
			storage->eraseEventItem( );
			setPos( Vector( family->getCameraPosX( ) + SCREEN_WIDTH / 2, 0 ) );
			setVec( Vector( ) );
		}
		//ボスが倒れている場合 && アイテムが無い[退場]
		StoragePtr storage( Storage::getTask( ) );
		if ( !Military::getTask( )->getBoss( ) &&
			 !storage->isExistanceEventItem( ) &&
			 world->getEvent( ) < EVENT_SHOP ) {
			setArea( AREA_STREET );
			world->setEvent( EVENT_NONE );
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
	if ( _action == ACTION_CALL ||
		 _action == ACTION_ENTRY ||
		 _action == ACTION_CONTINUE ) {
		return;
	}

	if ( !Debug::getTask( )->isDebug( ) &&
		 _action != ACTION_DAED ) {
		setAction( ACTION_BLOW_AWAY );
	}
}

int Player::getMoney( ) const {
	return _money;
}

void Player::addMoney( int money ) {
	_money += money;
}

int Player::getVirtue( ) const {
	return _virtue;
}

void Player::pickUpVirtue( ) {
	_virtue++;
}

void Player::setAction( ACTION action ) {
	_action = action;
	setActCount( 0 );
}

void Player::setSynchronousData( PLAYER player, int camera_pos ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	
	data->setStatusDevice( _player, _device_id );
	
	switch ( _action ) {
	case ACTION_ENTRY:
		data->setStatusState( _player, SynchronousData::STATE_ENTRY );
		data->setStatusProgress( _player, _progress_count );
		break;
	case ACTION_CONTINUE:
		data->setStatusState( _player, SynchronousData::STATE_CONTINUE ); 
		data->setStatusProgress( _player, _progress_count );
		break;
	default:
		if ( getArea( ) == AREA_STREET ) {
			data->setStatusState( _player, SynchronousData::STATE_PLAY_STREET ); 
		} else {
			data->setStatusState( _player, SynchronousData::STATE_PLAY_EVENT );
		}
		break;
	}

	data->setStatusX( player, ( int )getPos( ).x );
	data->setStatusPower( player, getPower( ) );
	data->setStatusMoney( player, getMoney( ) );
	data->setStatusVirtue( player, getVirtue( ) );

	unsigned char CONV[ MAX_ITEM ] = {
		SynchronousData::ITEM_DANGO,			
		SynchronousData::ITEM_HEART,			
		SynchronousData::ITEM_HYPERTROPHY,		
		SynchronousData::ITEM_SHORTENING,		
		SynchronousData::ITEM_WOOD,			
		SynchronousData::ITEM_FLAME,			
		SynchronousData::ITEM_MINERAL,
	};
	for ( int i = 0; i < MAX_ITEM; i++ ) {
		data->setInProssessionOfStatusItem( _player, CONV[ i ], _item[ i ] );
	}

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

	int off = MOTION_OFFSET[ _action ];
	int num = MOTION_NUM[ _player ][ _action ];
	int motion = 0;
	switch ( _action ) {
	case ACTION_BRAKE:
	case ACTION_DAMEGE:
	case ACTION_BLOW_AWAY:
		break;
	case ACTION_ENTRY:
	case ACTION_CONTINUE:
		return;
	case ACTION_WALK:
		motion = ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT / 4;
		break;
	case ACTION_FLOAT:
		motion = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
		break;
	case ACTION_WAIT:
	case ACTION_CALL:
		motion = getActCount( ) / PLAYER_ANIM_WAIT_COUNT / 2;
		break;
	case ACTION_OVER_CHARGE:
	{
		motion = getActCount( ) / PLAYER_ANIM_WAIT_COUNT / 2;
		break;
	}
	case ACTION_DAED:
	{
		int anim = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
		if ( anim >= DEAD_ANIM_NUM ) {
			anim = DEAD_ANIM_NUM - 1;
		}

		if ( player != PLAYER_TAROMI ) {
			anim = anim - 1;
		}
		motion = anim;
		break;
	}
	case ACTION_CHARGE:
		motion = _charge_count / ( CHARGE_PHASE_COUNT / 2 );
		break;
	}

	int pattern = off + motion % num;

	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}

	data->addObject( area, type, pattern, attribute, x, y );
	if ( _charge_count > 0 ) {
		const int ANIM[ ] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
		};
		int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		int phase = ( _charge_count / CHARGE_PHASE_COUNT ) * 2;
		int time = ( getActCount( ) / 2 ) % 2;
		data->addObject( area, SynchronousData::TYPE_SHOT, ANIM[ phase + time ], attribute, x, y );
	}
}
