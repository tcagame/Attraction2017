#include "Command.h"
#include "Keyboard.h"
#include "define.h"
#include "Drawer.h"
#include "Device.h"
#include "Log.h"
#include "StatusSender.h"
#include <sstream>
#include "Server.h"
#include "Application.h"

const unsigned char BACKSPACE = 0x08;
const unsigned char ENTER = 0x0d;

const std::string COMMAND_FIRST_WORD[ Command::MAX_COMMAND ] = {
	"ip",//IP
	"device",//DEVICE
	"continue",//CONTINUE
	"toku",//TOKU
	"power",//POWER
	"money",//MONEY
	"item",//ITEM
	"area",//AREA
};
const int STATE_NUM = 8;
const std::string AREA[ STATE_NUM ] = {
	"none",
	"wait",
	"entry",
	"street1",
	"street2",
	"street3",
	"result",
	"test"
};


CommandPtr Command::getTask( ) {
	return std::dynamic_pointer_cast< Command >( Application::getInstance( )->getTask( getTag( ) ) );
}


Command::Command( StatusPtr status ) :
_status( status ) {
}


Command::~Command( ) {
}

void Command::update( ) {
	KeyboardPtr keyboard( Keyboard::getTask( ) );
	char key = keyboard->getInputChar( );
	if ( key == 0 ) {
		return;
	}
	if ( key == ENTER ) {
		excute( );//実行
	} else {
		if ( key == BACKSPACE ) {
			if( _command.size( ) != 0 ) {
				_command.pop_back( );
			}
		} else {
			_command += key;
		}
	}
}

void Command::excute( ) {
	//登録されているコマンドと一致しているか確かめて実行
	std::vector< std::string > command = getSpritCommand( );
	StatusSenderPtr status_sender( StatusSender::getTask( ) );
	if ( command.size( ) == 0 ) {
		return;
	}
	std::string message = "#ERROR# " + _command;
	for ( int i = 0; i < MAX_COMMAND; i++ ) {
		//先頭の単語がコマンドと一致しているかどうか
		if ( command[ 0 ] == COMMAND_FIRST_WORD[ i ] ) {
			switch ( i ) {
			case COMMAND_IP:
				if ( excuteIp( ) ) {
					message = "[SUCCESS] IP.iniを生成しました";
				}
				break;
			case COMMAND_DEVICE:
				if ( excuteDevice( ) ) {
					message = "[SUCCESS] deviceを再接続しました!";
				}
				break;
			case COMMAND_CONTINUE:
				if ( excuteContinue( command ) ) {
					message = "[SUCCESS] " + _command;
				}
				break;
			case COMMAND_TOKU:
				if ( excuteToku( command ) ) {
					message = "[SUCCESS] " + _command;
				}
				break;
			case COMMAND_POWER:
				if ( excutePower( command ) ) {
					message = "[SUCCESS] " + _command;
				}
				break;
			case COMMAND_MONEY:
				if ( excuteMoney( command ) ) {
					message = "[SUCCESS] " + _command;
				}
				break;
			case COMMAND_ITEM:
				if ( excuteItem( command ) ) {
					message = "[SUCCESS] " + _command;
				}
				break;
			case COMMAND_AREA:
				if ( excuteArea( command ) ) {
					message = "[SUCCESS] " + _command;
				}
				break;
			}
			break;//for文を抜ける
		}
	}

	Log::getTask( )->addMessage( message );
	_command.clear( );
}

bool Command::excuteIp( ) const {
	Server::getTask( )->saveIP( );
	return true;
}

bool Command::excuteDevice( ) const {
	Device::getTask( )->resetup( );
	return true;
}

bool Command::excuteContinue( std::vector< std::string > command ) {
	bool result = false;
	if ( command.size( ) == 3 ) {
		int continue_num = std::atoi( command[ 2 ].c_str( ) );
		if ( command[ 1 ] == "all" ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				_status->getPlayer( i ).continue_num = continue_num;
			}
			result = true;
		} else {
			int player_num = std::atoi( command[ 1 ].c_str( ) );
			if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM && continue_num >= 0 ) {
				_status->getPlayer( player_num ).continue_num = continue_num;
				result = true;
			}
		}
	}
	return result;
};

