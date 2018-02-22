/*
 * sine_n_cosine.cpp
 *
 *  Created on: 8 θών. 2017 γ.
 *      Author: Sales
 */

#include <Math/sine_n_cosine.hpp>
#include "Math/int_math.h"

const uint8_t shift = SCALING_SHIFT;
const int64_t one = 1LL;

int32_t scale;
//double doubleScale;

static int64_t scaledPi;
static int64_t scaledHalfPi;
static int64_t scaledHalfPiMinus;
static int64_t scaledPiMinus;

int32_t getScale(){
	return scale;
}

double getDoubleFromLong(int64_t x){
	return ((double)x)/scale;
}

int64_t getLongFromDouble(double x){
	return (int64_t)(x*scale);
}

int8_t getShiftNeeded(double x){
	return -(int8_t)(log(fabs(x))/log(2.0));
}

int32_t k9_1;
int32_t k9_3;
int32_t k9_5;
int32_t k9_7;
int32_t k9_9;

int32_t k9_0;
int32_t k9_2;
int32_t k9_4;
int32_t k9_6;
int32_t k9_8;
int32_t k9_10;

uint8_t nn0;
uint8_t nn1;
uint8_t nn2;
uint8_t nn3;
uint8_t nn4;
uint8_t nn5;
uint8_t nn6;
uint8_t nn7;
uint8_t nn8;
uint8_t nn9;
uint8_t nn10;

int32_t sinInt9(int64_t angle) {
	int64_t tmp = angle;
	if(tmp > scaledHalfPi) tmp = scaledPi - tmp;
	if(tmp < scaledHalfPiMinus) tmp = scaledPiMinus - tmp;
	int64_t x2 = (tmp * tmp)>>shift;
	/*
	int32_t result;
	result = (x2  *  k9_9)           >> nn9;
	result = (x2  * (k9_7 + result)) >> nn7;
	result = (x2  * (k9_5 + result)) >> nn5;
	result = (x2  * (k9_3 + result)) >> nn3;
	result = (tmp * (k9_1 + result)) >> nn1;
	return (int32_t)result;
	*/
	return (int32_t)((tmp * (k9_1 + ((x2 * (k9_3 + ((x2 * (k9_5 + ((x2 * (k9_7 + ((x2 * k9_9) >> nn9))) >> nn7))) >> nn5))) >> nn3))) >> nn1);
}

int32_t cosInt9(int64_t angle) {
	int64_t tmp = angle;
	bool positiveResult = true;
	if(tmp > scaledHalfPi){
		tmp = scaledPi - tmp;
		positiveResult = false;
	}
	if(tmp < scaledHalfPiMinus){
		tmp = scaledPiMinus - tmp;
		positiveResult = false;
	}
	int64_t x2 = (tmp * tmp)>>shift;
/*
	int32_t result = (x2 * k9_10)     >>nn10;
	result = (x2 * (k9_8 + result))>>nn8;
	result = (x2 * (k9_6 + result))>>nn6;
	result = (x2 * (k9_4 + result))>>nn4;
	result = (x2 * (k9_2 + result))>>nn2;
	result = (k9_0 + result)>>nn0;
*/
	int32_t result = (k9_0 + ((x2 * (k9_2 + ((x2 * (k9_4 + ((x2 * (k9_6 + ((x2 * (k9_8 + ((x2 * k9_10)>>nn10)))>>nn8)))>>nn6)))>>nn4)))>>nn2))>>nn0;
	if(positiveResult) return result;
	else return -result;
}

float getMathTolerances(double fX){
	float tol = 0.0;
	int64_t iX = getLongFromDouble(fX);
	double dSin = sin(fX);
	double dCos = cos(fX);
	int32_t iSin = sinInt9(iX);
	int32_t iCos = cosInt9(iX);
	double diSin = getDoubleFromLong(iSin);
	double diCos = getDoubleFromLong(iCos);
	// check sin tolerance
	tol = tol + fabs(dSin - diSin);
	// check cos tolerance
	tol = tol + fabs(dCos - diCos);
	return tol;
}

bool testMath(){
	double dummyAccum = 0.0; // for suppresing optimizer
	uint8_t nTests = 255;
	// testing in 0..9*Pi range
	for(uint8_t i=0; i<=nTests; i++){
		double fX = 9*i*M_PI/nTests;
		float tol = getMathTolerances(fX);
		dummyAccum = dummyAccum + tol;
	}
	if(dummyAccum < 0.00001) return true;
	else return false;
}

void initMath(){
	scale = one << shift;
//	doubleScale = (double)scale;

	scaledPi = (int64_t)(M_PI*scale);
	scaledHalfPi = (int64_t)((M_PI/2.0)*scale);
	scaledHalfPiMinus = -scaledHalfPi;
	scaledPiMinus = -scaledPi;

	double dsk_1 = 0.999999982782301183838;
	double dsk_3 = -0.166666515202236230156;
	double dsk_5 = 0.00833296401821855059586;
	double dsk_7 = -0.000198047553009241346906;
	double dsk_9 = 0.00000259811044408555809666;

	uint8_t n1 = shift+getShiftNeeded(dsk_1);
	uint8_t n3 = shift+getShiftNeeded(dsk_3);
	uint8_t n5 = shift+getShiftNeeded(dsk_5);
	uint8_t n7 = shift+getShiftNeeded(dsk_7);
	uint8_t n9 = shift+getShiftNeeded(dsk_9);

	k9_1 = (int64_t)(dsk_1 * (one << n1));
	k9_3 = (int64_t)(dsk_3 * (one << n3));
	k9_5 = (int64_t)(dsk_5 * (one << n5));
	k9_7 = (int64_t)(dsk_7 * (one << n7));
	k9_9 = (int64_t)(dsk_9 * (one << n9));

	nn1 = n1;
	nn3 = n3-n1+shift;
	nn5 = n5-n3+shift;
	nn7 = n7-n5+shift;
	nn9 = n9-n7+shift;

	double dck_0 = 0.999999999845705468807;
	double dck_2 = -0.499999995116631679318;
	double dck_4 = 0.0416666418861910415758;
	double dck_6 = -0.00138884324659041369860;
	double dck_8 = 0.0000247637740463291155877;
	double dck_10 = -0.000000261150902081161051732;

	uint8_t n0  = shift+getShiftNeeded(dck_0);
	uint8_t n2  = shift+getShiftNeeded(dck_2);
	uint8_t n4  = shift+getShiftNeeded(dck_4);
	uint8_t n6  = shift+getShiftNeeded(dck_6);
	uint8_t n8  = shift+getShiftNeeded(dck_8);
	uint8_t n10 = shift+getShiftNeeded(dck_10);

	k9_0  = (int64_t)(dck_0  * (one << n0));
	k9_2  = (int64_t)(dck_2  * (one << n2));
	k9_4  = (int64_t)(dck_4  * (one << n4));
	k9_6  = (int64_t)(dck_6  * (one << n6));
	k9_8  = (int64_t)(dck_8  * (one << n8));
	k9_10 = (int64_t)(dck_10 * (one << n10));

	nn0 = n0-shift;
	nn2 = n2-n0+shift;
	nn4 = n4-n2+shift;
	nn6 = n6-n4+shift;
	nn8 = n8-n6+shift;
	nn10 = n10-n8+shift;

//	if(testMath()>1.0) osDelay(1);
}
