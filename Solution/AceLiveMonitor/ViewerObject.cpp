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
		draw( data->getIdx( SynchronousData::AREA_MAIN, i ) );
	}
}

void ViewerObject::drawEvent( ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	int num = data->getObjectNum( SynchronousData::AREA_EVENT );
	for ( int i = 0; i < num; i++ ) {
		draw( data->getIdx( SynchronousData::AREA_EVENT, i ) );
	}
}

void ViewerObject::draw( int idx ) const {
	/*
	Sprite sprite = getSprite( idx );
	_image[ sprite.graph ]->setRect( sprite.tx, sprite.ty, sprite.tw, sprite.th );
	_image[ sprite.graph ]->setPos( sprite.sx1, sprite.sy1, sprite.sx2, sprite.sy2 );
	_image[ sprite.graph ]->draw( );
	*/
}

