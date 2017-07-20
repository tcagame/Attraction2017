#include "ChipMenu.h"
#include "Mouse.h"
#include "Drawer.h"
#include "ChipEditor.h"
#include "Application.h"
#include "LoadCSV.h"
#include "Ground.h"
#include "Structure.h"

const int NUMBER_CHIP_SIZE = 32;
const int BG_WIDTH = 340;
const int BG_HEIGHT = 280;
const int TAG_GRAPH_WIDTH = 96;
const int TAG_GRAPH_HEIGHT = 32;
const int FRAME_SIZE = 5;
const int FRAME_WINDOW_WIDTH = BG_WIDTH + FRAME_SIZE * 2;
const int FRAME_WINDOW_HEIGHT = BG_HEIGHT + TAG_GRAPH_HEIGHT + FRAME_SIZE;
const int FRAME_X = 0;
const int FRAME_Y = 0;
const int TAG_Y = 0;
const int TAG_X = 10;
const int BG_X = FRAME_SIZE;
const int BG_Y = TAG_GRAPH_HEIGHT;
const int HEIGHT_X = BG_X + 10;
const int HEIGHT_Y = BG_Y + 10;
const int GROUND_X = HEIGHT_X;
const int GROUND_Y = HEIGHT_Y;
const int STRUCTURE_X = HEIGHT_X;
const int STRUCTURE_Y = HEIGHT_Y;
const int PAGE_ARROW_SIZE = 32;
const int PAGE_ARROW_Y = FRAME_WINDOW_HEIGHT - FRAME_SIZE - PAGE_ARROW_SIZE - 5;
const int PAGE_ARROW_DISTANCE_CENTER = 30;
const int GROUND_WIDTH_NUM = 3;
const int GROUND_HEIGHT_NUM = 2;
const int GROUND_SIZE = ( BG_WIDTH - 10 ) / GROUND_WIDTH_NUM;
const int STRUCTURE_WIDTH_NUM = 3;
const int STRUCTURE_HEIGHT_NUM = 2;
const int STRUCTURE_SIZE = ( BG_WIDTH - 10 ) / STRUCTURE_WIDTH_NUM;

ChipMenu::ChipMenu( ImagePtr menu_image, ChipEditorPtr chip_editor, GroundConstPtr ground, StructureConstPtr structure ) :
_active( false ),
_chip_editor( chip_editor ),
_select_tag( TAG_GROUND ),
_page( 0 ),
_image( menu_image ),
_ground( ground ),
_structure( structure ) {
	int ground_size = ground->getSize( );
	int structure_size = structure->getSize( );
	_ground_page_num = ( ground->getSize( ) - 1 ) / ( GROUND_HEIGHT_NUM * GROUND_WIDTH_NUM );
	_structure_page_num = ( structure->getSize( ) - 1 ) / ( STRUCTURE_HEIGHT_NUM * STRUCTURE_WIDTH_NUM );

}

ChipMenu::~ChipMenu( ) {
}

