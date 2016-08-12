/*
 * Helper.cpp
 *
 *  Created on: 22/07/2016
 *      Author: leonardo
 */

#include "Helper.h"

using namespace std;

#include<iostream>
#include <sstream>
#include <string>


Helper::Helper() {
	// TODO Auto-generated constructor stub

}

Helper::~Helper() {
	// TODO Auto-generated destructor stub
}

string Helper::intToString( int i){

	std::ostringstream temp;
	temp<<i;
	return temp.str();

}
