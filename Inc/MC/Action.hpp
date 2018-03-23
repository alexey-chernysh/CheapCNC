/*
 * Action.hpp
 *
 *  Created on: 26 џэт. 2018 у.
 *      Author: Sales
 */

#ifndef MC_ACTION_HPP_
#define MC_ACTION_HPP_

class Action {
public:
	Action();
	virtual ~Action();
	virtual void Reset();
	virtual bool IterateForward();
	virtual bool IterateBackward();
	virtual void OnResumeKeyPressed();
	virtual void OnStoreNResumeKeyPressed();
};

#endif /* MC_ACTION_HPP_ */
