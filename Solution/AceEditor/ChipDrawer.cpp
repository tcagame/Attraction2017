#include "ChipDrawer.h"
#include "ace_define.h"
#include "Drawer.h"
#include "Image.h"
#include "Ground.h"
#include "Structure.h"
#include "Data.h"
#include "Background.h"

const int BASE_X = -CHIP_WIDTH / 2;
const int BASE_Y = -CHIP_HEIGHT / 2;

ChipDrawer::ChipDrawer( DataConstPtr data, GroundConstPtr ground, StructureConstPtr structure, BackgroundPtr background ) :
_data( data ),
_ground( ground ),
_structure( structure ),
_background( background ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_choice_front = drawer->createImage( "preview/preview_cursor_front.png" );
	_image_choice_back = drawer->createImage( "preview/preview_cursor_back.png" );
}


ChipDrawer::~ChipDrawer( ) {
}

void ChipDrawer::drawChip( int mx, int my, int gx, int gy, bool select ) const {
	int sy = BASE_Y + gy * CHIP_HEIGHT / 2;
	sy -= CHIP_HEIGHT / 2 * _data->getHeight( mx, my );	//高さ
	int sx = BASE_X + gx  * CHIP_WIDTH;
	sx += ( my % 2 ) * CHIP_WIDTH / 2;	//横にずらす
	if ( select ) { // 選んでいるチップ表示
		_image_choice_back->setPos( sx, 0 );
		_image_choice_back->draw( );
	}
	int ground_num = _data->getGround( mx, my );
	ImagePtr ground = _ground->getImage( ground_num );
	if ( ground ) {
		ground->setPos( sx, sy );
		ground->setRect( );
		ground->draw( );
	}

	int structure_num = _data->getStructure( mx, my );
	ImagePtr structure = _structure->getImage( structure_num );
	if( structure ) {
		int width = 0;
		int height = 0;
		structure->getImageSize( width, height );
		structure->setPos( sx + CHIP_WIDTH / 2 - width / 2, sy - height + CHIP_HEIGHT );
		structure->setRect( );
		structure->draw( );
	}
	

	if ( select ) {// 選んでいるチップ表示
		_image_choice_front->setPos( sx, 0 );
		_image_choice_front->draw( );
	}
}

void ChipDrawer::drawBg( int screen_page, int scroll_mx ) const {
	int page_num = _data->getPageNum( );
	if ( page_num == 0 ) {
		return;
	}

	int diff = ( scroll_mx % PAGE_CHIP_WIDTH_NUM ) * CHIP_WIDTH;
	int start_page = scroll_mx / PAGE_CHIP_WIDTH_NUM;

	int page = ( screen_page + start_page ) % page_num;
	std::string tag = _data->getBg( page );
	if ( tag.size( ) == 0 ) {
		return;
	}
	ImagePtr image = _background->getImage( tag );
	if ( image == ImagePtr( ) ) {
		return;
	}
	int sx = screen_page * GRAPH_SIZE - diff;
	image->setPos( sx, 0 );
	image->draw( );
	
}
