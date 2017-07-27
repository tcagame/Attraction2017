#pragma once
#include "status.h"
#include "define.h"
#include <array>

class StatusSender {
public:
	StatusSender( );
	virtual ~StatusSender( );
public:
	void update( );
	ROCK_DATA getData( ) const;
	bool setContinueNum( int idx, int num );
	bool setTokuNum( int idx, int num );
	bool setPower( int idx, int power );
	bool setMoney( int idx, int money );
	bool setItem( int idx, int item );
private:
	ROCK_DATA _data;
	std::array< int, ROCK_PLAYER_NUM > _reset_count;//ボタンのカウント
};