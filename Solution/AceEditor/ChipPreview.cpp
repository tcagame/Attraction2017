#include "ChipPreview.h"
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

const int BASE_X = - CHIP_WIDTH / 2;
const int BASE_Y = - CHIP_HEIGHT / 2;
const std::string EDITOR_PATH = "../Resource/Ace/Editor/";

ChipPreview::ChipPreview( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor, GroundConstPtr ground, StructureConstPtr structure ) :
_data( data ),
_covor( true ),
_chip_cursor( chip_cursor ),
_chip_editor( chip_editor ),
_ground( ground ),
_structure( structure ) {
	DrawerPtr drawer = Drawer::getTask( );
	_image_choice_front = drawer->createImage( "preview/preview_cursor_front.png" );
	_image_choice_back = drawer->createImage( "preview/preview_cursor_back.png" );
	_image_background = ImageTargetPtr( new ImageTarget );
	_image_background->create( DISP_WIDTH, PREVIEW_HEIGHT );
}


ChipPreview::~ChipPreview( ) {
}

void ChipPreview::update( ) {
	KeyboardPtr key = Keyboard::getTask( );
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
			int mx = ( j + _chip_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_CHIP_WIDTH_NUM );
			int my = i;
			if ( !_covor && my >= MAP_COVER_HEIGHT ) {
				break;
			}
			int sy = BASE_Y + i * CHIP_HEIGHT / 2;
			sy -= CHIP_HEIGHT * _data->getHeightData( mx, my );	//高さ
			int sx = BASE_X + j * CHIP_WIDTH;
			sx += ( my % 2 ) * CHIP_WIDTH / 2;	//横にずらす
			bool select = false;
			for ( int k = 0; k < check_num; k++ ) {
				if ( j == select_gx[ k ] && i == select_gy[ k ] ) {
					select = true;
				}
			}
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
	}
	{//作成した画像を描画
		drawer->setImageTarget( );
		_image_background->setPos( PREVIEW_X, PREVIEW_Y );
		_image_background->draw( );
	}
}