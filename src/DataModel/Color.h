
#ifndef COLOR_H_
#define COLOR_H_

#include <string>

class Color {
public:
	Color(int c1 =-1, int c2 = -1, int c3 = -1, int freq = -1, int intensity = -1);
	virtual ~Color();

	int getChannel1();
	void setChannel1(int channel1);

	int getChannel2();
	void setChannel2(int channel2) ;

	int getChannel3();
	void setChannel3(int channel3);


	int getFreq();
	void setFreq(int freq);

	std::string toString();

	int channel1;
	int channel2;
	int channel3;
	int freq; /* Percentage of times color appears on the image pixels*/
	int intensity;
};

#endif /* COLOR_H_ */
