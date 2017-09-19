#include "RockPlayer.h"
#include "RockClientInfo.h"
#include "RockFamily.h"
#include "RockEnemy.h"
#include "RockMilitary.h"
#include "RockCamera.h"
#include "RockCharacter.h"
#include "RockArmoury.h"
#include "RockShot.h"
#include "RockDollHouse.h"
#include "RockAncestors.h"
#include "Status.h"
#include "Device.h"
#include "Drawer.h"
#include "MessageSender.h"
#include "Effect.h"
#include "RockShotPlayer.h"
#include "RockStudio.h"
#include "Sound.h"


//移動
static const double JUMP_POWER = 6.0;
static const double MOVE_SPEED = 6.5;
static const double BRAKE_SPEED = 0.5;
static const double KNOCK_BACK_SPEED = 5.0;
//アニメーション
static const double ANIM_SPEED = 1.0;

//プレイヤーキャラ設定
static const int RADIUS = 10;
static const int HEIGHT = 20;

//チャージ時間
static const int MAX_CHARGE_COUNT = 100;
static const int INTERVAL_TIME = 10;
static const int BURST_TIME = 60;
//エフェクト位置
static const Vector CHARGE_EFFECT_ADJUST( 0, 15, 0 );
static const Vector SPEED_DOWN_EFFECT_ADJUST( 0, 15, 0 );

//その他
static const int DAMAGE_COUNT = 20;
static const int MAX_WISH_COUNT = 100;
static const int ENHANCED_POWER = 2;
static const Vector SHOT_FOOT( 0, 35, 0 );//ショットの高さ
static const Vector BUBBLE_SEARCH_RANGE = Vector( 1, 1, 1 ) * 3000.0;
static const double BUBBLE_FOLLOW_RANGE = 60.0;
static const Vector BUBBLE_FOOT = Vector( 0, 60, 0 );
static const double BUBBLE_MOVE_SPEED = MOVE_SPEED * 0.9;
static const int DEAD_ANIM_TIME = 150;
static const int ENTRY_TIME = 30;
static const int FLOAT_HEIGHT = 1;
static const int SEVER_RAG_ADJUST_TIME = 10; // 参加受付からエントリーになるときのラグ対応のため

RockPlayer::RockPlayer( StatusPtr status, const Vector& pos, int id, RockAncestorsPtr ancestors ) :
RockCharacter( pos, ( DOLL )( DOLL_TAROSUKE_WAIT + id * ROCK_PLAYER_MOTION_NUM ), RADIUS, HEIGHT ),
_attack_count( 0 ),
_charge_effect_handle( -1 ),
_speed_down_effect_handle( -1 ),
_ancestors( ancestors ),
_bubble_count( 0 ),
_damage( 0 ),
_interval( 0 ),
_continue( false ),
_speed_down( false ),
_damage_count( DAMAGE_COUNT ) {
	_id = id;
	_status = status;
	setAction( ACTION_BUBBLE );
}


RockPlayer::~RockPlayer( ) {
}

void RockPlayer::act( ) {
	switch ( _action ) {
	case ACTION_BUBBLE:
		actOnBubble( );
		break;
	case ACTION_WAIT:
		actOnWaiting( );
		break;
	case ACTION_JUMP:
		actOnJumping( );
		break;
	case ACTION_WALK:
		actOnWalking( );
		break;
	case ACTION_BRAKE:
		actOnBraking( );
		break;
	case ACTION_CHARGE:
		actOnCharging( );
		break;
	case ACTION_BURST:
		actOnBurst( );
		break;
	case ACTION_DEAD:
		actOnDead( );
		break;
	case ACTION_WISH:
		actOnWish( );
		break;
	}
	actOnAttacking( );
	updateEffect( );
	updeteState( );
	sendDamage( );
	updateInCamera( );

	if ( _speed_down ) {
		Vector vec = getVec( ) * 0.5;
		vec.y = getVec( ).y;
		setVec( vec );
	}
	_damage_count++;
	_interval++;

}

