/*
 * Perfomance.cpp
 *
 *  Created on: 01/06/2016
 *      Author: leonardo
 */

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#include "Perfomance.h"


Perfomance::Perfomance() {
	// TODO Auto-generated constructor stub

}

Perfomance::~Perfomance() {
	// TODO Auto-generated destructor stub
}

void Perfomance::test(){
	double duration;
	duration = static_cast<double>(cv::getTickCount());

	/* run the program here */

	duration = static_cast<double>(cv::getTickCount())-duration;
	duration /= cv::getTickFrequency(); // the elapsed time in ms
}
