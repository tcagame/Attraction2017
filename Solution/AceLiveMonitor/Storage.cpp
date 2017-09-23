#include "Storage.h"
#include "Application.h"
#include "Item.h"
#include "Family.h"
#include "Player.h"
#include "ItemMoney.h"
#include "ItemVirtue.h"
#include "ItemDango.h"
#include "ItemEnhancedAttack.h"
#include "ItemEnhancedCharge.h"
#include "ItemYokaiSoup.h"
#include "ItemBox.h"
#include "SynchronousData.h"
#include "World.h"

PTR( ItemMoney );
PTR( ItemVirtue );
PTR( ItemBox );

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
		item->update( );

		//プレイヤーと当たる
		PlayerPtr hit_player = Family::getTask( )->getOverlappedPlayer( item );
		if ( hit_player ) {
			//アイテム取得
			if ( pickUpItem( item, hit_player ) ) {
				ite = _items.erase( ite );
				continue;
			}
		}

		//画面より左に行ったら削除
		if ( item->isOutRange( ) ) {
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
}

void Storage::add( ItemPtr item ) {
	_items.push_back( item );
}

bool Storage::isExistanceEventItem( ) const {
	bool result = false;
	std::list< ItemPtr >::const_iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		if ( item->getArea( ) == AREA_EVENT ) {
			result = true;
			break;
		}
		ite++;
	}
	return result;
}

bool Storage::pickUpItem( ItemPtr item, PlayerPtr player ) {
	bool result = true;
	{//お金
		ItemMoneyPtr money = std::dynamic_pointer_cast< ItemMoney >( item );
		if ( money ) {
			player->addMoney( money->getValue( ) );
			if ( player->getMode( ) == Player::MODE_VIRTUE ) {
				player->damage( 1 );
			}
		}
	}
	{//玉手箱
		ItemBoxPtr box = std::dynamic_pointer_cast< ItemBox >( item );
		if ( box ) {
			player->pickUpItem( Player::ITEM_BOX );
		}
	}
	{//徳
		ItemVirtuePtr virtue = std::dynamic_pointer_cast< ItemVirtue >( item );
		if ( virtue ) {
			result = player->pickUpVirtue( );
		}
	}
	{//ショップアイテム
		ShopItemPtr shop_item = std::dynamic_pointer_cast< ShopItem >( item );
		if ( shop_item ) {
			int price = shop_item->getPrice( );
			if ( player->getMoney( ) >= price ) {
				player->addMoney( -price );
			} else {
				//取得できない
				result = false;
			}
			if ( result ) {
				//だんご
				if ( std::dynamic_pointer_cast< ItemDango >( item ) ) {
					player->pickUpItem( Player::ITEM_DANGO );
				}
				//攻撃強化
				if ( std::dynamic_pointer_cast< ItemEnhancedAttack >( item ) ) {
					player->pickUpItem( Player::ITEM_HYPERTROPHY );
				}
				//チャージ強化
				if ( std::dynamic_pointer_cast< ItemEnhancedAttack >( item ) ) {
					player->pickUpItem( Player::ITEM_SHORTENING );
				}
				//すーぷ
				if ( std::dynamic_pointer_cast< ItemYokaiSoup >( item ) ) {
					player->recoverPower( );
				}
			}
		}
	}
	return result;
}

void Storage::eraseEventItem( ) {
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		if ( item->getArea( ) == AREA_EVENT ) {
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
}

void Storage::shiftPos( int map_width ) {
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		( *ite )->shiftPos( map_width );
		ite++;
	}
}

void Storage::pushDebugData( ViewerDebug::Data& data ) {
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		data.circle.push_back( ( *ite )->getDebugDataCircle( ) );
		ite++;
	}
	data.message.push_back( "Item:" + std::to_string( ( int )_items.size( ) ) );
}

void Storage::setSynchronousData( ) {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );
	for ( ItemPtr item : _items ) {
		item->setSynchronousData( camera_pos );
	}
}

