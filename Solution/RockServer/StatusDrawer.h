#pragma once
#include <array>
#include "Server.h"
#include <string>

PTR( StatusSender );

class StatusDrawer {
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
	StatusDrawer( StatusSenderConstPtr status_sender );
	virtual ~StatusDrawer( );
public:
	void draw( ) const;
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
	std::string BToS( unsigned char b ) const;
private:
	StatusSenderConstPtr _status_sender; 
};

