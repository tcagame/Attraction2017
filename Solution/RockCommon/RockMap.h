#pragma once
#include "Task.h"
#include <string>
#include <vector>
#include "ModelMV1.h"

PTR( RockMap );

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
	ModelMV1Ptr getColModel( ) const;
protected:
	virtual std::vector< std::string > getFilenames( ) const = 0;
	virtual std::string getFilenameCol( ) const = 0;
private:
	std::vector< ModelMV1Ptr > _models;
	ModelMV1Ptr _col_model;
};

