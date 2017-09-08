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
PTR( RockItemDango );
PTR( RockItemEnhancePower );
PTR( ModelMV1 );
PTR( RockCasket );
PTR( RockPopItem );
PTR( RockItemBubble );
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
	void addShopItem( RockItemPtr item );
	void addAlter( RockAlterPtr object );
	void addCasket( RockCasketPtr object );
	void addBubble( RockItemBubblePtr bubble );
	std::list< RockItemPtr > getItems( ) const;
	std::list< RockAlterPtr > getAlters( ) const;
	std::list< RockCasketPtr > getCaskets( ) const;
	std::list< RockItemBubblePtr > getBubbles( ) const;
	bool pickUpItem( RockItemPtr item, int player_id );
	void clean( );
private:
	void updateItem( );
	void updateAlter( );
	void updateCasket( );
	void updatePopItem( );
	void updateBubble( );
private:
	StatusPtr _status;
	std::list< RockItemPtr > _items;
	std::list< RockAlterPtr > _alters;
	std::list< RockCasketPtr > _caskets;
	std::list< RockPopItemPtr > _pop_items;
	std::list< RockItemBubblePtr > _bubbles;
};

