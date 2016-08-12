/*
 * Orientation.h
 *
 *  Created on: 03/08/2016
 *      Author: leonardo
 */

#ifndef ORIENTATION_H_
#define ORIENTATION_H_

class Orientation {
public:
	Orientation();
	Orientation(int position, float belief);
	virtual ~Orientation();

	float getPosition();
	void setPosition(float degrees);

	float getBelief();
	void setBelief(float belief);

private:
	float position;
	float belief;

};

#endif /* ORIENTATION_H_ */
