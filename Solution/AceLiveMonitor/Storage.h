#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Storage );
PTR( Item );
PTR( Player );

class Storage : public Task {
public:
	static std::string getTag( ) { return "STORAGE"; };
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
private:
	PlayerPtr getOverLappedPlayer( ItemPtr item ) const;
	void createToku( ); //debug�p
	void pickUpItem( ItemPtr item, PlayerPtr player );
private:
	std::list< ItemPtr > _items;
};

