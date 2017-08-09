#pragma once
#include "RockMap.h"


class RockMapStreet : public RockMap {
public:
	RockMapStreet( );
	virtual ~RockMapStreet( );
public:
	void update( );
protected:
	std::vector< std::string > getFilenames( ) const;
private:
	std::vector< std::string > _filenames;
};