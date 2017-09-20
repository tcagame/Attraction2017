#include "MessageReceiver.h"
#include "Status.h"
#include "Message.h"
#include "Server.h"
#include <sstream>
#include "Application.h"

const std::string COMMAND_FIRST_WORD[ Message::MAX_COMMAND ] = {
	"toku",//TOKU
	"power",//POWER
	"money",//MONEY
	"item",//ITEM
	"area",//AREA
	"continue",//CONTINUE
};

const int STATE_NUM = 8;
const std::string AREA[ STATE_NUM ] = {
	"none",	
	"entry",
	"street1",
	"street2",
	"street3",
	"boss",
	"result",
	"test"
};


MessageReceiverPtr MessageReceiver::getTask( ) {
	return std::dynamic_pointer_cast< MessageReceiver >( Application::getInstance( )->getTask( getTag( ) ) );
}


MessageReceiver::MessageReceiver( StatusPtr status, MessagePtr message ) :
_status( status ),
_message( message ) {
}


MessageReceiver::~MessageReceiver( ) {
}

void MessageReceiver::update( ) {
	if ( Server::getTask( )->isRecieving( ) ) {
		std::vector< std::string > command = getSprit( ( char* )_message->getPtr( ) );
		excute( command );
	}
}

std::vector< std::string > MessageReceiver::getSprit( std::string command ) const {
	std::vector< std::string > result = { };
	std::transform( command.begin( ), command.end( ), command.begin( ), tolower );//小文字に変換
	std::stringstream ss( command );
	std::string buffer;
	while ( std::getline( ss, buffer, ' ' ) ) {
		result.push_back( buffer );
	}
	return result;
}

void MessageReceiver::excute( std::vector< std::string > command ) {
	for ( int i = 0; i < Message::MAX_COMMAND; i++ ) {
		//先頭の単語がコマンドと一致しているかどうか
		if ( command[ 0 ] == COMMAND_FIRST_WORD[ i ] ) {
			switch ( i ) {
			case Message::COMMAND_TOKU:
				excuteToku( command );
				break;
			case Message::COMMAND_POWER:
				excutePower( command );
				break;
			case Message::COMMAND_MONEY:
				excuteMoney( command );
				break;
			case Message::COMMAND_ITEM:
				excuteItem( command );
				break;
			case Message::COMMAND_AREA:
				excuteState( command );
				break;
			case Message::COMMAND_CONTINUE:
				excuteContinue( command );
				break;
			}
			break;//for文を抜ける
		}
	}
}

void MessageReceiver::excuteToku( std::vector< std::string > command ) {
	if ( command.size( ) == 3 ) {
		int player_num = std::atoi( command[ 1 ].c_str( ) );
		int add = std::atoi( command[ 2 ].c_str( ) );
		if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
			_status->getPlayer( player_num ).toku += add;
		}
	}
}

void MessageReceiver::excutePower( std::vector< std::string > command ) {
	if ( command.size( ) == 3 ) {
		int player_num = std::atoi( command[ 1 ].c_str( ) );
		int add = std::atoi( command[ 2 ].c_str( ) );
		if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
			_status->getPlayer( player_num ).power += add;
			if ( _status->getPlayer( player_num ).power < 0 ) {
				_status->getPlayer( player_num ).power = 0;
			}
			if ( _status->getPlayer( player_num ).power > MAX_POWER ) {
				_status->getPlayer( player_num ).power = MAX_POWER;
			}
		}
	}
}

void MessageReceiver::excuteMoney( std::vector< std::string > command ) {
	if ( command.size( ) == 3 ) {
		int player_num = std::atoi( command[ 1 ].c_str( ) );
		int add = std::atoi( command[ 2 ].c_str( ) );
		if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
			if ( ( int )_status->getPlayer( player_num ).money + add < 0 ) {
				_status->getPlayer( player_num ).money = 0;
			} else {
				_status->getPlayer( player_num ).money += add;
			}
		}
	}
}

void MessageReceiver::excuteItem( std::vector< std::string > command ) {
	if ( command.size( ) == 3 ) {
		int player_num = std::atoi( command[ 1 ].c_str( ) );
		if ( command[ 2 ].size( ) == 8 ) {
			unsigned char item = 0b00000000;
			for ( int i = 0; i < 8; i++ ) {
				item |= command[ 2 ][ 7 - i ] == '0' ? 0 : 1 << i;
			}
			if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
				_status->getPlayer( player_num ).item |= item;
			}
		}
	}
}

void MessageReceiver::excuteState( std::vector< std::string > command ) {
	if ( command.size( ) == 3 ) {
		int player_num = std::atoi( command[ 1 ].c_str( ) );
		unsigned char area = 0b00000000;
		int check = std::atoi( command[ 2 ].c_str( ) );
		for ( int i = 0; i < 8; i++ ) {
			if ( check % 2 == 1 ) {
				area |= ( 1 << i );
			}
			check /= 10;
		}
		// resultに他プレイヤーがいたら入らない
		if ( area == AREA_RESULT ) {
			for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
				if ( i == player_num ) {
					continue;
				}
				if ( _status->getPlayer( i ).area == AREA_RESULT ) {
					return;
				}
			}
		}

		if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
			if ( area == AREA_WAIT ) {
				_status->resetPlayer( player_num );
			}
			_status->getPlayer( player_num ).area = area;
		}
	}
}

void MessageReceiver::excuteContinue( std::vector< std::string > command ) {
	if ( command.size( ) == 2 ) {
		int player_num = std::atoi( command[ 1 ].c_str( ) );
		if ( player_num >= 0 && player_num <= ROCK_PLAYER_NUM ) {
			if ( _status->getPlayer( player_num ).power <= 0 ) {
				_status->getPlayer( player_num ).power = MAX_POWER;
				_status->getPlayer( player_num ).continue_num++;
			}
		}
	}
}
