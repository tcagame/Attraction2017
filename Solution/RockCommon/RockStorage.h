#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockStorage );
PTR( RockItem );
PTR( RockItemMoney );
PTR( ModelMV1 );

class RockStorage : public Task {
public:
	static std::string getTag( ) { return "ROCKSTORAGE"; };
	static RockStoragePtr getTask( );
public:
	RockStorage( );
	virtual ~RockStorage( );
public:
	void update( );
	void add( RockItemPtr item );
	std::list< RockItemPtr > getItems( ) const;
	void pickUpItem( RockItemPtr item, int player_id );
private:
	std::list< RockItemPtr > _items;
};

