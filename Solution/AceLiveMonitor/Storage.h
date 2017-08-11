#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Storage );
PTR( Item );

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
private:
	std::list< ItemPtr > _items;
};

