#include "ViewerObject.h"
#include "SynchronousData.h"

ViewerObject::ViewerObject( ) {
}


ViewerObject::~ViewerObject( ) {
}

void ViewerObject::draw( AREA area, int sx, int sy ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	int num = data->getObjectNum( area );
	for ( int i = 0; i < num; i++ ) {
		int idx = data->getIdx( area, i );
		int x = data->getObjectX( idx ) + sx;
		int y = data->getObjectY( idx ) + sy;
		unsigned char type = data->getObjectType( idx );
		unsigned char attribute = data->getObjectAttribute( idx );
		int pattern = data->getObjectPattern( idx );
		drawSprite( x, y, type, attribute, pattern );
	}
}

void ViewerObject::drawSprite( int x, int y, unsigned char type, unsigned char attribute, int pattern ) const {
	Sprite sprite;
	switch ( type ) {
	case SynchronousData::TYPE_TAROSUKE:
		sprite = getSpritePlayerWait( GRAPH_PLAYER_TAROSUKE, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_TAROJIRO:
		sprite = getSpritePlayerWait( GRAPH_PLAYER_TAROJIRO, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_GARISUKE:
		sprite = getSpritePlayerWait( GRAPH_PLAYER_GARISUKE, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_TAROMI:
		sprite = getSpritePlayerWait( GRAPH_PLAYER_TAROMI  , x, y, attribute, pattern );
		break;
	};

	_image[ sprite.graph ]->setRect( sprite.tx, sprite.ty, sprite.tw, sprite.th );
	_image[ sprite.graph ]->setPos( sprite.sx1, sprite.sy1, sprite.sx2, sprite.sy2 );
	_image[ sprite.graph ]->draw( );
}

ViewerObject::Sprite ViewerObject::getSpritePlayerWait( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const {
	Sprite sprite;
	sprite.graph = graph;
	
	sprite.tx = pattern % PLAYER_CHAR_CHIP_WIDTH * NORMAL_CHAR_GRAPH_SIZE;
	sprite.ty = pattern / PLAYER_CHAR_CHIP_WIDTH * NORMAL_CHAR_GRAPH_SIZE;

	if ( attribute & SynchronousData::ATTRIBUTE_REVERSE ) {
		sprite.sx1 = x - NORMAL_CHAR_GRAPH_SIZE / 2 + NORMAL_CHAR_GRAPH_SIZE;
		sprite.sy1 = y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_CHAR_GRAPH_FOOT;
		sprite.sx2 = sprite.sx1 - NORMAL_CHAR_GRAPH_SIZE;
		sprite.sy2 = sprite.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	} else {
		sprite.sx1 = x - NORMAL_CHAR_GRAPH_SIZE / 2;
		sprite.sy1 = y - NORMAL_CHAR_GRAPH_SIZE + PLAYER_CHAR_GRAPH_FOOT;
		sprite.sx2 = sprite.sx1 + NORMAL_CHAR_GRAPH_SIZE;
		sprite.sy2 = sprite.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	}

	return sprite;
}

