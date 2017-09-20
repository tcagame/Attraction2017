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
#include "SynchronousData.h"
#include "World.h"

PTR( ItemMoney );
PTR( ItemVirtue );

StoragePtr Storage::getTask( ) {
	return std::dynamic_pointer_cast< Storage >( Application::getInstance( )->getTask( getTag( ) ) );
}


Storage::Storage( ) {
}

Storage::~Storage( ) {
}

void Storage::update( ) {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		item->update( );
		item->setSynchronousData( camera_pos );

		//プレイヤーと当たる
		PlayerPtr hit_player = family->getOverlappedPlayer( item );
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
	{//徳
		ItemVirtuePtr virtue = std::dynamic_pointer_cast< ItemVirtue >( item );
		if ( virtue ) {
			player->pickUpVirtue( );
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
		}
	}
	return result;
}
/*
void Storage::createShopItem( ) {
	{
		ItemPtr item = ShopItemPtr( new ItemDango( Vector( 500, 0 ) ) );
		item->setArea( AREA_EVENT );
		_items.push_back( item );
	}
	{
		ItemPtr item = ShopItemPtr( new ItemEnhancedAttack( Vector( 600, 0 ) ) );
		item->setArea( AREA_EVENT );
		_items.push_back( item );
	}
	{
		ItemPtr item = ShopItemPtr( new ItemEnhancedCharge( Vector( 700, 0 ) ) );
		item->setArea( AREA_EVENT );
		_items.push_back( item );
	}
}
*/

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
