#pragma once
#include <string>
#include "mathmatics.h"

class Status{
public:
	Status( );
	virtual ~Status( );	
public:
	struct STATUS{
		Vector device_dir;
		unsigned char device_button;
		unsigned char state;
		unsigned char continue_num;
		unsigned char toku;
		unsigned char item;
		unsigned char money;
		unsigned char power;
		STATUS( );
	};
public:
	static std::string BToS( unsigned char b );
};

