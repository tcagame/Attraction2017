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
	_enemy = drawer->createImage( "../Enemy/enemy_medium.png" );
	_choise = drawer->createImage( "guide/object_guide_cursor.png" );
}

ObjectPreview::~ObjectPreview( ) {
}

void ObjectPreview::draw( ) const {
	for ( int i = 0; i < OBJECT_CHIP_WIDTH_NUM; i++ ) {
		for ( int j = 0; j < OBJECT_CHIP_HEIGHT_NUM; j++ ) {
			int ox = ( i + _object_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM );
			int oy = j;
			if ( _data->getObject( ox, oy ) == OBJECT_BLOCK ) {
				_block->setRect( 0, 16, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
				_block->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE, PREVIEW_Y + j * OBJECT_CHIP_SIZE );
				_block->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_ONEWAY ) {
				_block->setRect( 16, 0, OBJECT_CHIP_SIZE, OBJECT_CHIP_SIZE );
				_block->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE, PREVIEW_Y + j * OBJECT_CHIP_SIZE );
				_block->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_ENEMY ) {
				_enemy->setRect( 0, 64 ,NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _object_cursor->getGX( )  == ox
				 && _object_cursor->getGY( ) == oy ) {
				_choise->setPos( PREVIEW_X + ox * OBJECT_CHIP_SIZE, PREVIEW_Y + oy * OBJECT_CHIP_SIZE );
				_choise->setRect( 0, 32, 16, 16 );
				_choise->draw( );
			}
		}
	}
}