#include "ObjectMenu.h"
#include "Drawer.h"
#include "ace_define.h"
#include "ace_enemy_rect.h"
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

const int ENEMY_WIDTH_NUM = 5;
const int ENEMY_HEIGHT_NUM = 3;

const int EVENT_SPRITE_SIZE = 128;
const int EVENT_DRAW_SIZE = 64;
const int EVENT_WIDTH_NUM = 3;
const int EVENT_HEIGHT_NUM = 3;

const int PAGE_ARROW_SIZE = 32;
const int PAGE_ARROW_Y = FRAME_WINDOW_HEIGHT - FRAME_SIZE - PAGE_ARROW_SIZE - 5;
const int PAGE_ARROW_DISTANCE_CENTER = 30;

const Rect enemies_rect[ ] = {
	RECT_PUPLE_ZOMBIE,
	RECT_FACE_AND_HAND,
	RECT_NO_FACE,
	RECT_LANCER,
	RECT_CROCO_SNAKE
};
const int MAX_ENEMY = sizeof( enemies_rect ) / sizeof( enemies_rect[ 0 ] );

ObjectMenu::ObjectMenu( ImagePtr image_menu, ImagePtr image_block, ImagePtr image_enemy, ImagePtr image_event, ObjectEditorPtr object_editor ) :
_active( false ),
_select_tag( TAG_BLOCK ),
_object_editor( object_editor ),
_menu( image_menu ),
_block( image_block ),
_enemy( image_enemy ),
_event( image_event ),
_page( 0 ) {
}

ObjectMenu::~ObjectMenu( ) {
}

void ObjectMenu::update( ) {
	_active = false;
	MousePtr mouse( Mouse::getTask( ) );
	if ( mouse->isPushLeftButton( ) ) {
		Vector mouse_pos = mouse->getPos( );
		{//tag選択
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
			case TAG_BLOCK: // block選択
			{
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
			}
				break;
			case TAG_ENEMY:
			{//page選択
				int sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 - PAGE_ARROW_DISTANCE_CENTER - PAGE_ARROW_SIZE;
				int sy1 = ( int )_pos.y + PAGE_ARROW_Y;
				int sx2 = sx1 + PAGE_ARROW_SIZE;
				int sy2 = sy1 + PAGE_ARROW_SIZE;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					_active = true;
					_page--;
					if ( _page < 0 ) {
						_page = 0;
					}
				}
				sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 + PAGE_ARROW_DISTANCE_CENTER;
				sx2 = sx1 + PAGE_ARROW_SIZE;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					_active = true;
					_page++;
					if ( _page > MAX_ENEMY / ( ENEMY_WIDTH_NUM * ENEMY_HEIGHT_NUM ) ) {
						_page = MAX_ENEMY / ( ENEMY_WIDTH_NUM * ENEMY_HEIGHT_NUM );
					}
				}
			}			
			{ //enemy選択
				int sx1 = ( int )_pos.x + BLOCK_X;
				int sy1 = ( int )_pos.y + BLOCK_Y;
				int sx2 = sx1 + NORMAL_CHAR_GRAPH_SIZE * ENEMY_WIDTH_NUM;
				int sy2 = sy1 + NORMAL_CHAR_GRAPH_SIZE * ENEMY_HEIGHT_NUM;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int x = ( int )( mouse_pos.x - sx1 ) / NORMAL_CHAR_GRAPH_SIZE;
					int y = ( int )( mouse_pos.y - sy1 ) / NORMAL_CHAR_GRAPH_SIZE;
					int enemy_idx = x + y * ENEMY_WIDTH_NUM + _page * ENEMY_WIDTH_NUM * ENEMY_HEIGHT_NUM;
					unsigned char enemy = getEnemy( enemy_idx );
					_object_editor->setObject( enemy );
				}
			}
			case TAG_EVENT:
			{//event選択
				int sx1 = ( int )_pos.x + BLOCK_X;
				int sy1 = ( int )_pos.y + BLOCK_Y;
				int sx2 = sx1 + EVENT_DRAW_SIZE * EVENT_WIDTH_NUM;
				int sy2 = sy1 + EVENT_DRAW_SIZE;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int x = ( int )( mouse_pos.x - sx1 ) / EVENT_DRAW_SIZE;
					int y = ( int )( mouse_pos.y - sy1 ) / EVENT_DRAW_SIZE;
					int idx = x + y * EVENT_WIDTH_NUM;
					unsigned char event = getEvent( idx );
					_object_editor->setObject( event );
				}
			}
		}
	}
}

