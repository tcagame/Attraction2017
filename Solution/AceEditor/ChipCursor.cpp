#include "ChipCursor.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ace_define.h"
#include "Data.h"

ChipCursor::ChipCursor( DataConstPtr data ) :
_data( data ),
_scroll_x( 0 ),
_gx( -1 ),
_gy( -1 ) {
}


ChipCursor::~ChipCursor( ) {
}

void ChipCursor::update( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	int add = 0;
	if ( keyboard->isPushKey( "ARROW_RIGHT" ) ) {
		add = 1;
	}
	if ( keyboard->isPushKey( "ARROW_LEFT" ) ) {
		add = _data->getPageNum( ) * PAGE_CHIP_WIDTH_NUM - 1;
	}
	_scroll_x = ( _scroll_x + add ) % ( _data->getPageNum( ) * PAGE_CHIP_WIDTH_NUM );

	// gx gy ‚ðŒŸo@‚à‚µchipMode‚Ìchipã‚É‚È‚¢ê‡‚Í -1‚ð‘ã“ü
	_gx = -1;
	_gy = -1;
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPos( );

	int dx = -1;
	int dy = -1;

	// preview
	{
		int x = ( int )pos.x - GUIDE_X;
		if ( x >= 0 && x < DISP_CHIP_WIDTH * CHIP_WIDTH + CHIP_WIDTH / 2 ) {
			dx = x;
		}
		int y = ( int )pos.y - ( PREVIEW_Y - CHIP_HEIGHT / 2 );
		if ( y >= 0 && y < ( DISP_CHIP_HEIGHT * CHIP_HEIGHT + CHIP_HEIGHT ) / 2 ) {
			dy = y;
		}

	}

	// guide
	{
		int x = ( int )pos.x - GUIDE_X;
		if ( x >= 0 && x < DISP_CHIP_WIDTH * CHIP_WIDTH + CHIP_WIDTH / 2 ) {
			dx = x;
		}
		int y = ( int )pos.y - GUIDE_Y;
		if ( y >= 0 && y < ( DISP_CHIP_HEIGHT * CHIP_HEIGHT + CHIP_HEIGHT ) / 2 ) {
			dy = y;
		}
	}

	// ŒvŽZ
	_gx = -1;
	_gy = -1;
	bool up = true;
	if ( dx >= 0 && dy >= 0 ) {
		int x = dx / ( CHIP_WIDTH / 2 );
		int y = dy / ( CHIP_HEIGHT / 2 );
		int ax = dx % ( CHIP_WIDTH / 2 ) / 4;
		int ay = dy % ( CHIP_HEIGHT / 2 );
		if ( ( x + y ) % 2 == 1 ) {
			ax = ( CHIP_HEIGHT / 2 ) - ax - 1;
		}
		up = ( ax + ay < CHIP_HEIGHT / 2 );
		
		_gx = x / 2;
		_gy = y;
		if ( up ) {
			_gy--;
		}
		if ( x % 2 == 0 ) {
			if ( y % 2 == 0 ) {
				if ( up ) {
					_gx--;
				}
			} else {
				if ( !up ) {
					_gx--;
				}
			}
		}

		if ( _gy < 0 || _gy >= DISP_CHIP_HEIGHT ||
			 _gx < 0 || _gx >= DISP_CHIP_WIDTH ) {
			_gx = -1;
			_gy = -1;
		}
	}
}

int ChipCursor::getScrollX( ) const {
	return _scroll_x;
}

int ChipCursor::getGX( ) const {
	return _gx;
}

int ChipCursor::getGY( ) const {
	return _gy;
}

bool ChipCursor::isOnChip( ) const {
	return _gx >= 0 && _gy >= 0;
}
