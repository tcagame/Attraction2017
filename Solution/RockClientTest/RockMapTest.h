#pragma once
#include "RockMap.h"
class RockMapTest :	public RockMap {
public:
	RockMapTest( );
	virtual ~RockMapTest( );
protected:
	std::vector< std::string > getFilenames( ) const;
private:
	std::vector< std::string > _filenames;
};

