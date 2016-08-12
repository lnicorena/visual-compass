
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "Params.h"
#include "Orientation.h"
#include "Matching.h"
#include "../ImageProcessing/ImageView.h"


using namespace cv;
using namespace std;

Matching::Matching() {
	// TODO Auto-generated constructor stub

}

Matching::~Matching() {
	// TODO Auto-generated destructor stub
}

Orientation Matching::getOrientation(Mat& panor_img, cv::Mat& img, int method, bool hsv_comparison){

	this->hsv_comparison = hsv_comparison;

	/*
	 * Template MAtching
	 * 		0: SQDIFF
	 *		1: SQDIFF NORMED
	 *		2: TM CCORR
	 *	 	3: TM CCORR NORMED
	 *		4: TM COEFF
	 *		5: TM COEFF NORMED
	 *
	 * */

	switch (method) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			return this->templateMatching(panor_img, img, method);
			break;
		default:

			return this->templateMatching(panor_img, img, CV_TM_CCOEFF);
			break;
	}

}


Orientation Matching::templateMatching(Mat& panor, cv::Mat img, int match_method){

//	Mat panor;
//	compass.panoramic.copyTo(panor);

	/// Create the result matrix
	int result_cols =  panor.cols - img.cols + 1;
	int result_rows = panor.rows - img.rows + 1;

	Mat result( result_cols, result_rows, CV_8UC1 );

	/// Do the Matching and Normalize
	matchTemplate(panor, img, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED ){
    	matchLoc = minLoc;
    }
    else{
    	matchLoc = maxLoc;
    }

	rectangle(panor, matchLoc, Point( matchLoc.x + img.cols , matchLoc.y + img.rows ), Scalar(0, 255, 0), 2);
	rectangle(result, matchLoc, Point( matchLoc.x + img.cols , matchLoc.y + img.rows ), Scalar(0, 255, 0), 2);

	ImageView viewer;
	imshow("panor",panor);
//	imwrite("asd.png", panor);
	imshow("result",result);
//	viewer.renderScaledImage(panor, "panor", 10, 10);
//	viewer.renderScaledImage(result, "result", 10, 10);

	float degree;

//	if(this->hsv_comparison)
		degree =floor((matchLoc.x * 360 )/(Params::pxWidth*360/Params::camVOpening * Params::panorStoreScale));
//	else
//		degree = floor(matchLoc.x *(360.0 / (float)Params::nCols));

	cout << "\n" << degree;
	Orientation o;
	o.setPosition(degree);

	return o;
}
