#include "RockMapStreetDrawer.h"
#include "ModelMV1.h"
#include "RockMap.h"
#include <assert.h>

const int STREET_MODEL_NUM = 2;

RockMapStreetDrawer::RockMapStreetDrawer( RockMapStreet::STAGE stage ) {
	RockMapPtr map( RockMap::getTask( ) );
	map->resetModels( );
	switch( stage )	{
	case RockMapStreet::STAGE_STREET:
	{
		for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
			ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
			char filename[ 256 ];
			sprintf_s( filename, "Resource/Rock/map/street1/map02_0%d.mv1", i + 1 );
			model->load( filename );
		
			model->draw( );
			map->addModel( model );
		}
		ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
		col_model->load( "Resource/Rock/map/street1/map02_col.mv1" );
		col_model->setTrans( Matrix::makeTransformTranslation( Vector( 0, 10, 0 ) ) );
		map->addColModel( col_model );

		//ModelMV1Ptr bg_model = ModelMV1Ptr( new ModelMV1 );
		//bg_model->load( "Resource/Rock/map/streetBoss/to_boss_street_bg.mv1" );
		//
		//bg_model->draw( );
		//map->addModel( bg_model );


		ModelMV1Ptr clear_model = ModelMV1Ptr( new ModelMV1 );
		clear_model->load( "Resource/Rock/map/street1/map02_03.mv1" );
		map->addCleannessModel( clear_model );
	}
		break;
	case RockMapStreet::STAGE_CAVE:
	{
		// 赤鬼用ダミーマップ
		ModelMV1Ptr boss_model = ModelMV1Ptr( new ModelMV1 );
		boss_model->load( "Resource/Rock/map/street1/floor01.mv1" );
		boss_model->draw( );
		map->addModel( boss_model );

		ModelMV1Ptr boss_col_model = ModelMV1Ptr( new ModelMV1 );
		boss_col_model->load( "Resource/Rock/map/test/map01_col.mv1" );
		boss_col_model->setScale( Matrix::makeTransformScaling( Vector( 0.4, 0.4, 0.4 ) ) );
		boss_col_model->draw( );
		map->addColModel( boss_col_model );

		ModelMV1Ptr boss_bg_model = ModelMV1Ptr( new ModelMV1 );
		boss_bg_model->load( "Resource/Rock/map/streetBoss/to_boss_street_bg.mv1" );
		
		boss_bg_model->draw( );
		map->addModel( boss_bg_model );
	}
		break;
	case RockMapStreet::STAGE_RYUGU:
	{
		ModelMV1Ptr ryugu_model = ModelMV1Ptr( new ModelMV1 );
		ryugu_model->load( "Resource/Rock/map/street1/map10.mv1" );
		ryugu_model->draw( );
		map->addModel( ryugu_model );
		ModelMV1Ptr ryugu_col_model = ModelMV1Ptr( new ModelMV1 );
		ryugu_col_model->load( "Resource/Rock/map/street1/map10_CL.mv1" );
		ryugu_col_model->draw( );
		map->addColModel( ryugu_col_model );
	}
		break;
	default:
		assert( stage == RockMapStreet::STAGE_STREET && stage == RockMapStreet::STAGE_CAVE );
	break;
	}
}

RockMapStreetDrawer::~RockMapStreetDrawer( ) {
}
