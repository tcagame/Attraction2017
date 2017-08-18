#include "ViewerObject.h"
#include "SynchronousData.h"

ViewerObject::ViewerObject( ) {
}


ViewerObject::~ViewerObject( ) {
}

void ViewerObject::drawMain( ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	int num = data->getObjectNum( SynchronousData::AREA_MAIN );
	for ( int i = 0; i < num; i++ ) {
		draw( false, i );
	}
}

void ViewerObject::drawEvent( ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	int num = data->getObjectNum( SynchronousData::AREA_EVENT );
	for ( int i = 0; i < num; i++ ) {
		draw( true, i );
	}
}

void ViewerObject::draw( bool event, int idx ) const {
	SynchronousData::AREA area = SynchronousData::AREA_MAIN;
	if ( event ) {
		area = SynchronousData::AREA_EVENT;
	}
}
