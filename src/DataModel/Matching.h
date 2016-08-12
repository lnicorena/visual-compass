
#include "Compass.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "Orientation.h"

#ifndef MATCHING_H_
#define MATCHING_H_

class Matching {
public:
	Matching();
	virtual ~Matching();

//	Orientation* getOrientation(Compass& compass, cv::Mat& img, int type);
	Orientation getOrientation(cv::Mat& panor_img, cv::Mat& img, int method = 0, bool hsv_comparison = false);

private:
	Orientation templateMatching(cv::Mat& panor, cv::Mat img, int match_method);

	bool hsv_comparison;

};

#endif /* MATCHING_H_ */
