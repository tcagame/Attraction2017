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

const int ABSTINENCE_DAMAGE = -2;
const int CASKET_MONEY = 50000;

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
		item->update( );
		bool col = false;
		RockPlayerPtr overlapped_player = family->getOverLappedPlayer( item );
		if ( overlapped_player &&
			 !overlapped_player->isBubble( ) ) {
			if ( pickUpItem( item, overlapped_player->getId( ) ) ) {
				col = true;
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
		casket->update( );
		RockPlayerPtr overlapped_player = family->getOverLappedPlayer( casket );
		if ( overlapped_player && !overlapped_player->isBubble( ) ) {
			bool success = casket->getOpenResult( ) == RockCasket::RESULT_SUCCESS;
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				RockPlayerPtr player = family->getPlayer( i );
				if ( player->isActive( ) && !player->isBubble( ) ) {
					if (success) {
						//��������ɓ����
						int money = CASKET_MONEY;
						MessageSender::getTask( )->sendMessage( player->getId( ), Message::COMMAND_MONEY, &money );
					} else {
						//���x�ቺ
						unsigned char item = SPEED_DOWN;
						MessageSender::getTask( )->sendMessage( player->getId( ), Message::COMMAND_ITEM, &item );
					}
				}
			}
			ite = _caskets.erase( ite );
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
	{//����
		RockItemMoneyPtr money = std::dynamic_pointer_cast< RockItemMoney >( item );
		if ( money ) {
			SoundPtr sound = Sound::getTask( );
			Status::Player player = _status->getPlayer( player_id );
			if ( player.area == AREA_STREET_3 ) {
				RockFamily::getTask( )->getPlayer( player_id )->damage( ABSTINENCE_DAMAGE );
			} else {
				sound->playSE( "yokai_voice_30.wav" );
				int value = money->getValue( );
				sender->sendMessage( player_id, Message::COMMAND_MONEY, &value );
			}
		}
	}

	{//�_���
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
	{//�_���
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

	{//�_���
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

	{//��  
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

	{//����
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
	{//�U���͋���
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
	{
		std::list< RockItemPtr >::iterator ite = _items.begin( );
		while ( ite != _items.end( ) ) {
			RockItemPtr item = *ite;
			item.reset( );
			ite++;
		}
		_items = { };
	}
	{
		std::list< RockPopItemPtr >::iterator ite = _pop_items.begin( );
		while ( ite != _pop_items.end( ) ) {
			RockPopItemPtr pop_item = *ite;
			pop_item.reset( );
			ite++;
		}
		_pop_items = { };
	}
	{
		std::list< RockItemBubblePtr >::iterator ite = _bubbles.begin( );
		while ( ite != _bubbles.end( ) ) {
			RockItemBubblePtr bubble = *ite;
			bubble.reset( );
			ite++;
		}
		_bubbles = { };
	}
	{
		std::list< RockCasketPtr >::iterator ite = _caskets.begin( );
		while ( ite != _caskets.end( ) ) {
			RockCasketPtr casket = *ite;
			casket.reset( );
			ite++;
		}
		_caskets = { };
	}
	{
		std::list< RockAlterPtr >::iterator ite = _alters.begin( );
		while ( ite != _alters.end( ) ) {
			RockAlterPtr alter = *ite;
			alter.reset( );
			ite++;
		}
		_alters = { };
	}
}
