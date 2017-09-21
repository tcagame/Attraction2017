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
#include "Keyboard.h"
#include <assert.h>
#include "Property.h"

//画像サイズ
const int PLAYER_FOOT = 7;
//速度
const int MAX_SPEED = 7;
const int ACCEL_SPEED_WALKING = 2;
const int BREAK_SPEED_WALKING = 1;
const int ACCEL_SPEED_FLOATING = 1;
const int BLOW_POWER = -30;
//攻撃関係
const int BURST_TIME = 30;
const int MAX_HP = 16;
const int COOL_TIME = 8;
//アニメーション
const int PLAYER_ANIM_WAIT_COUNT = 4;
const int PLAYER_ANIM_WIDTH_NUM = 10;
const int PLAYER_FLASH_WAIT_TIME = 2;
//カウント
const int MAX_DAMEGE_COUNT = 20;
const int MAX_BACK_COUNT = 6;
const int MAX_UNRIVALED_COUNT = 45;
const int MAX_DEAD_ACTCOUNT = 120;
const int MAX_IMPACT_COUNT = 30;
const int ENTERING_FADE_COUNT = 30;
const int ENTERING_SANZO_COUNT = 90;
const int MAX_SANDWICHED_COUNT = 300;

const int AUTO_FINISH_RANGE = 5;
const int HEAL_DANGO = 6;

// モーションテーブル
const int MOTION_OFFSET[Player::MAX_ACTION] = {
	0,   // ACTION_ENTRY,
	0,   // ACTION_CONTINUE,
	0,   // ACTION_WAIT,
	32,  // ACTION_WALK,
	160,  // ACTION_FLOAT,
	0,   // ACTION_ATTACK,
	176,  // ACTION_CHARGE,
	185,  // ACTION_OVER_CHARGE,
	49,  // ACTION_DAMEGE,
	162,  // ACTION_BLOW_AWAY,
	48,  // ACTION_DEAD,
	192, // ACTION_CALL,
	14 * 16,   //ACTION_ENTERING_FADEOUT,
	0,   //ACTION_ENTERING_SANZO,
	3 * 16 + 14,   //ACTION_AUDIENCE
	1,   //ACTION_ENDING
};

const int MOTION_NUM[MAX_PLAYER][Player::MAX_ACTION] = {
	{ // たろすけ
		1 , // ACTION_ENTRY,
		1 , // ACTION_CONTINUE,
		17, // ACTION_WAIT,
		16, // ACTION_WALK,
		11, // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		7 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		27, // ACTION_DEAD,
		18, // ACTION_CALL,
		8,  //ACTION_ENTERING_FADEOUT,
		1,  //ACTION_ENTERING_SANZO,
		1,  //ACTION_AUDIENCE
		1,  //ACTION_ENDING
	},
	{ // たろじろー
		1 , // ACTION_ENTRY,
		1 , // ACTION_CONTINUE,
		21, // ACTION_WAIT,
		12, // ACTION_WALK,
		11, // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		6 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		27, // ACTION_DEAD,
		18, // ACTION_CALL,
		8,  //ACTION_ENTERING_FADEOUT,
		1,  //ACTION_ENTERING_SANZO,
		1,  //ACTION_AUDIENCE
		1,  //ACTION_ENDING
	},
	{ // ガりすけ
		1 , // ACTION_ENTRY,
		1 , // ACTION_CONTINUE,
		16, // ACTION_WAIT,
		16, // ACTION_WALK,
		11, // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		7 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		27, // ACTION_DEAD,
		12, // ACTION_CALL,
		8,  //ACTION_ENTERING_FADEOUT,
		1,  //ACTION_ENTERING_SANZO,
		1,  //ACTION_AUDIENCE
		1,  //ACTION_ENDING
	},
	{ // たろみ
		1 , // ACTION_ENTRY,
		1 , // ACTION_CONTINUE,
		16, // ACTION_WAIT,
		16, // ACTION_WALK,
		11, // ACTION_FLOAT,
		1 , // ACTION_ATTACK,
		9 , // ACTION_CHARGE,
		7 , // ACTION_OVER_CHARGE,
		1 , // ACTION_DAMEGE,
		1 , // ACTION_BLOW_AWAY,
		32, // ACTION_DEAD,
		12, // ACTION_CALL,
		8,  //ACTION_ENTERING_FADEOUT,
		1,  //ACTION_ENTERING_SANZO,
		1,  //ACTION_AUDIENCE
		1,  //ACTION_ENDING
	}
};

