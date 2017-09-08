#include "RockMapResult.h"
#include "ModelMV1.h"

RockMapResult::RockMapResult( ) {
}


RockMapResult::~RockMapResult( ) {
}

void RockMapResult::initialize( ) {
	ModelMV1Ptr map01 = ModelMV1Ptr( new ModelMV1 );
	map01->load( "Resource/Rock/map/test/map01.mv1" );
	addModel( map01 );
	
	ModelMV1Ptr col01 = ModelMV1Ptr( new ModelMV1 );
	col01->load( "Resource/Rock/map/test/map01_col.mv1" );
	col01->setTrans( Matrix::makeTransformTranslation( Vector( 0, 10, 0 ) ) );
	col01->draw( );
	addColModel( col01 );
}


void RockMapResult::update( ) {
}

