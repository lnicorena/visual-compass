/* Criar projeto opencv: http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_eclipse/linux_eclipse.html
 * Project –> Properties -> C/C++ Build -> Settings -> Tool Settings
 * 		g
 */

#include <iostream>
#include "opencv2/highgui/highgui.hpp"

#include "tests/LoadImage.h"
#include "tests/DetectRedObj.h"
#include "tests/HsvTests.h"
#include "tests/BlobTests.h"
#include "tests/ColorReduction.h"
#include "ImageProcessing/Histogram.h"
#include "ImageProcessing/Processor.h"
#include "ImageProcessing/ColorProcessing.h"
#include "DataModel/Compass.h"


using namespace std;
using namespace cv;

int main( int argc, char** argv )
{

	LoadImage * loader;
	Histogram * hist;
	DetectRedObj * red;
	HsvTests * hsv;
	BlobTests * blob;

	ColorReduction * reduc;

	//hist->test();
	//loader->test();

	//hsv->test2();

	//blob->test1();

	//reduc->test();

	Processor * proc;

	//Mat out, img = imread("/home/leonardo/workspace/VisualCompass/images/test1/01.jpg");
	//proc->transform(img, out, "hsv");


	ColorProcessing color;
	//color.testHsvChannels();

	Compass bussola;

	waitKey(0);
	return 0;
}
