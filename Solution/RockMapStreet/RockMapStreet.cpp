#include "RockMapStreet.h"
#include "ModelMV1.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int STREET_MODEL_NUM = 3;

RockMapStreet::RockMapStreet( ) {
	_filenames = { };
	for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
		ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
		char filename[ 256 ];
		sprintf_s( filename, "Resource/Rock/map/street1/map02_0%d.mv1", i + 1 );
		model->load( filename );
		
		model->draw( );
		addModel( model );
	}
	ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
	col_model->load( "Resource/Rock/map/street1/map02_col.mv1" );
	col_model->setTrans( Matrix::makeTransformTranslation( Vector( 0, 0, 0 ) ) );
	addColModel( col_model );

	// 赤鬼用ダミーマップ
	ModelMV1Ptr boss_model = ModelMV1Ptr( new ModelMV1 );
	boss_model->load( "Resource/Rock/map/street1/floor01.mv1" );
	boss_model->setTrans( Matrix::makeTransformTranslation( Vector( -10000, 0, -1500 ) ) );
	boss_model->draw( );
	addModel( boss_model );
	/*
	ModelMV1Ptr boss_col_model = ModelMV1Ptr( new ModelMV1 );
	boss_col_model->load( "Resource/Rock/map/test/map01_col.mv1" );
	boss_col_model->setScale( Matrix::makeTransformScaling( Vector( 0.4, 0.4, 0.4 ) ) );
	boss_col_model->setTrans( Matrix::makeTransformTranslation( Vector( -10000, 0, -1500 ) ) );
	boss_col_model->draw( );
	addColModel( boss_col_model );*/
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::update( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		double length = ( Vector( -0, 0, -500 ) - player->getPos( ) ).getLength( );
		if ( length < 100 ) {
			player->warpRedDaemon( );
		}
	}
}