void RockPlayer::updateEffect( ) {
	EffectPtr effect( Effect::getTask( ) );
	if ( _charge_effect_handle > 0 ) {
		if ( _attack_count > 0 ) {
			double size = _attack_count / ( MAX_CHARGE_COUNT / ( MAX_PLAYER_SHOT_POWER - 1 ) ) + 4.0;
			effect->updateEffectTransform( _charge_effect_handle, getPos( ) + CHARGE_EFFECT_ADJUST, size );
		} else {
			effect->stopEffect( _charge_effect_handle );
		}
	}
	if ( _speed_down ) {
		effect->updateEffectTransform( _speed_down_effect_handle, getPos( ) + SPEED_DOWN_EFFECT_ADJUST );
	} else {
		effect->stopEffect( _speed_down_effect_handle );
	}
}

void RockPlayer::updeteState( ) {
	if ( _status->getPlayer( _id ).power <= 0 ) {
		setCol( false );
		setMass( false );
	}
	if ( _status->getPlayer( _id ).money >= TRANSITION_MONEY_NUM ) {
		if ( _status->getPlayer( _id ).area == AREA_STREET_1 ) {
			unsigned char state = AREA_STREET_2;
			MessageSender::getTask( )->sendMessage( _id, Message::COMMAND_AREA, &state );
			return;
		}
	}
}

void RockPlayer::updateInCamera( ) {
	// カメラに入り続ける
	DrawerPtr drawer( Drawer::getTask( ) );
	if ( !drawer->isInCamera( getPos( ) + getVec( ) ) ) {
		setVec( Vector( ) );
	}
	Vector dir = ( RockCamera::getTask( )->getTarget( ) - getPos( ) ).normalize( );
	while( !drawer->isInCamera( getPos( ) + getVec( ) ) ) {
		setVec( getVec( ) + dir );
	}
}