Player::Player( PLAYER player, Vector pos ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_player( player ),
_device_id( -1 ),
_money( 0 ),
_show_money( 0 ),
_virtue( 0 ),
_charge_count( 0 ),
_unrivaled_count( MAX_UNRIVALED_COUNT ),
_action( ACTION_ENTRY ),
_progress_count( 0 ),
_cool_time( COOL_TIME ),
_auto_move_target_x( -1 ),
_redo( 0 ) {
	setOverlappedRadius( 25 );
	setDir( DIR_RIGHT );
	PropertyPtr property = Property::getTask( );
	_jump_power             = property->getData( "PLAYER_JUMP_POWER" );
	_max_charge_phase_count = property->getData( "MAX_CHARGE_PHASE_COUNT" );
	_max_virtue             = property->getData( "MAX_VIRTUE" );
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
		_action != ACTION_BLOW_AWAY &&
		_action != ACTION_ENTERING_FADEOUT &&
		_action != ACTION_ENTERING_SANZO &&
		_action != ACTION_ENDING;
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
			_progress_count = 0;
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
	case ACTION_ENTERING_FADEOUT:
		actOnEnteringFadeOut( );
		break;
	case ACTION_ENTERING_SANZO:
		actOnEnteringSanzo( );
		break;
	case ACTION_AUDIENCE:
		actOnAudience( );
		break;
	case ACTION_ENDING:
		actOnEnding( );
		break;
	}

	actOnCamera( );
	_unrivaled_count++;
	_cool_time++;

	updateShowMoney( );
	updateProgressEffect( );
	checkSandwichedWall( );
	debugItem( );
}

void Player::debugItem( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	
	if ( keyboard->isPushKey( "NUM1" ) ) {
		pickUpItem( ITEM_DANGO );
	}
	if ( keyboard->isPushKey( "NUM2" ) ) {
		pickUpItem( ITEM_HEART );
	}
	if ( keyboard->isPushKey( "NUM3" ) ) {
		pickUpItem( ITEM_HYPERTROPHY );
	}
	if ( keyboard->isPushKey( "NUM4" ) ) {
		pickUpItem( ITEM_SHORTENING );
	}
	if ( keyboard->isPushKey( "NUM5" ) ) {
		pickUpItem( ITEM_WOOD );
	}
	if ( keyboard->isPushKey( "NUM6" ) ) {
		pickUpItem( ITEM_FLAME );
	}
	if ( keyboard->isPushKey( "NUM7" ) ) {
		pickUpItem( ITEM_MINERAL );
	}
	if ( keyboard->isPushKey( "NUM8" ) ) {
		pickUpVirtue( );
	}
	if ( keyboard->isPushKey( "R" ) ) {
		_redo++;
	}
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
		 _action == ACTION_CONTINUE ||
		 _action == ACTION_ENDING ) {
		return;
	}

	_progress_count += 3;
	if ( _progress_count >= 100 ) {
		_progress_count = 100;
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

		_virtue = 0;
		_money = 0;
		_redo = 0;
		_mode = MODE_NORMAL;
	}
}

