//
// Created by Listening on 2022/11/2.
// 生成器模式
//

#include <iostream>
#include <string>
#include <vector>

/**
 * 只有当你的产品相当复杂并需要大量配置时，使用生成器模式才有意义。
 * 复杂，需要大量的配置。
 *
 * 与其他创建模式不同，不同的具体创建者可以产生不相关的产品。换句话说，各种构建器的结果可能不总是遵循相同的接口。
 */
class Product1 {
public:
    std::vector<std::string> parts_;
    void ListParts() const
    {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            }
            else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


/**
 * 生成器接口指定了用于创建产品对象不同部分的方法。
 */
class Builder {
public:
    virtual ~Builder() = default;
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};
/**
 * Concrete Builder类遵循Builder接口，并提供构建步骤的具体实现。你的程序可能有几个不同的Builder，以不同的方式实现。
 */
class ConcreteBuilder1 : public Builder {
private:
    Product1* product;
    /**
	 * 一个新的生成器实例应该包含一个空白的产品对象，它被用于进一步组装。用于进一步的组装。
	 */
public:
    ConcreteBuilder1()
    {
        this->Reset();
    }

    ~ConcreteBuilder1()
    {
        delete product;
    }

    void Reset()
    {
        this->product = new Product1();
    }
    /**
	 * 所有的生产步骤都在同一个产品实例中工作。
	 */
    void ProducePartA() const override
    {
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB() const override
    {
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC() const override
    {
        this->product->parts_.push_back("PartC1");
    }

    /**
	 * Concrete Builders应该提供他们自己的方法来检索结果。这是因为各种类型的构建器可能会创建完全不同的产品，它们不遵循相同的接口。
	 * 因此，这种方法不能在基本的Builder接口中声明（至少在静态类型的编程语言中）。
	 *
	 * 通常情况下，在将最终结果返回给客户之后，一个构建器实例被期望准备好开始生产另一个产品。
	 * 这就是为什么通常的做法是在`getProduct`方法体的末尾调用重置方法。
	 * 然而，这种行为并不是强制性的，你可以让你的构建器在处理先前的结果之前，等待来自客户端代码的明确的重置调用。
	 */

    /**
	 * 请注意这里的内存所有权。一旦你调用GetProduct，这个函数的用户就有责任释放这段内存。
	 * 这里可能是一个更好的选择，即使用智能指针来避免内存泄漏。
	 */
    Product1* GetProduct()
    {
        Product1* result = this->product;
        this->Reset();
        return result;
    }
};

/**
 * Director只负责按特定顺序执行建造步骤。当按照特定的顺序或配置生产产品时，它很有帮助。
 * 严格来说，Director类是可选的，因为客户可以直接控制建造者。
 */
class Director {
    /**
	 * @var Builder
	 */
private:
    Builder* builder;
    /**
	 * Director与客户端代码传递给它的任何builder构建器实例一起工作。这样，客户端代码可以改变新组装产品的最终类型。
	 */
public:
    void SetBuilder(Builder* builder)
    {
        this->builder = builder;
    }

    /**
	 * Director（主管）可以使用相同的构造步骤建造几个产品变化。
	 */
    void BuildMinimalViableProduct()
    {
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedProduct()
    {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

/**
  * 客户端代码创建一个builder对象，将其传递给director（主管），然后启动构造过程。最终结果从builder建造者对象中获取。
 */
void ClientCode(Director& director)
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.SetBuilder(builder);
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();

    Product1* p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();

    p = builder->GetProduct();
    p->ListParts();
    delete p;

    // 请记住，没有Director类也可以使用Builder模式。
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main()
{
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}