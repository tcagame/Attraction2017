#include "ObjectMenu.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Mouse.h"
#include "Image.h"
#include "ObjectEditor.h"

const int WINDOW_WIDTH = 350;
const int WINDOW_HEIGHT = 320;

const int FRAME_X = 0;
const int FRAME_Y = 0;
const int BG_WIDTH = 340;
const int BG_HEIGHT = 280;
const int TAG_GRAPH_WIDTH = 96;
const int TAG_GRAPH_HEIGHT = 32;
const int FRAME_SIZE = 5;
const int FRAME_WINDOW_WIDTH = BG_WIDTH + FRAME_SIZE * 2;
const int FRAME_WINDOW_HEIGHT = BG_HEIGHT + TAG_GRAPH_HEIGHT + FRAME_SIZE;
const int BG_X = FRAME_SIZE;
const int BG_Y = TAG_GRAPH_HEIGHT;
const int TAG_X = 10;
const int TAG_Y = 0;

const int BLOCK_SPRITE_SIZE = 16;
const int BLOCK_X = 15;
const int BLOCK_Y = 42;
const int BLOCK_DRAW_SIZE = 64;
const int BLOCK_WIDTH_NUM = 3;

ObjectMenu::ObjectMenu( ImagePtr image_menu, ImagePtr image_block, ObjectEditorPtr object_editor ) :
_active( false ),
_select_tag( TAG_BLOCK ),
_object_editor( object_editor ),
_menu( image_menu ),
_block( image_block ) {
}

ObjectMenu::~ObjectMenu( ) {
}

void ObjectMenu::update( ) {
	_active = false;
	MousePtr mouse( Mouse::getTask( ) );
	if ( mouse->isPushLeftButton( ) ) {
		Vector mouse_pos = mouse->getPos( );
		{//tag‘I‘ð
			int sx1 = ( int )_pos.x + TAG_X;
			int sy1 = ( int )_pos.y + TAG_Y;
			int sx2 = sx1 + ( TAG_GRAPH_WIDTH + 1 ) * ( int )MAX_TAG;
			int sy2 = sy1 + TAG_GRAPH_HEIGHT;
			if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
				_select_tag = (TAG)( ( (int)mouse_pos.x - sx1 ) / TAG_GRAPH_WIDTH );
				_active = true;
			}
		}

		switch ( _select_tag ) {
		case TAG_BLOCK: // block‘I‘ð
			int sx1 = ( int )_pos.x + BLOCK_X;
			int sy1 = ( int )_pos.y + BLOCK_Y;
			int sx2 = sx1 + BLOCK_DRAW_SIZE * BLOCK_WIDTH_NUM;
			int sy2 = sy1 + BLOCK_DRAW_SIZE;
			if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
				int x = ( int )( mouse_pos.x - sx1 ) / BLOCK_DRAW_SIZE;
				int y = ( int )( mouse_pos.y - sy1 ) / BLOCK_DRAW_SIZE;
				int idx = x + y * BLOCK_WIDTH_NUM;
				unsigned char obj = getObj( idx );
				_object_editor->setObject( obj );
			}
			break;
		}
	}
}

unsigned char ObjectMenu::getObj( int idx ) {
	unsigned char result = OBJECT_NONE;
	switch ( idx ) {
	case 1:
		result = OBJECT_BLOCK;
		break;
	case 2:
		result = OBJECT_ONE_WAY;
		break;
	default:
		result = OBJECT_NONE;
		break;
	}
	return result;
}

void ObjectMenu::draw( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	{//frame
		int sx1 = ( int )_pos.x + FRAME_X;
		int sy1 = ( int )_pos.y + FRAME_Y;
		int tx = 32 * 3;
		int ty = 32 * 1;
		int tw = 32;
		int th = 32;
		int sx2 = sx1 + FRAME_WINDOW_WIDTH;
		int sy2 = sy1 + FRAME_WINDOW_HEIGHT;
		_menu->setPos( sx1, sy1, sx2, sy2 );
		_menu->setRect( tx, ty, tw, th );
		_menu->draw( );
	}
	{//bg
		int sx1 = ( int )_pos.x + BG_X;
		int sy1 = ( int )_pos.y + BG_Y;
		int tx = 32 * 2;
		int ty = 32 * 1;
		int tw = 32;
		int th = 32;
		int sx2 = sx1 + BG_WIDTH;
		int sy2 = sy1 + BG_HEIGHT;
		_menu->setPos( sx1, sy1, sx2, sy2 );
		_menu->setRect( tx, ty, tw, th );
		_menu->draw( );
	}
	{//tag_bg
		int sx1 = ( int )_pos.x + TAG_X;
		int sy1 = ( int )_pos.y + TAG_Y;
		int ty = 32 * 1;
		int tw = 32;
		int th = 32;
		int sx2 = sx1 + TAG_GRAPH_WIDTH;
		int sy2 = sy1 + TAG_GRAPH_HEIGHT;
		for ( int i = 0; i < MAX_TAG; i++ ) {
			int tx = 32 * 3;
			if ( _select_tag == i ) {
				tx -= 32;
			}
			tw = 32;
			ty = 32;
			_menu->setPos( sx1, sy1, sx2, sy2 );
			_menu->setRect( tx, ty, tw, th );
			_menu->draw( );

			tx = 0;
			ty = 64 + ( i + 3 ) * 32;
			tw = TAG_GRAPH_WIDTH;
			_menu->setPos( sx1, sy1, sx2, sy2 );
			_menu->setRect( tx, ty, tw, th );
			_menu->draw( );
			drawer->drawLine( sx2, sy1, sx2, sy2 );
			sx1 += TAG_GRAPH_WIDTH + 2;
			sx2 = sx1 + TAG_GRAPH_WIDTH;

		}
	}
	switch( _select_tag ) {
	case TAG_BLOCK:
		{//block
			int sx = ( int )_pos.x + BLOCK_X;
			int sy = ( int )_pos.y + BLOCK_Y;
			for ( int i = 0; i < BLOCK_WIDTH_NUM; i++, sx += BLOCK_DRAW_SIZE ) {
				int tx = ( i % 2 ) * BLOCK_SPRITE_SIZE;
				int ty = ( i / 2 ) * BLOCK_SPRITE_SIZE;
				_block->setRect( tx, ty, BLOCK_SPRITE_SIZE, BLOCK_SPRITE_SIZE );
				_block->setPos( sx, sy, sx + BLOCK_DRAW_SIZE, sy + BLOCK_DRAW_SIZE );
				_block->draw( );
			}
		}
		break;
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