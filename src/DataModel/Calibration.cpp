/*
 * Calibration.cpp
 *
 *  Created on: 20/07/2016
 *      Author: leonardo
 */
#include<iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../ImageProcessing/Processor.h"
#include "../ImageProcessing/Histogram.h"


#include "../tests/Helper.h"

#include "Compass.h"

#include "Params.h"

#include <sstream>
#include <string>

using namespace std;
using namespace cv;


#include "Calibration.h"


Calibration::Calibration() {
	// TODO Auto-generated constructor stub
}

Calibration::~Calibration() {
	// TODO Auto-generated destructor stub
}


void Calibration::initialize(Compass& compass){

	string loc = "/home/leonardo/workspace/VisualCompass/images/test1/",
			ext = ".png";

	string images[8][3] = {
			//name,hAngle,vAngle
			{"01", "0"  , "0"},
			{"02", "45" , "0"},
			{"03", "90" , "0"},
			{"04", "135", "0"},
			{"05", "180", "0"},
			{"06", "225", "0"},
			{"07", "270", "0"},
			{"08", "315", "0"}
	};

	Histogram hist;

	for (int i=0; i < 8; i++){

		string img_loc = loc + images[i][0] + ext;
		//cout << img_loc;
		//load img
		cv::Mat original_img = cv::imread(img_loc),
				image;

		int hAngle = atoi(images[i][1].c_str()),
			vAngle = atoi(images[i][2].c_str());


		Processor * improc;
		image = improc->storeImageFeatures(compass, original_img, hAngle, vAngle, true);
		//imwrite("cal_test1_img_hsv_" + images[i][0] + ext, image);
	}
}