bool Command::excuteToku( std::vector< std::string > command ) {
	bool result = false;
	if ( command.size( ) == 3 ) {
		int toku = std::atoi( command[ 2 ].c_str( ) );
		if ( command[ 1 ] == "all" ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				_status->getPlayer( i ).toku = toku;
			}
			result = true;
		} else {
			int player_num = std::atoi( command[ 1 ].c_str( ) );
			if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM && toku >= 0 ) {
				_status->getPlayer( player_num ).toku = toku;
				result = true;
			}
		}
	}
	return result;
}

bool Command::excutePower( std::vector< std::string > command ) {
	bool result = false;
	if ( command.size( ) == 3 ) {
		int power = std::atoi( command[ 2 ].c_str( ) );
		if ( power > MAX_POWER ) {
			power = MAX_POWER;
		}
		if ( command[ 1 ] == "all" ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				_status->getPlayer( i ).power = power;
			}
			result = true;
		} else {
			int player_num = std::atoi( command[ 1 ].c_str( ) );
			if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM && power >= 0 ) {
				_status->getPlayer( player_num ).power = power;
				result = true;
			}
		}
	}
	return result;
}

bool Command::excuteMoney( std::vector< std::string > command ) {
	bool result = false;
	if ( command.size( ) == 3 ) {
		int money = std::atoi( command[ 2 ].c_str( ) );
		if ( command[ 1 ] == "all" ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				_status->getPlayer( i ).money = money;
			}
			result = true;
		} else {
			int player_num = std::atoi( command[ 1 ].c_str( ) );
			if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM && money >= 0 ) {
				_status->getPlayer( player_num ).money = money;
				result = true;
			}
		}
	}
	return result;
}

bool Command::excuteItem( std::vector< std::string > command ) {
	bool result = false;
	if ( command.size( ) == 3 ) {
		if ( command[ 2 ].size( ) == 8 ) {
			int item = 0;
			for ( int i = 0; i < 8; i++ ) {
				item |= command[ 2 ][ 7 - i ] == '0' ? 0 : 1 << i;
			}
			if ( command[ 1 ] == "all" ) {
				for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
					_status->getPlayer( i ).item = item;
				}
				result = true;
			} else {
				int player_num = std::atoi( command[ 1 ].c_str( ) );
				if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
					_status->getPlayer( player_num ).item = item;
					result = true;
				}
			}
		}
	}
	return result;
}

bool Command::excuteArea( std::vector< std::string > command ) {
	bool result = false;
	if ( command.size( ) == 3 ) {
		unsigned int area = 0;
		bool same = false;
		for ( int i = 0; i < STATE_NUM; i++ ) {
			if ( command[ 2 ] == AREA[ i ] ) {
				same = true;
				area |= 1 << ( i - 1 );
				break;
			}
		}
		if ( !same ) {
			std::string message = "#ERROR# AREA " + command[ 2 ] + "は存在しません";
			Log::getTask( )->addMessage( message );
			return false;
		}
		if ( command[ 1 ] == "all" ) {
			if ( area == AREA_RESULT ) {
				std::string message = "#ERROR# 全キャラをリザルトにはできません";
				Log::getTask( )->addMessage( message );
				return false;
			}
			if ( area == AREA_ENTRY ) {
				for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
					_status->resetPlayer( i );
				}
			}
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				_status->getPlayer( i ).area = area;
			}
			result = true;
		} else {
			int player_num = std::atoi( command[ 1 ].c_str( ) );
			// resultに他プレイヤーがいたら入らない
			if ( area == AREA_RESULT ) {
				for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
					if ( i == player_num ) {
						continue;
					}
					if ( _status->getPlayer( i ).area == AREA_RESULT ) {
						std::string message = "#ERROR# すでに他キャラがリザルトにいます";
						Log::getTask( )->addMessage( message );
						return false;
					}
				}
			}

			if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
				if ( area == AREA_ENTRY ) {
					_status->resetPlayer( player_num );
				}
				_status->getPlayer( player_num ).area = area;
				result = true;
			}
		}
		
	}
	return result;
}

std::vector< std::string > Command::getSpritCommand( ) const {
	std::vector< std::string > result = { };
	std::string str = _command;
	std::transform( str.begin( ), str.end( ), str.begin( ), tolower );//小文字に変換
	std::stringstream ss( str );
	std::string buffer;
	while ( std::getline( ss, buffer, ' ' ) ) {
		result.push_back( buffer );
	}
	return result;
}

std::string Command::getCommand( ) const {
	return _command;
}
