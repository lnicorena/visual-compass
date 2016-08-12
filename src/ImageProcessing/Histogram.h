
#ifndef __Histogram_h_
#define __Histogram_h_

#include <opencv2/imgproc/imgproc.hpp>
#include "../DataModel/Color.h"

class Histogram
{
public:

	Histogram();

	~Histogram();

	void getHistogram1C(cv::Mat& src, int channel);
	void showHistogram2C(cv::Mat& hsv);
	void showHistogram3C(cv::Mat& src);

	void manualScanning(cv::Mat& image);

	std::pair<Color, Color> getMaxHue(cv::Mat& hsv);
	std::pair<Color, Color> getMaxHueSat(cv::Mat& hsv);
	std::pair<Color, Color> getMaxHueSatVal(cv::Mat& hsv);

	void test();

private:

};

#endif

