#include "RockStorage.h"
#include "Application.h"
#include "RockItem.h"
#include "RockItemDango.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"

RockStoragePtr RockStorage::getTask( ) {
	return std::dynamic_pointer_cast< RockStorage >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockStorage::RockStorage( ) {
	_items.push_back( RockItemPtr( new RockItemDango( Vector( 0, 10, 0 ) ) ) );
	_items.push_back( RockItemPtr( new RockItemMoney( Vector( 20, 10, 200 ), RockItemMoney::MONEY_VALUE_1 ) ) );
	_items.push_back( RockItemPtr( new RockItemMoney( Vector( 40, 10, 200 ), RockItemMoney::MONEY_VALUE_2 ) ) );
	_items.push_back( RockItemPtr( new RockItemMoney( Vector( 60, 10, 200 ), RockItemMoney::MONEY_VALUE_3 ) ) );
	_items.push_back( RockItemPtr( new RockItemMoney( Vector( 80, 10, 200 ), RockItemMoney::MONEY_VALUE_4 ) ) );
}


RockStorage::~RockStorage( ) {
}

void RockStorage::update( ) {
	std::list< RockItemPtr >::iterator ite = _items.begin( );
	RockFamilyPtr family( RockFamily::getTask( ) );
	while ( ite != _items.end( ) ) {
		RockItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		item->update( );
		bool col = false;
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
			RockPlayerPtr player = family->getPlayer( i );
			if ( item->isOverLapped( player ) ) {
				col = true;
				break;//for•¶‚ð”²‚¯‚é
			}
		}
		if ( col ) {
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
}

void RockStorage::add( RockItemPtr item ) {
	_items.push_back( item );
}

std::list< RockItemPtr > RockStorage::getItems( ) const {
	return _items;
}