void RockPlayer::setAction( ACTION action ) {
	EffectPtr effect = Effect::getTask( );
	_action = action;
	setActCount( 0 );
	switch ( _action ) {
	case ACTION_BUBBLE:
		setPos( getPos( ) + BUBBLE_FOOT );
	case ACTION_WAIT:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WAIT + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	case ACTION_JUMP:
		setDoll( ( DOLL )( DOLL_TAROSUKE_JUMP + _id * ROCK_PLAYER_MOTION_NUM ) );
		{
			Vector vec = getVec( );
			vec.y = JUMP_POWER;
			setVec( vec );
		}
		break;
	case ACTION_WALK:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WALK + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	case ACTION_DEAD:
		setDoll( ( DOLL )( DOLL_TAROSUKE_DEAD + _id * ROCK_PLAYER_MOTION_NUM ) );
		setVec( Vector( ) );
		effect->stopEffect( _speed_down_effect_handle );
		_attack_count = 0;
		_charge_effect_handle = -1;
		_speed_down_effect_handle = -1;
		_speed_down = false;
		break;
	case ACTION_CHARGE:
		setDoll( ( DOLL )( DOLL_TAROSUKE_CHARGE + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	case ACTION_BURST:
		setDoll( ( DOLL )( DOLL_TAROSUKE_BURST + _id * ROCK_PLAYER_MOTION_NUM ) );
		_attack_count = 0;
		effect->stopEffect( _charge_effect_handle );
		_charge_effect_handle = -1;
		setVec( Vector( ) );
		Sound::getTask( )->stopSE( "yokai_se_21.wav" );
		Sound::getTask( )->stopSE( "yokai_se_22.wav" );
		break;
	case ACTION_WISH:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WISH + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	default:
		setDoll( ( DOLL )( DOLL_TAROSUKE_WAIT + _id * ROCK_PLAYER_MOTION_NUM ) );
		break;
	}
}

bool RockPlayer::isActive( ) const {
	return ( RockClientInfo::getTask( )->isActiveState( _status->getPlayer( _id ).area ) );
}

void RockPlayer::actOnBubble( ) {
	Status::Player status = _status->getPlayer( _id );
	SoundPtr sound = Sound::getTask( );
	if ( status.area == AREA_RESULT ||
		 status.area == AREA_ENTRY ) {
		//参加受付状態ではないまたはリザルトに入ったら泡に入らない
		if ( isOnMapModel( ) ) {
			setMass( true );
			setCol( true );
			setAction( ACTION_JUMP );
			sound->playSE( "yokai_voice_17.wav" );
			return;
		}
	}
	setMass( false );
	setCol( false );
	if ( status.device_button &&
		 status.device_button != 0b00001111 ) {
		_bubble_count++;		
	} else {
		_bubble_count = 0;
	}

	if ( _bubble_count > ENTRY_TIME ) {
		if ( isOnMapModel( ) ) {
			if ( status.power <= 0 ) {
				if ( !_continue ) {
					_continue = true;
					MessageSender::getTask( )->sendMessage( _id, Message::COMMAND_CONTINUE, nullptr );
				}
			} else {
				_continue = false;
				setMass( true );
				setCol( true );
				setAction( ACTION_JUMP );
				sound->playSE( "yokai_voice_17.wav" );
			}
			if ( status.area & AREA_WAIT ) {
				unsigned char area = AREA_ENTRY;
				MessageSender::getTask( )->sendMessage( _id, Message::COMMAND_AREA, &area );
				setAction( ACTION_JUMP );
				sound->playSE( "yokai_voice_17.wav" );
				setMass( true );
				setCol( true );
			}
			return;
		}
	}
	int dir =  _id % 2 ? -1 : 1;
	double height_vec = sin( PI2 / 180 * getActCount( ) ) * FLOAT_HEIGHT * dir;
	double width_vec = sin( PI2 / 360 * getActCount( ) + 120 ) * FLOAT_HEIGHT * 2 * dir;
	setVec( getApproachesVec( ) + Vector( width_vec, height_vec, 0 ) );
}

void RockPlayer::actOnWaiting( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		Sound::getTask( )->playSE( "yokai_se_31.wav" );
		return;
	}
	if ( player.area == AREA_WAIT &&
		 getActCount( ) > SEVER_RAG_ADJUST_TIME ) {
		setAction( ACTION_BUBBLE );
		return;
	}
	//ジャンプ
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_C ) {
			setAction( ACTION_JUMP );
			Sound::getTask( )->playSE( "yokai_voice_17.wav" );
			return;
		}
	}
	//攻撃
	if ( player.device_button & BUTTON_A &&
		 _interval > INTERVAL_TIME ) {
		if ( isStanding( ) ) {
			setAction( ACTION_CHARGE );
		} else {
			_attack_count = 1;
		}
		return;
	}
	//移動
	bool want_move = player.device_x != 0 || player.device_y != 0;
	if (want_move) {
		if ( isStanding( ) ) {
			setAction( ACTION_WALK );
		} else {
			move( );
		} 
		return;
	}


	//ブレーキ
	//水平方向のベクトル
	Vector vec = getVec( );
	vec.y = 0;
	//移動条件以外でベクトルがある場合待機に移行する
	if ( vec.getLength( ) > 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	//_attack_count -= 2;
}

void RockPlayer::actOnJumping( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		Sound::getTask( )->playSE( "yokai_se_31.wav" );
		return;
	}
	if ( player.area == AREA_WAIT &&
		 getActCount( ) > SEVER_RAG_ADJUST_TIME ) {
		setAction( ACTION_BUBBLE );
		return;
	}
	if ( isStanding( ) ) {
	//攻撃
		if ( player.device_button & BUTTON_A &&
			 _interval > INTERVAL_TIME ) {
			setAction( ACTION_CHARGE );
		} else {
			setAction( ACTION_WAIT );
		}
		return;
	}
	//移動
	move( );
}

