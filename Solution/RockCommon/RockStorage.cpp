#include "RockStorage.h"
#include "Application.h"
#include "RockItem.h"
#include "RockItemDango.h"

RockStoragePtr RockStorage::getTask( ) {
	return std::dynamic_pointer_cast< RockStorage >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockStorage::RockStorage( ) {
	_items.push_back( RockItemPtr( new RockItemDango( Vector( 0, 10, 0 ) ) ) );
}


RockStorage::~RockStorage( ) {
}

void RockStorage::update( ) {
	std::list< RockItemPtr >::iterator ite = _items.begin( );
	while ( ite != _items.end( ) ) {
		RockItemPtr item = *ite;
		if ( !item ) {
			ite++;
			continue;
		}
		item->update( );
		ite++;
	}
}

void RockStorage::add( RockItemPtr item ) {
	_items.push_back( item );
}

std::list< RockItemPtr > RockStorage::getItems( ) const {
	return _items;
}
