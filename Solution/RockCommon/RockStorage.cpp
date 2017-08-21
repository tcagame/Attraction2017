#include "RockStorage.h"
#include "Application.h"
#include "RockItem.h"

RockStoragePtr RockStorage::getTask( ) {
	return std::dynamic_pointer_cast< RockStorage >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockStorage::RockStorage( ) {
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