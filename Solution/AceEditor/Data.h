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
	std::string getBg( int page ) const;
	void setGroundData( int mx, int my, int num );
	void setStructure( int mx, int my, int num );
	void setHeight( int mx, int my, int height );
	void setObject( int ox, int oy, unsigned char object );
	void insert( int page );	//挿入
	void erase( int page );		//削除
	void save( std::string directory, std::string filename ) const;
	void load( std::string directory, std::string filename );
	void savePage( std::string directory, std::string filename, int page ) const;
	void loadPage( std::string directory, std::string filename, int page );
	void loadBg( std::string directory, std::string filename, int page );
	void copy( std::vector< int >& mx, std::vector< int >& my );
	void paste( std::vector< int >& mx, std::vector< int >& my );
	void setFrontHeight( int mx, int front_height );
	bool isFront( int mx, int my ) const;
private:
	struct Chip {
		unsigned char ground;
		unsigned char structure;
		unsigned char height; // 上ビットにこっそりfrontフラグとして使う
	};
private:
	const Chip& getChip( int mx, int my ) const;
	Chip& getChip( int mx, int my );
private:
	std::vector< Chip > _copy;
	std::vector< Chip > _chips;
	std::vector< unsigned char > _objects;
	std::vector< std::string > _bg;
	int _page_num;
};

