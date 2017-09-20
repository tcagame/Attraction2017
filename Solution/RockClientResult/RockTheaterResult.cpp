#include "RockTheaterResult.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "ImageTarget.h"
#include "Status.h"
#include "MessageSender.h"

const int MONITOR_Y = 256;
const int ONE_MONITOR_WIDTH = SCREEN_WIDTH / 3;
const int INFO_HEIGHT = SCREEN_HEIGHT - 256;
const int ENDING_WIDTH = 640;
const int ENDING_HEIGHT = 480;
const int ENDING_SCREEN_X = SCREEN_WIDTH / 2 - ENDING_WIDTH / 2;
const int ENDING_SCREEN_Y = SCREEN_HEIGHT / 2 - ENDING_HEIGHT / 2;
const int SHOWN_RANGE = 100;
const int EXIT_TIME = 6000;
const int INIT_ENDING_VY = 0;
const int INIT_OFFSET_Y = 500;

RockTheaterResult::RockTheaterResult( StatusPtr status ) :
_play( true ),
_ending_index( 0 ),
_ending_time( 0 ),
_offset_y( INIT_OFFSET_Y ),
_ending_vy( INIT_ENDING_VY ),
_shown( false ),
_status( status ) {
}


RockTheaterResult::~RockTheaterResult( ) {
}

void RockTheaterResult::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	MoviePtr movie = drawer->createMovie( "result/ui_main_title.mp4" );
	_images.push_back( drawer->createImage( "result/play_monitor.JPG" ) );
	_images.push_back( drawer->createImage( "UI/breast1.png" ) );
	_images.push_back( drawer->createImage( "UI/breast2.png" ) );
	_images.push_back( drawer->createImage( "UI/breast3.png" ) );
	_images.push_back( drawer->createImage( "UI/breast4.png" ) );
	_images.push_back( drawer->createImage( "result/ui_cover_entry.png" ) );

	_end_image.push_back( drawer->createImage( "result/heaven/heaven1.png" ) );
	_end_image.push_back( drawer->createImage( "result/human/human1.png" ) );
	_end_image.push_back( drawer->createImage( "result/damn/damn1.png" ) );
	_end_image.push_back( drawer->createImage( "result/hungry/hungry1.png" ) );
	_end_image.push_back( drawer->createImage( "result/hell/hell1.png" ) );

	_end_image.push_back( drawer->createImage( "result/heaven/heaven2.png" ) );
	_end_image.push_back( drawer->createImage( "result/human/human2.png" ) );
	_end_image.push_back( drawer->createImage( "result/damn/damn2.png" ) );
	_end_image.push_back( drawer->createImage( "result/hungry/hungry2.png" ) );
	_end_image.push_back( drawer->createImage( "result/hell/hell2.png" ) );

	_end_image.push_back( drawer->createImage( "result/heaven/heaven3.png" ) );
	_end_image.push_back( drawer->createImage( "result/human/human3.png" ) );
	_end_image.push_back( drawer->createImage( "result/damn/damn3.png" ) );
	_end_image.push_back( drawer->createImage( "result/hungry/hungry3.png" ) );
	_end_image.push_back( drawer->createImage( "result/hell/hell3.png" ) );

	_end_image.push_back( drawer->createImage( "result/heaven/heaven4.png" ) );
	_end_image.push_back( drawer->createImage( "result/human/human4.png" ) );
	_end_image.push_back( drawer->createImage( "result/damn/damn4.png" ) );
	_end_image.push_back( drawer->createImage( "result/hungry/hungry4.png" ) );
	_end_image.push_back( drawer->createImage( "result/hell/hell4.png" ) );

	for ( int i = 0; i < _end_image.size( ); i++ ) {
		_end_image[ i ]->setPos( ENDING_SCREEN_X, ENDING_SCREEN_Y );
	}
	for ( int i = 0; i < ( int )_images.size( ); i++ ) {
		int width = 0;
		int height = 0;
		_images[ i ]->getImageSize( width, height );
		_images[ i ]->setRect( 0, 0, width, height );
	}
	_draw_image = ImageTargetPtr( new ImageTarget( ) );
	_draw_image->create( SCREEN_WIDTH, INFO_HEIGHT );
	_draw_image->setPos( 0, 256 );
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
			setImage( ImagePtr( ) );
			if ( !_shown ) {
				_shown = isShown( player->getPos( ) );
			}
			if ( _shown ) {
				createEndingImage( );
				updateEnding( );
				if ( _status->getPlayer( i ).device_button ) {
					exitClient( i );
				}
			}
			if ( _ending_time > EXIT_TIME ) {
				exitClient( i );
			}
			return;
		}
	}
	if ( !_play ) {
		playMovie( );
	}
	_ending_time = 0;
	_shown = false;
	createImage( );
}

