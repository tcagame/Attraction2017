#pragma once

#include "Task.h"
#include <string>

PTR( StatusDrawer );
PTR( Status );

class StatusDrawer : public Task {
public:
	static std::string getTag( ) { return "STATUSDRAWER"; };
	static StatusDrawerPtr getTask( );
public:
	StatusDrawer( StatusPtr status );
	virtual ~StatusDrawer( );
public:
	void update( );
private:
	std::string BToS( unsigned char b ) const;
	void drawDeviceDir( ) const;
	void drawDeviceButton( ) const;
	void drawState( ) const;
	void drawContinue( ) const;
	void drawToku( ) const;
	void drawItem( ) const;
	void drawMoney( ) const;
	void drawPower( ) const;
private:
	StatusPtr _status;
};

