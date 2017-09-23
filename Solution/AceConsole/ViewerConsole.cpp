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
	
	_image_bustup[ PLAYER_TAROSUKE ] = drawer->createImage( "UI/ui_bustup_tarosuke.png" );
	_image_bustup[ PLAYER_TAROJIRO ] = drawer->createImage( "UI/ui_bustup_tarojiro.png" );
	_image_bustup[ PLAYER_GARISUKE ] = drawer->createImage( "UI/ui_bustup_garisuke.png" );
	_image_bustup[ PLAYER_TAROMI   ] = drawer->createImage( "UI/ui_bustup_taromi.png"   );

	_image_message[ MESSAGE_GAMBLE0 ] = drawer->createImage( "UI/ui_dialogue_gamble.png" );
	_image_message[ MESSAGE_GAMBLE1 ] = drawer->createImage( "UI/ui_dialogue_gamble_han.png" );
	_image_message[ MESSAGE_GAMBLE2 ] = drawer->createImage( "UI/ui_dialogue_gamble_tyou.png" );
	_image_message[ MESSAGE_MIKO    ] = drawer->createImage( "UI/ui_dialogue_miko.png" );
	_image_message[ MESSAGE_RYUGU   ] = drawer->createImage( "UI/ui_dialogue_otohime.png" );
	_image_message[ MESSAGE_ENMA    ] = drawer->createImage( "UI/ui_dialogue1.png" );
	_image_message[ MESSAGE_BUDHA   ] = drawer->createImage( "UI/ui_dialogue2.png" );
	
	for ( int i = 0; i < MAX_MESSAGE; i++ ) {
		_image_message[ i ]->setRect( 0, 0, 320, 208 );
		_image_message[ i ]->setPos( 640 / 2, 7 );
	}

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

	_image_continue = drawer->createImage( "UI/ui_continue.png" );
	_image_continue->setPos( 0, 480 - 256 );
	
	_image_redo = drawer->createImage( "UI/ui_continue_picture.png" );

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
	case SynchronousData::STATE_CONTINUE:
	case SynchronousData::STATE_CONTINUE_FADE:
		Sound::getTask( )->stopBGM( );
	case SynchronousData::STATE_PLAY_STREET:
		drawAreaStreet( );
		break;
	case SynchronousData::STATE_PLAY_EVENT:
		drawAreaEvent( );
		break;
	case SynchronousData::STATE_OPENING:
		drawOpening( );
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

	int count = data->getStatusProgressCount( _player );
	if ( state == SynchronousData::STATE_ENTRY ) {
		_image_entry->draw( );
		int x = ( 640 - 122 ) / 2;
		int y = 100;
		int height = 138 * count / 100;
		_image_bustup[ _player ]->setRect( 0, 0, 122, 138 );
		_image_bustup[ _player ]->setPos( x, y );
		_image_bustup[ _player ]->setBlend( Image::BLEND_NONE, 0 );
		_image_bustup[ _player ]->draw( );
		_image_bustup[ _player ]->setRect( 0, 138 - height, 122, height);
		_image_bustup[ _player ]->setPos( x, y + 138 - height );
		_image_bustup[ _player ]->setBlend( Image::BLEND_ADD, 1.0 );
		_image_bustup[ _player ]->draw( );
	}
	if ( state == SynchronousData::STATE_CONTINUE_FADE ) {
		_image_continue->setBlend( Image::BLEND_ALPHA, 0.8 * count / 100 );
		_image_continue->draw( );
	}
	if ( state == SynchronousData::STATE_CONTINUE ) {
		_image_continue->setBlend( Image::BLEND_NONE, 0 );
		_image_continue->draw( );
		int x = 640 / 2;
		int y = 480 - 256 + 100;
		_image_redo->setRect( 0, 0, 32, 32 );
		_image_redo->setPos( x - count, y - count, x + count, y + count );
		_image_redo->draw( );
	}
	drawMessage( );
}

void ViewerConsole::drawAreaStreet( ) {
	Sound::getTask( )->stopBGM( );
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	int camera_pos = data->getStatusX( _player ) - 320;
	int offset_x = data->getStatusX( _player ) - data->getCameraX( ) - 320;
	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK, AREA_SX, AREA_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, AREA_SX - offset_x, AREA_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT, AREA_SX, AREA_SY, camera_pos );
}

void ViewerConsole::drawAreaEvent( ) {
	Sound::getTask( )->stopBGM( );
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
	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingBGM( ) ) {
		sound->playBGM( "yokai_music_05.wav" );
	}
	double ratio = SynchronousData::getTask( )->getStatusProgressCount( _player ) * 0.01;
	_image_opening->setBlend( Image::BLEND_ALPHA, ratio );
	_image_opening->draw( );
}

void ViewerConsole::drawMessage( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	switch ( data->getMessage( ) ) {
	case SynchronousData::MES_NONE:
		break;
	case SynchronousData::MES_GAMBLE0:
		_image_message[ MESSAGE_GAMBLE0 ]->draw( );
		break;
	case SynchronousData::MES_GAMBLE1:
		_image_message[ MESSAGE_GAMBLE1 ]->draw( );
		break;
	case SynchronousData::MES_GAMBLE2:
		_image_message[ MESSAGE_GAMBLE2 ]->draw( );
		break;
	case SynchronousData::MES_MIKO:
		_image_message[ MESSAGE_MIKO ]->draw( );
		break;
	case SynchronousData::MES_RYUGU:
		_image_message[ MESSAGE_RYUGU ]->draw( );
		break;
	case SynchronousData::MES_ENMA:
		_image_message[ MESSAGE_ENMA ]->draw( );
		break;
	case SynchronousData::MES_BUDHA:
		_image_message[ MESSAGE_BUDHA ]->draw( );
		break;
	}
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

	if ( data->getStatusPower( _player ) == 0 ) {
		if ( !_dead_se[ _player ] ) {
			sound->playSE( "yokai_se_31.wav" );
			_dead_se[ _player ] = true;
		}
	} else {
		_dead_se[ _player ] = false;
	}
}