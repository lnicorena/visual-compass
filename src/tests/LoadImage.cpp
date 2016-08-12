/*
 * LoadImage.cpp
 *
 *  Created on: 28/05/2016
 *      Author: leonardo
 */

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#include "LoadImage.h"

LoadImage::LoadImage() {
	// TODO Auto-generated constructor stub

}

LoadImage::~LoadImage() {
	// TODO Auto-generated destructor stub
}


void LoadImage::test(){
	  Mat image;
	  //image = imread( argv[1], 1 );
	  image = imread( "/home/leonardo/Imagens/fish.png",1 );
	  //if( argc != 2 || !image.data )
	  if( !image.data )
	    {
	      cout << "No image data \n";
	    }

	  namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	  imshow( "Display Image", image );

}
