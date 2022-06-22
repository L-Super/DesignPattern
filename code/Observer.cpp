//
// Created by Listening on 2022/6/22.
//
#include <iostream>
#include <string>
#include <list>

class BaseObserver {
 public:
	virtual ~BaseObserver() = default;
	virtual void update() = 0;
};

class BaseSubject{
 public:
	virtual ~BaseSubject() = default;
	virtual void Attach(BaseObserver *observer) = 0;
	virtual void Detach(BaseObserver *observer) = 0;
	virtual void Notify() = 0;
};

