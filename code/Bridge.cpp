// 桥接模式
#include <iostream>
#include <string>

/**
 * 定义了所有实现类的接口。它不必与抽象类的接口相匹配。实际上，
 * 这两个接口可以完全不同。通常，实现类的接口仅提供原始操作，而抽象类
 * 基于这些原始操作定义了更高级别的操作。
 */
class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * 每个具体实现类对应一个特定的平台，并使用该平台的API实现实现类接口。
 */
class ConcreteImplementationA : public Implementation {
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB : public Implementation {
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

/**
 * 抽象类定义了“控制”部分的接口，它维护对实现类层次结构中对象的引用，
 * 并将所有实际工作委托给该对象。
 */

class Abstraction {
    /**
   * @var Implementation
   */
protected:
    Implementation *implementation_;

public:
    Abstraction(Implementation *implementation) : implementation_(implementation) {}

    virtual ~Abstraction() {}

    virtual std::string Operation() const
    {
        return "Abstraction: Base operation with:\n" + this->implementation_->OperationImplementation();
    }
};

/**
 * 你可以在不改变实现类的情况下扩展抽象类。
 */
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation *implementation) : Abstraction(implementation) {}
    std::string Operation() const override
    {
        return "ExtendedAbstraction: Extended operation with:\n" + this->implementation_->OperationImplementation();
    }
};

/**
 * 除了在初始化阶段，抽象类对象与特定的实现类对象关联之外，客户端代码应
 * 仅依赖于抽象类。这样，客户端代码可以支持任何抽象类-实现类的组合。
 */
void ClientCode(const Abstraction &abstraction)
{
    // ...
    std::cout << abstraction.Operation() << std::endl;
    // ...
}

/**
 * 客户端代码应能够使用任何预配置的抽象类-实现类组合工作。
 */
int main()
{
    Implementation *implementation = new ConcreteImplementationA;
    Abstraction *abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}