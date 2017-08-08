#pragma once
#include "RockMap.h"


class RockStreet : public RockMap {
public:
	RockStreet( );
	virtual ~RockStreet( );
protected:
	std::vector< std::string > getFilenames( ) const;
private:
	std::vector< std::string > _filenames;
};