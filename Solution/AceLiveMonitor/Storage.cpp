#include "Storage.h"
#include "Application.h"
#include "Item.h"
#include "Family.h"
#include "Player.h"

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
		if ( isOverLappedPlayer( item ) ) {
			//プレイヤーがアイテムと接触
			ite = _items.erase( ite );
			continue;
		}
		ite++;
	}
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

bool Storage::isOverLappedPlayer( ItemConstPtr item ) const {
	bool result = false;
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( item->isOverlapped( player ) ) {
			result = true;
			break;
		}
	}
	return result;
}
