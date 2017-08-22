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
	void initialize( );
	std::vector< ModelMV1Ptr > getModels( ) const;
	std::vector< ModelMV1Ptr > getColModels( ) const;
protected:
	void addModel( ModelMV1Ptr model );
	void addColModel( ModelMV1Ptr model );
private:
	std::vector< ModelMV1Ptr > _models;
	std::vector< ModelMV1Ptr > _col_models;
};

