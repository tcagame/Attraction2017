#include "ObjectPreview.h"
#include "Drawer.h"
#include "ace_define.h"
#include "ace_enemy_rect.h"
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
			// エネミー
			if ( _data->getObject( ox, oy ) == OBJECT_PURPLE_ZOMBIE ) {
				_enemy->setRect( RECT_PUPLE_ZOMBIE.tx, RECT_PUPLE_ZOMBIE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_FACE_AND_HAND ) {
				_enemy->setRect( RECT_FACE_AND_HAND.tx, RECT_FACE_AND_HAND.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_NO_FACE ) {
				_enemy->setRect( RECT_NO_FACE.tx, RECT_NO_FACE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_LANCER ) {
				_enemy->setRect( RECT_LANCER.tx, RECT_LANCER.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_CROCO_SNAKE ) {
				_enemy->setRect( RECT_CROCO_SNAKE.tx, RECT_CROCO_SNAKE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GHOUL ) {
				_enemy->setRect( RECT_GHOUL.tx, RECT_GHOUL.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GHOST ) {
				_enemy->setRect( RECT_GHOST.tx, RECT_GHOST.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_ONE_EYE_SNAKE ) {
				_enemy->setRect( RECT_ONE_EYE_SNAKE.tx, RECT_ONE_EYE_SNAKE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy->draw( );
			}

			// オブジェクトブロック
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

			// 選択カーソル
			if ( _object_cursor->getGX( )  == ox
				 && _object_cursor->getGY( ) == oy ) {
				_choise->setPos( PREVIEW_X + ox * OBJECT_CHIP_SIZE, PREVIEW_Y + oy * OBJECT_CHIP_SIZE );
				_choise->setRect( 0, 32, 16, 16 );
				_choise->draw( );
			}
		}
	}
}