#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockStorage );
PTR( RockItem );
PTR( RockAlter );
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
	void addItem( RockItemPtr item );
	void addAlter( RockAlterPtr object );
	std::list< RockItemPtr > getItems( ) const;
	std::list< RockAlterPtr > getAlters( ) const;
	void pickUpItem( RockItemPtr item, int player_id );
private:
	void updateItem( );
	void updateAlter( );
private:
	std::list< RockItemPtr > _items;
	std::list< RockAlterPtr > _alters;
};

