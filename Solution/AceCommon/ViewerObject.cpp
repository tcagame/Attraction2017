#include "ViewerObject.h"
#include "SynchronousData.h"
#include "Drawer.h"
#include <assert.h>

ViewerObject::ViewerObject( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image[ GRAPH_PLAYER_TAROSUKE	] = drawer->createImage( "Family/tarosuke.png"				);
	_image[ GRAPH_PLAYER_TAROJIRO	] = drawer->createImage( "Family/tarojiro.png"				);
	_image[ GRAPH_PLAYER_GARISUKE	] = drawer->createImage( "Family/garisuke.png"				);
	_image[ GRAPH_PLAYER_TAROMI		] = drawer->createImage( "Family/taromi.png"				);
	_image[ GRAPH_MONMOTARO			] = drawer->createImage( "Family/momotaro.png"				);
	_image[ GRAPH_SANZO				] = drawer->createImage( "Family/hebisanzo.png"         	);
	_image[ GRAPH_SHOT				] = drawer->createImage( "Effect/psychic.png"				);
	_image[ GRAPH_ENEMY_MIDIUM		] = drawer->createImage( "Enemy/enemy_medium.png"			);
	_image[ GRAPH_ENEMY_SMALL		] = drawer->createImage( "Enemy/enemy_small.png"			);
	_image[ GRAPH_ENEMY_BIG			] = drawer->createImage( "Enemy/enemy_big.png"				);
	_image[ GRAPH_ENEMY_BOSS		] = drawer->createImage( "Enemy/enemy_boss.png"				);
	_image[ GRAPH_IMPACT			] = drawer->createImage( "Effect/impact.png"				);
	_image[ GRAPH_ITEM				] = drawer->createImage( "Item/item.png"					);
	_image[ GRAPH_ITEM2				] = drawer->createImage( "Item/item2.png"					);
	_image[ GRAPH_NPC				] = drawer->createImage( "Event/character/character.png"	);
	_image[ GRAPH_SHADOW			] = drawer->createImage( "Effect/effect_shadow.png"	);
	_image[ GRAPH_RYUGU			    ] = drawer->createImage( "Event/character/ryugu.png"     	);
	_image[ GRAPH_LAKE			    ] = drawer->createImage( "Event/character/miko.png"     	);
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
		int size = data->getObjectSize( idx );
		drawSprite( x, y, type, attribute, pattern, size );
	}
}

