#pragma once

#include "define.h"
#include <array>
#include "Task.h"
#include "Status.h"

PTR( StatusSender );
PTR( Status );

class StatusSender : public Task {
public:
	static std::string getTag( ) { return "STATUSSENDER"; };
	static StatusSenderPtr getTask( );
public:
	StatusSender( StatusPtr status );
	virtual ~StatusSender( );
public:
	void update( );
	bool setContinueNum( int idx, int num );
	bool setTokuNum( int idx, int num );
	bool setPower( int idx, int power );
	bool setMoney( int idx, int money );
	bool setItem( int idx, int item );
	bool setArea( int idx, unsigned int area );
private:
	StatusPtr _status;
	std::array< int, Status::PLAYER_NUM > _reset_count;//ボタンのカウント
};