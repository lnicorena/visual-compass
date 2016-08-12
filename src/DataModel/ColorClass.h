/*
 * ColorClass.h
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#ifndef COLORCLASS_H_
#define COLORCLASS_H_

#include <opencv2/imgproc/imgproc.hpp>
#include "Color.h"
// http://opencv-srf.blogspot.com.br/2010/09/object-detection-using-color-seperation.html

class ColorClass {
public:
	ColorClass();
	virtual ~ColorClass();

	void setMainColor(int hue, int sat, int val);
	void setSecundColor(int hue, int sat, int val);

	Color mainColor1C;
	Color mainColor2C;
	Color mainColor3C;

	Color secColor1C;
	Color secColor2C;
	Color secColor3C;


	void storeImage(cv::Mat img, cv::Mat img_ori, int x1, int y1, int x2, int y2);

	cv::Mat img_roi;
	cv::Mat img_roi_ori;
	int roi_x_ini;
	int roi_x_end;
	int roi_y_ini;
	int roi_y_end;


	cv::Mat& getImgRoi();

	void setImgRoi(cv::Mat& imgRoi);

	cv::Mat& getImgRoiOri();

	void setImgRoiOri(cv::Mat& imgRoiOri);

	Color& getMainColor1C();

	void setMainColor1C(Color& mainColor1C);

	Color& getMainColor2C();

	void setMainColor2C(Color& mainColor2C);

	Color& getMainColor3C();

	void setMainColor3C(Color& mainColor3C);

	int getRoiXEnd();

	void setRoiXEnd(int roiXEnd);

	int getRoiXIni();

	void setRoiXIni(int roiXIni);

	int getRoiYEnd();

	void setRoiYEnd(int roiYEnd);

	int getRoiYIni();

	void setRoiYIni(int roiYIni);

	Color& getSecColor1C();

	void setSecColor1C(Color& secColor1C);

	Color& getSecColor2C();

	void setSecColor2C(Color& secColor2C);

	Color& getSecColor3C();

	void setSecColor3C(Color& secColor3C);


};

#endif /* COLORCLASS_H_ */
