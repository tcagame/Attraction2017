#include "ChipPreview.h"
#include "Editor.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Keyboard.h"
#include "Data.h"
#include "Keyboard.h"
#include "ChipCursor.h"
#include "LoadCSV.h"
#include "ChipEditor.h"
#include "Ground.h"
#include "Structure.h"
#include "ChipDrawer.h"

const int BASE_X = - CHIP_WIDTH / 2;
const int BASE_Y = - CHIP_HEIGHT / 2;
const int VIEW_PAGE_NUM = SCREEN_WIDTH / GRAPH_SIZE;
const std::string EDITOR_PATH = "Resource/Ace/Editor/";

ChipPreview::ChipPreview( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor, ChipDrawerConstPtr chip_drawer ) :
_data( data ),
_cover( true ),
_chip_cursor( chip_cursor ),
_chip_editor( chip_editor ),
_chip_drawer( chip_drawer ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image = ImageTargetPtr( new ImageTarget );
	_image->create( DISP_WIDTH, PREVIEW_HEIGHT );
}


ChipPreview::~ChipPreview( ) {
}

void ChipPreview::update( ) {
	KeyboardPtr key( Keyboard::getTask( ) );
	if ( key->isPushKey( "SPACE" ) ) {
		_cover = !_cover;
	}
}

void ChipPreview::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	_image->clear( );
	drawer->setImageTarget( _image );

	drawBg( );
	drawChip( );

	{//ì¬‚µ‚½‰æ‘œ‚ð•`‰æ
		drawer->setImageTarget( );
		_image->setPos( PREVIEW_X, PREVIEW_Y );
		_image->draw( );
	}
}

void ChipPreview::drawBg( ) const {
	int scroll_x = _chip_cursor->getScrollX( );
	for ( int i = 0; i < VIEW_PAGE_NUM; i++ ) {
		_chip_drawer->drawBg( i, scroll_x );
	}
}

void ChipPreview::drawChip( ) const {
	std::vector< int > select_gx;
	std::vector< int > select_gy;
	_chip_editor->getReplacePos( select_gx, select_gy );
	int range = _chip_editor->getRange( );
	int check_num = range * range;
	int scroll_x = _chip_cursor->getScrollX( );

	for ( int i = 0; i < DISP_CHIP_HEIGHT; i++ ) {
		for ( int j = 0; j < DISP_CHIP_WIDTH; j++ ) {
			int gx = j;
			int gy = i;
			int mx = ( gx + scroll_x ) % ( _data->getPageNum( ) * PAGE_CHIP_WIDTH_NUM );
			int my = gy;
			if ( !_cover && _data->isFront( mx, my ) ) {
				continue;
			}
			bool select = false;
			for ( int k = 0; k < check_num; k++ ) {
				if ( gx == select_gx[ k ] && gy == select_gy[ k ] ) {
					select = true;
				}
			}
			if ( Editor::getTask( )->getMode( ) == Editor::MODE_OBJECT ) {
				select = false;
			}
			_chip_drawer->drawChip( mx, my, gx, gy, select );
		}
	}
}
