#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Storage );
PTR( Item );
PTR( ShopItem );
PTR( Player );

class Storage : public Task {
public:
	static std::string getTag( ) { return "ITEM"; };
	static StoragePtr getTask( );
public:
	Storage( );
	virtual ~Storage( );
public:
	void update( );
	void add( ItemPtr item );
	bool isExistanceEventItem( ) const;
	std::list< ItemPtr > getItems( ) const;
	void eraseEventItem( );
	void createShopItem( );
private:
	PlayerPtr getOverLappedPlayer( ItemPtr item ) const;
	void createVirtue( ); //debug�p
	void pickUpItem( ItemPtr item, PlayerPtr player );
private:
	std::list< ItemPtr > _items;
};

