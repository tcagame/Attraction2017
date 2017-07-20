#include "Command.h"
#include "Keyboard.h"
#include "define.h"
#include "Drawer.h"
#include "Log.h"
#include <sstream>
#include "Server.h"

const unsigned char BACKSPACE = 0x08;
const unsigned char ENTER = 0x0d;
const int COMMAND_WIDTH = 400;
const int COMMAND_HEIGHT = 30;
const int COMMAND_X = SCREEN_WIDTH - COMMAND_WIDTH - 10;
const int COMMAND_Y = SCREEN_HEIGHT - COMMAND_HEIGHT - 10;
const std::string COMMAND_FIRST_WORD[ Command::MAX_COMMAND ] = {
	"test",//TEST
	"ip"//IP
};

Command::Command( ) {
	_log = LogPtr( new Log );
}


Command::~Command( ) {
}

void Command::update( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
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
			case COMMAND_TEST:
				message = "[SUCCESS] test";
				break;
			case COMMAND_IP:
				//������ip����
				Server::getTask( )->saveIP( );
				message = "[SUCCESS] IP.ini�𐶐����܂���";
				break;
			}
			break;//for���𔲂���
		}
	}
	_log->addMessage( message );
	_command.clear( );
}

void Command::drawFrame( ) const{
	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawLine( COMMAND_X, COMMAND_Y, COMMAND_X + COMMAND_WIDTH, COMMAND_Y );
	drawer->drawLine( COMMAND_X, COMMAND_Y + COMMAND_HEIGHT , COMMAND_X + COMMAND_WIDTH, COMMAND_Y + COMMAND_HEIGHT );
	drawer->drawLine( COMMAND_X, COMMAND_Y, COMMAND_X, COMMAND_Y + COMMAND_HEIGHT );
	drawer->drawLine( COMMAND_X + COMMAND_WIDTH, COMMAND_Y, COMMAND_X + COMMAND_WIDTH, COMMAND_Y + COMMAND_HEIGHT );
}

void Command::drawString( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	std::string str = "command : " + _command;
	drawer->drawString( COMMAND_X + 10, COMMAND_Y + 6, str.c_str( ) );
}

std::vector< std::string > Command::getSpritCommand( ) const {
	std::vector< std::string > result = { };
	std::stringstream ss( _command );
	std::string buffer;
	while ( std::getline( ss, buffer, ' ' ) ) {
		result.push_back( buffer );
	}
	return result;
}