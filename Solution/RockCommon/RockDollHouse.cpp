#include "RockDollHouse.h"
#include "Application.h"
#include "ModelMV1.h"

RockDollHousePtr RockDollHouse::getTask( ) {
	return std::dynamic_pointer_cast< RockDollHouse >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockDollHouse::RockDollHouse( ) {
}

RockDollHouse::~RockDollHouse( ) {
}

void RockDollHouse::initialize( ) {
	for ( int i = 0; i < MAX_DOLL; i++ ) {
		_dolls[ i ] = ModelMV1Ptr( new ModelMV1 );
	}
	//player
	_dolls[ DOLL_TAROSUKE_WAIT		]->load( "Resource/Rock/player/tarosuke_wait.mv1" );
	_dolls[ DOLL_TAROSUKE_JUMP		]->load( "Resource/Rock/player/tarosuke_jump.mv1" );
	_dolls[ DOLL_TAROSUKE_WALK		]->load( "Resource/Rock/player/tarosuke_walk.mv1" );
	_dolls[ DOLL_TAROSUKE_DEAD		]->load( "Resource/Rock/player/tarosuke_dead.mv1" );
	_dolls[ DOLL_TAROSUKE_CHARGE	]->load( "Resource/Rock/player/tarosuke_charge.mv1" );
	_dolls[ DOLL_TAROSUKE_WISH		]->load( "Resource/Rock/player/tarosuke_wish.mv1" );

	_dolls[ DOLL_GARISUKE_WAIT		]->load( "Resource/Rock/player/garisuke_wait.mv1" );
	_dolls[ DOLL_GARISUKE_JUMP		]->load( "Resource/Rock/player/garisuke_jump.mv1" );
	_dolls[ DOLL_GARISUKE_WALK		]->load( "Resource/Rock/player/garisuke_walk.mv1" );
	_dolls[ DOLL_GARISUKE_DEAD		]->load( "Resource/Rock/player/garisuke_dead.mv1" );
	_dolls[ DOLL_GARISUKE_CHARGE	]->load( "Resource/Rock/player/garisuke_charge.mv1" );
	_dolls[ DOLL_GARISUKE_WISH		]->load( "Resource/Rock/player/garisuke_wish.mv1" );

	_dolls[ DOLL_TAROJIRO_WAIT		]->load( "Resource/Rock/player/tarojiro_wait.mv1" );
	_dolls[ DOLL_TAROJIRO_JUMP		]->load( "Resource/Rock/player/tarojiro_jump.mv1" );
	_dolls[ DOLL_TAROJIRO_WALK		]->load( "Resource/Rock/player/tarojiro_walk.mv1" );
	_dolls[ DOLL_TAROJIRO_DEAD		]->load( "Resource/Rock/player/tarojiro_dead.mv1" );
	_dolls[ DOLL_TAROJIRO_CHARGE	]->load( "Resource/Rock/player/tarojiro_charge.mv1" );
	_dolls[ DOLL_TAROJIRO_WISH		]->load( "Resource/Rock/player/tarojiro_wish.mv1" );

	_dolls[ DOLL_TAROMI_WAIT		]->load( "Resource/Rock/player/taromi_wait.mv1" );
	_dolls[ DOLL_TAROMI_JUMP		]->load( "Resource/Rock/player/taromi_jump.mv1" );
	_dolls[ DOLL_TAROMI_WALK		]->load( "Resource/Rock/player/taromi_walk.mv1" );
	_dolls[ DOLL_TAROMI_DEAD		]->load( "Resource/Rock/player/taromi_dead.mv1" );
	_dolls[ DOLL_TAROMI_CHARGE		]->load( "Resource/Rock/player/taromi_charge.mv1" );
	_dolls[ DOLL_TAROMI_WISH		]->load( "Resource/Rock/player/taromi_wish.mv1" );

	_dolls[ DOLL_ANCESTORS			]->load( "Resource/Rock/player/ancestors.mv1" );

	//enemy
	_dolls[ DOLL_GHOST		]->load( "Resource/Rock/enemy/enm05_yurei/enm05_a01.mv1" );
	_dolls[ DOLL_REDBARD	]->load( "Resource/Rock/enemy/enm02_bird/enm02_a01.mv1" );
	_dolls[ DOLL_WATERGHOST ]->load( "Resource/Rock/enemy/enm17_mizunoyokai/enm17_a02.mv1" );
	_dolls[ DOLL_CLOUD ]->load( "Resource/Rock/enemy/enm06_cloud/enm06_a01.mv1" );
	_dolls[ DOLL_FACE_AND_HAND ]->load( "Resource/Rock/enemy/enm03_face_and_hand/enm03_a01_face_and_hand.mv1" );
	_dolls[ DOLL_BOSS_ROCK		]->load( "Resource/Rock/enemy/enm22_rock/scenes/enm22_rock.mv1" );
	_dolls[ DOLL_BAT ]->load( "Resource/Rock/enemy/enm09_Babitto/enm09_a01.mv1" );
	_dolls[ DOLL_KIMONO		]->load( "Resource/Rock/enemy/enm07_Kimono-no-Yokai/enm07_a01.mv1" );

	//item
	_dolls[ DOLL_DANGO	 ]->load( "Resource/Rock/item/itm01/itm01.mv1" );
	_dolls[ DOLL_MONEY_1 ]->load( "Resource/Rock/item/itm04/itm04.mv1" );
	_dolls[ DOLL_MONEY_2 ]->load( "Resource/Rock/item/itm06/itm06.mv1" );
	_dolls[ DOLL_MONEY_3 ]->load( "Resource/Rock/item/itm07/itm07.mv1" );
	_dolls[ DOLL_MONEY_4 ]->load( "Resource/Rock/item/itm08/itm08.mv1" );
	_dolls[ DOLL_TOKU ]->load( "Resource/Rock/item/itm10/itm10.mv1" );
	_dolls[ DOLL_SACRED_ROCK ]->load( "Resource/Rock/object/sacred/sacred_rock.mv1" );
	_dolls[ DOLL_SACRED_ROCK ]->setScale( Matrix::makeTransformScaling( Vector( 2, 2, 2 ) ) );
	_dolls[ DOLL_SACRED_FIRE ]->load( "Resource/Rock/object/sacred/sacred_fire.mv1" );
	_dolls[ DOLL_SACRED_FIRE ]->setScale( Matrix::makeTransformScaling( Vector( 2, 2, 2 ) ) );
	_dolls[ DOLL_SACRED_TREE ]->load( "Resource/Rock/object/sacred/sacred_tree.mv1" );
	_dolls[ DOLL_SACRED_TREE ]->setScale( Matrix::makeTransformScaling( Vector( 2, 2, 2 ) ) );
	_dolls[ DOLL_BUBBLE ]->load( "Resource/Rock/object/bubble/bubble.mv1" );

	//obj
	_dolls[ DOLL_ALTER_BEFORE	]->load( "Resource/Rock/object/obj04/obj04.mv1" );
	_dolls[ DOLL_ALTER_AFTER	]->load( "Resource/Rock/object/obj05/obj05.mv1" );
	_dolls[ DOLL_CASKET	]->load( "Resource/Rock/object/obj01/obj01.mv1" );
	_dolls[ DOLL_CASKET ]->setScale( Matrix::makeTransformScaling( Vector( 10, 10, 10 ) ) );

	//event char
	_dolls[ DOLL_TURTLE ]->load( "Resource/Rock/event_chara/chr07.mv1" );
}

ModelMV1Ptr RockDollHouse::getModel( DOLL id ) const {
	return _dolls[ id ];
}

void RockDollHouse::update( ) {
}
