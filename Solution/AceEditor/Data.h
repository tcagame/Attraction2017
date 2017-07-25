#pragma once
#include <vector>

#include "ace_define.h"

class Data {
public:
	Data( );
	virtual ~Data( );
public:
	int getPageNum( ) const;
	int getGround( int mx, int my ) const;
	int getStructure( int mx, int my ) const;
	int getHeight( int mx, int my ) const;
	unsigned char getObject( int ox, int oy ) const;
	void setGroundData( int mx, int my, int num );
	void setStructure( int mx, int my, int num );
	void setHeight( int mx, int my, int height );
	void setObject( int ox, int oy, unsigned char object );
	void insert( int page );	//‘}“ü
	void erase( int page );		//íœ
	void save( std::string directory, std::string filename ) const;
	void load( std::string directory, std::string filename );
	void savePage( std::string directory, std::string filename, int page ) const;
	void loadPage( std::string directory, std::string filename, int page );
	void copy( std::vector< int >& mx, std::vector< int >& my );
	void paste( std::vector< int >& mx, std::vector< int >& my );
private:
	struct Chip {
		unsigned char ground;
		unsigned char structure;
		unsigned char height;
	};
private:
	const Chip& getChip( int mx, int my ) const;
	Chip& getChip( int mx, int my );
private:
	std::vector< Chip > _copy;
	std::vector< Chip > _chips;
	std::vector< unsigned char > _objects;
	int _page_num;
};

