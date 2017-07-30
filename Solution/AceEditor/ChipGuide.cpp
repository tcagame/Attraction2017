#include "ChipGuide.h"
#include "Drawer.h"
#include "Data.h"
#include "ChipCursor.h"
#include "ChipEditor.h"
#include "LoadCSV.h"
#include "Image.h"

ChipGuide::ChipGuide( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor ) :
_data( data ),
_chip_cursor( chip_cursor ),
_chip_editor( chip_editor ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_chip_guide = drawer->createImage( "guide/guide_chip.png" );

	LoadCSV structure( "Resource/Ace/Editor/structure/structure_list", STRUCTURE_LIST_NUM );
	for ( int i = 0; i < structure.getSize( ); i++ ) {
		std::string path = structure.getData( i );
		_struct_graph_data[ i ] = ( path != "" );
	}

	LoadCSV ground( "Resource/Ace/Editor/ground/ground_list", GROUND_LIST_NUM );
	for ( int i = 0; i < ground.getSize( ); i++ ) {
		std::string path = ground.getData( i );
		_ground_graph_data[ i ] = ( path != "" );
	}
}


ChipGuide::~ChipGuide( ) {
}

void ChipGuide::update( ) {

}

void ChipGuide::draw( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	
	std::vector< int > select_gx;
	std::vector< int > select_gy;
	_chip_editor->getReplacePos( select_gx, select_gy );
	int range = _chip_editor->getRange( );
	int check_num = range * range;

	for ( int i = 0; i < DISP_CHIP_WIDTH; i++ ) {
		for ( int j = 0; j < DISP_CHIP_HEIGHT; j++ ) {
			int gx = i;
			int gy = j;
			int mx = ( gx + _chip_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_CHIP_WIDTH_NUM );
			int my = gy;
			int tx = 0;
			int ty = 0;
			int height = 0;
			// 選択ページ
			int adjust = _chip_cursor->getScrollX( ) % PAGE_CHIP_WIDTH_NUM;
			int now_page = ( _chip_cursor->getGX( ) / PAGE_CHIP_WIDTH_NUM ) % _data->getPageNum( );
			if ( _chip_cursor->getGX( ) % PAGE_CHIP_WIDTH_NUM >= PAGE_CHIP_WIDTH_NUM - adjust ) {
				now_page++;
				now_page %= _data->getPageNum( );
			}
			if ( now_page == ( ( gx + adjust ) / PAGE_CHIP_WIDTH_NUM ) % _data->getPageNum( ) ) {
				ty = 48;
			}
			// たろすけが歩ける
			if ( gy >= MAP_COVER_HEIGHT ) {
				ty = 32;
			}
			// 選択チップ
			for ( int k = 0; k < check_num; k++ ) {
				if ( gx == select_gx[ k ] && gy == select_gy[ k ] ) {
					ty = 16;
				}
			}
			if ( _data->getGround( mx, my ) > 0 && _ground_graph_data[ _data->getGround( mx, my ) - 1 ] ) {
				tx += 64;
				height = _data->getHeight( mx, my );
			}
			if ( _data->getStructure( mx, my ) > 0 && _struct_graph_data[ _data->getStructure( mx, my ) - 1 ] ) {
				tx += 128;
			}
			int sx = GUIDE_X + gx * CHIP_WIDTH;
			int sy = GUIDE_Y + gy * CHIP_HEIGHT / 2;
			sx += ( gy % 2 ) * CHIP_WIDTH / 2;	//横にずらす

			_image_chip_guide->setPos( sx, sy );
			_image_chip_guide->setRect( tx, ty, CHIP_WIDTH, CHIP_HEIGHT );
			_image_chip_guide->draw( );
			if ( height > 0 ) {
				drawer->drawString( sx + CHIP_WIDTH / 2, sy, "%d", height );
			}
		}
	}
}
