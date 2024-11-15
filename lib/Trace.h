#pragma once
#ifndef TRACE_H
#define TRACE_H

#include <string>
#include <iostream>


class Trace {
private:
	std::string IP;
	std::string URL;
	int index;

public:
	Trace();
	~Trace();

	void getURL();
	void setURL(std::string& valueURL);
 	void executeTracerouteScript(); 
 	void executeIPinfo(const std::string& ipAddress);

	int getIndex();
	void Print();
};

 

#endif
