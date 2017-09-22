#pragma once
#include "Task.h"
#include <string>
#include <list>
#include "ViewerDebug.h"

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
	void eraseEventItem( );
	void shiftPos( int map_width );
	void pushDebugData( ViewerDebug::Data& data );
	void setSynchronousData( );
private:
	bool pickUpItem( ItemPtr item, PlayerPtr player );
private:
	std::list< ItemPtr > _items;
};

