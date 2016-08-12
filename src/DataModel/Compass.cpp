/*
 * Compass.cpp
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */
#include<iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../tests/Helper.h"

#include "../ImageProcessing/Processor.h"
#include "../ImageProcessing/Histogram.h"
#include "../ImageProcessing/ImageView.h"

#include "Compass.h"
#include "Params.h"
#include "Calibration.h"
#include "Matching.h"
#include "Orientation.h"

#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

Compass::Compass() {
	// TODO Auto-generated constructor stub

	totalColors = std::ceil(255.0 / (double)Params::colorRedFactor);

	nCols = Params::nCols;
	features = new Features[nCols];

	ImageView viewer;

	Calibration cal;

	cal.initialize(*this);

	imshow("ha", this->features[0].colors[0].img_roi);

	this->renderFeaturesOri("hsv");
	this->renderFeaturesOri("rgb");
	this->renderFeatures("hsv");
	this->saveFeaturesIntoPanoramic();
//	this->renderFeatures("rgb");

//	this->renderFeatures1C(0);
//	this->renderFeatures1C(1);
//	this->renderFeatures1C(2);

	Processor * improc;

	//Mat img, frame = imread("/home/leonardo/workspace/VisualCompass/images/test1/01_test.png");
	//improc->transform(frame, img, "hsv");


//	viewer.renderScaledImage(img, "Frame");
//	imshow("u", pan);

	/*	// Compare color classes
	Mat img, frame = imread("/home/leonardo/workspace/VisualCompass/images/test1/08.png");
	img = improc->storeImageFeatures(*this, frame, 0, 0);
	Mat pan = this->loadPanoramicFeatures();
	viewer.renderScaledImage(pan, "Panoramic");

	Orientation result;
	Matching * compare;
	//imshow("a",this->panoramic); imshow("b",img);
	result = compare->getOrientation(pan, img);
	cout << "\nPosition: " << result.getPosition() << "\nBelief: " << result.getBelief();
	 */

	 // Compare processed hsv images
	//Mat img, frame = imread("/home/leonardo/workspace/VisualCompass/images/test1/T01.png");
	Mat img, frame = imread("/home/leonardo/workspace/VisualCompass/images/test1/T02.png");
	improc->transform(frame, img, "hsv", Params::panorStoreScale);
	Orientation result;
	Matching * compare;
	//imshow("a",this->panoramic); imshow("b",img);
	compare->getOrientation(this->panoramic, img);


//	Histogram hist;
//	hist.showHistogram2C(img);

	//	cout << this->features;
}

Compass::~Compass() {

}


/*
 * Return the index of the array of the first Feature Column in which image infos should be inserted
 */
int Compass::getFeatureIndex(int imgAngleV){

	// Gets the right angle
	int ang = imgAngleV >= 360 ? imgAngleV % 360
			: imgAngleV < 0 ? (360 + imgAngleV % 360 )
			: imgAngleV;

	int a = ang / this->getDegsByFeature();
	return a;
}

/*
 * Return the amount of features per image frame
 */
int Compass::getNFeaturesByImg(){
	return Params::camHOpening / this->getDegsByFeature();
}

/*
 * Return the amount degrees per Feature
 */
float Compass::getDegsByFeature(){
	return 360.0 / (float) this->nCols;
}


/*
 * Return the amount degrees per Feature
 */
int Compass::getWPixelsByFeature(){
	return Params::pxWidth / this->getNFeaturesByImg();
}

int Compass::getFrameWidth(){
	return Params::pxWidth;
}


/*
 * Return the amount degrees per Feature
 */
int Compass::getHPixelsByFeature(){
	return Params::pxHeight / Params::nRows;
}

int Compass::getNRows(){
	return Params::nRows;
}

int Compass::getFrameHeight(){
	return Params::pxHeight;
}



void Compass::saveFeaturesIntoPanoramic(){

	float scale = Params::panorStoreScale;
	int y = (Params::pxHeight/Params::nRows) * scale;
	int x = ((Params::pxWidth*(360/Params::camHOpening))/Params::nCols) * scale;

	Mat output = Mat(Params::nRows * y, Params::nCols * x, CV_8UC3);
	output.setTo(255);
	for (int i = 0; i < Params::nCols; i++){ // for each feature

		for (int j = 0; j < Params::nRows; j++){ // for each row

			Size size(x,y);
			Mat dst;
			if(!this->features[i].colors[j].img_roi.empty()){
				//resize(this->features[i].colors[j].img_roi, dst, size);
				resize(this->features[i].colors[j].img_roi, dst, Size(), scale, scale);
				Rect rect = Rect(x*i,j*y,x,y);
				dst.copyTo(output(rect));		//Rect(int x, int y, int width, int height)
			}
		}
	}

	output.copyTo(this->panoramic);
}


