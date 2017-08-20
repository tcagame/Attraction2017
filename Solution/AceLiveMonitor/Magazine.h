#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( Magazine );
PTR( Impact );

class Magazine : public Task {
public:
	static std::string getTag( ) { return "MAGAZINE"; };
	static MagazinePtr getTask( );
public:
	Magazine( );
	virtual ~Magazine( );
public:
	void update( );
	void add( ImpactPtr impact );
	std::list< ImpactPtr > getImpactList( ) const;
private:
	std::list< ImpactPtr > _impacts;
};

