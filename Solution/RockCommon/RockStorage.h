#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockStorage );
PTR( RockItem );
PTR( ModelMV1 );

class RockStorage : public Task {
public:
	static std::string getTag( ) { return "ROCKSTORAGE"; };
	RockStoragePtr getTask( );
public:
	RockStorage( );
	virtual ~RockStorage( );
public:
	void update( );
	void add( RockItemPtr item );
private:
	std::list< RockItemPtr > _items;
};

