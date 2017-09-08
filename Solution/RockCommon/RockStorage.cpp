#include "RockStorage.h"
#include "Application.h"
#include "RockItem.h"
#include "RockItemDango.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"
#include "RockItemTree.h"
#include "RockItemFire.h"
#include "RockItemToku.h"
#include "RockItemEnhancePower.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"
#include "RockAlter.h"
#include "RockCasket.h"
#include "RockItemBubble.h"
#include "RockPopItem.h"
#include "Status.h"
#include "Sound.h"

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
	updateBubble( );
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
					break;//forï∂Çî≤ÇØÇÈ
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
					if ( player->wish( ) ) {
						alter->setActive( false );
					}
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

void RockStorage::addShopItem( RockItemPtr item ) {
	item->setShopItem( true );
	_items.push_back( item );
}


void RockStorage::addAlter( RockAlterPtr alter ) {
	_alters.push_back( alter );
}

void RockStorage::addCasket( RockCasketPtr casket ) {
	_caskets.push_back( casket );
}

void RockStorage::addBubble( RockItemBubblePtr bubble ) {
	bubble->setFinished( false );
	_bubbles.push_back( bubble );
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

std::list< RockItemBubblePtr > RockStorage::getBubbles( ) const {
	return _bubbles;
}

bool RockStorage::pickUpItem( RockItemPtr item, int player_id ) {
	MessageSenderPtr sender = MessageSender::getTask( );
	bool result = true;
	{//Ç®ã‡
		RockItemMoneyPtr money = std::dynamic_pointer_cast< RockItemMoney >( item );
		if ( money ) {
			Sound::getTask( )->playSE( "yokai_voice_30.wav" );
			int value = money->getValue( );
			sender->sendMessage( player_id, Message::COMMAND_MONEY, &value );
		}
	}

	{//ê_äÌä‚
		RockItemRockPtr rock = std::dynamic_pointer_cast< RockItemRock >( item );
		if ( rock ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				if ( _status->getPlayer( i ).area == AREA_STREET_2 ) {
					if ( _status->getPlayer( i ).item & ITEM_ROCK ) {
						result = false;
					} else {
						unsigned char item = ITEM_ROCK;
						sender->sendMessage( i, Message::COMMAND_ITEM, &item );
						rock->eraseBubble( );
					}
				}
			}
		}
	}
	{//ê_äÌâŒ
		RockItemFirePtr fire = std::dynamic_pointer_cast< RockItemFire >( item );
		if ( fire ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				if ( _status->getPlayer( i ).area == AREA_STREET_2 ) {
					if ( _status->getPlayer( i ).item & ITEM_FIRE ) {
						result = false;
					} else {
						unsigned char item = ITEM_FIRE;
						sender->sendMessage( i, Message::COMMAND_ITEM, &item );
						fire->eraseBubble( );
					}
				}
			}
		}
	}

	{//ê_äÌñÿ
		RockItemTreePtr tree = std::dynamic_pointer_cast< RockItemTree >( item );
		if ( tree ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				if ( _status->getPlayer( i ).area == AREA_STREET_2 ) {
					if ( _status->getPlayer( i ).item & ITEM_TREE ) {
						result = false;
					} else {
						unsigned char item = ITEM_TREE;
						sender->sendMessage( i, Message::COMMAND_ITEM, &item );
						tree->eraseBubble( );
					}
				}
			}
		}
	}

	{//ìø  
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

	{//ÇæÇÒÇ≤
		RockItemDangoPtr dango = std::dynamic_pointer_cast< RockItemDango >( item );
		if ( dango ) {
			if ( dango->isShopItem( ) ) {
				int price = dango->getPrice( );
				if ( (int)_status->getPlayer( player_id ).money >= price ) {
					int value = -price;
					sender->sendMessage( player_id, Message::COMMAND_MONEY, &value );
				} else {
					result = false;
				}
			}
			if ( result ) {
				unsigned char item = ITEM_DANGO;
				sender->sendMessage( player_id, Message::COMMAND_ITEM, &item );
			}
		}
	}
	{//çUåÇóÕã≠âª
		RockItemEnhancePowerPtr enhance_power = std::dynamic_pointer_cast< RockItemEnhancePower >( item );
		if ( enhance_power ) {
			if ( enhance_power->isShopItem( ) ) {
				int price = enhance_power->getPrice( );
				if ( (int)_status->getPlayer( player_id ).money >= price ) {
					int value = -price;
					sender->sendMessage( player_id, Message::COMMAND_MONEY, &value );
					enhance_power->eraseBubble( );
				} else {
					result = false;
				}
			}
			if ( result ) {
				unsigned char item = ITEM_ENHANCED_ATTACK;
				sender->sendMessage( player_id, Message::COMMAND_ITEM, &item );
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

void RockStorage::updateBubble( ) {
	std::list< RockItemBubblePtr >::iterator ite = _bubbles.begin( );
	while ( ite != _bubbles.end( ) ) {
		RockItemBubblePtr bubble = *ite;
		if ( !bubble ) {
			ite++;
			continue;
		}
		if ( bubble->isFinished( ) ) {
			if ( bubble->isRepop( ) ) {
				_pop_items.push_back( RockPopItemPtr( new RockPopItem( bubble, true ) ) );
			}
			ite = _bubbles.erase( ite );
			continue;
		}
		ite++;
	}
}


void RockStorage::clean( ) {
	_items = { };
	_pop_items = { };
}
