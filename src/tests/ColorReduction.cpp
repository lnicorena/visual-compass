/*
 * ColorReduction.cpp
 *
 *  Created on: 31/05/2016
 *      Author: leonardo
 */
#include <iostream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ColorReduction.h"

using namespace std;

ColorReduction::ColorReduction() {
	// TODO Auto-generated constructor stub

}

ColorReduction::~ColorReduction() {
	// TODO Auto-generated destructor stub
}

void ColorReduction::test(){

	int divs [] = {1, 43, 52, 64, 86, 128};
	int len = sizeof (divs)/ sizeof( divs[0]);
	cv::Mat inputs[6];
	printf("há: %d", len);

	for(int i = 0; i < len; i++){
//		inputs[i] = cv::imread("/home/leonardo/Imagens/fish.png");
		inputs[i] = cv::imread("/home/leonardo/workspace/VisualCompass/images/case1.jpg");

		if (inputs[i].empty())
		{
			cout << "!!! Failed imread()" << endl;
		}
		ColorReduction::colorReduceBook1(inputs[i], divs[i]);

		ostringstream stream;
		stream << "Color Reduced by " << divs[i];
		string label = stream.str();
		cv::imshow(label , inputs[i]);

	}

	cv::waitKey(0);
}


void ColorReduction::simpleTest(){

	 // Load input image (colored, 3-channel, BGR)
	cv::Mat input = cv::imread("/home/leonardo/Imagens/fish.png");
	if (input.empty())
	{
		std::cout << "!!! Failed imread()" << std::endl;
	}

	cv::imshow("Original image", input);

	//this->printPossibleOutputs(0);

	ColorReduction::colorReduceBook1(input);
	cv::imshow("Color Reduction", input);

	cv::waitKey(0);
}




void ColorReduction::colorReduceBook1(cv::Mat& image, int div /*6: 43+, 5: 52+, 4: 64+,  3: 86+, 2: 128+*/)
{

    int nl = image.rows;                    // number of lines
    int nc = image.cols * image.channels(); // number of elements per line
    for (int j = 0; j < nl; j++)
    {
        // get the address of row j
        uchar* data = image.ptr<uchar>(j);

        for (int i = 0; i < nc; i++)
        {
            // process each pixel
            data[i] = data[i] / div * div + div / 2;

        }
    }
}


void ColorReduction::printPossibleOutputs(int div){
	int last_v = -1;
	if(div == 0){
		for (div = 1; div < 256; div++) {
			printf("%3d -> ", div);
			for (int i = 0; i < 256; i++) {
				int v = (i / div * div + div / 2);
				if(last_v != v){
					last_v = v;
					//printf("%d / %d * %d + %d / 2 = %d \n", i , div, div, div, v);
					printf(" %3d ", v);
				}
			}
			printf("\n");
		}
	}
}
