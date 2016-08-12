#include "Histogram.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#include "../DataModel/Color.h"

using namespace std;
using namespace cv;

Histogram::Histogram() {
}

Histogram::~Histogram() {
}
void Histogram::getHistogram1C(Mat& src, int channel) {
	Mat dst;

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> channels;
	split(src, channels);

	/// Establish the number of bins
	int histSize = 16;

	/// Set the ranges
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat hist;

	/// Compute the histograms:
	calcHist(&channels[0], 1, 0, Mat(), hist, 1, &histSize, &histRange,
			uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double) hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());


	if(false){
		/// Draw for each channel
		for (int i = 1; i < histSize; i++) {
			line(histImage,
					Point(bin_w * (i - 1),
							hist_h - cvRound(hist.at<float>(i - 1))),
					Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
					Scalar(255, 0, 0), 2, 8, 0);
		}

		/// Display
		namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
		imshow("calcHist Demo", histImage);
	}
}

void Histogram::showHistogram2C(Mat& hsv) {

	    // Quantize the hue to 30 levels
	    // and the saturation to 32 levels
	    int hbins = 30, sbins = 32;
	    int histSize[] = {hbins, sbins};
	    // hue varies from 0 to 179, see cvtColor
	    float hranges[] = { 0, 180 };
	    // saturation varies from 0 (black-gray-white) to
	    // 255 (pure spectrum color)
	    float sranges[] = { 0, 256 };
	    const float* ranges[] = { hranges, sranges };
	    MatND hist;
	    // we compute the histogram from the 0-th and 1-st channels
	    int channels[] = {0, 1};

	    calcHist( &hsv, 1, channels, Mat(), // do not use mask
	             hist, 2, histSize, ranges,
	             true, // the histogram is uniform
	             false );
	    double maxVal=0;
	    minMaxLoc(hist, 0, &maxVal, 0, 0);

	    int scale = 10;
	    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

	    for( int h = 0; h < hbins; h++ )
	        for( int s = 0; s < sbins; s++ )
	        {
	            float binVal = hist.at<float>(h, s);
	            int intensity = cvRound(binVal*255/maxVal);
	            rectangle( histImg, Point(h*scale, s*scale),
	                        Point( (h+1)*scale - 1, (s+1)*scale - 1),
	                        Scalar::all(intensity),
	                        CV_FILLED );
	            if(binVal!=0 || intensity!=0)
	            	cout <<"["<< h<<","<< s<< "] = "<< binVal <<"  -->  "<< intensity << "\n";
	        }
	    cout << "\nMAx val: "<<maxVal;
	    namedWindow( "Source", 1 );
	    imshow( "Source", hsv );

	    namedWindow( "H-S Histogram", 1 );
	    imshow( "H-S Histogram", histImg );
}

std::pair<Color, Color> Histogram::getMaxHue(Mat& hsv) {

		int hbins = 256;
	    int histSize[] = {hbins};
	    // hue varies from 0 to 179, see cvtColor
	    float hranges[] = { 0, 180 };
	    const float* ranges[] = { hranges };
	    MatND hist;
	    int channels[] = {0};

	    calcHist( &hsv, 1, channels, Mat(), // do not use mask
	             hist, 1, histSize, ranges,
	             true, // the histogram is uniform
	             false );
	    double maxVal=0;
	    minMaxLoc(hist, 0, &maxVal, 0, 0);

	    std::pair<Color, Color> max_colors;
	    Color maxColor, secMaxColor;
	    int sec_maxVal = 0;
	    int count = 0;

	    for( int h = 0; h < hbins; h++ )
	        {
	            float binVal = hist.at<float>(h);
	            count += binVal;
	            int intensity = cvRound(binVal*100/maxVal);

	            if(binVal == maxVal){
	            	maxColor.channel1 = h;
	            	maxColor.freq = binVal;
	            	maxColor.intensity = intensity;
	            	max_colors.first = maxColor;
	            	continue;
	            }
	            if(sec_maxVal < binVal && binVal != maxVal){
	            	sec_maxVal = binVal;
	            	secMaxColor.channel1 = h;
					secMaxColor.intensity = intensity;
	            	secMaxColor.freq = binVal;
	            	max_colors.second = secMaxColor;
	            }
	            //if(binVal!=0 || intensity!=0)
	            //	cout <<"["<< h<<","<< s<< "] = "<< binVal <<"  -->  "<< intensity << "\n";
	        }
	    max_colors.first.freq = max_colors.first.freq * 100 / count;
	    max_colors.second.freq = max_colors.second.freq * 100 / count;

	    //cout << "\nMAx val: "<<maxVal;
	    //cout << "\n\nColor1::\n" << max_colors.first.toString() << "\n\nColor2::\n" << max_colors.second.toString();

	    return max_colors;
}



