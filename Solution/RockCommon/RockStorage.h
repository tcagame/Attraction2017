#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockStorage );
PTR( RockItem );
PTR( RockAlter );
PTR( RockItemMoney );
PTR( ModelMV1 );
PTR( RockCasket );

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
	void addCasket( RockCasketPtr object );
	std::list< RockItemPtr > getItems( ) const;
	std::list< RockAlterPtr > getAlters( ) const;
	std::list< RockCasketPtr > getCaskets( ) const;
	void pickUpItem( RockItemPtr item, int player_id );
private:
	void updateItem( );
	void updateAlter( );
	void updateCasket( );
private:
	std::list< RockItemPtr > _items;
	std::list< RockAlterPtr > _alters;
	std::list< RockCasketPtr > _caskets;
};