void RockPlayer::actOnWalking( ) {
	Status::Player player = _status->getPlayer( _id );
	SoundPtr sound = Sound::getTask( );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		Sound::getTask( )->playSE( "yokai_se_31.wav" );
		return;
	}
	if ( player.area == AREA_WAIT &&
		 getActCount( ) > SEVER_RAG_ADJUST_TIME ) {
		setAction( ACTION_BUBBLE );
		return;
	}
	//ジャンプ
	if ( isStanding( ) ) {
		if ( player.device_button & BUTTON_C ) {
			setAction( ACTION_JUMP );
			Sound::getTask( )->playSE( "yokai_voice_17.wav" );
			return;
		}
	}
	//浮いている
	if ( !isStanding( ) ) {
		setAction( ACTION_WAIT );
		return;
	}
	//ブレーキ
	if ( player.device_x == 0 &&
		 player.device_y == 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}

	//移動
	move( );

	if ( !sound->isPlayingSE( "yokai_voice_15.wav" ) ) {
		sound->playSE( "yokai_voice_15.wav" );
	}
}

void RockPlayer::actOnAttacking( ) {	
	Status::Player player = _status->getPlayer( _id );
	SoundPtr sound = Sound::getTask( );
	// 攻撃ボタンが離されたら攻撃
	if ( !( player.device_button & BUTTON_A ) &&
		 _attack_count > 0 ) {
		sound->stopSE( "yokai_se_21.wav" );
		sound->stopSE( "yokai_se_22.wav" );
		sound->playSE( "yokai_se_20.wav" );
		bool max_charge = ( MAX_CHARGE_COUNT == _attack_count );
		int power = _attack_count / ( MAX_CHARGE_COUNT / ( MAX_PLAYER_SHOT_POWER - 1 ) ) + 1;
		if ( player.item & ITEM_ENHANCED_ATTACK ) {
			power *= ENHANCED_POWER;
		}
		RockShotPtr shot( new RockShotPlayer( _id, getPos( ) + SHOT_FOOT, getDir( ), power, max_charge ) );
		RockArmoury::getTask( )->addShot( shot );
		setAction( ACTION_WAIT );
		Effect::getTask( )->stopEffect( _charge_effect_handle );
		_attack_count = 0;
		_charge_effect_handle = -1;
		_interval = 0;
	}
}

void RockPlayer::actOnCharging( ) {
	Status::Player player = _status->getPlayer( _id );
	SoundPtr sound = Sound::getTask( );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		Sound::getTask( )->playSE( "yokai_se_31.wav" );
		return;
	}
	if ( player.area == AREA_WAIT &&
		 getActCount( ) > SEVER_RAG_ADJUST_TIME ) {
		setAction( ACTION_BUBBLE );
		return;
	}

	if ( _attack_count == 0 ) {
		EffectPtr effect( Effect::getTask( ) );
		_charge_effect_handle = effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_CHARGE ) );
		effect->updateEffectTransform( _charge_effect_handle, getPos( ) + CHARGE_EFFECT_ADJUST );
	}
	
	if ( player.item & ITEM_ENHANCED_CHARGE ) {
		_attack_count += 2;
	} else {
		_attack_count++;
	}

	if ( _attack_count > MAX_CHARGE_COUNT ) {
		setAction( ACTION_BURST );
		return;
	}

	//攻撃中の移動
	if ( player.device_x != 0 ||
		player.device_y != 0 ) {
		setAction( ACTION_WALK );
		return;
	}
	Vector vec = getVec( );
	vec.y = 0;
	if ( vec.getLength2( ) != 0 ) {
		setAction( ACTION_BRAKE );
		return;
	}
	if ( player.device_button & BUTTON_C ) {
		setAction( ACTION_JUMP );
		Sound::getTask( )->playSE( "yokai_voice_17.wav" );
		return;
	}
	if ( !sound->isPlayingSE( "yokai_se_21.wav" ) ) {
		sound->playSE( "yokai_se_21.wav" );
	}
	if ( _attack_count > MAX_CHARGE_COUNT / 2 && sound->isPlayingSE( "yokai_se_21.wav" ) ) {
		sound->stopSE( "yokai_se_21.wav" );
		if ( !sound->isPlayingSE( "yokai_se_22.wav" ) ) { 
			sound->playSE( "yokai_se_22.wav" );
		}
	} 
}

