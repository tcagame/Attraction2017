#include "ObjectMenu.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Mouse.h"
#include "Image.h"

const int WINDOW_WIDTH = 350;
const int WINDOW_HEIGHT = 320;

ObjectMenu::ObjectMenu( ImagePtr image_menu ) :
_active( false ),
_image( image_menu ) {
}

ObjectMenu::~ObjectMenu( ) {
}

void ObjectMenu::update( ) {
	_active = false;
	MousePtr mouse( Mouse::getTask( ) );
	if ( mouse->getPos( ).x > _pos.x &&
		 mouse->getPos( ).x < _pos.x + WINDOW_WIDTH &&
		 mouse->getPos( ).y > _pos.y &&
		 mouse->getPos( ).y < _pos.y + WINDOW_HEIGHT ) {
		_active = true;
	}
}

void ObjectMenu::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	{//frame
		int sx1 = ( int )_pos.x;
		int sy1 = ( int )_pos.y;
		int tx = 32 * 3;
		int ty = 32 * 1;
		int tw = 32;
		int th = 32;
		int sx2 = sx1 + WINDOW_WIDTH;
		int sy2 = sy1 + WINDOW_HEIGHT;
		_image->setPos( sx1, sy1, sx2, sy2 );
		_image->setRect( tx, ty, tw, th );
		_image->draw( );
	}
}

void ObjectMenu::setPos( const Vector& pos ) {
	_pos = pos;
	if ( _pos.x + WINDOW_WIDTH > SCREEN_WIDTH ) {
		_pos.x = SCREEN_WIDTH - WINDOW_WIDTH;
	}
	if ( _pos.y + WINDOW_HEIGHT > SCREEN_HEIGHT ) {
		_pos.y = SCREEN_HEIGHT - WINDOW_HEIGHT;
	}
}

bool ObjectMenu::getActive( ) const {
	return _active;
}