void Player::actOnContinue( ) {
	adjustToCamera( );
	//updateProgressBar( );

	if ( _progress_count >= 100 ) {
		// 再登場のために初期化
		_redo++;
		appear( );
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
	if ( getDeviceButton( ) ) {
		_progress_count += 2;
		if ( _progress_count > 100 ) {
			_progress_count = 100;
		}
	} else {
		_progress_count = 0;
	}
}

void Player::actOnWaiting( ) {
	// 足場が無くなった
	SoundPtr sound = Sound::getTask( );
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		return;
	}

	// 入力があったら、ACTION_WALKへ
	double dir_x = getVec( ).x;
	if ( abs( getDeviceDirX( ) ) > 50 || dir_x != 0 ) {
		setAction( ACTION_WALK );
		return;
	}

	// 攻撃
	if ( getDevicePush( ) & BUTTON_A &&
		 _cool_time > COOL_TIME ) {
		setAction( ACTION_ATTACK );
		return;
	}

	// チャージ
	if ( getDeviceDirY( ) > 0 ) {
		MapPtr map = World::getTask( )->getMap( getArea( ) );
		if ( map->getObject( getPos( ) ) != OBJECT_WATER ) {
			setAction( ACTION_CHARGE );
			return;
		}
	}

	// ジャンプ
	if ( getDevicePush( ) & BUTTON_C ) {
		jump( );
		return;
	}

	// 止まっているときだけチャージが徐々に失われていく
	_charge_count -= 2;
	if ( _charge_count < 0 ) {
		_charge_count = 0;
	}
}

void Player::actOnWalking( ) {
	//スティックの入力が無い場合action_wait
	SoundPtr sound = Sound::getTask( );

	// 地面から離れた
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		setAction( ACTION_FLOAT );
		return;
	}

	// ジャンプする？
	if ( getDevicePush( ) & BUTTON_C ) {
		jump( );
		return;
	}

	Vector vec = getVec( );

	// ブレーキ処理
	if ( vec.x < 0 ) {
		vec.x += BREAK_SPEED_WALKING;
		if ( vec.x > 0 ) {
			vec.x = 0;
		}
	}
	if ( vec.x > 0 ) {
		vec.x += -BREAK_SPEED_WALKING;
		if ( vec.x < 0 ) {
			vec.x = 0;
		}
	}

	// アクセル処理
	if ( getDeviceDirX( ) < -50 ) {
		vec.x += -ACCEL_SPEED_WALKING;
		if ( vec.x < -MAX_SPEED ) {
			vec.x = -MAX_SPEED;
		}
	}
	if ( getDeviceDirX( ) > 50 ) {
		vec.x += ACCEL_SPEED_WALKING;
		if ( vec.x > MAX_SPEED ) {
			vec.x = MAX_SPEED;
		}
	}

	// 移動量更新
	setVec( vec );
	
	// 止まった
	if ( getVec( ).isOrijin( ) ) {
		setAction( ACTION_WAIT );
		return;
	}

	// ショット
	if ( getDevicePush( ) & BUTTON_A &&
		 _cool_time > COOL_TIME ) {
		setAction( ACTION_ATTACK );
	}
	
	// 歩く音
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
}

void Player::actOnFloating( ) {
	// 地面に降り立った
	if ( isStanding( ) ) {
		setAction( ACTION_WAIT );
		return;
	}

	// 攻撃
	if ( getDevicePush( ) & BUTTON_A &&
		 _cool_time > COOL_TIME ) {
		setAction( ACTION_ATTACK );
		return;
	}

	// 入力している方向にアクセルを加える
	int dir_x = getDeviceDirX( );
	Vector vec = getVec( );
	if ( dir_x < -50 ) {
		vec.x += -ACCEL_SPEED_FLOATING;
		if ( vec.x < -MAX_SPEED ) {
			vec.x = -MAX_SPEED;
		}
	}
	if ( dir_x > 50 ) {
		vec.x += ACCEL_SPEED_FLOATING;
		if ( vec.x > MAX_SPEED ) {
			vec.x = MAX_SPEED;
		}
	}
	setVec( vec );
}

void Player::actOnAttack( ) {
	int level = ( _charge_count / _max_charge_phase_count ) + 1;
	if ( _item[ ITEM_HYPERTROPHY ] ) {
		level++;
	}
	Sound::getTask( )->playSE( "yokai_se_20.wav" );
	ShotPlayerPtr shot( new ShotPlayer( _player, getPos( ), getDir( ), level ) );
	shot->setArea( getArea( ) );
	Armoury::getTask( )->add( shot );
	_charge_count = 0;
	_cool_time = 0;
	
	setAction( ACTION_FLOAT );
}

