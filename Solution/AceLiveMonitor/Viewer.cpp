#include "Viewer.h"
#include "Application.h"
#include "Drawer.h"

#include "ViewerFamily.h"
#include "ViewerStreet.h"
#include "ViewerArmoury.h"
#include "ViewerStatus.h"
#include "ViewerEvent.h"
#include "ViewerStorage.h"
#include "ViewerMagazine.h"

#include "ViewerDebug.h"
#include "Debug.h"

#include "ViewerObject.h"

#include "SynchronousData.h"

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
	_viewer_magazine	= ViewerMagazinePtr	( new ViewerMagazine( ) );
	_viewer_family		= ViewerFamilyPtr	( new ViewerFamily ); 
	_viewer_street		= ViewerStreetPtr	( new ViewerStreet );
	_viewer_armoury		= ViewerArmouryPtr	( new ViewerArmoury( ) );
	_viewer_event		= ViewerEventPtr	( new ViewerEvent );
	_viewer_status		= ViewerStatusPtr	( new ViewerStatus );
	_viewer_storage		= ViewerStoragePtr  ( new ViewerStorage );

	_viewer_debug = ViewerDebugPtr( new ViewerDebug );

	_viewer_object = ViewerObjectPtr  ( new ViewerObject );
}

void Viewer::update( ) {

	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->flip( );

	// Main描画
	_viewer_street->draw( ViewerStreet::LAYER_BACK );
	_viewer_object->draw( AREA_MAIN, MAIN_SX, MAIN_SY );
	_viewer_street->draw( ViewerStreet::LAYER_FRONT );

	// イベント描画
	_viewer_event->draw( );
	_viewer_object->draw( AREA_EVENT, EVENT_SX, EVENT_SY );
	
	// 旧描画（全て移行させる)
	_viewer_storage->draw( );
	_viewer_armoury->draw( );
	_viewer_magazine->draw( );

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
