/*
 * CNCTask.cpp
 *
 *  Created on: 28 янв. 2018 г.
 *      Author: Sales
 */

#include "MC/CNCTask.hpp"
#include "MC/Action.hpp"
#include "MC/Motion.hpp"
#include "MC/MotionStraight.hpp"
#include "MC/MotionArc.hpp"

CNCTask::CNCTask(MotionController *mc) {
	this->parent = mc;
    this->fillDebugTask();
    for(uint32_t i=0; i< this->getSize(); i++)
    	this->actions[i]->reset();
}

CNCTask::~CNCTask() {
	// TODO Auto-generated destructor stub
}


uint32_t CNCTask::getSize(){
	return this->size;
}

Action* CNCTask::getAction(uint32_t num){
	return this->actions[num];
}

void CNCTask::fillLines(){
	double v = velocitySettings.getStartVelocity();

    MotionStraight *straight1 = new MotionStraight(100.0, 0.0, WORKING, v, v);
    this->actions[0] = (Action*)straight1;

    MotionStraight *straight2 = new MotionStraight(-100.0, 0.0, WORKING, v, v);
    this->actions[1] = (Action*)straight2;

    this->size = 2;
}

void CNCTask::fillArcs(){
	double v = velocitySettings.getStartVelocity();
    double v1 = velocitySettings.getWorkingVelocity();
    double v2 = velocitySettings.getFreeRunVelocity();

    // 4 дуги на 90 градусов по чвсовой на рабочей скорости
    MotionArc *arc1 = new MotionArc(100.0, 100.0,  100.0, 0.0, CW, WORKING, v, v1);
    this->actions[0] = (Action*)arc1;

    MotionArc *arc2 = new MotionArc(100.0, -100.0, 0.0, -100.0, CW, WORKING, v1, v1);
    this->actions[1] = (Action*)arc2;

    MotionArc *arc3 = new MotionArc(-100.0, -100.0,  -100.0, 0.0, CW, WORKING, v1, v1);
    this->actions[2] = (Action*)arc3;

    MotionArc *arc4 = new MotionArc(-100.0, 100.0, 0.0, 100.0, CW, WORKING, v1, v);
    this->actions[3] = (Motion*)arc4;

    // 2 дуги на 180 градусов против часовой на скорости холостого хода
    MotionArc *arc5 = new MotionArc(200.0, 0.0,  100.0, 0.0, CCW, FREE_RUN, v, v2);
    this->actions[4] = (Action*)arc5;

    MotionArc *arc6 = new MotionArc(-200.0, 0.0, -100.0, 0.0, CCW, FREE_RUN, v2, v);
    this->actions[5] = (Action*)arc6;

    // полный круг по часовой на рабочей скорости
    MotionArc *arc7 = new MotionArc(0.0, 0.0,  100.0, 0.0, CW, WORKING, v, v);
    this->actions[6] = (Action*)arc7;

    this->size = 7;
}

void CNCTask::fillComplex(){
	double v = velocitySettings.getStartVelocity();
    double v1 = velocitySettings.getWorkingVelocity();
    double v2 = velocitySettings.getFreeRunVelocity();

    MotionStraight *straight1 = new MotionStraight(0.0, 45.0, WORKING, v, v1);
    this->actions[0] = (Action*)straight1;

    MotionArc *arc1 = new MotionArc(10.0, 10.0, 10.0, 0.0, CW, WORKING, v1, v1);
    this->actions[1] = (Action*)arc1;

    MotionStraight *straight2 = new MotionStraight(30.0,  0.0, WORKING, v1, v1);
    this->actions[2] = (Action*)straight2;

    MotionArc *arc2 = new MotionArc(10.0, -10.0, 0.0, -10.0, CW, WORKING, v1, v1);
    this->actions[3] = (Motion*)arc2;

    MotionStraight *straight3 = new MotionStraight(0.0, -30.0, WORKING, v1, v1);
    this->actions[4] = (Motion*)straight3;

    MotionArc *arc3 = new MotionArc(-10.0, -10.0, -10.0, 0.0, CW, WORKING, v1, v1);
    this->actions[5] = (Motion*)arc3;

    MotionStraight *straight4 = new MotionStraight(-45.0, 0.0, WORKING, v1, v);
    this->actions[6] = (Motion*)straight4;

    MotionStraight *straight5 = new MotionStraight(5.0, -5.0, FREE_RUN, v, v);
    this->actions[7] = (Motion*)straight5;

    this->size = 8;
}

void CNCTask::fillDebugTask(){
//	fillLines();
	this->fillArcs();
//	fillComplex();
}

void CNCTask::resetTask(){
    for(uint32_t i=0; i<this->size; i++){
    	this->actions[i]->reset();
    };
}
