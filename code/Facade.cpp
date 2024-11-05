//
// Created by Listening on 2023/4/10.
// Facade 外观模式

#include <iostream>
#include <memory>
#include <string>

/**
 * 子系统可以直接接受来自外观或客户端的请求。无论如何，对于子系统来说，外观是另一个客户端，它不是子系统的一部分。
 */
class Subsystem1 {
public:
    std::string Operation1() const
    {
        return "Subsystem1: Ready!\n";
    }
    // ...
    std::string OperationN() const
    {
        return "Subsystem1: Go!\n";
    }
};
/**
 * 一些外观可以同时与多个子系统一起工作。
 */
class Subsystem2 {
public:
    std::string Operation1() const
    {
        return "Subsystem2: Get ready!\n";
    }
    // ...
    std::string OperationZ() const
    {
        return "Subsystem2: Fire!\n";
    }
};

/**
 * Facade 类为一个或多个子系统的复杂逻辑提供了一个简单的接口。外观将客户端请求委托给子系统中的相应对象。
 * 外观还负责管理其生命周期。所有这些都保护客户端免受子系统不希望出现的复杂性。
 */
class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;
    /**
     * 根据应用程序的需要，可以为外观提供现有的子系统对象，也可以强制外观自行创建它们。
     */
public:
    /**
     * 在这种情况下，我们将内存所有权委托给外观类
     */
    explicit Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr)
    {
        // subsystem1 != nullptr ? subsystem1 : new Subsystem1 简写
        this->subsystem1_ = subsystem1 ?: new Subsystem1;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
    }
    ~Facade()
    {
        delete subsystem1_;
        delete subsystem2_;
    }
    /**
     * 外观的方法是通往子系统复杂功能的方便捷径。但是，客户端只能获得子系统功能的一小部分功能。
     */
    std::string Operation()
    {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

/**
 * 客户端代码通过外观提供的简单接口处理复杂的子系统。当外观管理子系统的生命周期时，客户端甚至可能不知道子系统的存在。此方法可让您控制复杂性。
 */
void ClientCode(Facade* facade)
{
    // ...
    std::cout << facade->Operation();
    // ...
}

/**
 * 客户端代码可能已创建某些子系统的对象。在这种情况下，可能值得使用这些对象初始化外观，而不是让外观创建新实例。
 */
int main()
{
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;

    std::unique_ptr<Facade> facade = std::make_unique<Facade>(subsystem1, subsystem2);
    ClientCode(facade.get());

    return 0;
}