/*
 * ColorReduction.h
 *
 *  Created on: 31/05/2016
 *      Author: leonardo
 */

#ifndef COLORREDUCTION_H_
#define COLORREDUCTION_H_

class ColorReduction {
public:
	ColorReduction();
	virtual ~ColorReduction();


	void simpleTest();
	void test();

	void colorReduceBook1(cv::Mat&, int div=64);
private:
	void printPossibleOutputs(int div=64);
};

#endif /* COLORREDUCTION_H_ */
