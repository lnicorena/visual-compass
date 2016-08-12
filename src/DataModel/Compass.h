/*
 * Compass.h
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#include "Features.h"
#include <string>

#ifndef COMPASS_H_
#define COMPASS_H_

class Compass {
public:
	Compass();
	virtual ~Compass();

	// Each column is an array os features
	Features * features;
	int nCols;

	int totalColors;

	cv::Mat panoramic;

	int getFeatureIndex(int imgAngleV);
	int getNFeaturesByImg();
	float getDegsByFeature();
	int getWPixelsByFeature();
	int getFrameWidth();
	int getHPixelsByFeature();
	int getNRows();
	int getFrameHeight();

	void saveFeaturesIntoPanoramic();
	void renderFeatures(std::string colorspace = "hsv");
	void renderFeaturesOri(std::string colorspace = "hsv");
	void renderFeatures1C(int channel = 0);
	cv::Mat loadPanoramicFeatures();

private:

};


#endif /* COMPASS_H_ */
