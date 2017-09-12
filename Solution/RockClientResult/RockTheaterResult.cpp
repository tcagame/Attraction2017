#include "RockTheaterResult.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "Image.h"
#include "Status.h"

const int MONITOR_Y = 256;
const int ONE_MONITOR_WIDTH = SCREEN_WIDTH / 3;
const int INFO_HEIGHT = SCREEN_HEIGHT - 256;

RockTheaterResult::RockTheaterResult( StatusPtr status ) :
_play( true ),
_status( status ) {
}


RockTheaterResult::~RockTheaterResult( ) {
}

void RockTheaterResult::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	MoviePtr movie = drawer->createMovie( "result/ui_main_title_tall.mov" );
	_images.push_back( drawer->createImage( "result/play_monitor.JPG" ) );
	_images.push_back( drawer->createImage( "UI/breast1.png" ) );
	_images.push_back( drawer->createImage( "UI/breast2.png" ) );
	_images.push_back( drawer->createImage( "UI/breast3.png" ) );
	_images.push_back( drawer->createImage( "UI/breast4.png" ) );
	_images.push_back( drawer->createImage( "result/ui_cover_entry.png" ) );

	for ( int i = 0; i < ( int )_images.size( ); i++ ) {
		int width = 0;
		int height = 0;
		_images[ i ]->getImageSize( width, height );
		_images[ i ]->setRect( 0, 0, width, height );
	}
	_draw_image = ImagePtr( new Image( ) );
	_draw_image->createGraph( SCREEN_WIDTH, INFO_HEIGHT );
	setMovie( movie );
	playMovie( );
	createImage( );
}

void RockTheaterResult::update( ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if( player->isActive( ) ) {
			stopMovie( );
			_play = false;
			return;
		}
	}
	if ( !_play ) {
		playMovie( );
	}
	createImage( );
}

void RockTheaterResult::createImage( ) {
	_draw_image->clearToGraph( );

	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		Status::Player player = _status->getPlayer( i );
		int sx = 0;
		int sy = 0;
		switch ( player.area ) {
		case AREA_WAIT:
			sx = i * ( SCREEN_WIDTH / 4 );
			sy = 0;
			_images[ 5 ]->setPos( sx + 100, sy, sx + ( SCREEN_WIDTH / 4 ), sy + 100 );
			_draw_image->drawSpriteToGraph( _images[ 5 ] );
			break;
		case AREA_ENTRY:
			sx = i * 100;
			sy = 100;
			break;
		case AREA_STREET_1:
		case AREA_STREET_3:
			sx = i * 100 + ONE_MONITOR_WIDTH * 1;
			sy = 100;
			break;
		case AREA_STREET_2:
			sx = i * 100 + ONE_MONITOR_WIDTH * 2;
			sy = 100;
			break;
		default:
			continue;
		}
		_images[ i + 1 ]->setPos( sx, sy, sx + 100, sy + 100 );
		_draw_image->drawSpriteToGraph( _images[ i + 1 ] );
	}

	_images[ 0 ]->setPos( 0, INFO_HEIGHT - 256 );
	_draw_image->drawSpriteToGraph( _images[ 0 ] );

	_draw_image->setPos( 0, 256 );
	setImage( _draw_image );
}
 
