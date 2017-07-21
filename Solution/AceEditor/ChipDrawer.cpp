#include "ChipDrawer.h"
#include "ace_define.h"
#include "Drawer.h"
#include "Image.h"
#include "Ground.h"
#include "Structure.h"
#include "Data.h"

const int BACK_HEIGHT_NUM = DISP_CHIP_HEIGHT - MAP_COVER_HEIGHT;
const int BASE_X = -CHIP_WIDTH / 2;
const int BASE_Y = -CHIP_HEIGHT / 2;

ChipDrawer::ChipDrawer( DataConstPtr data, GroundConstPtr ground, StructureConstPtr structure ) :
_data( data ),
_ground( ground ),
_structure( structure ) {
	DrawerPtr drawer = Drawer::getTask( );
	_image_choice_front = drawer->createImage( "preview/preview_cursor_front.png" );
	_image_choice_back = drawer->createImage( "preview/preview_cursor_back.png" );
}


ChipDrawer::~ChipDrawer( ) {
}


void ChipDrawer::draw( int mx, int my, int gx, int gy, bool select ) const {
	int sy = BASE_Y + gy * CHIP_HEIGHT / 2;
	sy -= CHIP_HEIGHT * _data->getHeightData( mx, my );	//高さ
	int sx = BASE_X + gx  * CHIP_WIDTH;
	sx += ( my % 2 ) * CHIP_WIDTH / 2;	//横にずらす
	if ( select ) { // 選んでいるチップ表示
		_image_choice_back->setPos( sx, 0 );
		_image_choice_back->draw( );
	}
	int ground_num = _data->getGroundData( mx, my );
	if ( ground_num > 0 ) { //地面
		ImagePtr ground = _ground->getImage( ground_num - 1 );
		ground->setPos( sx, sy );
		ground->setRect( );
		ground->draw( );
	}
	int structure_num = _data->getStructureData( mx, my );
	if ( structure_num > 0 ) { // ストラクチャー
		ImagePtr structure = _structure->getImage( structure_num - 1 );
		int width = 0;
		int height = 0;
		structure->getImageSize( width, height );
		structure->setPos( sx, sy - height + CHIP_HEIGHT );
		structure->setRect( );
		structure->draw( );
	}

	if ( select ) {// 選んでいるチップ表示
		_image_choice_front->setPos( sx, 0 );
		_image_choice_front->draw( );
	}
}