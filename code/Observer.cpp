//
// Created by Listening on 2022/6/22.
//
#include <iostream>
#include <string>
#include <list>

class BaseObserver {
 public:
	virtual ~BaseObserver() = default;
	virtual void update(const std::string& msgFromSubject) = 0;
};

class BaseSubject{
 public:
	virtual ~BaseSubject() = default;
	virtual void Attach(BaseObserver *observer) = 0;
	virtual void Detach(BaseObserver *observer) = 0;
	virtual void Notify() = 0;
};

/**
 * Subject 拥有一些重要的状态，并在状态更改时通知观察者。
 */
class Subject:public BaseSubject{
 public:
	virtual ~Subject() {std::cout<<"Subject "}

};