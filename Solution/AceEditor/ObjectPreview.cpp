#include "ObjectPreview.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Data.h"
#include "ObjectCursor.h"

ObjectPreview::ObjectPreview( DataConstPtr data, ObjectCursorConstPtr object_cursor ) :
_data( data ),
_object_cursor( object_cursor ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_block = drawer->createImage( "block/block.png" );
	_choise = drawer->createImage( "guide/object_guide_cursor.png" );
}

ObjectPreview::~ObjectPreview( ) {
}

void ObjectPreview::draw( ) const {
	for ( int i = 0; i < OBJECT_CHIP_WIDTH_NUM; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			int ox = ( i + _object_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM );
			int oy = j;
			if ( _data->getBlockData( ox, oy ) == OBJECT_BLOCK ) {
				_block->setPos( PREVIEW_X + i * OBJECT_GUIDE_SIZE, PREVIEW_Y + j * OBJECT_GUIDE_SIZE );
				_block->draw( );
			}
			if ( _object_cursor->getGX( )  == ox
				 && _object_cursor->getGY( ) == oy ) {
				_choise->setPos( PREVIEW_X + ox * OBJECT_GUIDE_SIZE, PREVIEW_Y + oy * OBJECT_GUIDE_SIZE );
				_choise->setRect( 16, 16, 16, 16 );
				_choise->draw( );
			}
		}
	}
}