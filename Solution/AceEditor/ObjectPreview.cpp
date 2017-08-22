#include "ObjectPreview.h"
#include "Drawer.h"
#include "ace_define.h"
#include "ace_enemy_rect.h"
#include "Data.h"
#include "ObjectCursor.h"

ObjectPreview::ObjectPreview( DataConstPtr data, ObjectCursorConstPtr object_cursor, ImagePtr enemy_midium_image, ImagePtr enemy_big_image, ImagePtr enemy_wide_image, ImagePtr enemy_small_image, ImagePtr image_event ) :
_data( data ),
_object_cursor( object_cursor ),
_event( image_event ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_choise = drawer->createImage( "guide/object_guide_cursor.png" );
	_block = drawer->createImage( "block/block.png" );
	_enemy[ GRAPH_ENEMY_MIDIUM ] = enemy_midium_image;
	_enemy[ GRAPH_ENEMY_BIG ] = enemy_big_image;
	_enemy[ GRAPH_ENEMY_WIDE ] = enemy_wide_image;
	_enemy[ GRAPH_ENEMY_SMALL ] = enemy_small_image;
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
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_PUPLE_ZOMBIE.tx, RECT_PUPLE_ZOMBIE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_FACE_AND_HAND ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_FACE_AND_HAND.tx, RECT_FACE_AND_HAND.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_NO_FACE ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_NO_FACE.tx, RECT_NO_FACE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_LANCER ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_LANCER.tx, RECT_LANCER.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_CROCO_SNAKE ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_CROCO_SNAKE.tx, RECT_CROCO_SNAKE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GHOUL ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_GHOUL.tx, RECT_GHOUL.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GHOST ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_GHOST.tx, RECT_GHOST.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_ONE_EYE_SNAKE ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_ONE_EYE_SNAKE.tx, RECT_ONE_EYE_SNAKE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_WHITE_MIST ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_WHITE_MIST.tx, RECT_WHITE_MIST.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GRAY_MIST ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_GRAY_MIST.tx, RECT_GRAY_MIST.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_STONE_FACE ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_STONE_FACE.tx, RECT_STONE_FACE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_NO_NECK_GHOST ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_NO_NECK_GHOST.tx, RECT_NO_NECK_GHOST.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SHISHIMAI_DAEMON ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_SHISHIMAI_DAEMON.tx, RECT_SHISHIMAI_DAEMON.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SHISHIMAI ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_SHISHIMAI.tx, RECT_SHISHIMAI.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_ARCHER ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_ARCHER.tx, RECT_ARCHER.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_HAND ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_HAND.tx, RECT_HAND.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_RED_BIRD ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_RED_BIRD.tx, RECT_RED_BIRD.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_BLUE_MONK ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_BLUE_MONK.tx, RECT_BLUE_MONK.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GREEN_ZOMBIE ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_GREEN_ZOMBIE.tx, RECT_GREEN_ZOMBIE.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_HUG_DAEMON ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_HUG_DAEMON.tx, RECT_HUG_DAEMON.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SWAMP_ZOMBIE_A ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_SWAMP_ZOMBIE_A.tx, RECT_SWAMP_ZOMBIE_A.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SWAMP_ZOMBIE_B ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_SWAMP_ZOMBIE_B.tx, RECT_SWAMP_ZOMBIE_B.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SWAMP_ZOMBIE_C ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_SWAMP_ZOMBIE_C.tx, RECT_SWAMP_ZOMBIE_C.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SKELETON ) {
				_enemy[ GRAPH_ENEMY_WIDE ]->setRect( RECT_SKELETON.tx, RECT_SKELETON.ty, BIG_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_WIDE ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_WIDE ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_LADY ) {
				_enemy[ GRAPH_ENEMY_WIDE ]->setRect( RECT_LADY.tx, RECT_LADY.ty, BIG_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_WIDE ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_WIDE ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_WIND ) {
				_enemy[ GRAPH_ENEMY_BIG ]->setRect( RECT_WIND.tx, RECT_WIND.ty, BIG_CHAR_GRAPH_SIZE, BIG_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_BIG ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_BIG ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_ONYUDO ) {
				_enemy[ GRAPH_ENEMY_BIG ]->setRect( RECT_ONYUDO.tx, RECT_ONYUDO.ty, BIG_CHAR_GRAPH_SIZE, BIG_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_BIG ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_BIG ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_JIZO ) {
				_enemy[ GRAPH_ENEMY_BIG ]->setRect( RECT_JIZO.tx, RECT_JIZO.ty, BIG_CHAR_GRAPH_SIZE, BIG_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_BIG ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_BIG ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_TREE ) {
				_enemy[ GRAPH_ENEMY_BIG ]->setRect( RECT_TREE.tx, RECT_TREE.ty, BIG_CHAR_GRAPH_SIZE, BIG_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_BIG ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_BIG ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_GAMA ) {
				_enemy[ GRAPH_ENEMY_BIG ]->setRect( RECT_GAMA.tx, RECT_GAMA.ty, BIG_CHAR_GRAPH_SIZE, BIG_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_BIG ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_BIG ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_FLOG ) {
				_enemy[ GRAPH_ENEMY_SMALL ]->setRect( RECT_FLOG.tx, RECT_FLOG.ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_SMALL ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_SMALL ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_BAT ) {
				_enemy[ GRAPH_ENEMY_SMALL ]->setRect( RECT_BAT.tx, RECT_BAT.ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_SMALL ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_SMALL ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_STONE ) {
				_enemy[ GRAPH_ENEMY_SMALL ]->setRect( RECT_STONE.tx, RECT_STONE.ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_SMALL ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_SMALL ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_MOTH ) {
				_enemy[ GRAPH_ENEMY_SMALL ]->setRect( RECT_MOTH.tx, RECT_MOTH.ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_SMALL ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_SMALL ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_EYE_DAEMON ) {
				_enemy[ GRAPH_ENEMY_SMALL ]->setRect( RECT_EYE_DAEMON.tx, RECT_EYE_DAEMON.ty, SMALL_CHAR_GRAPH_SIZE, SMALL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_SMALL ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( SMALL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_SMALL ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_SHELL ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_SHELL.tx, RECT_SHELL.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_WATER_GHOST ) {
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setRect( RECT_WATER_GHOST.tx, RECT_WATER_GHOST.ty, NORMAL_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_MIDIUM ]->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_RAY ) {
				_enemy[ GRAPH_ENEMY_WIDE ]->setRect( RECT_RAY.tx, RECT_RAY.ty, BIG_CHAR_GRAPH_SIZE, NORMAL_CHAR_GRAPH_SIZE );
				_enemy[ GRAPH_ENEMY_WIDE ]->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - ( BIG_CHAR_GRAPH_SIZE / 2 ), PREVIEW_Y + j * OBJECT_CHIP_SIZE - ( NORMAL_CHAR_GRAPH_SIZE - OBJECT_CHIP_SIZE ) );
				_enemy[ GRAPH_ENEMY_WIDE ]->draw( );
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

			//event
			if ( _data->getObject( ox, oy ) == OBJECT_EVENT_REDDAEMON ) {
				_event->setRect( 0, 0, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_EVENT_FIRE ) {
				_event->setRect( 32, 0, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_EVENT_TREE ) {
				_event->setRect( 64, 0, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_EVENT_ROCK ) {
				_event->setRect( 96, 0, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_EVENT_SHOP ) {
				_event->setRect( 0, 32, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
			}
			if ( _data->getObject( ox, oy ) == OBJECT_EVENT_LAKE ) {
				_event->setRect( 32, 32, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
			}if ( _data->getObject( ox, oy ) == OBJECT_EVENT_RYUGU ) {
				_event->setRect( 64, 32, 32, 32 );
				_event->setPos( PREVIEW_X + i * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE / 2, PREVIEW_Y + j * OBJECT_CHIP_SIZE - OBJECT_CHIP_SIZE );
				_event->draw( );
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