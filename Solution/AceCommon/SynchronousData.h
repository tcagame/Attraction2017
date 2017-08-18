#pragma once

#include "ace_define.h"
#include "Data.h"
#include "Task.h"
#include <string>

PTR( SynchronousData );

class SynchronousData : public Data, public Task {
public:
	static const unsigned char ITEM_DANGO       = 0x01;
	static const unsigned char ITEM_HEART       = 0x02;
	static const unsigned char ITEM_HYPERTROPHY = 0x04;
	static const unsigned char ITEM_SHORTENING  = 0x08;
	static const unsigned char ITEM_WOOD        = 0x10;
	static const unsigned char ITEM_FLAME       = 0x20;
	static const unsigned char ITEM_MINERAL     = 0x40;
public:
	static std::string getTag( ) { return "SYNCHRONOUSDATA"; };
	static SynchronousDataPtr getTask( );
	void update( );
public:
	SynchronousData( );
	virtual ~SynchronousData( );
public:
	void * getPtr( );
	int getSize( );
	int getStatusPower( int idx );
	int getStatusMoney( int idx );
	bool isInProssessionOfStatusItem( int idx, unsigned char item );
	int getStatusVirtue( int idx );
	int getStatusRedo( int idx );
	unsigned char getStatusState( int idx );
	void setStatusPower( int idx, int power );
	void setStatusMoney( int idx, int money );
	void setInProssessionOfStatusItem( int idx, unsigned char item, bool possession );
	void setStatusVirtue( int idx, int virtue );
	void setStatusRedo( int idx, int redo );
	void setStatusState( int idx, unsigned char state );
	void resetObject( );
	int getObjectNum( );
	int getObjectX( int idx );
	int getObjectY( int idx );
	unsigned char getObjectType( int idx );
	int getObjectPattern( int idx );
	void addObject( unsigned char type, int pattern, unsigned char attribute, int x, int y );
private:
	static const int OBJECT_NUM = 140;

	#pragma pack( 1 )
		struct SyncData {
			struct Status {
				unsigned char power;
				unsigned char money;
				unsigned char items;
				unsigned char virtue;
				unsigned char redo;
				unsigned char state;
			} status[ ACE_PLAYER_NUM ];
			struct Object {
				unsigned char type;
				unsigned char pattern;
				unsigned char attribute;
				unsigned long x;
				unsigned long y;
			} object[ OBJECT_NUM ];
		};
	#pragma pack( )	
private:
	SyncData _data;
	int _object_num;
};