void Compass::renderFeatures(string colorspace){

	//imshow("ha", this->features[0].colors[0].img_roi);

	float scale = Params::panorViewScale;
	int y = (Params::pxHeight/Params::nRows) * scale;
	int x = ((Params::pxWidth*(360/Params::camHOpening))/Params::nCols) * scale;

	Mat output = Mat(Params::nRows * y, Params::nCols * x, CV_8UC3);
	output.setTo(255);
	for (int i = 0; i < Params::nCols; i++){ // for each feature

		for (int j = 0; j < Params::nRows; j++){ // for each row


			Size size(x,y);
			Mat dst;
			if(!this->features[i].colors[j].img_roi.empty()){
				//resize(this->features[i].colors[j].img_roi, dst, size);
				resize(this->features[i].colors[j].img_roi, dst, Size(), scale, scale);
				Rect rect = Rect(x*i,j*y,x,y);
				dst.copyTo(output(rect));		//Rect(int x, int y, int width, int height)
			}
		}
	}

	if(colorspace == "hsv"){
		imshow("Panoramic Image HSV", output);
	}else {
		Mat output2;
		cvtColor(output, output2, COLOR_HSV2BGR);
		imshow("Panoramic Image RGB", output2);
	}
}


void Compass::renderFeaturesOri(string colorspace){

	float scale = Params::panorViewScale;
	int y = (Params::pxHeight/Params::nRows) * scale;
	int x = ((Params::pxWidth*(360/Params::camHOpening))/Params::nCols) * scale;

	Mat output = Mat(Params::nRows * y, Params::nCols * x, CV_8UC3);
	output.setTo(255);
	for (int i = 0; i < Params::nCols; i++){ // for each feature

		for (int j = 0; j < Params::nRows; j++){ // for each row


			Size size(x,y);
			Mat dst;
			if(!this->features[i].colors[j].img_roi_ori.empty()){
				//resize(this->features[i].colors[j].img_roi, dst, size);
				resize(this->features[i].colors[j].img_roi_ori, dst, Size(), scale, scale);
				dst.copyTo(output(Rect(x*i,j*y,x,y)));		//Rect(int x, int y, int width, int height)
			}
		}
	}

	if(colorspace == "hsv"){
		imshow("Panoramic Original Image HSV", output);
	}else {
		Mat output2;
		cvtColor(output, output2, COLOR_HSV2BGR);
		imshow("Panoramic Original Image RGB", output2);
	}

}




void Compass::renderFeatures1C(int channel){

	float scale = Params::panorViewScale;
	int y = (Params::pxHeight/Params::nRows) * scale;
	int x = ((Params::pxWidth*(360/Params::camHOpening))/Params::nCols) * scale;

	Mat output = Mat(Params::nRows * y, Params::nCols * x, CV_8UC1);
	output.setTo(255);
	for (int i = 0; i < Params::nCols; i++){ // for each feature

		for (int j = 0; j < Params::nRows; j++){ // for each row

			Size size(x,y);
			Mat dst;
			if(!this->features[i].colors[j].img_roi.empty()){
				vector<Mat> imgChannels(3);
				split(this->features[i].colors[j].img_roi, imgChannels);

				//resize(this->features[i].colors[j].img_roi, dst, size);
				resize(imgChannels[channel], dst, Size(), scale, scale);
				dst.copyTo(output(Rect(x*i,j*y,x,y)));		//Rect(int x, int y, int width, int height)
			}
		}
	}

//	Mat output2; 	cvtColor(output, output2, COLOR_HSV2BGR); imshow("a", output2);
	imshow("Panoramic Image - Channel " + Helper::intToString(channel), output);

}



Mat Compass::loadPanoramicFeatures(){

	int y = (Params::nRows);
	int x = (Params::nCols);

	Mat output = Mat(y, x, CV_8UC1);
	output.setTo(-1);

	for (int feat = 0; feat < Params::nCols; feat++){ // for each feature
		for (int color = 0; color < Params::nRows; color++){ // for each row
			output.at<uchar>(color,feat) = this->features[feat].colors[color].mainColor1C.channel1;
		}
	}
	return output;
}


