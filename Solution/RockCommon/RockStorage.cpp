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
#include "RockPopItem.h"
#include "Status.h"

RockStoragePtr RockStorage::getTask( ) {
	return std::dynamic_pointer_cast< RockStorage >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockStorage::RockStorage( StatusPtr status ) :
_status( status ) {
}


RockStorage::~RockStorage( ) {
}

void RockStorage::update( ) {
	updateItem( );
	updateAlter( );
	updateCasket( );
	updatePopItem( );
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
			if ( !player->isActive( ) ||
				 player->isBubble( ) ) {
				continue;
			}
			if ( item->isOverLapped( player ) ) {
				if ( pickUpItem( item, i ) ) {
					col = true;
					break;//forΆπ²―ι
				} else {
					continue;
				}
			}
		}
		if ( col ) {
			if ( item->isRepop( ) ) {
				_pop_items.push_back( RockPopItemPtr( new RockPopItem( item ) ) );
			}
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

void RockStorage::addDropItem( RockItemPtr item ) {
	item->setRepop( false );
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



bool RockStorage::pickUpItem( RockItemPtr item, int player_id ) {
	MessageSenderPtr sender = MessageSender::getTask( );
	bool result = true;
	{//¨ΰ
		RockItemMoneyPtr money = std::dynamic_pointer_cast< RockItemMoney >( item );
		if ( money ) {
			int value = money->getValue( );
			sender->sendMessage( player_id, Message::COMMAND_MONEY, &value );
		}
	}

	//_νβ
	if ( _status->getPlayer( player_id ).item & ITEM_ROCK ) {
		result = false;
	} else {
		RockItemRockPtr rock = std::dynamic_pointer_cast< RockItemRock >( item );
		if ( rock ) {
			unsigned char item = ITEM_ROCK;
			sender->sendMessage( player_id, Message::COMMAND_ITEM, &item );
		}
	}
//	//_νΞ
//	if ( _status->getPlayer( player_id ).item & ITEM_FIRE ) {
//		result = false;
//	} else {
//		RockItemRockPtr fire = std::dynamic_pointer_cast< RockItemFire >( item );
//		if ( fire ) {
//			unsigned char item = ITEM_FIRE;
//			sender->sendMessage( player_id, Message::COMMAND_ITEM, &item );
//		}
//	}
//	//_νΨ
//	if ( _status->getPlayer( player_id ).item & ITEM_TREE ) {
//		result = false;
//	} else {
//		RockItemRockPtr tree = std::dynamic_pointer_cast< RockItemTree >( item );
//		if ( tree ) {
//			unsigned char item = ITEM_TREE;
//			sender->sendMessage( player_id, Message::COMMAND_ITEM, &item );
//		}
//	}

	{//Ώ  
		RockItemTokuPtr toku = std::dynamic_pointer_cast< RockItemToku >( item );
		if ( toku ) {
			Status::Player player = _status->getPlayer( player_id );
			if ( player.money >= TRANSITION_MONEY_NUM ) {
				int virtue = 1;
				sender->sendMessage( player_id, Message::COMMAND_TOKU, &virtue );
			} else {
				result = false;
			}
		}
	}
	return result;
}

void RockStorage::updatePopItem( ) {
	std::list< RockPopItemPtr >::iterator ite = _pop_items.begin( );
	while ( ite != _pop_items.end( ) ) {
		RockPopItemPtr pop_item = *ite;
		if ( !pop_item ) {
			ite++;
			continue;
		}
		pop_item->update( );
		if ( pop_item->isFinished( ) ) {
			ite = _pop_items.erase( ite );
			continue;
		}
		ite++;
	}
}

void RockStorage::clean( ) {
	_items = { };
	_pop_items = { };
}
