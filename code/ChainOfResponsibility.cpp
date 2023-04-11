//
// Created by Listening on 2023/4/11.
// 职责链模式
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * Handler接口声明用于生成处理程序链的方法。它还声明了执行请求的方法。
 */
class Handler {
public:
    virtual std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};
/**
 * 默认链行为可以在基本处理程序类中实现。
 */
class AbstractHandler : public Handler {
    /**
     * @var Handler
     */
private:
    std::shared_ptr<Handler> next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {}
    std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler) override
    {
        this->next_handler_ = handler;
        // Returning a handler from here will let us link handlers in a convenient way like this:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }
    std::string Handle(std::string request) override
    {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};
/**
 * 所有Concrete Handlers要么处理请求，要么将其传递给链中的下一个处理程序。
 */
class MonkeyHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override
    {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class SquirrelHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override
    {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class DogHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override
    {
        if (request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
/**
 * 客户端代码通常适合使用单个处理程序。在大多数情况下，它甚至不知道处理程序是链的一部分。
 */
void ClientCode(Handler &handler)
{
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const auto &f: food) {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        }
        else {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}
/**
 * 客户端代码的另一部分构造实际的链。
 */
int main()
{
//    MonkeyHandler *monkey = new MonkeyHandler;
//    SquirrelHandler *squirrel = new SquirrelHandler;
//    DogHandler *dog = new DogHandler;
//    monkey->SetNext(squirrel)->SetNext(dog);
    auto monkey = std::make_shared<MonkeyHandler>();
    auto squirrel = std::make_shared<SquirrelHandler>();
    auto dog = std::make_shared<DogHandler>();

    std::cout<<"monkey count: "<<monkey.use_count()<<" squirrel count: "<<squirrel.use_count()<<" dog count: "<<dog.use_count()<<std::endl;
    monkey->SetNext(squirrel)->SetNext(dog);

    std::cout<<"monkey count: "<<monkey.use_count()<<" squirrel count: "<<squirrel.use_count()<<" dog count: "<<dog.use_count()<<std::endl;
    /**
     * 客户端应该能够向任何处理程序发送请求，而不仅仅是链中的第一个处理程序。
     */
    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    std::cout<<"monkey count: "<<monkey.use_count()<<" squirrel count: "<<squirrel.use_count()<<" dog count: "<<dog.use_count()<<std::endl;
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);
    std::cout<<"monkey count: "<<monkey.use_count()<<" squirrel count: "<<squirrel.use_count()<<" dog count: "<<dog.use_count()<<std::endl;

//    delete monkey;
//    delete squirrel;
//    delete dog;

    return 0;
}
