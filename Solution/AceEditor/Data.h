#pragma once
#include <vector>

class Data {
public:
	Data( );
	virtual ~Data( );
public:
	int getPageNum( ) const;
	int getGroundData( int mx, int my ) const;
	int getStructureData( int mx, int my ) const;
	int getHeightData( int mx, int my ) const;
	int getBlockData( int ox, int oy ) const;
	void setGroundData( int mx, int my, int num );
	void setStructureData( int mx, int my, int num );
	void setHeightData( int mx, int my, int height );
	void setBlockData( int ox, int oy, int num );
	void insert( int page );	//‘}“ü
	void erase( int page );		//íœ
	void save( std::string filename ) const;
	void load( std::string filename );
	void savePage( std::string filename, int page ) const;
	void loadPage( std::string filename, int page );
	void copy( std::vector< int >& mx, std::vector< int >& my );
	void paste( std::vector< int >& mx, std::vector< int >& my );
private:
	struct Chip {
		unsigned char ground;
		unsigned char structure;
		unsigned char height;
	};
	struct Object {
		unsigned char block;
	};
private:
	const Chip& getChip( int mx, int my ) const;
	Chip& getChip( int mx, int my );
	const Object& getObject( int ox, int oy ) const;
	Object& getObject( int ox, int oy );
private:
	std::vector< Chip > _copy;
	std::vector< Chip > _chips;
	std::vector< Object > _objects;
	int _page_num;
};

