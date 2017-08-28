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
	}
}

RockMapBossDrawer::~RockMapBossDrawer( ) {
}

void RockMapBossDrawer::loadStage( const std::string map_filename, const std::string col_filename ) {
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
}

RockMapBoss::STAGE RockMapBossDrawer::getStage( ) const {
	return _stage;
}
