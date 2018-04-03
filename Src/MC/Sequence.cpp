/*
 * CNCTask.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/Motions/Motion.hpp>
#include <MC/Motions/MotionArc.hpp>
#include <MC/Motions/MotionStraight.hpp>
#include <MC/Sequence.hpp>
#include "MC/Action.hpp"
#include "MC/MotionController.hpp"

Sequence::Sequence() {
    this->FillDebugTask();
    for(uint32_t i=0; i< this->GetSize(); i++)
    	this->actions[i]->Init();
}

Sequence::~Sequence() {
	// TODO Auto-generated destructor stub
}


uint32_t Sequence::GetSize(){
	return this->size;
}

Action* Sequence::GetAction(uint32_t num){
	return this->actions[num];
}

void Sequence::FillLines(){
	double v = motionController->velocityProfile.GetVelocity(START);

    MotionStraight *straight1 = new MotionStraight(100.0, 0.0, WORKING, v, v);
    this->actions[0] = (Action*)straight1;

    MotionStraight *straight2 = new MotionStraight(-100.0, 0.0, WORKING, v, v);
    this->actions[1] = (Action*)straight2;

    this->size = 2;
}

void Sequence::FillArcs(){
	double v  = motionController->velocityProfile.startVelocity.Get();
    double v1 = motionController->velocityProfile.workingVelocity.Get();
    double v2 = motionController->velocityProfile.freeRunVelocity.Get();

    // 4 ���� �� 90 �������� �� ������� �� ������� ��������
    MotionArc *arc1 = new MotionArc(100.0, 100.0,  100.0, 0.0, CW, WORKING, v, v1);
    this->actions[0] = (Action*)arc1;

    MotionArc *arc2 = new MotionArc(100.0, -100.0, 0.0, -100.0, CW, WORKING, v1, v1);
    this->actions[1] = (Action*)arc2;

    MotionArc *arc3 = new MotionArc(-100.0, -100.0,  -100.0, 0.0, CW, WORKING, v1, v1);
    this->actions[2] = (Action*)arc3;

    MotionArc *arc4 = new MotionArc(-100.0, 100.0, 0.0, 100.0, CW, WORKING, v1, v);
    this->actions[3] = (Motion*)arc4;

    // 2 ���� �� 180 �������� ������ ������� �� �������� ��������� ����
    MotionArc *arc5 = new MotionArc(200.0, 0.0,  100.0, 0.0, CCW, FREE_RUN, v, v2);
    this->actions[4] = (Action*)arc5;

    MotionArc *arc6 = new MotionArc(-200.0, 0.0, -100.0, 0.0, CCW, FREE_RUN, v2, v);
    this->actions[5] = (Action*)arc6;

    // ������ ���� �� ������� �� ������� ��������
    MotionArc *arc7 = new MotionArc(0.0, 0.0,  100.0, 0.0, CW, WORKING, v, v);
    this->actions[6] = (Action*)arc7;

    this->size = 7;
}

void Sequence::FillComplex(){
	double v  = motionController->velocityProfile.GetVelocity(START);
    double v1 = motionController->velocityProfile.GetVelocity(WORKING);

    MotionStraight *straight1 = new MotionStraight(0.0, 95.0, WORKING, v, v1);
    this->actions[0] = (Action*)straight1;

    MotionArc *arc1 = new MotionArc(10.0, 10.0, 10.0, 0.0, CW, WORKING, v1, v1);
    this->actions[1] = (Action*)arc1;

    MotionStraight *straight2 = new MotionStraight(80.0,  0.0, WORKING, v1, v1);
    this->actions[2] = (Action*)straight2;

    MotionArc *arc2 = new MotionArc(10.0, -10.0, 0.0, -10.0, CW, WORKING, v1, v1);
    this->actions[3] = (Motion*)arc2;

    MotionStraight *straight3 = new MotionStraight(0.0, -80.0, WORKING, v1, v1);
    this->actions[4] = (Motion*)straight3;

    MotionArc *arc3 = new MotionArc(-10.0, -10.0, -10.0, 0.0, CW, WORKING, v1, v1);
    this->actions[5] = (Motion*)arc3;

    MotionStraight *straight4 = new MotionStraight(-95.0, 0.0, WORKING, v1, v);
    this->actions[6] = (Motion*)straight4;

    MotionStraight *straight5 = new MotionStraight(5.0, -5.0, FREE_RUN, v, v);
    this->actions[7] = (Motion*)straight5;

    this->size = 8;
}

void Sequence::FillDebugTask(){
//	fillLines();
	this->FillArcs();
//	this->FillComplex();
}

void Sequence::ResetTask(){
    for(uint32_t i=0; i<this->size; i++){
    	this->actions[i]->Init();
    };
}
