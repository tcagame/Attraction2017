#pragma once
#include "Task.h"
#include <string>
#include <vector>

PTR( RockMap );
PTR( ModelMV1 );

class RockMap : public Task {
public:
	static std::string getTag( ) { return "ROCKMAP"; };
	static RockMapPtr getTask( );
public:
	RockMap( );
	virtual ~RockMap( );
public:
	std::vector< ModelMV1Ptr > getModels( ) const;
	std::vector< ModelMV1Ptr > getColModels( ) const;
	std::vector< ModelMV1Ptr > getBackGroundModels( ) const;
	void addModel( ModelMV1Ptr model );
	void addColModel( ModelMV1Ptr model );
	void addBackGroundModel( ModelMV1Ptr model );
	void resetModels( );
private:
	std::vector< ModelMV1Ptr > _models;
	std::vector< ModelMV1Ptr > _col_models;
	std::vector< ModelMV1Ptr > _back_ground_models;
};