void Player::actOnCharge( ) {
	SoundPtr sound = Sound::getTask( );
	sound->playSE( "yokai_se_21.wav", true );
	if ( !isStanding( ) ) {
		sound->playSE( "yokai_voice_17.wav" );
		sound->stopSE( "yokai_se_21.wav" );
		sound->stopSE( "yokai_se_22.wav" );
		setAction( ACTION_FLOAT );
		return;
	}
	if ( getDevicePush( ) & BUTTON_A &&
		 _cool_time > COOL_TIME ) {
		sound->stopSE( "yokai_se_21.wav" );
		sound->stopSE( "yokai_se_22.wav" );
		setAction( ACTION_ATTACK );
		return;
	}
	if ( getDeviceDirY( ) <= 0 ) {
		if ( getDeviceDirX( ) == 0 ) {
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
		if ( getDevicePush( ) & BUTTON_C ) {
			jump( );
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
	if ( _charge_count > _max_charge_phase_count * 4 - 1 ) {
		_charge_count = 0;
		sound->stopSE( "yokai_se_22.wav" );
		setAction( ACTION_OVER_CHARGE );
	}
}

void Player::actOnOverCharge( ) {
	if ( getActCount( ) > BURST_TIME ) {
		setAction( ACTION_WAIT );
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
	//左
	if ( pos.x + vec.x - radius < x ) {
		pos.x = x + radius;
		vec.x = 0;
		setPos( pos );
		setVec( vec );
		//壁に挟まれていたら吹っ飛ぶ
		if ( getArea( ) == AREA_STREET ) {
			if ( World::getTask( )->getMap( AREA_STREET )->getObject( getPos( ) ) == OBJECT_BLOCK ) {
				damage( 1 );
				blowAway( );
			}
		}
	}
	//右
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
		_progress_count = 0;
		setAction( ACTION_CONTINUE );
		setArea( AREA_STREET );
	}
}

void Player::actOnCall( ) {
	MonmotaroConstPtr monmo( Family::getTask( )->getMonmotaro( ) );
	
	if ( monmo->getAction( ) == Monmotaro::ACTION_MOVE ) {
		setAction( ACTION_WAIT );
	}
}

void Player::actOnEnteringFadeOut( ) {

}

void Player::actOnEnteringSanzo( ) {
}

void Player::actOnAudience( ) {
}

void Player::actOnEnding( ) {
	if ( getDeviceButton( ) & BUTTON_A ||
		 getDeviceButton( ) & BUTTON_B ||
		 getDeviceButton( ) & BUTTON_C ||
		 getDeviceButton( ) & BUTTON_D ) {
		_progress_count++;
		if ( _progress_count > 100 ) {
			_progress_count = 100;
		}
	} else {
		_progress_count = 0;
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
	Vector self = getOverlappedPos( );
	Vector nonself  = target->getOverlappedPos( );
	Vector distance = nonself - self;

	//自分よりも相手が上にいた場合false
	if ( distance.y < 0 ) {
		return false;
	}
	//接近しすぎの場合false
	if ( distance.getLength( ) < target->getOverlappedRadius( ) ) {
		return false;
	}

	//横方向だった場合false
	if ( self.x < nonself.x - target->getOverlappedRadius( ) ||
		 self.x > nonself.x + target->getOverlappedRadius( ) ) {
		return false;
	}
	return true;
}

void Player::bound( ) {
	jump( );
}

void Player::blowAway( ) {
	if ( isExist( ) &&
		 !Debug::getTask( )->isDebug( ) ) {
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
	if ( _virtue > 9 ) {
		_virtue = 9;
	}
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
		data->setStatusProgress( _player, SynchronousData::PROGRESS_BAR, _progress_count );
		break;
	case ACTION_CONTINUE:
		data->setStatusState( _player, SynchronousData::STATE_CONTINUE ); 
		data->setStatusProgress( _player, SynchronousData::PROGRESS_BAR, _progress_count );
		break;
	case ACTION_ENDING:
		data->setStatusState( _player, SynchronousData::STATE_CONTINUE ); 
		data->setStatusProgress( _player, SynchronousData::PROGRESS_ENDING, _progress_count );
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
	data->setStatusRedo( _player, _redo );

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
	case ACTION_DAMEGE:
	case ACTION_BLOW_AWAY:
		break;
	case ACTION_ENTRY:
	case ACTION_CONTINUE:
	case ACTION_ENDING:
		return;
	case ACTION_WALK:
		motion = ( int )getPos( ).x / PLAYER_ANIM_WAIT_COUNT / 4;
		break;
	case ACTION_FLOAT:
		motion = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
		break;
	case ACTION_WAIT:
	case ACTION_CALL:
		motion = getActCount( ) / PLAYER_ANIM_WAIT_COUNT;
		break;
	case ACTION_OVER_CHARGE:
		motion = getActCount( ) * num / BURST_TIME;
		if ( motion > num - 1 ) {
			motion = num - 1;
		}
			
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
			int anim = _charge_count / ( _max_charge_phase_count / 6 );
			if ( anim >= num ) {
				anim = num - 1;
			}
			motion = anim;
			break;
		}
	case ACTION_ENTERING_FADEOUT:
		motion = getActCount( ) * num / ENTERING_FADE_COUNT;
		break;
	case ACTION_ENTERING_SANZO:
		{
			// 蛇三蔵
			Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), PI * getActCount( ) / ENTERING_SANZO_COUNT );
			Vector pos = Vector( x, y - 256 ) + mat.multiply( Vector( 256, 0 ) );
			data->addObject( AREA_STREET, SynchronousData::TYPE_SANZO, getActCount( ) / PLAYER_ANIM_WAIT_COUNT % 6 ,0 ,( int )pos.x, ( int )pos.y );
			if ( getActCount( ) > ENTERING_SANZO_COUNT / 2 ) {
				x = ( int )pos.x;
				y = ( int )pos.y;
			}
			break;
		}
	case ACTION_AUDIENCE:
		motion = 0;
		break;
	}

	if ( isStanding( ) && map->getObject( getPos( ) ) == OBJECT_WATER ) {
		off = off + 80;
	}

	pattern = off + motion % num;

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
		int phase = ( _charge_count / _max_charge_phase_count ) * 2;
		int time = ( getActCount( ) / 2 ) % 2;
		data->addObject( area, SynchronousData::TYPE_SHOT, ANIM[ phase + time ], attribute, x, y );
	}
}