void ChipMenu::update( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isPushLeftButton( ) ) {
		Vector mouse_pos = mouse->getPos( ); 
		_active = false;
		{//tag選択
			int sx1 = ( int )_pos.x + TAG_X;
			int sy1 = ( int )_pos.y + TAG_Y;
			int sx2 = sx1 + ( TAG_GRAPH_WIDTH + 1 ) * ( int )MAX_TAG;
			int sy2 = sy1 + TAG_GRAPH_HEIGHT;
			if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
				_select_tag = (TAG)( ( (int)mouse_pos.x - sx1 ) / TAG_GRAPH_WIDTH );
				_page = 0;
				_active = true;
			}
		}

		switch( _select_tag ) {
		case TAG_GROUND:
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
					if ( _page > _ground_page_num ) {
						_page = _ground_page_num;
					}
				}
			}
			{//ground選択
				int sx1 = ( int )_pos.x + GROUND_X;
				int sy1 = ( int )_pos.y + GROUND_Y;
				int sx2 = sx1 + GROUND_WIDTH_NUM * GROUND_SIZE;
				int sy2 = sy1 + GROUND_HEIGHT_NUM * GROUND_SIZE;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int x = ( int )( mouse_pos.x - sx1 ) / GROUND_SIZE;
					int y = ( int )( mouse_pos.y - sy1 ) / GROUND_SIZE;
					int idx = x + y * GROUND_WIDTH_NUM + _page * GROUND_WIDTH_NUM * GROUND_HEIGHT_NUM;
					_chip_editor->setMode( ChipEditor::MODE_GROUND, idx );
				}
			}
			break;
		case TAG_STRUCTURE:
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
					if ( _page > _structure_page_num ) {
						_page = _structure_page_num;
					}
				}
			}
			{//structure選択
				int sx1 = ( int )_pos.x + STRUCTURE_X;
				int sy1 = ( int )_pos.y + STRUCTURE_Y;
				int sx2 = sx1 + STRUCTURE_WIDTH_NUM * STRUCTURE_SIZE;
				int sy2 = sy1 + STRUCTURE_HEIGHT_NUM * STRUCTURE_SIZE;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int x = ( int )( mouse_pos.x - sx1 ) / STRUCTURE_SIZE;
					int y = ( int )( mouse_pos.y - sy1 ) / STRUCTURE_SIZE;
					int idx = x + y * STRUCTURE_WIDTH_NUM + _page * STRUCTURE_WIDTH_NUM * STRUCTURE_HEIGHT_NUM;
					_chip_editor->setMode( ChipEditor::MODE_STRUCTURE, idx );
				}
			}
			break;
		case TAG_HEIGHT:
			{
				int sx1 = ( int )_pos.x + HEIGHT_X;
				int sy1 = ( int )_pos.y + HEIGHT_Y;
				int sx2 = sx1 + NUMBER_CHIP_SIZE * 10;
				int sy2 = sy1 + NUMBER_CHIP_SIZE;
				if ( sx1 < mouse_pos.x && sx2 > mouse_pos.x && sy1 < mouse_pos.y && sy2 > mouse_pos.y ) {
					int height = ( ( int )mouse_pos.x - sx1 ) / NUMBER_CHIP_SIZE;
					_chip_editor->setMode( ChipEditor::MODE_HEIGHT, height );
				}
				break;
			}
		}
		
	}
}

