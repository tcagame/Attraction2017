#include "Viewer.h"
#include "Application.h"
#include "Drawer.h"

#include "ViewerStreet.h"
#include "ViewerStatus.h"
#include "ViewerEvent.h"

#include "ViewerDebug.h"
#include "Debug.h"

#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Family.h"

const int EVENT_SX = 0;
const int EVENT_SY = 0;
const int MAIN_SX  = 0;
const int MAIN_SY  = 256;



ViewerPtr Viewer::getTask( ) {
	return std::dynamic_pointer_cast< Viewer >( Application::getInstance( )->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	_viewer_street		= ViewerStreetPtr	( new ViewerStreet );
	_viewer_event		= ViewerEventPtr	( new ViewerEvent );
	_viewer_status		= ViewerStatusPtr	( new ViewerStatus );

	_viewer_debug = ViewerDebugPtr( new ViewerDebug );

	_viewer_object = ViewerObjectPtr  ( new ViewerObject );
}

void Viewer::update( ) {

	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->flip( );
	
	FamilyConstPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK, MAIN_SX, MAIN_SY, camera_pos );
	_viewer_object->draw( AREA_STREET, MAIN_SX, MAIN_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT, MAIN_SX, MAIN_SY, camera_pos );

	// イベント描画
	_viewer_event->draw( EVENT_SX, EVENT_SY );
	_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
	
	// ステータス描画
	_viewer_status->draw( );

	// デバッグ
	if ( Debug::getTask( )->isDebug( ) ) {
		_viewer_debug->draw( );
	}

	// 同期データ初期化
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->resetObject( );
}
