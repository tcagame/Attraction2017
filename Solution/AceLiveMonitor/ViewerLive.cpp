#include "ViewerLive.h"
#include "Application.h"
#include "Drawer.h"

#include "ViewerStreet.h"
#include "ViewerStatus.h"
#include "ViewerEvent.h"
#include "ViewerTitle.h"
#include "ViewerDebug.h"
#include "Debug.h"

#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Family.h"

#include "World.h"
#include "Map.h"

const int EVENT_SX = 0;
const int EVENT_SY = 0;
const int MAIN_SX  = 0;
const int MAIN_SY  = 256;

ViewerLivePtr ViewerLive::getTask( ) {
	return std::dynamic_pointer_cast< ViewerLive >( Application::getInstance( )->getTask( getTag( ) ) );
}

ViewerLive::ViewerLive( ) {
}

ViewerLive::~ViewerLive( ) {
}

void ViewerLive::initialize( ) {
	_viewer_street = ViewerStreetPtr( new ViewerStreet );
	_viewer_event  = ViewerEventPtr	( new ViewerEvent  );
	_viewer_title  = ViewerTitlePtr ( new ViewerTitle  );
	_viewer_status = ViewerStatusPtr( new ViewerStatus );
	_viewer_debug  = ViewerDebugPtr( new ViewerDebug );
	_viewer_object = ViewerObjectPtr( new ViewerObject );

	DrawerPtr drawer = Drawer::getTask( );
	_image_frame = drawer->createImage( "UI/area_event_frame.png" );
	_image_frame->setRect( 0, 0, 1280, 256 );
	_image_frame->setPos( 0, 0 );
}

void ViewerLive::update( ) {
	SynchronousDataPtr data( SynchronousData::getTask( ) );

	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->waitForSync( );
	drawer->flip( );
	
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	// Main�`��
	_viewer_street->draw( ViewerStreet::LAYER_BACK, MAIN_SX, MAIN_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, MAIN_SX, MAIN_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT, MAIN_SX, MAIN_SY, camera_pos );

	// �C�x���g�`��
	EVENT event = data->getEvent( );
	if ( event == EVENT_NONE ) {
		_viewer_title->draw( );
	} else {
		_viewer_event->draw( event, EVENT_SX, EVENT_SY );
	}

	// �C�x���g�g�`��
	_image_frame->draw( );

	// �I�u�W�F�N�g�`��
	_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
	
	// �X�e�[�^�X�`��
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_viewer_status->draw( ( PLAYER )i, i * VIEW_STATUS_WIDTH, VIEW_STATUS_Y );
	}

	// �f�o�b�O
	if ( Debug::getTask( )->isDebug( ) ) {
		_viewer_debug->draw( );
	}

	// �����f�[�^������
	data->resetObject( );
}
