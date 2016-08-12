/*
 * ColorProcessing.h
 *
 *  Created on: 31/05/2016
 *      Author: leonardo
 */

#ifndef COLORPROCESSING_H_
#define COLORPROCESSING_H_

class ColorProcessing {
public:
	ColorProcessing();
	virtual ~ColorProcessing();

	void bgrToHsv(cv::Mat&, cv::Mat&);
	void hsvToBgr(cv::Mat&, cv::Mat&);

	void imageOpening(cv::Mat&, int size = 5);
	void imageClosing(cv::Mat&, int size = 5);

	void colorReduction(cv::Mat&, int div = 64); /* More efficient scanning */
	void colorReductionSimple(cv::Mat&, int div = 64);
	void colorReductionFaster(cv::Mat&, int div = 64);


	void testColorspace();
	void testHsvChannels();
	void testOpeningClosing();
};

#endif /* COLORPROCESSING_H_ */
