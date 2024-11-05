//
// Created by Listening on 2023/4/14.
// 原型模式

#include <iostream>
#include <string>
#include <unordered_map>

using std::string;

enum Type { PROTOTYPE_1 = 0, PROTOTYPE_2 };

/**
 * 具有克隆功能的示例类。我们将看到如何克隆具有不同类型的字段的值。
 */
class Prototype {
protected:
    string prototypeName;
    float prototypeField{};

public:
    Prototype() = default;
    Prototype(const string& prototype_name) : prototypeName(prototype_name) {}
    virtual ~Prototype() = default;
    virtual Prototype* Clone() const = 0;
    virtual void Method(float prototype_field)
    {
        this->prototypeField = prototype_field;
        std::cout << "Call Method from " << prototypeName << " with field : " << prototype_field << std::endl;
    }
};

/**
 * ConcretePrototype1 是 Prototype 的一个子类，并实现了 Clone 方法。
 * 在此示例中，Prototype 类的所有数据成员都在栈中。
 * 如果你的属性中有指针，例如：string* name_，则需要实现拷贝构造函数以确保拥有来自克隆方法的深拷贝
 */
class ConcretePrototype1 : public Prototype {
private:
    float concretePrototypeField1;

public:
    ConcretePrototype1(const string& prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concretePrototypeField1(concrete_prototype_field)
    {}

    /**
     * 注意，Clone 方法返回指向新的 ConcretePrototype1 副本的指针。因此，客户端（调用克隆方法）有责任释放该内存。你可能更喜欢在这里使用unique_pointer。
    */
    Prototype* Clone() const override
    {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float concretePrototypeField2;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concretePrototypeField2(concrete_prototype_field)
    {}
    Prototype* Clone() const override
    {
        return new ConcretePrototype2(*this);
    }
};

/**
 * 在PrototypeFactory中，你有两个具体的原型，每个具体的原型类都有一个，所以每次你想创建一个子弹，你可以使用 现有的原型并克隆这些原型。
 */
class PrototypeFactory {
private:
    std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;

public:
    PrototypeFactory()
    {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    ~PrototypeFactory()
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    /**
     * 注意，这里你只需要指定你想要的原型的类型，该方法将从这个类型的对象中创建。
     */
    Prototype* CreatePrototype(Type type)
    {
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory& prototype_factory)
{
    std::cout << "Let's create a Prototype 1\n";

    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);

    delete prototype;
}

int main()
{
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return 0;
}