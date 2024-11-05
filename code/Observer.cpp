//
// Created by Listening on 2022/6/22.
// 观察者模式
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>

class BaseObserver {
public:
    virtual ~BaseObserver() = default;
    virtual void Update(const std::string& msgFromSubject) = 0;
};

class BaseSubject {
public:
    virtual ~BaseSubject() = default;
    virtual void Attach(BaseObserver* observer) = 0;
    virtual void Detach(BaseObserver* observer) = 0;
    virtual void Notify() = 0;
};

/**
 * Subject 拥有一些重要的状态，并在状态更改时通知观察者。
 */
class Subject : public BaseSubject {
public:
    virtual ~Subject()
    {
        std::cout << "Subject destructor" << std::endl;
    }
    /**
	 * 订阅管理方法。
	 * @param observer
	 */
    void Attach(BaseObserver* observer) override
    {
        observerList.push_back(observer);
    }

    void Detach(BaseObserver* observer) override
    {
        std::cout << "Detach observer:" << &observer << std::endl;
        observerList.remove(observer);
    }
    void Notify() override
    {
        ObserverNums();
        for (auto it: observerList) { it->Update(msg); }
    }
    void CreateMessage(const std::string& message = "empty")
    {
        this->msg = message;
        Notify();
    }
    /**
	 * 通常，订阅逻辑只是 Subject 真正可以做的一小部分。Subjects通常包含一些重要的业务逻辑，当重要的事情即将发生（或之后）时，它会触发通知方法。
	 */
    void SomeBusinessLogic()
    {
        this->msg = "change message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    size_t ObserverNums()
    {
        std::cout << "There are " << observerList.size() << " observers in the list\n";
        return observerList.size();
    }

private:
    std::string msg;
    std::list<BaseObserver*> observerList;
};

class Observer : public BaseObserver {
public:
    Observer() = default;
    Observer(std::shared_ptr<Subject> s) : subject(s)
    {
        this->subject->Attach(this);
        std::cout << "I'm the Observer \"" << ++Observer::staticNumber << "\".\n";
        this->number = Observer::staticNumber;
    }
    virtual ~Observer()
    {
        std::cout << "Observer destructor" << std::endl;
    }
    void Update(const std::string& messageFromSubject) override
    {
        this->msgFromSubject = messageFromSubject;
        PrintInfo();
    }
    void RemoveMeFromList()
    {
        subject->Detach(this);
        std::cout << "Observer \"" << number << "\" removed from the list.\n";
    }
    void PrintInfo()
    {
        std::cout << "Observer \"" << this->number << "\": a new message is available --> " << this->msgFromSubject
                  << "\n";
    }

private:
    std::string msgFromSubject;
    std::shared_ptr<Subject> subject;
    static int staticNumber;
    int number;
};

int Observer::staticNumber = 0;

void ClientCode()
{
    std::shared_ptr<Subject> subject = std::make_shared<Subject>();
    std::cout << "Smart ptr count " << subject.use_count() << "\n";

    auto observer1 = std::make_shared<Observer>(subject);//初始化observer时Attach
    auto observer2 = std::make_shared<Observer>(subject);
    auto observer3 = std::make_shared<Observer>(subject);

    std::shared_ptr<Observer> observer4(new Observer());

    subject->CreateMessage("Hello World! :D");
    subject->Attach(observer4.get());//也可以直接使用subject Attach

    std::cout << "Smart ptr count " << subject.use_count() << "\n";

    observer1->RemoveMeFromList();   //自己remove
    subject->Detach(observer2.get());//subject remove
    subject->CreateMessage("The weather is hot today! :p");
}

int main()
{
    ClientCode();
    return 0;
}