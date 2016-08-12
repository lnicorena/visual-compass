/*
 * Processor.cpp
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include "../DataModel/Params.h"

#include "ColorProcessing.h"
#include "Processor.h"
#include "Histogram.h"
#include "../DataModel/Compass.h"

using namespace std;
using namespace cv;

Processor::Processor() {
	// TODO Auto-generated constructor stub

}

Processor::~Processor() {
	// TODO Auto-generated destructor stub
}


void Processor::execute(){

	string img_src = "/home/leonardo/Imagens/fish.png";
	//Processor::getImage(img_src, true);

	Mat image, image2, hsvimg;
	image = this->getImage(img_src);
	ColorProcessing * color_processor;

	//color_processor->testColorspace();
	color_processor->testHsvChannels();
	//color_processor->testOpeningClosing();

}

void Processor::transform(Mat& image, Mat& output, string format, float scale){

	ColorProcessing * color_processor;

	//image = imread("/home/leonardo/workspace/VisualCompass/images/case1.jpg");
	//imshow("BGR Original Image", image);
	Mat hsv_image;

	color_processor->bgrToHsv(image, hsv_image);

	color_processor->imageOpening(hsv_image, Params::imOpeningK);
	color_processor->imageClosing(hsv_image, Params::imClosingK);

	color_processor->colorReduction(hsv_image, Params::colorRedFactor);

	if (scale != 1.0)
		resize(hsv_image, output, Size(), scale, scale);


	if (format != "hsv"){
		color_processor->hsvToBgr(hsv_image, output);
	} else if (scale == 1.0){
		hsv_image.copyTo(output);
	}

}


Mat Processor::storeImageFeatures(Compass& compass, Mat& src_image, int hAngle, int vAngle, bool update_compass){

	//Debug
	bool draw_lines = false;		// default false
	bool return_image_ori_size = true;// default false


	Mat image;
	this->transform(src_image, image, "hsv");

	Histogram hist;

	/* Load the feature index to be inserted
	 * */
	int fStart = compass.getFeatureIndex(hAngle),
		fTotal= compass.getNFeaturesByImg(),
		fEnd = fTotal + fStart,
		// Load the pixels count of each feature
		fWPx = compass.getWPixelsByFeature(),
		fHPx = compass.getHPixelsByFeature(),
		wPx = compass.getFrameWidth(),
		hPx = compass.getFrameHeight(),
		nRows = compass.getNRows();

	int vscale = 1, hscale=1;
	Mat return_image = Mat(Params::nRows * hscale, (Params::nCols/(360/Params::camHOpening)) * vscale, CV_8UC1);
	return_image.setTo(-1);
	int ret_col = 0, ret_row = 0;

	int col = 0;
	// For each feature (to be inserted on the compass)
	for (int f = fStart; f < fEnd; f++){

		// goes through the pixels of the feature
		//for (int k = f * fWPx; k < f*fWPx+fWPx; k++){
		for (int k = col * fWPx; k < col*fWPx+fWPx; k+=fWPx){

			if(k+fWPx <= image.cols){
				for (int row = 0; row < nRows; row++){

					int x1 = row*fHPx,
						y1 = row*fHPx+fHPx-1,
						x2 = k,
						y2 = k+fWPx-1;


					// Extract de Region of Interest to be analyzed
					cv::Mat imageROI= image(cv::Range(x1,y1), cv::Range(x2,y2));
					cv::Mat imageROI_ori= src_image(cv::Range(x1,y1), cv::Range(x2,y2));
					//imshow(Helper::intToString(k) + " " + Helper::intToString(row*fHPx), imageROI);

					std::pair<Color, Color> max_colors1C = hist.getMaxHue(imageROI);
					std::pair<Color, Color> max_colors2C = hist.getMaxHueSat(imageROI);



					if(draw_lines){
						for(int p=0; p<=imageROI.cols; p++){
							for(int z=0; z<3; z++)
							{
								imageROI.at<Vec3b>(imageROI.rows - z,p)[0] = 255;
								imageROI.at<Vec3b>(imageROI.rows - z,p)[1] = 255;
								imageROI.at<Vec3b>(imageROI.rows - z,p)[2] = 255;
							}
						}
						for(int q=0; q<=imageROI.rows; q++){
							for(int z=0; z<3; z++)
							{
								imageROI.at<Vec3b>(q,imageROI.cols - z)[0] = 255;
								imageROI.at<Vec3b>(q,imageROI.cols - z)[1] = 255;
								imageROI.at<Vec3b>(q,imageROI.cols - z)[2] = 255;
							}
						}
					}

					if(update_compass){
						compass.features[f].colors[row].storeImage(imageROI,imageROI_ori, x1, y1, x2, y2);

						//cout << "(" << x1 << "," << y1 << ") " << "(" << x2 << "," << y2 << ")\n";

						compass.features[f].colors[row].mainColor1C = max_colors1C.first;
						compass.features[f].colors[row].secColor1C = max_colors1C.second;

						compass.features[f].colors[row].mainColor2C = max_colors2C.first;
						compass.features[f].colors[row].secColor2C = max_colors2C.second;

						//cout << "\n\nColor1::\n" << max_colors2C.first.toString();
					}



//						for (int j=ret_col* hscale; j <= ret_col * hscale + hscale - 1; j++ )
//							for (int i=ret_row * vscale; i <= ret_row * vscale +vscale - 1; i++ ){
					for (int j=(f - fStart)* hscale; j <= (f-fStart) * hscale + hscale - 1; j++ )
						for (int i=row * vscale; i <= row * vscale +vscale - 1; i++ ){
								return_image.at<uchar>(i,j) = max_colors1C.first.channel1;
							}
		//			return_image.at<uchar>(ret_row,ret_col) = max_colors1C.first.channel1;

					ret_row++;
				}
			}

			/*
			if(f % 2 == 0){
				for (int y=0; y<image.rows; y++){

					//cout << "\n" << image.at<Vec3b>(y,k);

					image.at<Vec3b>(y,k)[0]= image.at<Vec3b>(y,k)[0] + 30;
					image.at<Vec3b>(y,k)[1]= image.at<Vec3b>(y,k)[1] + 30;
					image.at<Vec3b>(y,k)[2]= 0;

				}
			}

			imshow("h", image);
			*/


		}
		ret_col++;
		col++;
	}
	if(return_image_ori_size)
		return image;
	else
		return return_image;
}


Mat Processor::getImage(string img_src, bool show_img){

	Mat image;
	image = imread( img_src, 1 /* 1 returns image in 3 channel BGR colorspace*/);

	if( !image.data ){
	  cout << "No image data \n";
	}

	if(show_img){
		namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
		imshow( "Display Image", image );
	}
	return image;
}


