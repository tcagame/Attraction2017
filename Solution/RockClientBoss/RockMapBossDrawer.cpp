#include "RockMapBossDrawer.h"
#include "ModelMV1.h"

const std::string DIRECTORY = "Resource/Rock/map/streetBoss/";

RockMapBossDrawer::RockMapBossDrawer( RockMapBoss::STAGE stage ) :
_stage( stage ) {
	switch( _stage ) {
	case RockMapBoss::STAGE_FIRE:
		loadStage( "room_fire.mv1", "room_fire_col.mv1" );
		break;
	case RockMapBoss::STAGE_TREE:
		loadStage( "room_tree.mv1", "room_tree_col.mv1" );
		break;
	case RockMapBoss::STAGE_ROCK:
		loadStage( "room_rock.mv1", "room_rock_col.mv1" );
		break;
	case RockMapBoss::STAGE_FIRE_TO_ROCK:
	case RockMapBoss::STAGE_ROCK_TO_TREE:
	case RockMapBoss::STAGE_TREE_TO_FIRE:
		loadStage( "bossToboss.mv1", "bossToboss_col.mv1", "to_boss_street_bg.mv1" );
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

RockMapBoss::STAGE RockMapBossDrawer::getStage( ) const {
	return _stage;
}
