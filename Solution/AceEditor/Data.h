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
	void setGroundData( int mx, int my, int num );
	void setStructureData( int mx, int my, int num );
	void setHeightData( int mx, int my, int height );
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
private:
	const Chip& getChip( int mx, int my ) const;
	Chip& getChip( int mx, int my );
private:
	std::vector< Chip > _copy;
	std::vector< Chip > _chips;
	int _page_num;
};

