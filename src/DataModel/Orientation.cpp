
#include "Orientation.h"

Orientation::Orientation() {
}

Orientation::Orientation(int degrees, float belief) {
	this->position = degrees;
	this->belief = belief;
}

Orientation::~Orientation() {
	// TODO Auto-generated destructor stub
}


float Orientation::getPosition(){
	return this->position;
}

void Orientation::setPosition(float degrees){
	this->position = degrees;
}

float Orientation::getBelief(){
	return this->belief;
}

void Orientation::setBelief(float belief){
	this->belief = belief;
}
