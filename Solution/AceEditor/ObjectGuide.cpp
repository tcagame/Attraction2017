#include "ObjectGuide.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Data.h"
#include "ObjectCursor.h"
#include "Image.h"

ObjectGuide::ObjectGuide( DataConstPtr data, ObjectCursorConstPtr object_cursor ) :
_data( data ),
_object_cursor( object_cursor ) {
	DrawerPtr drawer = Drawer::getTask( );
	_image = drawer->createImage( "guide/object_guide_cursor.png" );
}


ObjectGuide::~ObjectGuide( ) {
}

void ObjectGuide::update( ) {
}

void ObjectGuide::draw( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	// block表示
	for ( int i = 0; i < OBJECT_CHIP_WIDTH_NUM; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			int ox = ( i + _object_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM );
			int oy = j;
			if ( _data->getBlockData( ox, oy ) == OBJECT_BLOCK ) {
				_image->setPos( PREVIEW_X + i * OBJECT_GUIDE_SIZE, GUIDE_Y + j * OBJECT_GUIDE_SIZE );
				_image->setRect( 0, 0, 16, 16 );
				_image->draw( );
			}
		}
	}
	// カーソル
	int sx = PREVIEW_X + _object_cursor->getGX( ) * OBJECT_GUIDE_SIZE;
	int sy = GUIDE_Y + _object_cursor->getGY( ) * OBJECT_GUIDE_SIZE;
	if ( _object_cursor->getGX( ) >= 0 ||
		 _object_cursor->getGY( ) >= 0 ) {
		_image->setPos( sx, sy );
		_image->setRect( 16, 16, 16, 16 );
		_image->draw( );
	}
	// ライン
	const int COVER_SIZE = DISP_CHIP_HEIGHT - MAP_COVER_HEIGHT;
	const int CHIP_HEIGHT_NUM = (int)( ( ( DISP_CHIP_HEIGHT - COVER_SIZE ) / 2.0 ) + 0.5 );
	for ( int i = 0; i <= DISP_WIDTH / OBJECT_GUIDE_SIZE; i++ ) {
		for ( int j = 0; j <= CHIP_HEIGHT_NUM; j++ ) {
			// 縦ライン
			int x = i * OBJECT_GUIDE_SIZE + PREVIEW_X;
			drawer->drawLine( x, GUIDE_Y, x, GUIDE_Y + ( OBJECT_GUIDE_SIZE * CHIP_HEIGHT_NUM ) );
			// 横ライン
			int y = j * OBJECT_GUIDE_SIZE + GUIDE_Y;
			drawer->drawLine( PREVIEW_X, y, PREVIEW_X + DISP_WIDTH, y );
		}
	}
}