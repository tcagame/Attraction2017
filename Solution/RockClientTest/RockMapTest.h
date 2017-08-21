#pragma once
#include "RockMap.h"
#include "mathmatics.h"

class RockMapTest :	public RockMap {
public:
	RockMapTest( );
	virtual ~RockMapTest( );
public:
	void update( );
protected:
	std::vector< std::string > getFilenames( ) const;
	std::string getFilenameCol( ) const;
private:
	bool isNext( const Vector& pos ) const;
private:
	std::vector< std::string > _filenames;
	std::string _filename_col;
};

