/*
 * ImageView.cpp
 *
 *  Created on: 04/08/2016
 *      Author: leonardo
 */

#include "ImageView.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../DataModel/Params.h"

using namespace std;
using namespace cv;


ImageView::ImageView() {
	// TODO Auto-generated constructor stub

}

ImageView::~ImageView() {
	// TODO Auto-generated destructor stub
}

void ImageView::renderScaledImage(Mat& img, string name, float hscale, float vscale){

		Mat output = Mat(img.rows * hscale, img.cols * vscale, CV_8UC1);
		output.setTo(0);

		for (int col = 0; col < img.cols; col++){ // for each feature

			for (int row = 0; row < img.rows; row++){ // for each row
				for (int i=col * vscale; i <= col * vscale +vscale - 1; i++ )
					for (int j=row * hscale; j <= row * hscale +hscale- 1; j++ ){
						output.at<uchar>(j,i) = img.at<uchar>(row,col);
					}
			}
		}
		imshow(name, output);

}


void ImageView::renderImageFeatures(Mat& image){

	float hscale = 20;
	float vscale = 10;

	int y = (Params::nRows) * hscale;
	int x = (Params::nCols) * vscale;

	Mat output = Mat(y, x, CV_8UC1);
	output.setTo(0);

	for (int feat = 0; feat < Params::nCols; feat++){ // for each feature

		for (int color = 0; color < Params::nRows; color++){ // for each row
			for (int i=feat * vscale; i <= feat * vscale +vscale - 1; i++ )
				for (int j=color * hscale; j <= color * hscale +hscale- 1; j++ ){
			//		output.at<uchar>(j,i) = this->features[feat].colors[color].mainColor1C.channel1;
			//		cout << "\n" << i << "," << j;
				}
		}
	}
	imshow("a", output);

}



