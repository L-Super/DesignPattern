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

class Base