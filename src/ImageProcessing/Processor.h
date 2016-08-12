/*
 * Processor.h
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "../DataModel/Compass.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Processor {
public:
	Processor();
	virtual ~Processor();

	cv::Mat getImage(string img_src, bool show_img = false);

	void execute();
	void transform(Mat& image, Mat& output, string format, float resize = 1.0);
	Mat storeImageFeatures(Compass& compass, Mat& src_image, int hAngle, int vAngle,
			bool update_compass = false);
};

#endif /* PROCESSOR_H_ */
