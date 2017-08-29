#include "RockStorage.h"
#include "Application.h"
#include "RockItem.h"
#include "RockItemDango.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"
#include "RockItemToku.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"
#include "RockAlter.h"
#include "RockCasket.h"

RockStoragePtr RockStorage::getTask( ) {
	return std::dynamic_pointer_cast< RockStorage >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockStorage::RockStorage( ) {
	//_items.push_back( RockItemPtr( new RockItemDango( Vector( 0, 10, 0 ) ) ) );
	//_items.push_back( RockItemPtr( new RockItemMoney( Vector( 20, 10, 200 ), RockItemMoney::MONEY_VALUE_1 ) ) );
	//_items.push_back( RockItemPtr( new RockItemMoney( Vector( 40, 10, 200 ), RockItemMoney::MONEY_VALUE_2 ) ) );
	//_items.push_back( RockItemPtr( new RockItemMoney( Vector( 60, 10, 200 ), RockItemMoney::MONEY_VALUE_3 ) ) );
	//_items.push_back( RockItemPtr( new RockItemMoney( Vector( 80, 10, 200 ), RockItemMoney::MONEY_VALUE_4 ) ) );
	
}


RockStorage::~RockStorage( ) {
}

void RockStorage::update( ) {
	updateItem( );
	updateAlter( );
}


void RockStorage::updateItem( ) {
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
				pickUpItem( item, i );
				break;//forï∂Çî≤ÇØÇÈ
			}
		}
		if ( col ) {
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
}

void RockStorage::updateAlter( ) {
	std::list< RockAlterPtr >::iterator ite = _alters.begin( );
	RockFamilyPtr family( RockFamily::getTask( ) );
	while ( ite != _alters.end( ) ) {
		RockAlterPtr alter = *ite;
		if ( !alter ) {
			ite++;
			continue;
		}
		if ( alter->isActive( ) ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				RockPlayerPtr player = family->getPlayer( i );
				if ( alter->isInRange( player->getPos( ) ) ) {
					alter->setActive( false );
					player->wish( );
				}
			}
		}
		ite++;
	}
}

void RockStorage::updateCasket( ) {
	std::list< RockCasketPtr >::iterator ite = _caskets.begin( );
	RockFamilyPtr family( RockFamily::getTask( ) );
	while ( ite != _caskets.end( ) ) {
		RockCasketPtr casket = *ite;
		if ( !casket ) {
			ite++;
			continue;
		}
		ite++;
	}
}

void RockStorage::addItem( RockItemPtr item ) {
	_items.push_back( item );
}

void RockStorage::addAlter( RockAlterPtr alter ) {
	_alters.push_back( alter );
}

void RockStorage::addCasket( RockCasketPtr casket ) {
	_caskets.push_back( casket );
}

std::list< RockItemPtr > RockStorage::getItems( ) const {
	return _items;
}

std::list< RockAlterPtr > RockStorage::getAlters( ) const {
	return _alters;
}

std::list< RockCasketPtr > RockStorage::getCaskets( ) const {
	return _caskets;
}



void RockStorage::pickUpItem( RockItemPtr item, int player_id ) {
	MessageSenderPtr sender = MessageSender::getTask( );
	
	//Ç®ã‡
	RockItemMoneyPtr money = std::dynamic_pointer_cast< RockItemMoney >( item );
	if ( money ) {
		int value = money->getValue( );
		sender->sendMessage( player_id, Message::COMMAND_MONEY, &value );
	}
	//ê_äÌä‚
	RockItemRockPtr rock = std::dynamic_pointer_cast< RockItemRock >( item );
	if ( rock ) {
		unsigned char value = 1; 
		sender->sendMessage( player_id, Message::COMMAND_ITEM, &value );
	}
}
