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
//カウント
static const int MAX_DAMEGE_COUNT = 20;
static const int MAX_BACK_COUNT = 6;
static const int MAX_UNRIVALED_COUNT = 45;
static const int MAX_DEAD_ACTCOUNT = 120;
static const int MAX_IMPACT_COUNT = 30;

static const int HEAL_DANGO = 6;

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
	80,  // ACTION_DEAD,
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
		27, // ACTION_DEAD,
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
		27, // ACTION_DEAD,
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
		27, // ACTION_DEAD,
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
		32, // ACTION_DEAD,
		12, // ACTION_CALL,
	}
};

Player::Player( PLAYER player, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_over_charge_time( -1 ),
_player( player ),
_device_id( -1 ),
_money( 0 ),
_show_money( 0 ),
_virtue( 0 ),
_charge_count( 0 ),
_unrivaled_count( MAX_UNRIVALED_COUNT ),
_action( ACTION_ENTRY ),
_progress_count( 0 ) {
	setOverlappedRadius( 25 );
	setDir( DIR_RIGHT );

	for ( int i = 0; i < MAX_ITEM; i++ ) {
		_item[ i ] = false;
	}
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

void Player::setProgressType( unsigned char type ) {
	_progress_type = type;
	_progress_count = 0;
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
		if ( device->getButton( _device_id ) == BUTTON_B + BUTTON_C + BUTTON_D ) {
			setAction( ACTION_ENTRY );
		}
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
		actOnContinue();
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
	case ACTION_DEAD:
		actOnDead( );
		break;
	case ACTION_CALL:
		actOnCall( );
		break;
	}

	actOnCamera( );
	_unrivaled_count++;

	updateShowMoney( );
	updateProgressEffect( );
}

void Player::updateShowMoney( ) {
	if ( _money == _show_money ) {
		return;
	}

	int d = ( _money - _show_money ) / 9;
	if ( d != 0 ) {
		_show_money += d;
	} else {
		_show_money = _money;
	}
}

void Player::updateProgressEffect( ) {
	if ( _action == ACTION_ENTRY ||
		 _action == ACTION_CONTINUE ) {
		return;
	}

	_progress_count += 3;
	if ( _progress_count >= 100 ) {
		_progress_type = SynchronousData::PROGRESS_NONE;
	}
}

void Player::actOnEntry( ) {
	adjustToCamera( );
	updateProgressBar( );

	if ( _progress_count >= 100 ) {
		// 再登場のために初期化
		appear( );
		// アイテム初期化
		for ( int i = 0; i < MAX_ITEM; i++ ) {
			_item[ i ] = false;
		}
		_virtue = 9;
		_money = 98765;
	}
}

void Player::actOnContinue() {
	adjustToCamera( );
	updateProgressBar( );

	if ( _progress_count >= 100 ) {
		// 再登場のために初期化
		appear();
	}
}

void Player::appear( ) {
	_action = ACTION_FLOAT;
	setPower( MAX_HP );
	setArea( AREA_STREET );
	_unrivaled_count = 0;
}

void Player::adjustToCamera( ) {
	Vector pos = getPos( );
	pos.x = Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2;
	pos.y = -100;
	setPos( pos );
}

void Player::updateProgressBar( ) {
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
		MapPtr map = World::getTask( )->getMap( getArea( ) );
		if ( map->getObject( getPos( ) ) != OBJECT_WATER ) {
			setAction( ACTION_CHARGE );
			return;
		}
	}
	if ( device->getPush( _device_id ) & BUTTON_C ) {
		sound->playSE( "yokai_voice_17.wav" );
		vec.y = JUMP_POWER;
		setVec( vec );
		setAction( ACTION_FLOAT );
		return;
	}
	_charge_count -= 2;
	if ( _charge_count < 0 ) {
		_charge_count = 0;
	}
}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	DevicePtr device( Device::getTask( ) );
	SoundPtr sound = Sound::getTask( );

	// 遷移
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		return;
	}
	Vector vec = getVec( );
	if ( device->getDirX( _device_id ) * vec.x < 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	if ( device->getDirX( _device_id ) == 0 ) {
		setAction( ACTION_WAIT );
		return;
	}

	if ( device->getPush( _device_id ) & BUTTON_C ) {
		sound->playSE( "yokai_voice_17.wav" );
		vec.y = JUMP_POWER;
		setVec( vec );
		setAction( ACTION_FLOAT );
		return;
	}

	// 歩く処理
	if ( device->getDirX( _device_id ) < -50 ) {
		vec.x = -MOVE_SPEED;
	}
	if ( device->getDirX( _device_id ) > 50 ) {
		vec.x = MOVE_SPEED;
	}
	MapPtr map = World::getTask( )->getMap( getArea( ) );
	if ( map->getObject( getPos( ) ) == OBJECT_WATER ) {
		if ( !sound->isPlayingSE( "yokai_voice_14.wav" ) ) {
			sound->playSE( "yokai_voice_14.wav" );
		}
	} else {
		if ( !sound->isPlayingSE( "yokai_voice_15.wav" ) ) {
			sound->playSE( "yokai_voice_15.wav" );
		}
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
		Sound::getTask( )->playSE( "yokai_voice_17.wav" );
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
	int level = ( _charge_count / CHARGE_PHASE_COUNT ) + 1;
	if ( _item[ ITEM_HYPERTROPHY ] ) {
		level++;
	}
	Sound::getTask( )->playSE( "yokai_se_20.wav" );
	ShotPlayerPtr shot( new ShotPlayer( _player, getPos( ), getDir( ), level ) );
	shot->setArea( getArea( ) );
	Armoury::getTask( )->add( shot );
	setAction( ACTION_WAIT );
	_charge_count = 0;
}

void Player::actOnCharge( ) {
	DevicePtr device( Device::getTask( ) );
	SoundPtr sound = Sound::getTask( );
	sound->playSE( "yokai_se_21.wav", true );
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		sound->stopSE( "yokai_se_21.wav" );
		sound->stopSE( "yokai_se_22.wav" );
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
			sound->stopSE( "yokai_se_21.wav" );
			sound->stopSE( "yokai_se_22.wav" );
			setAction( ACTION_WAIT );
			return;
		} else {
			sound->stopSE( "yokai_se_21.wav" );
			sound->stopSE( "yokai_se_22.wav" );
			setAction( ACTION_WALK );
			return;
		}
		Vector vec = getVec( );
		if ( device->getPush( _device_id ) & BUTTON_C ) {
			Sound::getTask( )->playSE( "yokai_voice_17.wav" );
			vec.y = JUMP_POWER;
			setVec( vec );
			setAction( ACTION_FLOAT );
			return;
		}
	}
	_charge_count++;
	if ( _item[ ITEM_SHORTENING ] ) {
		_charge_count++;
	}
	if ( _charge_count > 75 ) {
		sound->stopSE( "yokai_se_21.wav" );
		if ( !sound->isPlayingSE( "yokai_se_22.wav" ) ) {
			sound->playSE( "yokai_se_22.wav", true );
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
	double radius = getOverlappedRadius( );
	if ( pos.x + vec.x - radius < x ) {
		pos.x = x + radius;
		vec.x = 0;
		setPos( pos );
		setVec( vec );
	}
	if ( getPos( ).x + getVec( ).x + getOverlappedRadius( ) > x + SCREEN_WIDTH ) {
		pos.x = ( x + SCREEN_WIDTH ) - radius;
		vec.x = 0;
		setPos( pos );
		setVec( vec );
	}
}

void Player::actOnDamege( ) {
	int act_count = getActCount( );
	if ( act_count > MAX_BACK_COUNT ) {
		setVec( Vector( 0, getVec( ).y ) );
	}
	if ( act_count > MAX_DAMEGE_COUNT / 2 ) {
		//ひるみ中でも移動できるようにする
		setAction( ACTION_WAIT );
		// HPがなくなったら
		if ( getPower( ) <= 0 ) {
			if ( _item[ ITEM_DANGO ] ) {
				// 団子を使用
				_item[ ITEM_DANGO ] = false;
				setProgressType( SynchronousData::PROGRESS_ITEM_DANGO );
				setPower( HEAL_DANGO );
			} else if ( _item[ ITEM_HEART ] ) {
				// ハートを使用
				_item[ ITEM_HEART ] = false;
				setProgressType( SynchronousData::PROGRESS_ITEM_HEART );
				setPower( MAX_HP );
			} else {
				// 死んだ
				setAction( ACTION_DEAD );
				setVec( Vector( ) );
			}
		}
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
	_unrivaled_count = MAX_UNRIVALED_COUNT;
	int act_count = getActCount( );
	AREA area = getArea( );
	if ( act_count > MAX_DEAD_ACTCOUNT ) {
		// 爆発する
		int chip_size = getChipSize( );
		Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, chip_size / 2 ), area, chip_size * 2 ) ) );
		// コンティニューへ
		setAction(ACTION_CONTINUE);
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
		 _unrivaled_count < MAX_UNRIVALED_COUNT ) {
		return;
	}

	SoundPtr sound = Sound::getTask( );
	switch( _player ) {
	case 0:
		sound->playSE( "yokai_voice_26.wav" );
		break; 
	case 1:
		sound->playSE( "yokai_voice_26_1.wav" );
		break;
	case 2:
		sound->playSE( "yokai_voice_26_3.wav" );
		break;
	case 3:
		sound->playSE( "yokai_voice_26_2.wav" );
		break; 
	}

	Character::damage( force );

	setAction( ACTION_DAMEGE );
	if ( getDir( ) == DIR_LEFT ) {
		setVec( Vector( 4, 0 ) );
	} else {
		setVec( Vector( -4, 0 ) );
	}

	_unrivaled_count = 0;
}

