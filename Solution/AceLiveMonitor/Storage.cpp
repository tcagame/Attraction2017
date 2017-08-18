#include "Storage.h"
#include "Application.h"
#include "Item.h"
#include "Family.h"
#include "Player.h"
#include "ItemMoney.h"
#include "ItemToku.h"

PTR( ItemMoney );
PTR( ItemToku );

StoragePtr Storage::getTask( ) {
	return std::dynamic_pointer_cast< Storage >( Application::getInstance( )->getTask( getTag( ) ) );
}


Storage::Storage( ) {
}

Storage::~Storage( ) {
}

void Storage::update( ) {
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		item->update( );
		PlayerPtr hit_player = getOverLappedPlayer( item );
		if ( hit_player ) {
			//プレイヤーがアイテムと接触
			pickUpItem( item, hit_player );
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
	//createToku( );
}

void Storage::add( ItemPtr item ) {
	_items.push_back( item );
}

std::list< ItemPtr > Storage::getItems( ) const {
	return _items;
}

bool Storage::isExistanceEventItem( ) const {
	bool result = false;
	std::list< ItemPtr >::const_iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		if ( item->getState( ) == Character::STATE_EVENT ) {
			result = true;
			break;
		}
		ite++;
	}
	return result;
}

PlayerPtr Storage::getOverLappedPlayer( ItemPtr item ) const {
	PlayerPtr result = PlayerPtr( );
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->isOverlapped( item ) ) {
			result = player;
			break;
		}
	}
	return result;
}

void Storage::createToku( ) {
	static int count = 0;
	count++;
	const int create_time = 30;
	if ( !( count % create_time ) ) {
		FamilyPtr family( Family::getTask( ) );
		Vector pos = Vector( family->getCameraPos( ) + ( rand( ) % SCREEN_WIDTH ), 100 );
		add( ItemPtr( new ItemToku( pos ) ) );
	}
}

void Storage::eraseEventItem( ) {
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		if ( item->getState( ) == Character::STATE_EVENT ) {
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
}

void Storage::pickUpItem( ItemPtr item, PlayerPtr player ) {
	{//お金
		ItemMoneyPtr money = std::dynamic_pointer_cast< ItemMoney >( item );
		if ( money ) {
			player->pickUpMoney( money->getValue( ) );
		}
	}
	{//徳
		ItemTokuPtr toku = std::dynamic_pointer_cast< ItemToku >( item );
		if ( toku ) {
			player->pickUpToku( );
		}
	}
}
