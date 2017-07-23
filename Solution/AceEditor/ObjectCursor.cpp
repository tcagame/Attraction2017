#include "ObjectCursor.h"
#include "ace_define.h"
#include "Mouse.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Data.h"

ObjectCursor::ObjectCursor( DataConstPtr data ) :
_gx( -1 ),
_gy( -1 ),
_data( data ) {
}


ObjectCursor::~ObjectCursor( ) {
}

void ObjectCursor::update( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	int add = 0;
	if ( keyboard->isPushKey( "ARROW_RIGHT" ) ) {
		add = 4;
	}
	if ( keyboard->isPushKey( "ARROW_LEFT" ) ) {
		add = _data->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM - 4;
	}
	_scroll_x = ( _scroll_x + add ) % ( _data->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM );

	// gx gy ‚ðŒŸo@‚à‚µobjectMode‚Ìchipã‚É‚È‚¢ê‡‚Í -1‚ð‘ã“ü
	_gx = -1;
	_gy = -1;
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPos( );

	// guide
	const int GUIDE_HEIGHT_NUM = GRAPH_SIZE / CHIP_HEIGHT;
	if ( pos.x >= PREVIEW_X &&
		 pos.x < PREVIEW_X + DISP_WIDTH &&
		 pos.y > GUIDE_Y &&
		 pos.y < GUIDE_Y + GUIDE_HEIGHT_NUM * OBJECT_GUIDE_SIZE ) {
		_gx = ( int )( mouse->getPos( ).x - PREVIEW_X ) / OBJECT_GUIDE_SIZE;
		_gy = ( int )( mouse->getPos( ).y - GUIDE_Y	  ) / OBJECT_GUIDE_SIZE;
	}

	//preview
	if ( pos.x >= PREVIEW_X &&
		 pos.x < PREVIEW_X + DISP_WIDTH &&
		 pos.y > PREVIEW_Y &&
		 pos.y < SCREEN_HEIGHT ) {
		_gx = ( int )( mouse->getPos( ).x - PREVIEW_X ) / OBJECT_GUIDE_SIZE;
		_gy = ( int )( mouse->getPos( ).y - PREVIEW_Y ) / OBJECT_GUIDE_SIZE;
	}
}

int ObjectCursor::getGX( ) const {
	return _gx;
}

int ObjectCursor::getGY( ) const {
	return _gy;
}

bool ObjectCursor::isOnChip( ) const {
	return _gx >= 0 && _gy >= 0;
}

int ObjectCursor::getScrollX( ) const {
	return _scroll_x;
}

void ObjectCursor::setScrollX( int scroll_x ) {
	_scroll_x = scroll_x * 2;
}