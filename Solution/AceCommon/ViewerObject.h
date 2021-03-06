#pragma once

#include "ace_define.h"
#include "Image.h"
#include <array>

class ViewerObject {
public:
	ViewerObject();
	virtual ~ViewerObject( );
public:
	void draw( AREA area, int sx, int sy ) const;
private:
	enum GRAPH {
		GRAPH_PLAYER_TAROSUKE,
		GRAPH_PLAYER_TAROJIRO,
		GRAPH_PLAYER_GARISUKE,
		GRAPH_PLAYER_TAROMI,
		GRAPH_MONMOTARO,
		GRAPH_SHOT,
		GRAPH_ENEMY_MIDIUM,
		GRAPH_ENEMY_SMALL,
		GRAPH_ENEMY_BIG,
		GRAPH_ENEMY_BOSS,
		GRAPH_IMPACT,
		GRAPH_ITEM,
		GRAPH_ITEM2,
		GRAPH_NPC,
		GRAPH_SANZO,
		GRAPH_SHADOW,
		GRAPH_RYUGU,
		GRAPH_LAKE,
		MAX_GRAPH,
	};
	struct Sprite {
		GRAPH graph;
		int tx;
		int ty;
		int tw;
		int th;
		int sx1;
		int sy1;
		int sx2;
		int sy2;
	};
private:
	void drawSprite( int x, int y, unsigned char type, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpritePlayer( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const;
	Sprite getSpriteEffect( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const;
	Sprite getSpriteEnemy( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteEnemyBoss( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteImpact( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteItem( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteItem2( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteNPC( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteSanzo( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteShadow( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteRyugu( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
	Sprite getSpriteLake( GRAPH graph, int x, int y, unsigned char attribute, int pattern, int size ) const;
private:
	std::array< ImagePtr, MAX_GRAPH > _image;
};

