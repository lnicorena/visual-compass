/*
 * Color.cpp
 *
 *  Created on: 03/08/2016
 *      Author: leonardo
 */

#include "Color.h"
#include <string>

#include "../tests/Helper.h"

Color::Color(int c1, int c2, int c3, int freq, int intensity) {
	this->channel1 = c1;
	this->channel2 = c2;
	this->channel3 = c3;
	this->freq = freq;
	this->intensity = intensity;
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}


std::string Color::toString() {
	std::string s = "\nC1: " +
			Helper::intToString(channel1) +
			"\nC2: " + Helper::intToString(channel2) +
			"\nC3: " + Helper::intToString(channel3) +
			"\nFreq: " + Helper::intToString(freq)+
			"\nIntensity: " + Helper::intToString(intensity)+
			"\n";
	return s;
}

int Color::getChannel1() {
	return channel1;
}

void Color::setChannel1(int channel1) {
	this->channel1 = channel1;
}

int Color::getChannel2() {
	return channel2;
}

void Color::setChannel2(int channel2) {
	this->channel2 = channel2;
}

int Color::getChannel3(){
	return channel3;
}

void Color::setChannel3(int channel3) {
	this->channel3 = channel3;
}

int Color::getFreq(){
	return freq;
}

void Color::setFreq(int freq) {
	this->freq = freq;
}