void RockTheaterResult::createImage( ) {
	_draw_image->clear( );
	Drawer::getTask( )->setImageTarget( _draw_image );
	
	_images[ 0 ]->setPos( 0, INFO_HEIGHT - 256 );
	_images[ 0 ]->draw( );

	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		Status::Player player = _status->getPlayer( i );
		int sx = 0;
		int sy = 30;
		switch ( player.area ) {
		case AREA_WAIT:
			sx = i * ( SCREEN_WIDTH / 4 );
			sy += 0;
			_images[ 5 ]->setPos( sx + 100, sy, sx + ( SCREEN_WIDTH / 4 ), sy + 100 );
			_images[ 5 ]->draw( );
			break;
		case AREA_ENTRY:
			sx = i * 100;
			sy += 120;
			break;
		case AREA_STREET_1:
		case AREA_STREET_3:
			sx = i * 100 + ONE_MONITOR_WIDTH * 1;
			sy += 120;
			break;
		case AREA_STREET_2:
			sx = i * 100 + ONE_MONITOR_WIDTH * 2;
			sy += 120;
			break;
		default:
			continue;
		}
		_images[ i + 1 ]->setPos( sx, sy, sx + 100, sy + 100 );
		_images[ i + 1 ]->draw( );
	}
		
	Drawer::getTask( )->setImageTarget( ImageTargetPtr( ) );

	setImage( _draw_image );
}

void RockTheaterResult::createEndingImage( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		Status::Player player = _status->getPlayer( i );
		if ( player.area == AREA_RESULT ) {
			switch ( player.continue_num ) {
			case 0:
				_ending_index = ENDING_HEAVEN + i * 5;
				break;
			case 1:
			case 2:
				_ending_index = ENDING_HUMAN + i * 5;
				break;
			case 3:
			case 4:
				_ending_index = ENDING_BRUET + i * 5;
				break;
			case 5:
			case 6:
				_ending_index = ENDING_BRAD + i * 5;
				break;
			default:
				_ending_index = ENDING_HELL + i * 5;
				break;
			}
		}
	}

	setImage( _end_image[ _ending_index ] );
}

void RockTheaterResult::updateEnding( ) {
	_ending_time++;

	_ending_vy--;
	_offset_y += _ending_vy;
	if ( _offset_y < 60 ) {
		_offset_y = 60;
		_ending_vy = -_ending_vy * 3 / 5;
	}

	int sx = ENDING_SCREEN_X;
	int sy = ENDING_SCREEN_Y - _offset_y;
	_end_image[ _ending_index ]->setPos( sx, sy );
}

bool RockTheaterResult::isShown( const Vector& pos ) {
	Vector shown_pos( 270, 140, 20 );
	Vector distance = pos - shown_pos;
	if ( distance.getLength2( ) < SHOWN_RANGE * SHOWN_RANGE ) {
		return true;
	}
	return false;
}

void RockTheaterResult::exitClient( int player ) {
	_shown = false;
	_ending_vy = INIT_ENDING_VY;
	_offset_y = INIT_OFFSET_Y;
	unsigned char area = AREA_WAIT;
	MessageSender::getTask( )->sendMessage( player, Message::COMMAND_AREA, &area );
}
