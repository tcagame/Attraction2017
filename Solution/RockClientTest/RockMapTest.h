#pragma once
#include "RockMap.h"
class RockMapTest :	public RockMap {
public:
	RockMapTest( );
	virtual ~RockMapTest( );
public:
	void update( );
protected:
	std::vector< std::string > getFilenames( ) const;
private:
	bool isNext( Vector pos ) const;
private:
	std::vector< std::string > _filenames;
};

