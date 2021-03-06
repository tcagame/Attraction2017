#include "EventGamble.h"
#include "Family.h"
#include "Player.h"
#include "Magazine.h"
#include "Impact.h"
#include "SynchronousData.h"
#include "ItemDice.h"
#include "Storage.h"

const int START_POS_X = 256 + 100;
const int START_POS_Y = 200;
const int AUDIENCE_COUNT = 100;
const int BET_POS_Y = 210;
const int FEVER_COUNT = 10;
const int SUCCESS_COUNT = 100;
const int FINISHED_COUNT = 60;
const int SHAKE_COUNT = 100;

const int START_DICE_X = 640;
const int START_DICE_Y = 100;

EventGamble::EventGamble( ) :
Event( EVENT_GAMBLE, DIR_LEFT ),
_count( 0 ),
_phase( PHASE_AUDIENCE ) {
}


EventGamble::~EventGamble( ) {
}

void EventGamble::update( ) {
	switch ( _phase ) {
	case PHASE_AUDIENCE:
		if ( _player->isFinishedAutomoving( ) ) {
			_player->audience( );
		}
		_count++;
		if ( _count > AUDIENCE_COUNT ) {
			SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_GAMBLE0 );
			_phase = PHASE_BET;
			_player->free( );
		}
		break;
	case PHASE_BET:
		if ( _player->getArea( ) == AREA_STREET ) {
			SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_NONE );
			break;
		}
		if ( _player->isStanding( ) ) {
			if ( _player->getPos( ).y < BET_POS_Y ) {
				_player->audience( false );
				_phase = PHASE_SHAKE;
				_count = 0;
				_dice[ 0 ] = ItemDicePtr( new ItemDice( Vector( START_DICE_X - 20, START_DICE_Y ), AREA_EVENT ) );
				_dice[ 1 ] = ItemDicePtr( new ItemDice( Vector( START_DICE_X + 20, START_DICE_Y ), AREA_EVENT ) );
				Storage::getTask( )->add( _dice[ 0 ] );
				Storage::getTask( )->add( _dice[ 1 ] );
			}
		}
		escape( );
		break;
	case PHASE_SHAKE:
		_count++;
	 	if ( _count > SHAKE_COUNT ) {
			_phase = PHASE_DICE;
			_dice[ 0 ]->stop( );
			_dice[ 1 ]->stop( );
		}
		break;
	case PHASE_DICE:
		{
			// 今回の結果をランダムで決定
			int dice = ( _dice[ 0 ]->getNum( ) + _dice[ 1 ]->getNum( ) ) % 2;
			if ( dice == 0 ) {
				SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_GAMBLE1 );
			} else {
				SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_GAMBLE2 );
			}
			// 選択したBETを取得
			int bet = 0;
			if ( _player->getPos( ).x < 1280 / 2 ) {
				bet = 1;
			}
			// 正解か調べる
			if ( bet == dice ) {
				_phase = PHASE_SUCCESS;
			} else {
				_player->pickUpMoney( -10000 );
				_phase = PHASE_FINISHED;
				Magazine::getTask( )->add( ImpactPtr( new Impact( _player->getPos( ), AREA_EVENT ) ) );
			}
			// 次へ
			_count = 0;
		}
		break;
	case PHASE_SUCCESS:
		_count++;
		if ( _count % FEVER_COUNT == 0 ) {
			_player->pickUpMoney( 10000 );
		}
		if ( _count > SUCCESS_COUNT ) {
			_phase = PHASE_FINISHED;
			_count = 0;
		}
		break;
	case PHASE_FINISHED:
		_count++;
		if ( _count > FINISHED_COUNT ) {
			exit( );
			SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_NONE );
		}
		break;
	}
}

void EventGamble::join( PLAYER target ) {
	//定員一名
	if ( _player ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
	player->autoMove( 1280 / 2 );
	_player = player;
}