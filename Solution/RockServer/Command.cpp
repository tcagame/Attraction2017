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

const unsigned char BACKSPACE = 0x08;
const unsigned char ENTER = 0x0d;
const int COMMAND_WIDTH = 400;
const int COMMAND_HEIGHT = 30;
const int COMMAND_X = SCREEN_WIDTH - COMMAND_WIDTH - 10;
const int COMMAND_Y = SCREEN_HEIGHT - COMMAND_HEIGHT - 10;
const std::string COMMAND_FIRST_WORD[ Command::MAX_COMMAND ] = {
	"ip",//IP
	"device",//DEVICE
	"continue",//CONTINUE
	"toku",//TOKU
	"power",//POWER
	"money",//MONEY
	"item",//ITEM
};

Command::Command( StatusSenderPtr status_sender ) :
_status_sender( status_sender ) {
	_log = LogPtr( new Log );
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
		excute( );//���s
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

void Command::draw( ) const {
	drawFrame( );
	drawString( );
	_log->draw( );
}

void Command::excute( ) {
	//�o�^����Ă���R�}���h�ƈ�v���Ă��邩�m���߂Ď��s
	std::vector< std::string > command = getSpritCommand( );
	if ( command.size( ) == 0 ) {
		return;
	}
	std::string message = "#ERROR# " + _command;
	for ( int i = 0; i < MAX_COMMAND; i++ ) {
		if ( command[ 0 ] == COMMAND_FIRST_WORD[ i ] ) {
			switch ( i ) {//�ŏ��ɏ����Ă���P��
			case COMMAND_IP:
				//������ip����
				Server::getTask( )->saveIP( );
				message = "[SUCCESS] IP.ini�𐶐����܂���";
				break;
			case COMMAND_DEVICE:
				Device::getTask( )->resetup( );
				message = "[SUCCESS] device���Đڑ����܂���!";
				break;
			case COMMAND_CONTINUE:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int continue_num = std::atoi( command[ 2 ].c_str( ) );
					if ( _status_sender->setContinueNum( player_num, continue_num ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_TOKU:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int toku_num = std::atoi( command[ 2 ].c_str( ) );
					if ( _status_sender->setTokuNum( player_num, toku_num ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_POWER:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int power = std::atoi( command[ 2 ].c_str( ) );
					if ( _status_sender->setPower( player_num, power ) ) {
						message = "[SUCCESS] " + _command;
					}
				}
				break;
			case COMMAND_MONEY:
				if ( command.size( ) == 3 ) {
					int player_num = std::atoi( command[ 1 ].c_str( ) );
					int money = std::atoi( command[ 2 ].c_str( ) );
					if ( _status_sender->setMoney( player_num, money ) ) {
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
							item += command[ 2 ][ 7 - i ] == '0' ? 0 : (int)pow( 2, i );
						}
						if ( _status_sender->setItem( player_num, item ) ) {
							message = "[SUCCESS] " + _command;
						}
					}
				}
				break;
			}
			break;//for���𔲂���
		}
	}
	_log->addMessage( message );
	_command.clear( );
}

void Command::drawFrame( ) const{
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawLine( COMMAND_X, COMMAND_Y, COMMAND_X + COMMAND_WIDTH, COMMAND_Y );
	drawer->drawLine( COMMAND_X, COMMAND_Y + COMMAND_HEIGHT , COMMAND_X + COMMAND_WIDTH, COMMAND_Y + COMMAND_HEIGHT );
	drawer->drawLine( COMMAND_X, COMMAND_Y, COMMAND_X, COMMAND_Y + COMMAND_HEIGHT );
	drawer->drawLine( COMMAND_X + COMMAND_WIDTH, COMMAND_Y, COMMAND_X + COMMAND_WIDTH, COMMAND_Y + COMMAND_HEIGHT );
}

void Command::drawString( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	std::string str = "command : " + _command;
	drawer->drawString( COMMAND_X + 10, COMMAND_Y + 6, str.c_str( ) );
}

std::vector< std::string > Command::getSpritCommand( ) const {
	std::vector< std::string > result = { };
	std::string str = _command;
	std::transform( str.begin( ), str.end( ), str.begin( ), tolower );//�������ɕϊ�
	std::stringstream ss( str );
	std::string buffer;
	while ( std::getline( ss, buffer, ' ' ) ) {
		result.push_back( buffer );
	}
	return result;
}