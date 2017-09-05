#include "Storage.h"
#include "Application.h"
#include "Item.h"
#include "Family.h"
#include "Player.h"
#include "ItemMoney.h"
#include "ItemVirtue.h"
#include "SynchronousData.h"
#include "ItemDango.h"
#include "ItemEnhancedAttack.h"
#include "ItemEnhancedCharge.h"

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
	int camera_pos = Family::getTask( )->getCameraPosX( );
	std::list< ItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		ItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		item->update( );
		item->setSynchronousData( SynchronousData::TYPE_ITEM, camera_pos );
		PlayerPtr hit_player = getOverLappedPlayer( item );
		if ( hit_player ) {
			//プレイヤーがアイテムと接触
			pickUpItem( item, hit_player );
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
	//createVirtue( );
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
		if ( item->getArea( ) == AREA_EVENT ) {
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
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->isOverlapped( item ) ) {
			result = player;
			break;
		}
	}
	return result;
}

void Storage::createVirtue( ) {
	static int count = 0;
	count++;
	const int create_time = 60;
	if ( !( count % create_time ) ) {
		FamilyPtr family( Family::getTask( ) );
		Vector pos = Vector( family->getCameraPosX( ) + ( rand( ) % SCREEN_WIDTH ), 100 );
		ItemPtr virtue( new ItemVirtue( pos ) );
		virtue->setArea( AREA_STREET );
		add( virtue );
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
		if ( item->getArea( ) == AREA_EVENT ) {
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
			player->addMoney( money->getValue( ) );
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
			}
		}
	}
}

void Storage::createShopItem( ) {
	{
		ItemPtr item = ItemPtr( new ItemDango( Vector( 500, 0 ) ) );
		item->setArea( AREA_EVENT );
		_items.push_back( item );
	}
	{
		ItemPtr item = ItemPtr( new ItemEnhancedAttack( Vector( 600, 0 ) ) );
		item->setArea( AREA_EVENT );
		_items.push_back( item );
	}
	{
		ItemPtr item = ItemPtr( new ItemEnhancedCharge( Vector( 700, 0 ) ) );
		item->setArea( AREA_EVENT );
		_items.push_back( item );
	}
}
