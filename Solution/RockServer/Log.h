#pragma once
#include <string>
#include <array>

class Log {
public:
	Log( );
	virtual ~Log( );
public:
	void update( );
	void draw( );
	void addMessage( std::string message );
private:
	void drawFrame( ) const;
	void drawString( ) const;
private:
	static const int MESSAGE_COUNT = 10;
private:
	std::array< std::string, MESSAGE_COUNT > _message;
};


