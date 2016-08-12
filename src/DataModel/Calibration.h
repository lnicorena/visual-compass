/*
 * Calibration.h
 *
 *  Created on: 20/07/2016
 *      Author: leonardo
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

class Calibration {
public:
	Calibration();
	virtual ~Calibration();

	void initialize(Compass& compass);
};

#endif /* CALIBRATION_H_ */
