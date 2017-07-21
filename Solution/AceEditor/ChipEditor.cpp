#include "ChipEditor.h"
#include "Data.h"
#include "Keyboard.h"
#include "ChipCursor.h"
#include "Mouse.h"
#include "Application.h"
#include "Drawer.h"
#include "ace_define.h"

const std::string DIRECTORY = "../Resource/Ace/MapData/";

ChipEditor::ChipEditor( DataPtr data, ChipCursorConstPtr chip_cursor ) :
_data( data ),
_chip_cursor( chip_cursor ),
_mode( MODE_GROUND ),
_number( 0 ),
_range( 1 ) {
}


ChipEditor::~ChipEditor( ) {
}

void ChipEditor::update( ) {
	updateMode( );
	changeRange( );
	// セーブ
	edit( );
}

void ChipEditor::edit( ) {
	editWidth( );
	editChip( );
}

void ChipEditor::setMode( MODE mode, int number ) {
	_mode = mode;
	_number = number;
	_click_active = false;
}

void ChipEditor::getMode( MODE& mode, int& number ) const {
	mode = _mode;
	number = _number;
}

int ChipEditor::getRange( ) const {
	return _range;
}

void ChipEditor::updateMode( ) {
	// sutructuer&ground chip の編集
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "C" ) ) {
		if ( _mode != MODE_COPY ) {
			_before_mode = _mode;
		}
		_mode = MODE_COPY;
		std::vector< int > mx;
		std::vector< int > my;
		getReplacePos( mx, my, true );
		_data->copy( mx, my );
	}

}

void ChipEditor::getReplacePos( std::vector< int >& x, std::vector< int >& y, bool mx_my ) const {
	x = { };
	y = { };
	int cx = _chip_cursor->getGX( );
	if ( mx_my ) {
		cx += _chip_cursor->getScrollX( );
	}
	int cy = _chip_cursor->getGY( );
	int replace = _range * _range;
	x.resize( replace );
	y.resize( replace );
	if ( cy < 0 ) {
		for ( int i = 0; i < replace; i++ ) {
			x[ i ] = -1;
			y[ i ] = -1;
		}
	}
	int base_x = cx;
	int base_y = cy;
	for ( int i = 0; i < _range; i++ ) {
		int check_x = base_x;
		int check_y = base_y;
		for ( int j = 0; j < _range; j++ ) {
			x[ i * _range + j ] = check_x;
			y[ i * _range + j ] = check_y;
			if ( check_y % 2 == 1 ) {
				check_x++;
			}
			check_y--;
		}
		if ( base_y % 2 == 0 ) {
			base_x--;
		}
		base_y--;
	}
}

void ChipEditor::editWidth( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	int mx = _chip_cursor->getScrollX( ) + _chip_cursor->getGX( );
	if ( keyboard->isPushKey( "+" ) ) {
		_data->insert( ( mx * CHIP_WIDTH / GRAPH_SIZE ) % _data->getPageNum( ) );
	}
	if ( keyboard->isPushKey( "-" ) ) {
		_data->erase( ( mx * CHIP_WIDTH / GRAPH_SIZE ) % _data->getPageNum( ) );
	}
}

void ChipEditor::editChip( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isHoldLeftButton( ) && _click_active ) {
		std::vector< int > mx;
		std::vector< int > my;
		getReplacePos( mx, my, true );
		int replace = _range * _range;
		for ( int i = 0; i < replace; i++ ) {
			if ( mx[ i ] >= 0 && my[ i ] >= 0 ) {
				switch ( _mode ) {
				case MODE_HEIGHT:
					_data->setHeightData( mx[ i ], my[ i ], _number );
					break;
				case MODE_STRUCTURE:
					_data->setStructureData( mx[ i ], my[ i ], _number );
					break;
				case MODE_GROUND:
					_data->setGroundData( mx[ i ], my[ i ], _number );
					break;
				}
			}
		}
		if ( _mode == MODE_COPY ) {
			_data->paste( mx, my );
			_click_active = false;
		}
	}
	
	if ( !mouse->isHoldLeftButton( ) ) {
		_click_active = true;
	}
}

void ChipEditor::changeRange( ) {
	const char * KEY[ 9 ] = {
		"NUM1",
		"NUM2",
		"NUM3",
		"NUM4",
		"NUM5",
		"NUM6",
		"NUM7",
		"NUM8",
		"NUM9",
	};
	KeyboardPtr keyboard = Keyboard::getTask( );
	for ( int i = 0; i < 9; i++ ) {
		if ( keyboard->isPushKey( KEY[ i ] ) ) {
			_range = i + 1;
			if ( _mode == MODE_COPY ) {
				_mode = _before_mode;
			}
		}
	}
}


void ChipEditor::save( ) const {
	std::string filename = Application::getInstance( )->inputString( 0, 20 );
	if ( filename.size( ) == 0 ) {
		return;
	}
	_data->save( DIRECTORY + filename );
}
void ChipEditor::load( ) {
	std::string filename = Application::getInstance( )->inputString( 0, 20 );
	if ( filename.size( ) == 0 ) {
		return;
	}
	_data->load( DIRECTORY + filename );
}
void ChipEditor::savePage( ) const {
	std::string filename = Application::getInstance( )->inputString( 0, 20 );
	if ( filename.size( ) == 0 ) {
		return;
	}
	int page = ( _chip_cursor->getScrollX( ) + _chip_cursor->getGX( ) ) / PAGE_CHIP_WIDTH_NUM;
	page %= _data->getPageNum( );
	_data->savePage( DIRECTORY + filename, page );
}
void ChipEditor::loadPage( ) {
	std::string filename = Application::getInstance( )->inputString( 0, 20 );
	if ( filename.size( ) == 0 ) {
		return;
	}
	int page = ( _chip_cursor->getScrollX( ) + _chip_cursor->getGX( ) ) / PAGE_CHIP_WIDTH_NUM;
	page %= _data->getPageNum( );
	_data->loadPage( DIRECTORY + filename, page );
}