Player::ACTION Player::getAction( ) const {
	return _action;
}

int Player::getChargeCount( ) const {
	return _charge_count;
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
	if ( vec.getLength( ) < target->getOverlappedRadius( ) ) {
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
	Sound::getTask( )->playSE( "yokai_voice_17.wav" );
	Vector vec = getVec( );
	vec.y = JUMP_POWER;
	setVec( vec );
}

void Player::blowAway( ) {
	if ( isExist( ) ) {
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
	_progress_count = 0;
}

void Player::setSynchronousData( PLAYER player, int camera_pos ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	
	data->setStatusDevice( _player, _device_id );
	
	switch ( _action ) {
	case ACTION_ENTRY:
		data->setStatusState( _player, SynchronousData::STATE_ENTRY );
		data->setStatusProgress( _player, SynchronousData::PROGRESS_BAR, _progress_count );
		break;
	case ACTION_CONTINUE:
		data->setStatusState( _player, SynchronousData::STATE_CONTINUE ); 
		data->setStatusProgress( _player, SynchronousData::PROGRESS_BAR, _progress_count );
		break;
	default:
		if ( getArea( ) == AREA_STREET ) {
			data->setStatusState( _player, SynchronousData::STATE_PLAY_STREET ); 
		} else {
			data->setStatusState( _player, SynchronousData::STATE_PLAY_EVENT );
		}

		data->setStatusProgress( _player, _progress_type, _progress_count );
		break;
	}

	data->setStatusX( player, ( int )getPos( ).x );
	data->setStatusPower( player, getPower( ) );
	data->setStatusMoney( player, getMoney( ) );
	data->setStatusVirtue( player, getVirtue( ) );
	data->setStatusMoney( player, _show_money );

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

	MapPtr map = World::getTask( )->getMap( getArea( ) );
	int off = MOTION_OFFSET[ _action ];
	int num = MOTION_NUM[ _player ][ _action ];
	int motion = 0;
	int pattern = 0;
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
		if ( player == PLAYER_TAROJIRO ) {
			num = num - 1;
		}
		motion = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
		break;
	case ACTION_DEAD:
		{
			int anim = getActCount( ) / ( PLAYER_ANIM_WAIT_COUNT / 2 );
			if ( anim >= num ) {
				anim = num - 1;
			}
			motion = anim;
			break;
		}
	case ACTION_CHARGE:
		{
			int anim = _charge_count / ( CHARGE_PHASE_COUNT / 6 );
			if ( anim >= num ) {
				anim = num - 1;
			}
			motion = anim;
			break;
		}

	}
	pattern = off + motion % num;

	if ( isStanding() && map->getObject( getPos( ) ) == OBJECT_WATER ) {
		pattern += 16 * 9;
	}

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

void Player::enterEvent( ) {
	setArea( AREA_EVENT );
	setPos( Vector( GRAPH_SIZE * 3 / 2, 0 ) );
	setVec( Vector( ) );
}

void Player::leaveEvent( ) {
	setArea( AREA_STREET );
	setPos( Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, 0 ) );
	setVec( Vector( ) );
}

EVENT Player::getOnEvent( ) const {
	if ( !isStanding( ) ||
		 getArea( ) == AREA_EVENT ||
		 !isExist( ) ) {
		return EVENT_NONE;
	}

	MapPtr map = World::getTask( )->getMap( AREA_STREET );
	unsigned char obj = map->getObject( getPos( ) );
	EVENT event = EVENT_NONE;
	switch ( obj ) {
	case OBJECT_EVENT_REDDAEMON:
		event = EVENT_REDDAEMON;
		break;
	case OBJECT_EVENT_FLAME:
		event = EVENT_FLAME;
		break;
	case OBJECT_EVENT_WOOD:
		event = EVENT_WOOD;
		break;
	case OBJECT_EVENT_MINERAL:
		event = EVENT_MINERAL;
		break;
	case OBJECT_EVENT_SHOP:
		event = EVENT_SHOP;
		break;
	case OBJECT_EVENT_LAKE:
		event = EVENT_LAKE;
		break;
	case OBJECT_EVENT_RYUGU:
		event = EVENT_RYUGU;
		break;
	case OBJECT_EVENT_CALL:
		event = EVENT_CALL;
		break;
	case OBJECT_EVENT_GAMBLE:
		event = EVENT_GAMBLE;
		break;
	}
	return event;
}


void Player::pickUpItem( ITEM item ) {
	_item[ item ] = true;
}
