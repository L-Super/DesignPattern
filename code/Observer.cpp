//
// Created by Listening on 2022/6/22.
//
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

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
	virtual ~Subject() {std::cout<<"Subject destructor"<<std::endl;}
	/**
	 * 订阅管理方法。
	 * @param observer
	 */
	void Attach(BaseObserver* observer) override{
		observerList.push_back(observer);
	}

	void Detach(BaseObserver *observer) override{
		observerList.remove(observer);
	}
	void Notify() override{
		ObserverNums();
		for(auto it:observerList)
		{
			it->update(msg);
		}
	}
	void CreateMessage(const std::string& message = "empty")
	{
		this->msg = message;
		Notify();
	}
	/**
	 * 通常，订阅逻辑只是 Subject 真正可以做的一小部分。Subjects通常包含一些重要的业务逻辑，当重要的事情即将发生（或之后）时，它会触发通知方法。
	 */
	void SomeBusinessLogic() {
		this->msg = "change message message";
		Notify();
		std::cout << "I'm about to do some thing important\n";
	}
 private:
	int ObserverNums(){
		std::cout<<" There are "<<observerList.size()<<" observers in the list\n";
		return observerList.size();
	}
 private:
	std::string msg;
	std::list<BaseObserver*> observerList;
};