#include "RockMapBossDrawer.h"
#include "ModelMV1.h"

const std::string DIRECTORY = "Resource/Rock/map/streetBoss/";

RockMapBossDrawer::RockMapBossDrawer( RockMapBoss::STAGE stage ) :
_stage( stage ) {
	switch( _stage ) {
	case RockMapBoss::STAGE_FIRE:
		loadStage( "room_fire.mv1", "room_fire_col.mv1" );
		break;
	case RockMapBoss::STAGE_FIRE_TO_ROCK:
		loadStage( "fire_to_rock.mv1", "fire_to_rock_col.mv1", "to_boss_street_bg.mv1" );
		break;
	case RockMapBoss::STAGE_TREE:
		loadRoomTree( );
		break;
	case RockMapBoss::STAGE_ROCK_TO_TREE:
		loadStage( "rock_to_tree_1.mv1", "rock_to_tree_col.mv1", "to_boss_street_bg.mv1" );
		{// “¹’†‚Ì–Ø
			ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
			std::string map_path = DIRECTORY + "rock_to_tree_2.mv1";
			model->load( map_path.c_str( ) );
			RockMap::getTask( )->addCleannessModel( model );
		}
		break;
	case RockMapBoss::STAGE_ROCK:
		loadStage( "room_rock.mv1", "room_rock_col.mv1" );
		break;
	case RockMapBoss::STAGE_TREE_TO_FIRE:
		loadStage( "tree_to_fire_1.mv1", "tree_to_fire_col.mv1", "to_boss_street_bg.mv1" );
		{// “¹’†‚Ì–Ø
			ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
			std::string map_path = DIRECTORY + "tree_to_fire_2.mv1";
			model->load( map_path.c_str( ) );
			RockMap::getTask( )->addCleannessModel( model );
		}
		break;
	}
}

RockMapBossDrawer::~RockMapBossDrawer( ) {
}

void RockMapBossDrawer::loadStage( const std::string map_filename, const std::string col_filename, const std::string back_ground_filename ) {
	RockMapPtr map( RockMap::getTask( ) );
	map->resetModels( );
	std::string map_path = DIRECTORY + map_filename;
	ModelMV1Ptr model = ModelMV1Ptr( new ModelMV1 );
	model->load( map_path.c_str( ) );
	model->draw( );
	map->addModel( model );
		
	std::string col_path = DIRECTORY + col_filename;
	ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
	col_model->load( col_path.c_str( ) );
	map->addColModel( col_model );

	if ( back_ground_filename.size( ) > 1 ) {
		std::string back_ground_path = DIRECTORY + back_ground_filename;
		ModelMV1Ptr back_ground_model = ModelMV1Ptr( new ModelMV1 );
		back_ground_model->load( back_ground_path.c_str( ) );
		map->addBackGroundModel( back_ground_model );
	}
}

void RockMapBossDrawer::loadRoomTree( ) {
	RockMapPtr map( RockMap::getTask( ) );
	map->resetModels( );
	{
		std::string map1_path = DIRECTORY + "room_tree_1.mv1";
		ModelMV1Ptr model_1 = ModelMV1Ptr( new ModelMV1 );
		model_1->load( map1_path.c_str( ) );
		model_1->draw( );
		map->addModel( model_1 );
	}

	{
		std::string map2_path = DIRECTORY + "room_tree_2.mv1";
		ModelMV1Ptr model_2 = ModelMV1Ptr( new ModelMV1 );
		model_2->load( map2_path.c_str( ) );
		model_2->draw( );
		map->addModel( model_2 );
	}

	{
		std::string map3_path = DIRECTORY + "room_tree_3.mv1";
		ModelMV1Ptr model_3 = ModelMV1Ptr( new ModelMV1 );
		model_3->load( map3_path.c_str( ) );
		model_3->draw( );
		map->addModel( model_3 );
	}
	
	{
		std::string col_path = DIRECTORY + "room_tree_col.mv1";
		ModelMV1Ptr col_model = ModelMV1Ptr( new ModelMV1 );
		col_model->load( col_path.c_str( ) );
		col_model->draw( );
		map->addColModel( col_model );
	}
	
	{
		std::string back_path = DIRECTORY + "room_tree_bg.mv1";
		ModelMV1Ptr back_ground = ModelMV1Ptr( new ModelMV1 );
		back_ground->load( back_path.c_str( ) );
		back_ground->draw( );
		map->addBackGroundModel( back_ground );
	}
}

RockMapBoss::STAGE RockMapBossDrawer::getStage( ) const {
	return _stage;
}
