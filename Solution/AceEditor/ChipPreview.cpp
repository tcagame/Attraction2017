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
const std::string EDITOR_PATH = "Resource/Ace/Editor/";

ChipPreview::ChipPreview( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor, ChipDrawerConstPtr chip_drawer ) :
_data( data ),
_covor( true ),
_chip_cursor( chip_cursor ),
_chip_editor( chip_editor ),
_chip_drawer( chip_drawer ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_background = ImageTargetPtr( new ImageTarget );
	_image_background->create( DISP_WIDTH, PREVIEW_HEIGHT );
}


ChipPreview::~ChipPreview( ) {
}

void ChipPreview::update( ) {
	KeyboardPtr key( Keyboard::getTask( ) );
	if ( key->isPushKey( "SPACE" ) ) {
		_covor = !_covor;
	}
}

void ChipPreview::draw( ) const {
	std::vector< int > select_gx;
	std::vector< int > select_gy;
	_chip_editor->getReplacePos( select_gx, select_gy );
	int range = _chip_editor->getRange( );
	int check_num = range * range;

	DrawerPtr drawer = Drawer::getTask( );
	_image_background->clear( );
	drawer->setImageTarget( _image_background );
	for ( int i = 0; i < DISP_CHIP_HEIGHT; i++ ) {
		for ( int j = 0; j < DISP_CHIP_WIDTH; j++ ) {
			int gx = j;
			int gy = i;
			int mx = ( gx + _chip_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_CHIP_WIDTH_NUM );
			int my = gy;
			if ( !_covor && my >= MAP_COVER_HEIGHT ) {
				break;
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
			_chip_drawer->draw( mx, my, gx, gy, select );
		}
	}

	{//ì¬‚µ‚½‰æ‘œ‚ð•`‰æ
		drawer->setImageTarget( );
		_image_background->setPos( PREVIEW_X, PREVIEW_Y );
		_image_background->draw( );
	}
}