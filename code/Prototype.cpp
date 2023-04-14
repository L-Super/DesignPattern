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
    Prototype(const string &prototype_name) : prototypeName(prototype_name) {}
    virtual ~Prototype() = default;
    virtual Prototype *Clone() const = 0;
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
    ConcretePrototype1(const string &prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concretePrototypeField1(concrete_prototype_field)
    {}

    /**
   * Notice that Clone method return a Pointer to a new ConcretePrototype1
   * replica. so, the client (who call the clone method) has the responsability
   * to free that memory. I you have smart pointer knowledge you may prefer to
   * use unique_pointer here.
   */
    Prototype *Clone() const override { return new ConcretePrototype1(*this); }
};

class ConcretePrototype2 : public Prototype {
private:
    float concretePrototypeField2;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concretePrototypeField2(concrete_prototype_field)
    {}
    Prototype *Clone() const override { return new ConcretePrototype2(*this); }
};

/**
 * In PrototypeFactory you have two concrete prototypes, one for each concrete
 * prototype class, so each time you want to create a bullet , you can use the
 * existing ones and clone those.
 */

class PrototypeFactory {
private:
    std::unordered_map<Type, Prototype *, std::hash<int>> prototypes_;

public:
    PrototypeFactory()
    {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    /**
   * Be carefull of free all memory allocated. Again, if you have smart pointers
   * knowelege will be better to use it here.
   */

    ~PrototypeFactory()
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    /**
   * Notice here that you just need to specify the type of the prototype you
   * want and the method will create from the object with this type.
   */
    Prototype *CreatePrototype(Type type) { return prototypes_[type]->Clone(); }
};

void Client(PrototypeFactory &prototype_factory)
{
    std::cout << "Let's create a Prototype 1\n";

    Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
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
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return 0;
}