void Player::setActionEnteringFadeOut( ) {
	setVec( Vector( ) );
	setAction( ACTION_ENTERING_FADEOUT );
}

void Player::setActionEnteringSanzo( ) {
	setVec( Vector( ) );
	setAction( ACTION_ENTERING_SANZO );
}

bool Player::isEntering( ) const {
	if ( _action == ACTION_ENTERING_FADEOUT ) {
		return getActCount( ) >= ENTERING_FADE_COUNT;
	}

	if ( _action == ACTION_ENTERING_SANZO ) {
		return getActCount( ) >= ENTERING_SANZO_COUNT;
	}

	return false;
}

bool Player::isWearingItem( ITEM item ) const {
	return _item[ item ];
}

void Player::enterEvent( int x, int y ) {
	setArea( AREA_EVENT );
	setPos( Vector( x, y ) );
	setVec( Vector( ) );
	setAction( ACTION_FLOAT );
}


void Player::leaveEvent( ) {
	Magazine::getTask( )->add( ImpactPtr( new Impact( getPos( ) + Vector( 0, getOverlappedRadius( ) ), getArea( ), ( int )getOverlappedRadius( ) * 2 ) ) );

	setArea( AREA_STREET );
	setPos( Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, 0 ) );
	setVec( Vector( ) );
	setAction( ACTION_FLOAT );
}

