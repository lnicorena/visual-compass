/*
 * ImageView.h
 *
 *  Created on: 04/08/2016
 *      Author: leonardo
 */

#ifndef IMAGEVIEW_H_
#define IMAGEVIEW_H_

#include <opencv2/imgproc/imgproc.hpp>
#include <string>

class ImageView {
public:
	ImageView();
	virtual ~ImageView();

	void renderScaledImage(cv::Mat& img, std::string name = "Image", float hscale = 20, float vscale = 10);
	void renderImageFeatures(cv::Mat& image);

};

#endif /* IMAGEVIEW_H_ */
