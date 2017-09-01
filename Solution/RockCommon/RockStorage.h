#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockStorage );
PTR( RockItem );
PTR( RockAlter );
PTR( RockItemMoney );
PTR( RockItemRock );
PTR( RockItemTree );
PTR( RockItemFire );
PTR( RockItemToku );
PTR( ModelMV1 );
PTR( RockCasket );
PTR( RockPopItem );
PTR( Status );

class RockStorage : public Task {
public:
	static std::string getTag( ) { return "ROCKSTORAGE"; };
	static RockStoragePtr getTask( );
public:
	RockStorage( StatusPtr status );
	virtual ~RockStorage( );
public:
	void update( );
	void addItem( RockItemPtr item );
	void addDropItem( RockItemPtr item );
	void addAlter( RockAlterPtr object );
	void addCasket( RockCasketPtr object );
	std::list< RockItemPtr > getItems( ) const;
	std::list< RockAlterPtr > getAlters( ) const;
	std::list< RockCasketPtr > getCaskets( ) const;
	bool pickUpItem( RockItemPtr item, int player_id );
	void clean( );
private:
	void updateItem( );
	void updateAlter( );
	void updateCasket( );
	void updatePopItem( );
private:
	StatusPtr _status;
	std::list< RockItemPtr > _items;
	std::list< RockAlterPtr > _alters;
	std::list< RockCasketPtr > _caskets;
	std::list< RockPopItemPtr > _pop_items;
};

