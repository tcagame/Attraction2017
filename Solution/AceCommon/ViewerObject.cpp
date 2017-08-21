#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Drawer.h"

ViewerObject::ViewerObject( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image[ GRAPH_PLAYER_TAROSUKE	] = drawer->createImage( "Family/tarosuke.png"		);
	_image[ GRAPH_PLAYER_TAROJIRO	] = drawer->createImage( "Family/tarojiro.png"		);
	_image[ GRAPH_PLAYER_GARISUKE	] = drawer->createImage( "Family/garisuke.png"		);
	_image[ GRAPH_PLAYER_TAROMI		] = drawer->createImage( "Family/taromi.png"		);
	_image[ GRAPH_SHOT				] = drawer->createImage( "Effect/psychic.png"		);
	_image[ GRAPH_ENEMY_MIDIUM		] = drawer->createImage( "Enemy/enemy_medium.png"	);
	_image[ GRAPH_ENEMY_SMALL		] = drawer->createImage( "Enemy/enemy_small.png"	);
	_image[ GRAPH_ENEMY_BIG			] = drawer->createImage( "Enemy/enemy_big.png"		);
	_image[ GRAPH_ENEMY_BOSS		] = drawer->createImage( "Enemy/enemy_boss.png"	);
}


ViewerObject::~ViewerObject( ) {
}

void ViewerObject::draw( AREA area, int sx, int sy ) const {
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	int num = data->getObjectNum( area );
	for ( int i = 0; i < num; i++ ) {
		int idx = data->getIdx( area, i );
		int x = data->getObjectAX( idx ) + sx;
		int y = data->getObjectAY( idx ) + sy;
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
		sprite = getSpritePlayer( GRAPH_PLAYER_TAROSUKE	, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_TAROJIRO:
		sprite = getSpritePlayer( GRAPH_PLAYER_TAROJIRO	, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_GARISUKE:
		sprite = getSpritePlayer( GRAPH_PLAYER_GARISUKE	, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_TAROMI:
		sprite = getSpritePlayer( GRAPH_PLAYER_TAROMI	, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_CHARGE:
		sprite = getSpritePlayer( GRAPH_SHOT			, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_ENEMY_MIDIUM:
		sprite = getSpriteEnemy( GRAPH_ENEMY_MIDIUM		, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_ENEMY_SMALL:
		sprite = getSpriteEnemy( GRAPH_ENEMY_SMALL		, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_ENEMY_BIG:
		sprite = getSpriteEnemy( GRAPH_ENEMY_BIG		, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_ENEMY_BOSS:
		sprite = getSpriteEnemy( GRAPH_ENEMY_BOSS		, x, y, attribute, pattern );
		break;
	};

	_image[ sprite.graph ]->setRect( sprite.tx, sprite.ty, sprite.tw, sprite.th );
	_image[ sprite.graph ]->setPos( sprite.sx1, sprite.sy1, sprite.sx2, sprite.sy2 );
	_image[ sprite.graph ]->draw( );
}

ViewerObject::Sprite ViewerObject::getSpritePlayer( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const {
	Sprite sprite;
	sprite.graph = graph;
	
	sprite.tx = pattern % PLAYER_CHAR_CHIP_WIDTH * NORMAL_CHAR_GRAPH_SIZE;
	sprite.ty = pattern / PLAYER_CHAR_CHIP_WIDTH * NORMAL_CHAR_GRAPH_SIZE;
	sprite.tw = NORMAL_CHAR_GRAPH_SIZE;
	sprite.th = NORMAL_CHAR_GRAPH_SIZE;

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

ViewerObject::Sprite ViewerObject::getSpriteEnemy( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const {
	Sprite sprite;
	sprite.graph = graph;
	int chip_size = 0;
	int width_num = 0;
	switch ( graph ) {
	case GRAPH_ENEMY_SMALL:
		chip_size = SMALL_CHAR_GRAPH_SIZE;
		width_num = ENEMY_SMALL_CHIP_WIDTH;
		break;
	case GRAPH_ENEMY_MIDIUM:
		chip_size = NORMAL_CHAR_GRAPH_SIZE;
		width_num = ENEMY_NORMAL_CHIP_WIDTH;
		break;
	case GRAPH_ENEMY_BIG:
		chip_size = BIG_CHAR_GRAPH_SIZE;
		width_num = ENEMY_BIG_CHIP_WIDTH;
		break;
	case GRAPH_ENEMY_BOSS:
		//chip_size = SMALL_CHAR_GRAPH_SIZE;
		//width_num = ENEMY_SMALL_CHIP_WIDTH;
		break;
	}
	sprite.tx = pattern % width_num * chip_size;
	sprite.ty = pattern / width_num * chip_size;
	sprite.tw = chip_size;
	sprite.th = chip_size;

	if ( attribute & SynchronousData::ATTRIBUTE_REVERSE ) {
		sprite.sx1 = x - chip_size / 2 + chip_size;
		sprite.sy1 = y - chip_size;
		sprite.sx2 = sprite.sx1 - chip_size;
		sprite.sy2 = sprite.sy1 + chip_size;
	} else {
		sprite.sx1 = x - chip_size / 2;
		sprite.sy1 = y - chip_size;
		sprite.sx2 = sprite.sx1 + chip_size;
		sprite.sy2 = sprite.sy1 + chip_size;
	}

	return sprite;
}