std::pair<Color, Color> Histogram::getMaxHueSat(Mat& hsv) {

	    // Quantize the hue to 30 levels
	    // and the saturation to 32 levels
	    int hbins = 256, sbins = 256;
	    int histSize[] = {hbins, sbins};
	    // hue varies from 0 to 179, see cvtColor
	    float hranges[] = { 0, 180 };
	    // saturation varies from 0 (black-gray-white) to
	    // 255 (pure spectrum color)
	    float sranges[] = { 0, 256 };
	    const float* ranges[] = { hranges, sranges };
	    MatND hist;
	    // we compute the histogram from the 0-th and 1-st channels
	    int channels[] = {0, 1};

	    calcHist( &hsv, 1, channels, Mat(), // do not use mask
	             hist, 2, histSize, ranges,
	             true, // the histogram is uniform
	             false );
	    double maxVal=0;
	    minMaxLoc(hist, 0, &maxVal, 0, 0);

	    int scale = 1;
	    Mat histImg = Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);

	    std::pair<Color, Color> max_colors;
	    Color maxColor, secMaxColor;
	    int sec_maxVal = 0;
	    int count = 0;

	    for( int h = 0; h < hbins; h++ )
	        for( int s = 0; s < sbins; s++ )
	        {
	            float binVal = hist.at<float>(h, s);
	            count += binVal;
	            int intensity = cvRound(binVal*100/maxVal);

	            if(binVal == maxVal){
	            	maxColor.channel1 = h;
	            	maxColor.channel2 = s;
	            	maxColor.freq = binVal;
	            	maxColor.intensity = intensity;
	            	max_colors.first = maxColor;
	            	continue;
	            }
	            if(sec_maxVal < binVal && binVal != maxVal){
	            	sec_maxVal = binVal;
	            	secMaxColor.channel1 = h;
					secMaxColor.channel2 = s;
	            	secMaxColor.intensity = intensity;
	            	secMaxColor.freq = binVal;

	            	max_colors.second = secMaxColor;
	            }

	            /*
	            // Show img hist
	            int intensity = cvRound(binVal*255/maxVal);
	            rectangle( histImg, Point(h*scale, s*scale),
	                        Point( (h+1)*scale - 1, (s+1)*scale - 1),
	                        Scalar::all(intensity),
	                        CV_FILLED );
				*/


	            //if(binVal!=0 || intensity!=0)
	            //	cout <<"["<< h<<","<< s<< "] = "<< binVal <<"  -->  "<< intensity << "\n";

	        }
	    max_colors.first.freq = max_colors.first.freq * 100 / count;
	    max_colors.second.freq = max_colors.second.freq * 100 / count;

	    //cout << "\nMAx val: "<<maxVal;
	    //cout << "\n\nColor1::\n" << max_colors.first.toString() << "\n\nColor2::\n" << max_colors.second.toString();


	    /*
	     // show img hist
	    namedWindow( "Source", 1 );
	    imshow( "Source", hsv );

	    namedWindow( "H-S Histogram", 1 );
	    imshow( "H-S Histogram", histImg );
	    */

	    return max_colors;
}


