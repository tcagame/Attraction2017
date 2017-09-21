#include "ViewerConsole.h"
#include "Application.h"
#include "Drawer.h"
#include "ViewerObject.h"
#include "ViewerStreet.h"
#include "ViewerEvent.h"
#include "ViewerStatus.h"
#include "SynchronousData.h"
#include "Client.h"
#include "Sound.h"

const char * FILENAME[ ] = {
	"Result/heaven/heaven_tarosuke.png",
	"Result/heaven/heaven_tarojiro.png",
	"Result/heaven/heaven_tgarisuke.png",
	"Result/heaven/heaven_taromi.png",
	"Result/human/human_tarosuke.png",
	"Result/human/human_tarojiro.png",
	"Result/human/human_tgarisuke.png",
	"Result/human/human_taromi.png",
	"Result/hungry/hungry_tarosuke.png",
	"Result/hungry/hungry_tarojiro.png",
	"Result/hungry/hungry_tgarisuke.png",
	"Result/hungry/hungry_taromi.png",
	"Result/damn/damn_tarosuke.png",
	"Result/damn/damn_tarojiro.png",
	"Result/damn/damn_tgarisuke.png",
	"Result/damn/damn_taromi.png",
	"Result/hell/hell_tarosuke.png",
	"Result/hell/hell_tarojiro.png",
	"Result/hell/hell_tgarisuke.png",
	"Result/hell/hell_taromi.png",
};













const int AREA_SX  = 0;
const int AREA_SY  = 480 - 256;

ViewerConsolePtr ViewerConsole::getTask( ) {
	return std::dynamic_pointer_cast< ViewerConsole >( Application::getInstance( )->getTask( getTag( ) ) );
}

ViewerConsole::ViewerConsole( PLAYER player ) :
_player( player ),
_ending_type( -1 ) {
	_dead_se = { false };
}

ViewerConsole::~ViewerConsole( ) {
}

void ViewerConsole::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );

	_viewer_object = ViewerObjectPtr( new ViewerObject );
	_viewer_street = ViewerStreetPtr( new ViewerStreet );
	_viewer_event  = ViewerEventPtr	( new ViewerEvent );
	_viewer_status = ViewerStatusPtr( new ViewerStatus );

	_image_bar_upper = drawer->createImage( "UI/ui_bar.png" );
	_image_bar_upper->setRect( 0, 0, 640, 8 );
	_image_bar_upper->setPos( 0, 0 );

	_image_bar_lower = drawer->createImage( "UI/ui_bar.png" );
	_image_bar_lower->setRect( 0, 0, 640, 8 );
	_image_bar_lower->setPos( 0, 208 + 8 );

	_image_minimap = drawer->createImage( "UI/ui_minimap.png" );
	_image_minimap->setRect( 0, 0, 320, 208 );
	_image_minimap->setPos( 320, 8 );
	
	_image_device = drawer->createImage( "UI/ui_device.png" );
	
	_image_entry = drawer->createImage( "UI/ui_entry.png" );
	_image_opening = drawer->createImage( "UI/ui_tutorial.png" );
	_image_opening->setPos( 0, 480 - 256 );
	int w, h;
	_image_device->getImageSize( w, h );
	_image_device->setPos( ( 640 - w ) / 2, ( 480 - h ) / 2 );
}

void ViewerConsole::update( ) {
	ClientPtr client( Client::getTask( ) );
	DrawerPtr drawer( Drawer::getTask( ) );
	
	// ステータス描画
	if ( Client::getTask( )->getPhase( ) != "PHASE_CONNECTING" ) {
		Drawer::getTask( )->drawString( 0, 0, "NOT_CONNECTING" );
		drawer->flip( );
		return;
	}
	if ( !client->isRecievingUDP( ) ) {
		return;
	}

	drawer->flip( );

	drawConsole( );
	drawDevice( );

	playSe( );
}

void ViewerConsole::drawConsole( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	unsigned char state = data->getStatusState( _player );

	switch ( state ) {
	case SynchronousData::STATE_PLAY_STREET:
		drawAreaStreet( );
		break;
	case SynchronousData::STATE_PLAY_EVENT:
		drawAreaEvent( );
		break;
	case SynchronousData::STATE_OPENING:
		drawOpening( );
		break;
	case SynchronousData::STATE_CONTINUE:
		drawContinue( );
		break;
	}	

	_image_bar_upper->draw( );
	_image_bar_lower->draw( );

	_viewer_status->draw( _player, 0, 8 );
	_image_minimap->draw( );
	
	if ( state == SynchronousData::STATE_ENDING ) {
		int type = data->getStatusRedo( _player );
		if ( type > 4 ) {
			type = 4;
		}
		type = _player + type * MAX_PLAYER;
		if ( _ending_type != type ) {
			_image_ending = Drawer::getTask( )->createImage( FILENAME[ type ] );
			_ending_type = type;
		}
		_image_ending->draw( );
	}
}

void ViewerConsole::drawAreaStreet( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	int camera_pos = data->getStatusX( _player ) - 320;
	int offset_x = data->getStatusX( _player ) - data->getCameraX( ) - 320;
	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK, AREA_SX, AREA_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, AREA_SX - offset_x, AREA_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT, AREA_SX, AREA_SY, camera_pos );
}

void ViewerConsole::drawAreaEvent( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	// イベント描画
	EVENT event = data->getEvent( );
	if ( event == EVENT_NONE ) {
		return;
	}

	int camera_pos = data->getStatusX( _player ) - 320;
	if ( camera_pos < 0 ) {
		camera_pos = 0;
	}
	if ( camera_pos > 1280 - 640 - 1 ) {
		camera_pos = 1280 - 640 - 1;
	}

	_viewer_event->draw( event, AREA_SX - camera_pos, AREA_SY );
	_viewer_object->draw( AREA_EVENT, AREA_SX - camera_pos, AREA_SY );
}

void ViewerConsole::drawDevice( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	if ( data->getStatusDevice( _player ) < 0 ) {
		_image_device->draw( );
	}
}

void ViewerConsole::drawOpening( ) {
	_image_opening->draw( );
}

void ViewerConsole::drawContinue( ) {
}


void ViewerConsole::playSe( ) {
	SynchronousDataPtr data = SynchronousData::getTask( );
	SoundPtr sound = Sound::getTask( );
	if ( data->getStatusPower( _player ) <= 4 ) {
		if( !sound->isPlayingSE( "yokai_se_02.wav" ) ) {
			sound->playSE( "yokai_se_02.wav" );
		}
	}
	
	if ( data->getStatusPower( _player ) == 0 || data->getStatusPower( _player ) > 4  ) {
		sound->stopSE( "yokai_se_02.wav" );
	}

	if ( _dead_se[ _player ] ) {
		_dead_se[ _player ] = false;
	}

	if ( data->getStatusPower( _player ) == 0 ) {
		if ( !_dead_se[ _player ] ) {
	//		sound->playSE( "yokai_se_31.wav" );
			_dead_se[ _player ] = true;
		}
	}
}