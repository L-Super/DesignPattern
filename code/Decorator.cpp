//
// Created by Listening on 2023/4/12.
// 装饰模式
#include <iostream>
#include <string>
#include <memory>

/**
 * 基本组件接口定义了可以由装饰器更改的操作。
 */
class Component {
public:
    virtual ~Component() = default;
    virtual std::string Operation() const = 0;
};
/**
 * 具体组件类提供操作的默认实现。这些类可能有多种变体。
 */
class ConcreteComponent : public Component {
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    }
};
/**
 * 基础装饰器类遵循与其他组件相同的接口。这个类的主要目的是为所有具体的装饰器定义包装接口。
 * 包裹代码的默认实现可能包括一个用于存储被包裹组件的字段和初始化它的方法。
 */
class Decorator : public Component {
    /**
   * @var Component
   */
protected:
    Component* component_;

public:
    Decorator(Component* component) : component_(component) {
    }
    /**
   * 装饰器将所有工作委托给包装的组件。
   */
    std::string Operation() const override {
        return this->component_->Operation();
    }
};
/**
 * Concrete Decorators 调用包装的对象并以某种方式更改其结果。
 */
class ConcreteDecoratorA : public Decorator {
    /**
   * 装饰器可以调用操作的父级实现，而不是直接调用被包装的对象。这种方法简化了对 装饰器类的扩展。
   */
public:
    // 委托构造
    ConcreteDecoratorA(Component* component) : Decorator(component) {
    }
    std::string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};
/**
 * 装饰器可以在调用一个被包装的对象之前或之后执行其行为。
 */
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {
    }

    std::string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    }
};
/**
 * 客户端代码使用组件接口处理所有对象。这样，它可以独立于它所处理的具体组件类。
 */
void ClientCode(Component* component) {
    // ...
    std::cout << "RESULT: " << component->Operation();
    // ...
}

int main() {
    // 这样客户端代码可以支持两个简单的组件...
    Component* simple = new ConcreteComponent;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";

    // ...以及装饰的。请注意，装饰器不仅可以包装简单的组件，还可以包装其他装饰器。
    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    std::cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator2);
    std::cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;

    return 0;
}