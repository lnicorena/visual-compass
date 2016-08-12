
#include "ColorClass.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

ColorClass::ColorClass() {
}

ColorClass::~ColorClass() {
}


void ColorClass::storeImage(cv::Mat img, cv::Mat img_ori, int x1, int y1, int x2, int y2) {
	img_roi = cv::Mat(img.clone());
	img_roi_ori  = cv::Mat(img_ori.clone());
	roi_x_ini = x1;
	roi_x_end = x2;
	roi_y_ini = y1;
	roi_y_end = y2;
}


cv::Mat& ColorClass::getImgRoi() {
	return img_roi;
}

void ColorClass::setImgRoi(cv::Mat& imgRoi) {
	img_roi = imgRoi;
}

cv::Mat& ColorClass::getImgRoiOri() {
	return img_roi_ori;
}

void ColorClass::setImgRoiOri(cv::Mat& imgRoiOri) {
	img_roi_ori = imgRoiOri;
}

Color& ColorClass::getMainColor1C() {
	return mainColor1C;
}

void ColorClass::setMainColor1C(Color& mainColor1C) {
	this->mainColor1C = mainColor1C;
}

Color& ColorClass::getMainColor2C() {
	return mainColor2C;
}

void ColorClass::setMainColor2C(Color& mainColor2C) {
	this->mainColor2C = mainColor2C;
}

Color& ColorClass::getMainColor3C() {
	return mainColor3C;
}

void ColorClass::setMainColor3C(Color& mainColor3C) {
	this->mainColor3C = mainColor3C;
}

int ColorClass::getRoiXEnd() {
	return roi_x_end;
}

void ColorClass::setRoiXEnd(int roiXEnd) {
	roi_x_end = roiXEnd;
}

int ColorClass::getRoiXIni() {
	return roi_x_ini;
}

void ColorClass::setRoiXIni(int roiXIni) {
	roi_x_ini = roiXIni;
}

int ColorClass::getRoiYEnd() {
	return roi_y_end;
}

void ColorClass::setRoiYEnd(int roiYEnd) {
	roi_y_end = roiYEnd;
}

int ColorClass::getRoiYIni() {
	return roi_y_ini;
}

void ColorClass::setRoiYIni(int roiYIni) {
	roi_y_ini = roiYIni;
}

Color& ColorClass::getSecColor1C() {
	return secColor1C;
}

void ColorClass::setSecColor1C(Color& secColor1C) {
	this->secColor1C = secColor1C;
}

Color& ColorClass::getSecColor2C() {
	return secColor2C;
}

void ColorClass::setSecColor2C(Color& secColor2C) {
	this->secColor2C = secColor2C;
}

Color& ColorClass::getSecColor3C() {
	return secColor3C;
}

void ColorClass::setSecColor3C(Color& secColor3C) {
	this->secColor3C = secColor3C;
}
