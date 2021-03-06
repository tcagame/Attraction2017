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
const int BLOCK_DRAW_SIZE = 48;
const int BLOCK_WIDTH_NUM = 6;

const int CHARA_WIDTH_NUM = 6;
const int CHARA_HEIGHT_NUM = 4;
const int CHARA_DRAW_SIZE = 48;

const int EVENT_SPRITE_SIZE = 32;
const int EVENT_SPRITE_WIDTH_NUM = 4;
const int EVENT_DRAW_SIZE = 48;
const int EVENT_WIDTH_NUM = 6;
const int EVENT_HEIGHT_NUM = 4;

const int PAGE_ARROW_SIZE = 32;
const int PAGE_ARROW_Y = FRAME_WINDOW_HEIGHT - FRAME_SIZE - PAGE_ARROW_SIZE - 5;
const int PAGE_ARROW_DISTANCE_CENTER = 30;

const Rect character_rect[ ] = {
	RECT_PUPLE_ZOMBIE,
	RECT_FACE_AND_HAND,
	RECT_NO_FACE,
	RECT_LANCER,
	RECT_CROCO_SNAKE,
	RECT_GHOUL,
	RECT_GHOST,
	RECT_ONE_EYE_SNAKE,
	RECT_WHITE_MIST,
	RECT_GRAY_MIST,
	RECT_STONE_FACE,
	RECT_NO_NECK_GHOST,
	RECT_SHISHIMAI_DAEMON,
	RECT_SHISHIMAI,
	RECT_ARCHER,
	RECT_HAND,
	RECT_RED_BIRD,
	RECT_BLUE_MONK,
	RECT_GREEN_ZOMBIE,
	RECT_HUG_DAEMON,
	RECT_SWAMP_ZOMBIE_A,
	RECT_SWAMP_ZOMBIE_B,
	RECT_SWAMP_ZOMBIE_C,
	RECT_SHELL,
	RECT_WATER_GHOST,
	RECT_TURTLE,
	RECT_SKELETON,
	RECT_LADY,
	RECT_RAY,
	RECT_WIND,
	RECT_ONYUDO,
	RECT_JIZO,
	RECT_TREE,
	RECT_GAMA,
	RECT_FLOG,
	RECT_BAT,
	RECT_STONE,
	RECT_MOTH,
	RECT_EYE_DAEMON,
	RECT_MONEY_BAG,
	RECT_MONEY_PURSE,
	RECT_MONEY_500,
	RECT_MONEY_1000,
	RECT_MONEY_5000,
	RECT_MONEY_10000,
};
const int MAX_CHARA = sizeof( character_rect ) / sizeof( character_rect[ 0 ] );

ObjectMenu::ObjectMenu( ImagePtr image_menu, ImagePtr image_block, ImagePtr enemy_midium_image, ImagePtr enemy_big_image, ImagePtr enemy_wide_image, ImagePtr enemy_small_image, ImagePtr image_event, ObjectEditorPtr object_editor ) :
_active( false ),
_select_tag( TAG_BLOCK ),
_object_editor( object_editor ),
_menu( image_menu ),
_block( image_block ),
_event( image_event ),
_page( 0 ) {
	_enemy[ GRAPH_ENEMY_MIDIUM ] = enemy_midium_image;
	_enemy[ GRAPH_ENEMY_BIG ] = enemy_big_image;
	_enemy[ GRAPH_ENEMY_WIDE ] = enemy_wide_image;
	_enemy[ GRAPH_ENEMY_SMALL ] = enemy_small_image;
	_money = Drawer::getTask( )->createImage( "item/money.png" );
}

ObjectMenu::~ObjectMenu( ) {
}

