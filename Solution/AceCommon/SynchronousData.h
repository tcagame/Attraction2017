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
	static const unsigned char STATE_MAIN       = 0x01;
	static const unsigned char STATE_EVENT      = 0x02;
	static const unsigned char ATTRIBUTE_REVERSE = 0x01;
	static const unsigned char TYPE_TAROSUKE = 10;
	static const unsigned char TYPE_TAROJIRO = 11;
	static const unsigned char TYPE_GARISUKE = 12;
	static const unsigned char TYPE_TAROMI   = 13;
public:
	static std::string getTag( ) { return "SYNCHRONOUSDATA"; };
	static SynchronousDataPtr getTask( );
	void update( );
public:
	SynchronousData( );
	virtual ~SynchronousData( );
public:
	int getStatusPower( int idx ) const;
	int getStatusMoney( int idx ) const;
	bool isInProssessionOfStatusItem( int idx, unsigned char item ) const;
	int getStatusVirtue( int idx ) const;
	int getStatusRedo( int idx ) const;
	unsigned char getStatusState( int idx ) const;
	int getObjectNum( AREA area ) const;
	int getObjectAX( int idx ) const;
	int getObjectAY( int idx ) const;
	unsigned char getObjectType( int idx ) const;
	unsigned char getObjectAttribute( int idx ) const;
	int getObjectPattern( int idx ) const;
	int getIdx( AREA area, int relative_idx ) const;
public:
	void * getPtr( );
	int getSize( );
	void setStatusPower( int idx, int power );
	void setStatusMoney( int idx, int money );
	void setInProssessionOfStatusItem( int idx, unsigned char item, bool possession );
	void setStatusVirtue( int idx, int virtue );
	void setStatusRedo( int idx, int redo );
	void setStatusState( int idx, unsigned char state );
	void resetObject( );
	void addObject( AREA area, unsigned char type, int pattern, unsigned char attribute, int ax, int ay );
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
				long          ax;
				long          ay;
			} object[ OBJECT_NUM ];
		};
	#pragma pack( )
private:
	SyncData _data;
	int _object_idx[ MAX_AREA ];
};

