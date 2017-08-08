#include "Command.h"
#include "Keyboard.h"
#include "define.h"
#include "Drawer.h"
#include "Device.h"
#include "Log.h"
#include "StatusSender.h"
#include <sstream>
#include "Server.h"
#include <iostream>
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
	"state",//STATE
};
const int STATE_NUM = 8;
const std::string STATE[ STATE_NUM ] = {
	"none",	
	"entry",
	"street1",
	"street2",
	"street3",
	"boss",
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
		if ( command[ 0 ] == COMMAND_FIRST_WORD[ i ] ) {
			switch ( i ) {//最初に書いてある単語
			case COMMAND_IP:
				//ここでip生成
				Server::getTask( )->saveIP( );
				message = "[SUCCESS] IP.iniを生成しました";
				break;
			case COMMAND_DEVICE:
				Device::getTask( )->resetup( );
				message = "[SUCCESS] deviceを再接続しました!";
				break;
			case COMMAND_CONTINUE:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int continue_num = std::atoi( command[ 2 ].c_str( ) );
					if ( status_sender->setContinueNum( player_num, continue_num ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_TOKU:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int toku_num = std::atoi( command[ 2 ].c_str( ) );
					if ( status_sender->setTokuNum( player_num, toku_num ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_POWER:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int power = std::atoi( command[ 2 ].c_str( ) );
					if ( status_sender->setPower( player_num, power ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_MONEY:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int money = std::atoi( command[ 2 ].c_str( ) );
					if ( status_sender->setMoney( player_num, money ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_ITEM:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					if ( command[ 2 ].size( ) == 8 ) {
						int item = 0;
						for ( int i = 0; i < 8; i++ ) {
							item |= command[ 2 ][ 7 - i ] == '0' ? 0 : 1 << i;
						}
						if ( status_sender->setItem( player_num, item ) ) {
							message = "[SUCCESS] " + _command;
						}
					}
				}
				break;
			case COMMAND_STATE:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					unsigned int state = getState( command[ 2 ] );
					if ( !( state < 0 ) ) {
						if ( status_sender->setState( player_num, state ) ) {
							message = "[SUCCESS] " + _command;
						}
					}
				}
				break;
			}
			break;//for文を抜ける
		}
	}

	Log::getTask( )->addMessage( message );
	_command.clear( );
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

unsigned int Command::getState( std::string str ) {
	unsigned int result = -1;
	for ( int i = 0; i < STATE_NUM; i++ ) {
		if ( str == STATE[ i ] ) {
			result = 0;
			result |= 1 << ( i - 1 );
			break;
		}
	}
	return result;
}

std::string Command::getCommand( ) const {
	return _command;
}
