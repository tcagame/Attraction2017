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
		col_model->load( "Resource/Rock/map/street1/map02_CL.mv1" );
		col_model->setTrans( Matrix::makeTransformTranslation( Vector( 0, 0, 0 ) ) );
		map->addColModel( col_model );


		ModelMV1Ptr see_model = ModelMV1Ptr( new ModelMV1 );
		see_model->load( "Resource/Rock/map/street1/map02_03.mv1" );
		map->addCleannessModel( see_model );
		ModelMV1Ptr lake_model = ModelMV1Ptr( new ModelMV1 );
		lake_model->load( "Resource/Rock/map/street1/map02_04.mv1" );
		map->addCleannessModel( lake_model );
	}
		break;
	case RockMapStreet::STAGE_CAVE:
	{
		// 赤鬼用ダミーマップ
		ModelMV1Ptr boss_model = ModelMV1Ptr( new ModelMV1 );
		boss_model->load( "Resource/Rock/map/street1/map03.mv1" );
		boss_model->draw( );
		map->addModel( boss_model );

		ModelMV1Ptr boss_col_model = ModelMV1Ptr( new ModelMV1 );
		boss_col_model->load( "Resource/Rock/map/street1/map03_CL.mv1" );

		boss_col_model->draw( );
		map->addColModel( boss_col_model );

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