EVENT Player::getOnEvent( ) const {
	if ( !isStanding( ) ||
		 getArea( ) == AREA_EVENT ||
		 !isExist( )  ) {
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


	if ( _mode == MODE_ENMA ) {
		event = EVENT_ENMA;
	}
	if ( _virtue >= _max_virtue ) {
		event = EVENT_BUDHA;
	}

	return event;
}


void Player::pickUpItem( ITEM item ) {
	_item[ item ] = true;
	switch ( item ) {
	case ITEM_DANGO      : setProgressType( SynchronousData::PROGRESS_ITEM_DANGO       ); break;
	case ITEM_HEART	     : setProgressType( SynchronousData::PROGRESS_ITEM_HEART	      ); break;
	case ITEM_HYPERTROPHY: setProgressType( SynchronousData::PROGRESS_ITEM_HYPERTROPHY ); break;
	case ITEM_SHORTENING : setProgressType( SynchronousData::PROGRESS_ITEM_SHORTENING  ); break;	
	case ITEM_WOOD	     : setProgressType( SynchronousData::PROGRESS_ITEM_WOOD	      ); break;
	case ITEM_FLAME	     : setProgressType( SynchronousData::PROGRESS_ITEM_FLAME	      ); break;
	case ITEM_MINERAL    : setProgressType( SynchronousData::PROGRESS_ITEM_MINERAL     ); break;
	}

	if ( _item[ ITEM_WOOD ] &&
		 _item[ ITEM_FLAME ] &&
		 _item[ ITEM_MINERAL ] &&
		 _mode == MODE_NORMAL ) {
		_mode = MODE_ENMA;
	}
}

void Player::jump( ) {
	Sound::getTask( )->playSE( "yokai_voice_17.wav" );
	Vector vec = getVec( );
	vec.y = -_jump_power;
	setVec( vec );
	setAction( ACTION_FLOAT );
}

Player::MODE Player::getMode( ) const {
	return _mode;
}

void Player::autoMove( int target_x ) {
	_auto_move_target_x = target_x;
}

bool Player::isFinishedAutomoving( ) const {
	return _auto_move_target_x < 0;
}

void Player::audience( ) {
	setVec( Vector( ) );
	setAction( ACTION_AUDIENCE );
}

void Player::setModeVirtue( ) {
	_mode = MODE_VIRTUE;
}

void Player::setActionEnding( ) {
	_action = ACTION_ENDING;
}


int Player::getDeviceDirX( ) {
	if ( abs( getPos( ).x - _auto_move_target_x ) < 5.0 ) {
		_auto_move_target_x = -1;
	}

	if ( _auto_move_target_x < 0 ) {
		DevicePtr device = Device::getTask( );
		return device->getDirX( _device_id );
	}

	return 100 - 200 * ( _auto_move_target_x - getPos( ).x < 0 );
}

int Player::getDeviceDirY( ) {
	if ( _auto_move_target_x < 0 ) {
		DevicePtr device = Device::getTask( );
		return device->getDirY( _device_id );
	}
	return 0;
}

unsigned char Player::getDevicePush( ) {
	if ( _auto_move_target_x < 0 ) {
		DevicePtr device = Device::getTask( );
		return device->getPush( _device_id );
	}
	return 0;
}

unsigned char Player::getDeviceButton( ) {
	if ( _auto_move_target_x < 0 ) {
		DevicePtr device = Device::getTask( );
		return device->getButton( _device_id );
	}
	return 0;
}

bool Player::isLeaveAlone( ) const {
	return getActCount( ) > 30 * 30 && _action == ACTION_WAIT;
}

void Player::checkSandwichedWall( ) {
	if ( getPos( ).x - Family::getTask( )->getCameraPosX( ) < 80 ) {
		_sandwiched_count++;
	} else {
		_sandwiched_count = 0;
	}
	if ( _sandwiched_count > MAX_SANDWICHED_COUNT ) {
		damage( 1 );
		blowAway( );
	}
}