void ObjectMenu::update( ) {
	_active = false;
	MousePtr mouse( Mouse::getTask( ) );
	if ( mouse->isPushLeftButton( ) ) {
		Vector mouse_pos = mouse->getPos( );
		{//tag�I��
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
			case TAG_BLOCK: // block�I��
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
			{//page�I��
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
					if ( _page > MAX_CHARA / ( CHARA_WIDTH_NUM * CHARA_HEIGHT_NUM ) ) {
						_page = MAX_CHARA / ( CHARA_WIDTH_NUM * CHARA_HEIGHT_NUM );
					}
				}
			}			
			{ //enemy�I��
				int sx1 = ( int )_pos.x + BLOCK_X;
				int sy1 = ( int )_pos.y + BLOCK_Y;
				int sx2 = sx1 + CHARA_DRAW_SIZE * CHARA_WIDTH_NUM;
				int sy2 = sy1 + CHARA_DRAW_SIZE * CHARA_HEIGHT_NUM;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int x = ( int )( mouse_pos.x - sx1 ) / CHARA_DRAW_SIZE;
					int y = ( int )( mouse_pos.y - sy1 ) / CHARA_DRAW_SIZE;
					int enemy_idx = x + y * CHARA_WIDTH_NUM + _page * CHARA_WIDTH_NUM * CHARA_HEIGHT_NUM;
					unsigned char enemy = getEnemy( enemy_idx );
					_object_editor->setObject( enemy );
				}
			}
			break;
			case TAG_EVENT:
			{//event�I��
				int sx1 = ( int )_pos.x + BLOCK_X;
				int sy1 = ( int )_pos.y + BLOCK_Y;
				int sx2 = sx1 + EVENT_DRAW_SIZE * EVENT_WIDTH_NUM;
				int sy2 = sy1 + EVENT_DRAW_SIZE * EVENT_HEIGHT_NUM;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int x = ( int )( mouse_pos.x - sx1 ) / EVENT_DRAW_SIZE;
					int y = ( int )( mouse_pos.y - sy1 ) / EVENT_DRAW_SIZE;
					int idx = x + y * EVENT_WIDTH_NUM;
					unsigned char event = getEvent( idx );
					_object_editor->setObject( event );
				}
			}
			break;
		}
	}
}

unsigned char ObjectMenu::getObj( int idx ) const {
	unsigned char result = OBJECT_NONE;
	switch ( idx ) {
	case 0:
		result = OBJECT_NONE;
		break;
	case 1:
		result = OBJECT_BLOCK;
		break;
	case 2:
		result = OBJECT_ONEWAY;
		break;
	case 3:
		result = OBJECT_WATER;
		break;
	default:
		result = _object_editor->getObject( );
		break;
	}
	return result;
}

