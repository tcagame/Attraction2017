#pragma once

#include "ace_define.h"
#include "Data.h"
#include "Task.h"
#include <string>

PTR( SynchronousData );

class SynchronousData : public Data, public Task {
public:
	static const unsigned char STATE_NONE           = 0x00;
	static const unsigned char STATE_ENTRY          = 0x01;
	static const unsigned char STATE_CONTINUE       = 0x02;
	static const unsigned char STATE_PLAY_STREET    = 0x10;
	static const unsigned char STATE_PLAY_EVENT     = 0x11;
	static const unsigned char ITEM_DANGO			= 0x01;
	static const unsigned char ITEM_HEART			= 0x02;
	static const unsigned char ITEM_HYPERTROPHY		= 0x04;
	static const unsigned char ITEM_SHORTENING		= 0x08;
	static const unsigned char ITEM_WOOD			= 0x10;
	static const unsigned char ITEM_FLAME			= 0x20;
	static const unsigned char ITEM_MINERAL			= 0x40;
	static const unsigned char ATTRIBUTE_REVERSE	= 0x01;
	static const unsigned char TYPE_TAROSUKE		= 0x10;
	static const unsigned char TYPE_TAROJIRO		= 0x11;
	static const unsigned char TYPE_GARISUKE		= 0x12;
	static const unsigned char TYPE_TAROMI			= 0x13;
	static const unsigned char TYPE_MONMOTARO		= 0x20;
	static const unsigned char TYPE_SHOT			= 0x21;
	static const unsigned char TYPE_ENEMY_MIDIUM	= 0x22;
	static const unsigned char TYPE_ENEMY_SMALL		= 0x23;
	static const unsigned char TYPE_ENEMY_BIG		= 0x24;
	static const unsigned char TYPE_ENEMY_BOSS		= 0x25;
	static const unsigned char TYPE_IMPACT			= 0x26;
	static const unsigned char TYPE_ITEM			= 0x27;
	static const unsigned char TYPE_NPC 			= 0x28;
	static const unsigned char TYPE_SANZO 			= 0x29;
	static const unsigned char PROGRESS_NONE             = 0x00;
	static const unsigned char PROGRESS_BAR              = 0x01;
	static const unsigned char PROGRESS_ITEM_DANGO       = 0x02;
	static const unsigned char PROGRESS_ITEM_HEART	     = 0x03;
	static const unsigned char PROGRESS_ITEM_HYPERTROPHY = 0x04;	
	static const unsigned char PROGRESS_ITEM_SHORTENING	 = 0x05;
	static const unsigned char PROGRESS_ITEM_WOOD	     = 0x06;
	static const unsigned char PROGRESS_ITEM_FLAME	     = 0x07;
	static const unsigned char PROGRESS_ITEM_MINERAL     = 0x08;	
	static const unsigned char PROGRESS_ITEM_VIRTUE      = 0x09;
public:
	static std::string getTag( ) { return "SYNCHRONOUSDATA"; };
	static SynchronousDataPtr getTask( );
	void update( );
public:
	SynchronousData( );
	virtual ~SynchronousData( );
public:
	EVENT getEvent( ) const;
	int getCameraX( ) const;
	unsigned char getStatusProgressType( PLAYER player ) const;
	int getStatusProgressCount( PLAYER player ) const;
	int getStatusX( PLAYER player ) const;
	int getStatusPower( PLAYER player ) const;
	int getStatusMoney( PLAYER player ) const;
	bool isInProssessionOfStatusItem( PLAYER player, unsigned char item ) const;
	int getStatusVirtue( PLAYER player ) const;
	int getStatusRedo( PLAYER player ) const;
	unsigned char getStatusState( PLAYER player ) const;
	int getStatusDevice( PLAYER player ) const;
	int getObjectNum( AREA area ) const;
	int getObjectAX( int idx ) const;
	int getObjectAY( int idx ) const;
	unsigned char getObjectType( int idx ) const;
	unsigned char getObjectAttribute( int idx ) const;
	int getObjectPattern( int idx ) const;
	int getObjectSize( int idx ) const;
	int getIdx( AREA area, int relative_idx ) const;
	int getFade( ) const;
public:
	void * getPtr( );
	int getSize( );
	void setEvent( EVENT event );
	void setCameraX( int x );
	void setStatusDevice( PLAYER player, int id );
	void setStatusProgress( PLAYER player, unsigned char type, int count );
	void setStatusX( PLAYER player, int x );
	void setStatusPower( PLAYER player, int power );
	void setStatusMoney( PLAYER player, int money );
	void setInProssessionOfStatusItem( PLAYER player, unsigned char item, bool possession );
	void setStatusVirtue( PLAYER player, int virtue );
	void setStatusRedo( PLAYER player, int redo );
	void setStatusState( PLAYER player, unsigned char area );
	void setFade( int fade );
	void resetObject( );
	void addObject( AREA area, unsigned char type, int pattern, unsigned char attribute, int ax, int ay, int size = -1 );
private:
	static const int OBJECT_NUM = 140;

	#pragma pack( 1 )
		struct SyncData {
			long camera_x;
			unsigned char event;
			unsigned char fade; // 0 - 99
			struct Status {
				char          device;
				unsigned char progress_type;
				char          progress_count; // 0 - 99
				long          x;
				unsigned char power;
				unsigned long money;
				unsigned char items;
				unsigned char virtue;
				unsigned char redo;
				unsigned char state;
			} status[ MAX_PLAYER ];
			struct Object {
				unsigned char type;
				unsigned int pattern;
				unsigned char attribute;
				long          ax;
				long          ay;
				int size;
			} object[ OBJECT_NUM ];
			int idx[ MAX_AREA ];
		};
	#pragma pack( )
private:
	SyncData _data;
};