std::pair<Color, Color> Histogram::getMaxHueSatVal(Mat& hsv) {

	    // Quantize the hue to 30 levels
	    // and the saturation to 32 levels
	    int hbins = 256, sbins = 256, vbins = 256;
	    int histSize[] = {hbins, sbins, vbins};
	    // hue varies from 0 to 179, see cvtColor
	    float hranges[] = { 0, 180 };
	    // saturation varies from 0 (black-gray-white) to
	    // 255 (pure spectrum color)
	    float sranges[] = { 0, 256 };
	    float vranges[] = { 0, 256 };
	    const float* ranges[] = { hranges, sranges, vranges };
	    MatND hist;
	    // we compute the histogram from the 0-th and 2-st channels
	    int channels[] = {0, 1, 2};

	    calcHist( &hsv, 1, channels, Mat(), // do not use mask
	             hist, 3, histSize, ranges,
	             true, // the histogram is uniform
	             false );
	    double maxVal=0;

	    for( int h = 0; h < hbins; h++ )
	        for( int s = 0; s < sbins; s++ )
		        for( int v = 0; v < sbins; v++ ){
		        	if(maxVal < hist.at<float>(h, s, v))
		        		maxVal = hist.at<float>(h, s, v);
		        }

	    //minMaxLoc(hist, 0, &maxVal, 0, 0);

	    std::pair<Color, Color> max_colors;
	    Color maxColor, secMaxColor;
	    int sec_maxVal = 0;
	    int count = 0;

	    for( int h = 0; h < hbins; h++ )
	        for( int s = 0; s < sbins; s++ )
		        for( int v = 0; v < sbins; v++ )
	        {
	            float binVal = hist.at<float>(h, s, v);
	            count += binVal;
	            int intensity = cvRound(binVal*100/maxVal);

	            if(binVal == maxVal){
	            	maxColor.channel1 = h;
	            	maxColor.channel2 = s;
	            	maxColor.channel3 = v;
	            	maxColor.freq = binVal;
	            	maxColor.intensity = intensity;
	            	max_colors.first = maxColor;
	            	continue;
	            }
	            if(sec_maxVal < binVal && binVal != maxVal){
	            	sec_maxVal = binVal;
	            	secMaxColor.channel1 = h;
					secMaxColor.channel2 = s;
					secMaxColor.channel3 = v;
	            	secMaxColor.intensity = intensity;
	            	secMaxColor.freq = binVal;

	            	max_colors.second = secMaxColor;
	            }

	            //if(binVal!=0 || intensity!=0)
	            //	cout <<"["<< h<<","<< s<< "] = "<< binVal <<"  -->  "<< intensity << "\n";

	        }
	    max_colors.first.freq = max_colors.first.freq * 100 / count;
	    max_colors.second.freq = max_colors.second.freq * 100 / count;

	    cout << "\nMAx val: "<<maxVal;
	    cout << "\n\nColor1::\n" << max_colors.first.toString() << "\n\nColor2::\n" << max_colors.second.toString();

	    return max_colors;
}

void Histogram::manualScanning(Mat& image){

	vector<int> histogram(256);
	for (int i = 0; i < image.rows; i++)
		for (int j=0; j < image.cols; j++){
			//cout << image.at<Vec3b>(i,j)<<":" << image.at<Vec3b>(i,j) << ":"<<image.at<Vec3b>(i,j);
	    	//histogram[(int)image.at<Vec3b>(i,j).val]++;
			//hist[]
		}
	cout << "ha";
}


void Histogram::showHistogram3C(Mat& src) {
	Mat dst;

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> channels;
	split(src, channels);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&channels[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange,
			uniform, accumulate);
	calcHist(&channels[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange,
			uniform, accumulate);
	calcHist(&channels[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange,
			uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double) hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++) {
		line(histImage,
				Point(bin_w * (i - 1),
						hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
				Scalar(255, 0, 0), 2, 8, 0);
		line(histImage,
				Point(bin_w * (i - 1),
						hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
				Scalar(0, 255, 0), 2, 8, 0);
		line(histImage,
				Point(bin_w * (i - 1),
						hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
				Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

}

void Histogram::test() {
	Mat gray = imread("/home/leonardo/Imagens/fish.png", 0);
	namedWindow("Gray", 1);
	imshow("Gray", gray);

	// Initialize parameters
	int histSize = 256;    // bin size
	float range[] = { 0, 255 };
	const float *ranges[] = { range };

	// Calculate histogram
	MatND hist;
	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	// Show the calculated histogram in command window
	double total;
	total = gray.rows * gray.cols;
	for (int h = 0; h < histSize; h++) {
		float binVal = hist.at<float>(h);
		cout << " " << binVal;
	}

	// Plot the histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double) hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++) {
		line(histImage,
				Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
				Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow("Result", 1);
	imshow("Result", histImage);

	waitKey(0);

}