unsigned char ObjectMenu::getObj( int idx ) const {
	unsigned char result = OBJECT_NONE;
	switch ( idx ) {
	case 1:
		result = OBJECT_BLOCK;
		break;
	case 2:
		result = OBJECT_ONEWAY;
		break;
	default:
		result = OBJECT_NONE;
		break;
	}
	return result;
}

unsigned char ObjectMenu::getEnemy( int idx ) const {
	unsigned char result = OBJECT_NONE;
	switch( idx ) {
	case 0:
		result = OBJECT_PURPLE_ZOMBIE;
		break;
	case 1:
		result = OBJECT_FACE_AND_HAND;
		break;
	case 2:
		result = OBJECT_NO_FACE;
		break;
	case 3:
		result = OBJECT_LANCER;
		break;
	case 4:
		result = OBJECT_CROCO_SNAKE;
		break;
	default:
		result = OBJECT_NONE;
		break;
	}
	return result;
}

unsigned char ObjectMenu::getEvent( int idx ) const {
	unsigned char result = OBJECT_NONE;
	switch( idx ) {
	case 0:
		result = OBJECT_EVENT_REDDEAMON;
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
				int tx = ( i % 3 ) * BLOCK_SPRITE_SIZE;
				int ty = 0;
				_block->setRect( tx, ty, BLOCK_SPRITE_SIZE, BLOCK_SPRITE_SIZE );
				_block->setPos( sx, sy, sx + BLOCK_DRAW_SIZE, sy + BLOCK_DRAW_SIZE );
				_block->draw( );
			}
		}
		break;
	case TAG_ENEMY:		
		{//Arrow
			int sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 - PAGE_ARROW_DISTANCE_CENTER - PAGE_ARROW_SIZE;
			int sy1 = ( int )_pos.y + PAGE_ARROW_Y;
			int tx = 32 * 4;
			int ty = 32 * 1;
			int sx2 = sx1 + PAGE_ARROW_SIZE;
			int sy2 = sy1 + PAGE_ARROW_SIZE;
			_menu->setPos( sx1, sy1, sx2, sy2 );
			_menu->setRect( tx, ty, PAGE_ARROW_SIZE, PAGE_ARROW_SIZE );
			_menu->draw( );
			sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 + PAGE_ARROW_DISTANCE_CENTER + PAGE_ARROW_SIZE;
			sx2 = sx1 - PAGE_ARROW_SIZE;
			_menu->setPos( sx1, sy1, sx2, sy2 );
			_menu->setRect( tx, ty, PAGE_ARROW_SIZE, PAGE_ARROW_SIZE );
			_menu->draw( );
		}
		{//enemy
			for ( int i = 0; i < MAX_ENEMY; i++ ) {
				int sx = ( int )_pos.x + BLOCK_X + ( i % ENEMY_WIDTH_NUM ) * NORMAL_CHAR_GRAPH_SIZE;
				int sy = ( int )_pos.y + BLOCK_Y + ( i / ENEMY_WIDTH_NUM ) * NORMAL_CHAR_GRAPH_SIZE;
				_enemy->setRect( enemies_rect[ i ].tx, enemies_rect[ i ].ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( sx, sy, sx + NORMAL_CHAR_GRAPH_SIZE, sy + NORMAL_CHAR_GRAPH_SIZE );
				_enemy->draw( );
			}
		}
		break;
		case TAG_EVENT:		
		{//event
			int sx = ( int )_pos.x + BLOCK_X;
			int sy = ( int )_pos.y + BLOCK_Y;
			for ( int i = 0; i < EVENT_WIDTH_NUM; i++, sx += EVENT_DRAW_SIZE ) {
				int tx = ( i % 3 ) * EVENT_SPRITE_SIZE;
				int ty = 0;
				_event->setRect( tx, ty, EVENT_SPRITE_SIZE, EVENT_SPRITE_SIZE );
				_event->setPos( sx, sy, sx + EVENT_DRAW_SIZE, sy + EVENT_DRAW_SIZE );
				_event->draw( );
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