void RockPlayer::actOnBurst( ) {
	if ( getActCount( ) > BURST_TIME ) {
		setAction( ACTION_WAIT );
	}
}

void RockPlayer::actOnBraking( ) {
	Status::Player player = _status->getPlayer( _id );
	//死亡
	if ( player.power <= 0 ) {
		setAction( ACTION_DEAD );
		Sound::getTask( )->playSE( "yokai_se_31.wav" );
		return;
	}
	if ( player.area == AREA_WAIT &&
		 getActCount( ) > SEVER_RAG_ADJUST_TIME ) {
		setAction( ACTION_BUBBLE );
		return;
	}
	//水平方向のベクトル
	Vector vec = getVec( );
	double tmp_y = vec.y;
	vec.y = 0;
	//ベクトルがない場合は待機かチャージに移行する
	if ( vec.getLength( ) < 0.001 ) {
		if ( player.device_button & BUTTON_A &&
			 _interval > INTERVAL_TIME ) {
			setAction( ACTION_CHARGE );
		} else {
			setAction( ACTION_WAIT );
		}
		return;
	}
	//移動入力があったらwarkに移行
	if ( player.device_x != 0 ||
		player.device_y != 0 ) {
		setAction( ACTION_WALK );
		return;
	}

	//減速処理
	if ( vec.getLength( ) > BRAKE_SPEED ) {
		vec -= vec.normalize( ) * BRAKE_SPEED;
	} else {
		vec = Vector( );
	}

	//垂直方向のベクトルを戻す
	vec.y = tmp_y;

	setVec( vec );
}

void RockPlayer::actOnDead( ) {
	if ( getActCount( ) < DEAD_ANIM_TIME ) {
		return;
	}
	setAction( ACTION_BUBBLE );
}

Vector RockPlayer::getApproachesVec( ) {
	Vector result = Vector( );
	RockFamilyPtr family = RockFamily::getTask( );
	Vector near_distance = BUBBLE_SEARCH_RANGE;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _id == i ) {
			continue;
		}
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ||
			 player->isDead( ) ||
			 player->isBubble( ) ||
			 player->getVec( ) == Vector( ) ) {
			continue;
		}
		Vector distance = player->getPos( ) + BUBBLE_FOOT - getPos( );
		if ( near_distance.getLength2( ) > distance.getLength2( ) &&
			 distance.getLength2( ) > BUBBLE_FOLLOW_RANGE * BUBBLE_FOLLOW_RANGE ) {
			near_distance = distance;
		}
	}
	if ( near_distance != BUBBLE_SEARCH_RANGE ) {
		Vector vec = near_distance;
		if ( vec.getLength2( ) > BUBBLE_MOVE_SPEED * BUBBLE_MOVE_SPEED ) {
			vec = vec.normalize( ) * BUBBLE_MOVE_SPEED;
		}
		result = vec;
	}
	return result;
}

void RockPlayer::actOnWish( ) {
	if ( getActCount( ) > MAX_WISH_COUNT ) {
		setAction( ACTION_WAIT );
	}
}

