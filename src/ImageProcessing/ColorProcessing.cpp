/*
 * ColorProcessing.cpp
 *
 *  Created on: 31/05/2016
 *      Author: leonardo
 */

#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

#include "ColorProcessing.h"

ColorProcessing::ColorProcessing() {
	// TODO Auto-generated constructor stub

}

ColorProcessing::~ColorProcessing() {
	// TODO Auto-generated destructor stub
}

void ColorProcessing::testOpeningClosing() {

	Mat original_image, image_back_to_bgr, hsv_imgage;
	original_image = imread(
			"/home/leonardo/workspace/VisualCompass/images/case1.jpg");
	imshow("BGR Original Image", original_image);

	this->bgrToHsv(original_image, hsv_imgage);

	this->imageOpening(hsv_imgage, 5);
	this->imageClosing(hsv_imgage, 5);

	this->colorReduction(hsv_imgage, 70);

	imshow("BGR to HSV Image", hsv_imgage);

	this->hsvToBgr(hsv_imgage, image_back_to_bgr);
	imshow("HSV to BGR Image", image_back_to_bgr);
}

void ColorProcessing::testColorspace() {
	ColorProcessing * color;
	Mat original_image, image_back_to_bgr, hsv_imgage;

	original_image = imread(
			"/home/leonardo/workspace/VisualCompass/images/case1.jpg");

	imshow("BGR Original Image", original_image);

	color->bgrToHsv(original_image, hsv_imgage);

	imshow("BGR to HSV Image", hsv_imgage);

	color->hsvToBgr(hsv_imgage, image_back_to_bgr);
	imshow("HSV to BGR Image", image_back_to_bgr);
}

void ColorProcessing::testHsvChannels() { /* Reference: http://silveiraneto.net/2009/12/08/opencv-hue-saturation-and-value/ */

	Mat img, hsv;

	/* Load command line passed image, check it. */
	//img = imread("/home/leonardo/workspace/VisualCompass/images/sunset2.jpg");
	img = imread("/home/leonardo/workspace/VisualCompass/images/case1.jpg");
	imshow("1", img);
	/* Convert from Red-Green-Blue to Hue-Saturation-Value */
	cvtColor(img, hsv, COLOR_BGR2HSV);
	imshow("2", hsv);

	/* Split hue, saturation and value of hsv on them */
	vector<Mat> hsvChannels(3);
	split(hsv, hsvChannels);

/*
	imshow("original", img);
	imshow("hsv", hsv);
	imshow("hue", hsvChannels[0]);
	imshow("saturation", hsvChannels[1]);
	imshow("value", hsvChannels[2]);
*/

	int histSize[3] = {8, 8, 8};
	float range[2] = {0, 256};
	const float * ranges[3] = {range, range, range};
	int channels[3] = {0, 1, 2};
	Mat hist;
	calcHist(&img, 1, channels, Mat(), hist, 3, histSize, ranges);
	cout << "Hist.dims = " << hist.dims << endl;
	cout << "Value: " << hist.at<double>(0,0, 0) << endl;
	cout << "Hist.rows = "<< hist.rows << endl;
	cout << "Hist.cols = "<< hist.cols << endl;
	for (MatConstIterator_<double> it = hist.begin<double>(); it != hist.end<double>(); it++) {
		cout << "Value: " << *it << "\n";
	}

	cvWaitKey(0);

}
void ColorProcessing::bgrToHsv(Mat& image, Mat& output) {
	//Convert the captured frame from BGR to HSV
	cvtColor(image, output, COLOR_BGR2HSV);

	/*** test
	for (int i=0; i < 100; i++){
		int x =  random()%image.rows,y = random()%image.cols;
		cout << "\n(" << x << "," << y << ")\t"<< image.at<Vec3b>(x,y) << "\t-> " << " " << output.at<Vec3b>(x,y);
	}
	*/

}

void ColorProcessing::hsvToBgr(Mat& image, Mat& output) {
	cvtColor(image, output, COLOR_HSV2BGR);
}

void ColorProcessing::imageOpening(Mat& image, int size) {

	//morphological opening (remove small objects from the foreground)
	erode(image, image, getStructuringElement(MORPH_ELLIPSE, Size(size, size)));
	dilate(image, image, getStructuringElement(MORPH_ELLIPSE, Size(size, size)));

}

void ColorProcessing::imageClosing(Mat& image, int size) {

	//morphological closing (fill small holes in the foreground)
	dilate(image, image, getStructuringElement(MORPH_ELLIPSE, Size(size, size)));
	erode(image, image, getStructuringElement(MORPH_ELLIPSE, Size(size, size)));

}

//@TODO Reduzir o canal Hue (quando for HSV) com valores entre 0 - 180
void ColorProcessing::colorReduction(cv::Mat& image, int div) { /*div = 6: 43+, 5: 52+, 4: 64+,  3: 86+, 2: 128+ */

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels();
	if (image.isContinuous()) {
		// then no padded pixels
		nc = nc * nl;
		nl = 1; // it is now a 1D array
	}
	// this loop is executed only once
	// in case of continuous images
	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			// process each pixel ---------------------

			//floors the division result to the nearest lower integer
			data[i] = data[i] / div * div + div / 2;

			//floors the division result to the nearest multiple of div
			//data[i] = data[i] - data[i] % div + div/2;

			// end of pixel processing ----------------
		} // end of line
	}

}


void ColorProcessing::colorReductionFaster(cv::Mat& image, int div) {
	int nl= image.rows; // number of lines
	int nc= image.cols ; // number of columns
	// is it a continous image?
	if (image.isContinuous()) {
	// then no padded pixels
	nc= nc*nl;
	nl= 1; // it is now a 1D array
	}
	int n= static_cast<int>(
	log(static_cast<double>(div))/log(2.0));
	// mask used to round the pixel value
	uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0
	// for all pixels
	for (int j=0; j<nl; j++) {
	// pointer to first column of line j
	uchar* data= image.ptr<uchar>(j);
	for (int i=0; i<nc; i++) {
		// process each pixel ---------------------

		*data++= *data&mask + div/2;
		*data++= *data&mask + div/2;
		*data++= *data&mask + div/2;
		// end of pixel processing ----------------
		} // end of line
	}

}

void ColorProcessing::colorReductionSimple(cv::Mat& image, int div) {

	int nl = image.rows;                    // number of lines
	int nc = image.cols * image.channels(); // number of elements per line
	for (int j = 0; j < nl; j++) {
		// get the address of row j
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {
			// process each pixel
			data[i] = data[i] / div * div + div / 2;

		}
	}
}