void ViewerObject::drawSprite( int x, int y, unsigned char type, unsigned char attribute, int pattern, int size ) const {
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
	case SynchronousData::TYPE_MONMOTARO:
		sprite = getSpritePlayer( GRAPH_MONMOTARO		, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_SHOT:
		sprite = getSpriteEffect( GRAPH_SHOT			, x, y, attribute, pattern );
		break;
	case SynchronousData::TYPE_ENEMY_MIDIUM:
		sprite = getSpriteEnemy( GRAPH_ENEMY_MIDIUM		, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_ENEMY_SMALL:
		sprite = getSpriteEnemy( GRAPH_ENEMY_SMALL		, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_ENEMY_BIG:
		sprite = getSpriteEnemy( GRAPH_ENEMY_BIG		, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_ENEMY_BOSS:
		sprite = getSpriteEnemyBoss( GRAPH_ENEMY_BOSS	, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_IMPACT:
		sprite = getSpriteImpact( GRAPH_IMPACT			, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_ITEM:
		sprite = getSpriteItem( GRAPH_ITEM				, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_ITEM2:
		sprite = getSpriteItem2( GRAPH_ITEM2			, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_NPC:
		sprite = getSpriteNPC( GRAPH_NPC				, x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_SANZO:
		sprite = getSpriteSanzo( GRAPH_SANZO            , x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_SHADOW:
		sprite = getSpriteShadow( GRAPH_SHADOW          , x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_RYUGU:
		sprite = getSpriteRyugu( GRAPH_RYUGU            , x, y, attribute, pattern, size );
		break;
	case SynchronousData::TYPE_LAKE:
		sprite = getSpriteLake( GRAPH_LAKE            , x, y, attribute, pattern, size );
		break;
	default: assert( 0 );
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

ViewerObject::Sprite ViewerObject::getSpriteEffect( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const {
	Sprite sprite;
	sprite.graph = graph;
	
	sprite.tx = pattern % EFFECT_CHIP_WIDTH * NORMAL_CHAR_GRAPH_SIZE;
	sprite.ty = pattern / EFFECT_CHIP_WIDTH * NORMAL_CHAR_GRAPH_SIZE;
	sprite.tw = NORMAL_CHAR_GRAPH_SIZE;
	sprite.th = NORMAL_CHAR_GRAPH_SIZE;

	if ( attribute & SynchronousData::ATTRIBUTE_REVERSE ) {
		sprite.sx1 = x - NORMAL_CHAR_GRAPH_SIZE / 2 + NORMAL_CHAR_GRAPH_SIZE;
		sprite.sy1 = y - NORMAL_CHAR_GRAPH_SIZE;
		sprite.sx2 = sprite.sx1 - NORMAL_CHAR_GRAPH_SIZE;
		sprite.sy2 = sprite.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	} else {
		sprite.sx1 = x - NORMAL_CHAR_GRAPH_SIZE / 2;
		sprite.sy1 = y - NORMAL_CHAR_GRAPH_SIZE;
		sprite.sx2 = sprite.sx1 + NORMAL_CHAR_GRAPH_SIZE;
		sprite.sy2 = sprite.sy1 + NORMAL_CHAR_GRAPH_SIZE;
	}

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteEnemy( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	int chip_size = size;
	int width_num = 0;
	if ( size < 0 ) {
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
		}
	} else {
		switch ( graph ) {
		case GRAPH_ENEMY_SMALL:
			width_num = 256 / size;
			break;
		case GRAPH_ENEMY_MIDIUM:
			width_num = 1280 / size;
			break;
		case GRAPH_ENEMY_BIG:
			width_num = 1280 / size;
			break;
		}
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

ViewerObject::Sprite ViewerObject::getSpriteEnemyBoss( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	int width_num = 2048 / size;
	sprite.tx = pattern % width_num * size;
	sprite.ty = pattern / width_num * size;
	sprite.tw = size;
	sprite.th = size;

	if ( attribute & SynchronousData::ATTRIBUTE_REVERSE ) {
		sprite.sx1 = x - size / 2 + size;
		sprite.sy1 = y - size;
		sprite.sx2 = sprite.sx1 - size;
		sprite.sy2 = sprite.sy1 + size;
	} else {
		sprite.sx1 = x - size / 2;
		sprite.sy1 = y - size;
		sprite.sx2 = sprite.sx1 + size;
		sprite.sy2 = sprite.sy1 + size;
	}

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteImpact( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	sprite.tx = pattern % IMPACT_CHIP_WIDTH * IMPACT_GRAPH_SIZE;
	sprite.ty = pattern / IMPACT_CHIP_WIDTH * IMPACT_GRAPH_SIZE;
	sprite.tw = IMPACT_GRAPH_SIZE;
	sprite.th = IMPACT_GRAPH_SIZE;

	sprite.sx1 = x - size / 2;
	sprite.sy1 = y - size;
	sprite.sx2 = sprite.sx1 + size;
	sprite.sy2 = sprite.sy1 + size;

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteItem( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	if ( size < 0 ) {
		size = 32;
	}
	int width_num = 128 / size;
	sprite.tx = pattern % width_num * size;
	sprite.ty = pattern / width_num * size;
	sprite.tw = size;
	sprite.th = size;
	
	sprite.sx1 = x - size / 2;
	sprite.sy1 = y - size;
	sprite.sx2 = sprite.sx1 + size;
	sprite.sy2 = sprite.sy1 + size;

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteItem2( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	const int WIDTH_NUM = 4;
	const int CHIP_SIZE = 32;

	sprite.tx = pattern % WIDTH_NUM * CHIP_SIZE;
	sprite.ty = pattern / WIDTH_NUM * CHIP_SIZE;
	sprite.tw = size;
	sprite.th = size;
	
	sprite.sx1 = x - size / 2;
	sprite.sy1 = y - size;
	sprite.sx2 = sprite.sx1 + size;
	sprite.sy2 = sprite.sy1 + size;

	return sprite;
}
ViewerObject::Sprite ViewerObject::getSpriteNPC( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;

	const int GRAPH_SIZE = 1024;

	int width_num = GRAPH_SIZE / size;
	sprite.tx = pattern % width_num * size;
	sprite.ty = pattern / width_num * size;
	sprite.tw = size;
	sprite.th = size;

	if ( attribute & SynchronousData::ATTRIBUTE_REVERSE ) {
		sprite.sx1 = x - size / 2 + size;
		sprite.sy1 = y - size;
		sprite.sx2 = sprite.sx1 - size;
		sprite.sy2 = sprite.sy1 + size;
	} else {
		sprite.sx1 = x - size / 2;
		sprite.sy1 = y - size;
		sprite.sx2 = sprite.sx1 + size;
		sprite.sy2 = sprite.sy1 + size;
	}
	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteSanzo( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	sprite.tx = pattern % 6 * 64;
	sprite.ty = pattern / 6 * 64;
	sprite.tw = 64;
	sprite.th = 64;

	sprite.sx1 = x - 64 / 2;
	sprite.sy1 = y - 64;
	sprite.sx2 = sprite.sx1 + 64;
	sprite.sy2 = sprite.sy1 + 64;

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteShadow( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	sprite.tx = -1;
	sprite.ty = -1;
	sprite.tw = -1;
	sprite.th = -1;

	sprite.sx1 = x - 64 / 2;
	sprite.sy1 = y - 64;
	sprite.sx2 = sprite.sx1 + 64;
	sprite.sy2 = sprite.sy1 + 64;

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteRyugu( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	if ( size < 0 ) {
		size = 32;
	}
	int width_num = 2048 / size;
	sprite.tx = pattern % width_num * size;
	sprite.ty = pattern / width_num * size;
	sprite.tw = size;
	sprite.th = size;
	
	sprite.sx1 = x - size / 2;
	sprite.sy1 = y - size;
	sprite.sx2 = sprite.sx1 + size;
	sprite.sy2 = sprite.sy1 + size;

	return sprite;
}

ViewerObject::Sprite ViewerObject::getSpriteLake( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const {
	Sprite sprite;
	sprite.graph = graph;
	if ( size < 0 ) {
		size = 32;
	}
	int width_num = 1024 / size;
	sprite.tx = pattern % width_num * size;
	sprite.ty = pattern / width_num * size;
	sprite.tw = size;
	sprite.th = size;
	
	sprite.sx1 = x - size / 2;
	sprite.sy1 = y - size;
	sprite.sx2 = sprite.sx1 + size;
	sprite.sy2 = sprite.sy1 + size;

	return sprite;
}