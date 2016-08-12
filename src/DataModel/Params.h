/*
 * Params.h
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#ifndef PARAMS_H_
#define PARAMS_H_

class Params {
public:
	Params();
	virtual ~Params();

	//static const int pxWidth = 1280;
	//static const int pxHeight = 960;

	static const int pxWidth = 800;
	static const int pxHeight = 600;

	static const int nCols = 128;
	static const int nRows = 8;

	static const int camHOpening = 45;
	static const int camVOpening = 45;


	static const int imOpeningK = 15;
	static const int imClosingK = 15;

	static const int colorRedFactor = 70 ; // 70 -> 4 value for channel = 64 colors

	static const float panorStoreScale = 0.2;
	static const float panorViewScale = 0.4;


};

#endif /* PARAMS_H_ */
