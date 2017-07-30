#pragma once
#include <array>
#include "Server.h"
#include <string>
#include "Task.h"

PTR( TableDrawer );
PTR( Status );

class TableDrawer : public Task {
public:
	static std::string getTag( ) { return "TABLEDRAWER"; };
	static TableDrawerPtr getTask( );
public:
	enum TAG {
		TAG_PLAYER,
		TAG_DEVICE_DIR,
		TAG_DEVICE_BUTTON,
		TAG_STATE,
		TAG_CONTINUE,
		TAG_TOKU,
		TAG_ITEM,
		TAG_MONEY,
		TAG_POWER,
		MAX_TAG,
	};
public:
	TableDrawer( StatusPtr status );
	virtual ~TableDrawer( );
public:
	void update( );
private:
	void drawFlame( ) const;
	void drawDeviceNum( ) const;
	void drawPlayer( ) const;
	void drawDeviceDir( ) const;
	void drawDeviceButton( ) const;
	void drawState( ) const;
	void drawContinue( ) const;
	void drawToku( ) const;
	void drawItem( ) const;
	void drawMoney( ) const;
	void drawPower( ) const;
	void drawCommand( ) const;
	void drawLog( ) const;
	void drawConnect( ) const;
	std::string BToS( unsigned char b ) const;
private:
	StatusPtr _status;
};