ModelMV1Ptr RockPlayer::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );
	switch ( _action ) {
	case ACTION_WAIT:		
		anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
		break;
	case ACTION_JUMP:
	{
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		if ( anim_time >= end_time ) {
			anim_time = end_time;
		}
	}
		break;
	case ACTION_WALK:
		anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
		break;
	case ACTION_DEAD:
	{
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		if ( anim_time >= end_time ) {
			anim_time = end_time;
		}
	}
		break;
	case ACTION_CHARGE:
		anim_time = ( double )getActCount( ) * ANIM_SPEED;
		break;
	case ACTION_BURST:
	case ACTION_WISH:
		anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
		break;
	default:
		anim_time = 0;
		break;
	}

	model->setAnimTime( anim_time );
	double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	if ( isBubble( ) ) {
		rot = Vector( 0, 0, -1 ).angle( Vector( 0, 0, -1 ) );
	}
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockPlayer::damage( int force ) {
	if ( isDead( ) ||
		 isBubble( ) ) {
		return;
	}
	if ( _damage_count > DAMAGE_COUNT ) {
		_damage += force;
		_damage_count = 0;
		_attack_count = 0;
		Effect::getTask( )->stopEffect( _charge_effect_handle );
		_charge_effect_handle = -1;
	}
}

void RockPlayer::bound( ) {
	SoundPtr sound = Sound::getTask( );
	if ( isBubble( ) ) {
		return;
	}
	setAction( ACTION_JUMP );
	RockCharacter::bound( );
	Sound::getTask( )->playSE( "yokai_voice_17.wav" );
}

void RockPlayer::back( ) {
	Vector vec = getVec( );
	setPos( getPos( ) - Vector( vec.x, 0, vec.z ) );
}

bool RockPlayer::wish( ) {
	if ( !isStanding( ) ||
		 _action == ACTION_WISH ) {
		return false;
	}
	setAction( ACTION_WISH );
	Sound::getTask( )->playSE( "yokai_voice_06.wav" );
	setVec( Vector( ) );
	_ancestors->pop( );
	return true;
}

void RockPlayer::resetPos( const Vector& pos ) {
	setPos( pos );
	setAction( ACTION_JUMP );
}

bool RockPlayer::isDead( ) const {
	return _action == ACTION_DEAD;
}

bool RockPlayer::isBubble( ) const {
	return _action == ACTION_BUBBLE;
}

void RockPlayer::resetBubble( ) {
	_bubble_count = 0;
	setAction( ACTION_BUBBLE );
}

void RockPlayer::sendDamage( ) {
	SoundPtr sound = Sound::getTask( );
	if ( _damage != 0 ) {
		switch(_id ) {
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
		MessageSender::getTask( )->sendMessage( _id, Message::COMMAND_POWER, &_damage );
		_damage = 0;
	}
}

void RockPlayer::move( ) {
	Status::Player player = _status->getPlayer( _id );
	RockCameraPtr camera( RockCamera::getTask( ) );
	Vector camera_dir = camera->getTarget( ) - camera->getPos( );
	camera_dir.y = 0;
	Vector axis( 0, -1, 0 );
	if ( Vector( 0, 0, 1 ).cross( camera_dir ).y < 0 ) {
		axis = Vector( 0, 1, 0 );
	}
	double angle = Vector( 0, 0, 1 ).angle( camera_dir );
	Matrix rot = Matrix::makeTransformRotation( axis, angle );
	Vector vec = Vector( player.device_x, 0, -player.device_y ).normalize( ) * MOVE_SPEED;
	vec = rot.multiply( vec );
	vec.y = getVec( ).y;
	setVec( vec );
}

void RockPlayer::setAdmissionPos( const Vector& camera_pos ) {
	setPos( camera_pos + BUBBLE_FOOT );
}

int RockPlayer::getId( ) const {
	return _id;
}

void RockPlayer::speedDown( ) {
	_speed_down = true;
	_speed_down_effect_handle = Effect::getTask( )->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_SPEED_DOWN ) );
}

void RockPlayer::knockBack( RockEnemyPtr enemy ) {
	Vector dir = getPos( ) - enemy->getPos( );
	dir.y = 0;
	dir = dir.normalize( );
	Vector vec = dir * KNOCK_BACK_SPEED;
	if ( _status->getPlayer( _id ).power > 0 ) {
		setVec( vec );
	}
}