unsigned char ObjectMenu::getEnemy( int idx ) const {
	unsigned char result = OBJECT_NONE;
	switch( idx ) {
	// midium
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
	case 5:
		result = OBJECT_GHOUL;
		break;
	case 6:
		result = OBJECT_GHOST;
		break;
	case 7:
		result = OBJECT_ONE_EYE_SNAKE;
		break;
	case 8:
		result = OBJECT_WHITE_MIST;
		break;
	case 9:
		result = OBJECT_GRAY_MIST;
		break;
	case 10:
		result = OBJECT_STONE_FACE;
		break;
	case 11:
		result = OBJECT_NO_NECK_GHOST;
		break;
	case 12:
		result = OBJECT_SHISHIMAI_DAEMON;
		break;
	case 13:
		result = OBJECT_SHISHIMAI;
		break;
	case 14:
		result = OBJECT_ARCHER;
		break;
	case 15:
		result = OBJECT_HAND;
		break;
	case 16:
		result = OBJECT_RED_BIRD;
		break;
	case 17:
		result = OBJECT_BLUE_MONK;
		break;
	case 18:
		result = OBJECT_GREEN_ZOMBIE;
		break;
	case 19:
		result = OBJECT_HUG_DAEMON;
		break;
	case 20:
		result = OBJECT_SWAMP_ZOMBIE_A;
		break;
	case 21:
		result = OBJECT_SWAMP_ZOMBIE_B;
		break;
	case 22:
		result = OBJECT_SWAMP_ZOMBIE_C;
		break;
	case 23:
		result = OBJECT_SHELL;
		break;
	case 24:
		result = OBJECT_WATER_GHOST;
		break;
	case 25:
		result = OBJECT_TURTLE;
		break;
	// wide
	case 26:
		result = OBJECT_SKELETON;
		break;
	case 27:
		result = OBJECT_LADY;
		break;
	case 28:
		result = OBJECT_RAY;
		break;
	// big
	case 29:
		result = OBJECT_WIND;
		break;
	case 30:
		result = OBJECT_ONYUDO;
		break;
	case 31:
		result = OBJECT_JIZO;
		break;
	case 32:
		result = OBJECT_TREE;
		break;
	case 33:
		result = OBJECT_GAMA;
		break;
	// small
	case 34:
		result = OBJECT_FLOG;
		break;
	case 35:
		result = OBJECT_BAT;
		break;
	case 36:
		result = OBJECT_STONE;
		break;
	case 37:
		result = OBJECT_MOTH;
		break;
	case 38:
		result = OBJECT_EYE_DAEMON;
		break;
	case 39:
		result = OBJECT_MONEY_BAG;
		break;
	case 40:
		result = OBJECT_MONEY_PURSE;
		break;
	case 41:
		result = OBJECT_MONEY_500;
		break;
	case 42:
		result = OBJECT_MONEY_1000;
		break;
	case 43:
		result = OBJECT_MONEY_5000;
		break;
	case 44:
		result = OBJECT_MONEY_10000;
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
		result = OBJECT_EVENT_REDDAEMON;
		break;
	case 1:
		result = OBJECT_EVENT_FLAME;
		break;
	case 2:
		result = OBJECT_EVENT_WOOD;
		break;
	case 3:
		result = OBJECT_EVENT_MINERAL;
		break;
	case 4:
		result = OBJECT_EVENT_SHOP;
		break;
	case 5:
		result = OBJECT_EVENT_LAKE;
		break;
	case 6:
		result = OBJECT_EVENT_RYUGU;
		break;
	case 7:
		result = OBJECT_EVENT_CALL;
		break;
	case 8:
		result = OBJECT_EVENT_GAMBLE;
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
				int tx = i * BLOCK_SPRITE_SIZE;
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
			int add = _page * CHARA_HEIGHT_NUM * CHARA_WIDTH_NUM;
			for ( int i = 0; i < CHARA_HEIGHT_NUM; i++ ) {
				for ( int j = 0; j < CHARA_WIDTH_NUM; j++ ) {
					int idx = j + i * CHARA_WIDTH_NUM + add;
					if ( idx >= MAX_CHARA ) {
						break;
					}
					if ( idx != -1 ) {
						int sx = ( int )_pos.x + BLOCK_X + j * CHARA_DRAW_SIZE;
						int sy = ( int )_pos.y + BLOCK_Y + i * CHARA_DRAW_SIZE;
						if ( idx < 26 ) {
							_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( character_rect[ idx ].tx, character_rect[ idx ].ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
							_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( sx, sy, sx + CHARA_DRAW_SIZE, sy + CHARA_DRAW_SIZE );
							_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
						}
						if ( 25 < idx && idx < 29 ) {
							_enemy[ GRAPH_ENEMY_WIDE ]->setRect( character_rect[ idx ].tx, character_rect[ idx ].ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
							_enemy[ GRAPH_ENEMY_WIDE ]->setPos( sx, sy, sx + CHARA_DRAW_SIZE, sy + CHARA_DRAW_SIZE );
							_enemy[ GRAPH_ENEMY_WIDE ]->draw( );
						}
						if ( 28 < idx && idx < 34 ) {
							_enemy[ GRAPH_ENEMY_BIG ]->setRect( character_rect[ idx ].tx, character_rect[ idx ].ty, BIG_CHAR_GRAPH_SIZE, BIG_CHAR_GRAPH_SIZE );
							_enemy[ GRAPH_ENEMY_BIG ]->setPos( sx, sy, sx + CHARA_DRAW_SIZE, sy + CHARA_DRAW_SIZE );
							_enemy[ GRAPH_ENEMY_BIG ]->draw( );
						}
						if ( 33 < idx && idx < 39 ) {
							_enemy[ GRAPH_ENEMY_SMALL ]->setRect( character_rect[ idx ].tx, character_rect[ idx ].ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
							_enemy[ GRAPH_ENEMY_SMALL ]->setPos( sx, sy, sx + CHARA_DRAW_SIZE, sy + CHARA_DRAW_SIZE );
							_enemy[ GRAPH_ENEMY_SMALL ]->draw( );
						}
						if ( 38 < idx && idx < 45 ) {
							_money->setRect( character_rect[ idx ].tx, character_rect[ idx ].ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
							_money->setPos( sx, sy, sx + CHARA_DRAW_SIZE, sy + CHARA_DRAW_SIZE );
							_money->draw( );
						}
					}
				}
			}
		}
		break;
		case TAG_EVENT:	
			for ( int i = 0; i < EVENT_HEIGHT_NUM * EVENT_WIDTH_NUM; i++ ) {
				int sx = ( int )_pos.x + BLOCK_X + ( i % EVENT_WIDTH_NUM ) * EVENT_DRAW_SIZE;
				int sy = ( int )_pos.y + BLOCK_Y + ( i / EVENT_WIDTH_NUM ) * EVENT_DRAW_SIZE;
				int tx = ( i % EVENT_SPRITE_WIDTH_NUM ) * EVENT_SPRITE_SIZE;
				int ty = ( i / EVENT_SPRITE_WIDTH_NUM ) * EVENT_SPRITE_SIZE;
				_event->setRect( tx, ty, EVENT_SPRITE_SIZE, EVENT_SPRITE_SIZE );
				_event->setPos( sx, sy, sx + EVENT_DRAW_SIZE, sy + EVENT_DRAW_SIZE );
				_event->draw( );
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
