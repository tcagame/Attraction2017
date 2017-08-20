#include "ObjectGuide.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Data.h"
#include "ObjectCursor.h"
#include "Image.h"

ObjectGuide::ObjectGuide( ImagePtr block_image, DataConstPtr data, ObjectCursorConstPtr object_cursor ) :
_data( data ),
_object_cursor( object_cursor ),
_image( block_image ) {
}


ObjectGuide::~ObjectGuide( ) {
}

void ObjectGuide::update( ) {
}

void ObjectGuide::draw( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	const int TEX_SIZE = 16;
	const int COVER_SIZE = DISP_CHIP_HEIGHT - MAP_COVER_HEIGHT;
	const int CHIP_HEIGHT_NUM = (int)( ( ( DISP_CHIP_HEIGHT - COVER_SIZE ) / 2.0 ) + 0.5 );
	for ( int i = 0; i < DISP_WIDTH / OBJECT_CHIP_SIZE; i++ ) {
		for ( int j = 0; j < PREVIEW_HEIGHT / OBJECT_CHIP_SIZE; j++ ) {
			int sx = ( i * OBJECT_CHIP_SIZE ) + PREVIEW_X;
			int sy = ( j * OBJECT_CHIP_SIZE ) + GUIDE_Y;
			int tx = 0;
			int ty = 0;

			int ox = ( i + _object_cursor->getScrollX( ) ) % ( _data->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM );
			int oy = j;
			// 選択ページ
			int adjust = _object_cursor->getScrollX( ) % PAGE_OBJECT_WIDTH_NUM;
			int now_page = ( _object_cursor->getGX( ) / PAGE_OBJECT_WIDTH_NUM ) % _data->getPageNum( );
			if ( _object_cursor->getGX( ) % PAGE_OBJECT_WIDTH_NUM >= PAGE_OBJECT_WIDTH_NUM - adjust ) {
				now_page++;
				now_page %= _data->getPageNum( );
			}
			if ( now_page == ( ( ox ) / PAGE_OBJECT_WIDTH_NUM ) % _data->getPageNum( ) ) {
				tx = 0;
				ty = 16;
			}
			unsigned char obj = _data->getObject( ox, oy );

			// 不可侵ブロック
			if ( obj == OBJECT_BLOCK ) {
				tx = 16;
				ty = 0;
			}
			// 上方侵入ブロック
			if ( obj == OBJECT_ONEWAY ) {
				tx = 16 * 2;
				ty = 0;
			}
			//エネミー配置ブロック
			if ( obj >= OBJECT_PURPLE_ZOMBIE &&
				 obj < OBJECT_ENEMY_END ) {
				tx = 16;
				ty = 32;
			}
			//イベント配置ブロック
			if ( obj >= OBJECT_EVENT_REDDAEMON ) {
				tx = 32;
				ty = 32;
			}
			_image->setRect( tx, ty, TEX_SIZE, TEX_SIZE );
			_image->setPos( sx, sy );
			_image->draw( );
		}
	}
	// カーソル
	int sx = PREVIEW_X + _object_cursor->getGX( ) * OBJECT_CHIP_SIZE;
	int sy = GUIDE_Y + _object_cursor->getGY( ) * OBJECT_CHIP_SIZE;
	if ( _object_cursor->isOnChip( ) ) {
		_image->setPos( sx, sy );
		_image->setRect( 0, 32, TEX_SIZE, TEX_SIZE );
		_image->draw( );
	}
}