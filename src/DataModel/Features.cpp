/*
 * Features.cpp
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#include "Params.h"
#include "ColorClass.h"


#include "Features.h"

Features::Features() {

	size = Params::nRows;

	colors = new ColorClass[size];
}

Features::~Features() {
	// TODO Auto-generated destructor stub
}

