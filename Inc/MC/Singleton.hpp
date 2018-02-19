/*
 * Singleton.hpp
 *
 *  Created on: 19 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_SINGLETON_HPP_
#define MC_SINGLETON_HPP_

template<typename T>
class Singleton {
protected:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
	static T& GetInstance(){
	    static T instance;
	    return instance;
	};
};

#endif /* MC_SINGLETON_HPP_ */
