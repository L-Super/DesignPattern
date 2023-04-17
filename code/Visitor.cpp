//
// Created by Listening on 2023/4/17.
//
#include <iostream>
#include <array>

/**
 * Visitor 接口声明一组与组件类对应的访问方法。访问方法的签名允许访问者识别它正在处理的组件的确切类别。
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

/**
 * Component 接口声明一个“accept”方法，该方法应将基本访问者接口作为参数。
 */
class Component {
public:
    virtual ~Component() {}
    virtual void Accept(Visitor *visitor) const = 0;
};

/**
 * 每个Concrete Component都必须以这样一种方式实现“Accept”方法，即它调用与组件的类相对应的访问者方法。
 */
class ConcreteComponentA : public Component {
    /**
     * 注意，我们调用的是“visitConcreteComponentA”，它与当前类名匹配。通过这种方式，我们让访问者知道它使用的组件的类。
     */
public:
    void Accept(Visitor *visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
    /**
     * 具体组件类可能具有基类或接口中不存在的特殊方法。访问者仍然可以使用这些方法，因为它知道组件的具体类。
     */
    std::string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class ConcreteComponentB : public Component {
    /**
     * 同样的: visitConcreteComponentB => ConcreteComponentB
     */
public:
    void Accept(Visitor *visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
    std::string SpecialMethodOfConcreteComponentB() const {
        return "B";
    }
};

/**
 * Concrete Visitors implement several versions of the same algorithm, which can
 * work with all concrete component classes.
 *
 * You can experience the biggest benefit of the Visitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 * Concrete Visitors 实现同一算法的多个版本，可以与所有具体组件类一起使用。
 * 当将访问者模式与复杂的对象结构（如复合树）一起使用时，您可以体验到它的最大好处。在这种情况下，在对结构的各种对象执行访问者的方法时存储算法的一些中间状态可能会有所帮助。
 */
class ConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};
/**
 * The client code can run visitor operations over any set of elements without
 * figuring out their concrete classes. The accept operation directs a call to
 * the appropriate operation in the visitor object.
 */
void ClientCode(std::array<const Component *, 2> components, Visitor *visitor) {
    // ...
    for (const Component *comp : components) {
        comp->Accept(visitor);
    }
    // ...
}

int main() {
    std::array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component *comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}