void ChipMenu::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	{//frame
		int sx1 = ( int )_pos.x + FRAME_X;
		int sy1 = ( int )_pos.y + FRAME_Y;
		int tx = 32 * 3;
		int ty = 32 * 1;
		int tw = 32;
		int th = 32;
		int sx2 = sx1 + FRAME_WINDOW_WIDTH;
		int sy2 = sy1 + FRAME_WINDOW_HEIGHT;
		_image->setPos( sx1, sy1, sx2, sy2 );
		_image->setRect( tx, ty, tw, th );
		_image->draw( );
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
		_image->setPos( sx1, sy1, sx2, sy2 );
		_image->setRect( tx, ty, tw, th );
		_image->draw( );
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
			_image->setPos( sx1, sy1, sx2, sy2 );
			_image->setRect( tx, ty, tw, th );
			_image->draw( );

			tx = 0;
			ty = 64 + i * 32;
			tw = TAG_GRAPH_WIDTH;
			_image->setPos( sx1, sy1, sx2, sy2 );
			_image->setRect( tx, ty, tw, th );
			_image->draw( );
			drawer->drawLine( sx2, sy1, sx2, sy2 );
			sx1 += TAG_GRAPH_WIDTH + 2;
			sx2 = sx1 + TAG_GRAPH_WIDTH;

		}
	}
	switch( _select_tag ) {
	case TAG_GROUND:
		{//Arrow
			int sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 - PAGE_ARROW_DISTANCE_CENTER - PAGE_ARROW_SIZE;
			int sy1 = ( int )_pos.y + PAGE_ARROW_Y;
			int tx = 32 * 4;
			int ty = 32 * 1;
			int sx2 = sx1 + PAGE_ARROW_SIZE;
			int sy2 = sy1 + PAGE_ARROW_SIZE;
			_image->setPos( sx1, sy1, sx2, sy2 );
			_image->setRect( tx, ty, PAGE_ARROW_SIZE, PAGE_ARROW_SIZE );
			_image->draw( );
			sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 + PAGE_ARROW_DISTANCE_CENTER + PAGE_ARROW_SIZE;
			sx2 = sx1 - PAGE_ARROW_SIZE;
			_image->setPos( sx1, sy1, sx2, sy2 );
			_image->setRect( tx, ty, PAGE_ARROW_SIZE, PAGE_ARROW_SIZE );
			_image->draw( );
		}
		{//ground
			int add = _page * GROUND_HEIGHT_NUM * GROUND_WIDTH_NUM;
			int ground_size = _ground->getSize( );
			for ( int i = 0; i < GROUND_HEIGHT_NUM; i++ ) {
				int y = i;
				int sx1 = ( int )_pos.x + GROUND_X;
				int sy1 = ( int )_pos.y + GROUND_Y + i * STRUCTURE_SIZE;
				int sx2 = sx1 + GROUND_SIZE;
				int sy2 = sy1 + GROUND_SIZE;
				for ( int j = 0; j < GROUND_WIDTH_NUM; j++ ) {
					int x = j;
					int idx = x + y * GROUND_WIDTH_NUM + add;
					if ( idx >= ground_size ) {
						break;
					}
					if ( idx != 0 ) {
						int tw = 0;
						int th = 0;
						ImagePtr ground = _ground->getImage( idx );
						ground->getImageSize( tw, th );
						ground->setRect( 0, 0, tw, th );
						ground->setPos( sx1, sy1, sx2, sy2 );
						ground->draw( );
					}
					sx1 += GROUND_SIZE;
					sx2 = sx1 + GROUND_SIZE;
				}
			}
		}
		break;
	case TAG_STRUCTURE:
		{//Arrow
			int sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 - PAGE_ARROW_DISTANCE_CENTER - PAGE_ARROW_SIZE;
			int sy1 = ( int )_pos.y + PAGE_ARROW_Y;
			int tx = 32 * 4;
			int ty = 32 * 1;
			int sx2 = sx1 + PAGE_ARROW_SIZE;
			int sy2 = sy1 + PAGE_ARROW_SIZE;
			_image->setRect( tx, ty, PAGE_ARROW_SIZE, PAGE_ARROW_SIZE );
			_image->setPos( sx1, sy1, sx2, sy2 );
			_image->draw( );
			sx1 = ( int )_pos.x + FRAME_WINDOW_WIDTH / 2 + PAGE_ARROW_DISTANCE_CENTER + PAGE_ARROW_SIZE;
			sx2 = sx1 - PAGE_ARROW_SIZE;
			_image->setPos( sx1, sy1, sx2, sy2 );
			_image->draw( );
		}
		{//structure
			int structure_size = _structure->getSize( );
			int add = _page * STRUCTURE_HEIGHT_NUM * STRUCTURE_WIDTH_NUM;
			for ( int i = 0; i < STRUCTURE_HEIGHT_NUM; i++ ) {
				int y = i;
				int sx1 = ( int )_pos.x + STRUCTURE_X;
				int sy1 = ( int )_pos.y + STRUCTURE_Y + i * STRUCTURE_SIZE;
				int sx2 = sx1 + STRUCTURE_SIZE;
				int sy2 = sy1 + STRUCTURE_SIZE;
				for ( int j = 0; j < STRUCTURE_WIDTH_NUM; j++ ) {
					int x = j;
					int idx = x + y * STRUCTURE_WIDTH_NUM + add;
					if ( idx >= structure_size ) {
						break;
					}
					if ( idx != 0 ) {
						int tw = 0;
						int th = 0;
						ImagePtr structure = _structure->getImage( idx );
						structure->getImageSize( tw, th );
						structure->setRect( 0, 0, tw, th );
						structure->setPos( sx1, sy1, sx2, sy2 );
						structure->draw( );
					}
					sx1 += STRUCTURE_SIZE;
					sx2 = sx1 + STRUCTURE_SIZE;
				}
			}
		}
		break;
	case TAG_HEIGHT:
		{
			int sx = ( int )_pos.x + HEIGHT_X;
			int sy = ( int )_pos.y + HEIGHT_Y;
			for ( int i = 0; i < 10; i++ ) {
				int tx = ( i % 8 ) * NUMBER_CHIP_SIZE;
				int ty = ( i / 8 ) * NUMBER_CHIP_SIZE;
				_image->setPos( sx, sy );
				_image->setRect( tx, ty, NUMBER_CHIP_SIZE, NUMBER_CHIP_SIZE );
				_image->draw( );
				sx += NUMBER_CHIP_SIZE;
			}
		}
		break;
	}
}

void ChipMenu::setPos( const Vector& pos ) {
	_pos = pos;
	if ( _pos.x + FRAME_WINDOW_WIDTH > SCREEN_WIDTH ) {
		_pos.x = SCREEN_WIDTH - FRAME_WINDOW_WIDTH;
	}
	if ( _pos.y + FRAME_WINDOW_HEIGHT > SCREEN_HEIGHT ) {
		_pos.y = SCREEN_HEIGHT - FRAME_WINDOW_HEIGHT;
	}
}

bool ChipMenu::getActive( ) const {
	return _active;
}