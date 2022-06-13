//
// Created by Listening on 2022/6/13.
// 抽象工厂
#include <iostream>
#include <string>
/**
 * 产品系列的每个不同产品都应该有一个基本接口。产品的所有变体都必须实现此接口。
 */
class AbstractProductA {
 public:
	virtual ~AbstractProductA(){};
	virtual std::string UseFuncA() const = 0;
};

/**
 * 具体产品由相应的具体工厂创建。
 */
class ConcreteProductA1 : public AbstractProductA {
 public:
	std::string UseFuncA() const override {
		return "The product A1.";
	}
};

class ConcreteProductA2 : public AbstractProductA {
	std::string UseFuncA() const override {
		return "The product A2.";
	}
};

/**
 * 这是另一个产品的基本接口。所有产品都可以相互交互，但只有在相同具体变体的产品之间才能进行适当的交互。
 */
class AbstractProductB {
	/**
	 * 产品B能够做自己的事情......
	 */
 public:
	virtual ~AbstractProductB(){};
	virtual std::string UseFuncB() const = 0;
	/**
	 * ...但它也可以与 ProductA 协作。抽象工厂确保它创建的所有产品都具有相同的变体，因此是兼容的。
	 */
	virtual std::string AnotherUseFuncB(const AbstractProductA &collaborator) const = 0;
};

/**
 * 具体产品由相应的具体工厂创建。
 */
class ConcreteProductB1 : public AbstractProductB {
 public:
	std::string UseFuncB() const override {
		return "The product B1.";
	}
	/**
	 * Product B1只能够正确地与Product A1一起工作。然而，它接受任何 AbstractProductA 实例作为参数。
	 */
	std::string AnotherUseFuncB(const AbstractProductA &collaborator) const override {
		const std::string result = collaborator.UseFuncA();
		return "The result of the B1 collaborating with ( " + result + " )";
	}
};

class ConcreteProductB2 : public AbstractProductB {
 public:
	std::string UseFuncB() const override {
		return "The product B2.";
	}
	/**
	 * Product B2只能够正确地与 Product A2一起工作。然而，它接受任何 AbstractProductA 实例作为参数。
	 */
	std::string AnotherUseFuncB(const AbstractProductA &collaborator) const override {
		const std::string result = collaborator.UseFuncA();
		return "The result of the B2 collaborating with ( " + result + " )";
	}
};

/**
 * 抽象工厂接口声明了一组返回不同抽象产品的方法。这些产品被称为一个系列，并通过一个高层次的主题或概念相关联。一个系列的产品通常能够相互合作。
 * 一个产品系列可能有几个变体，但是一个变体的产品与另一个变体的产品是不兼容的。
 */
class AbstractFactory {
 public:
	virtual AbstractProductA *CreateProductA() const = 0;
	virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * 具体工厂生产属于单一变体的产品系列。工厂保证产品的兼容性。请注意，Concrete Factory 方法返回一个抽象产品，而在方法内部实例化一个具体产品。
 */
class ConcreteFactory1 : public AbstractFactory {
 public:
	AbstractProductA *CreateProductA() const override {
		return new ConcreteProductA1();
	}
	AbstractProductB *CreateProductB() const override {
		return new ConcreteProductB1();
	}
};

/**
 * 每个Concrete Factory工厂都有相应的产品变体。
 */
class ConcreteFactory2 : public AbstractFactory {
 public:
	AbstractProductA *CreateProductA() const override {
		return new ConcreteProductA2();
	}
	AbstractProductB *CreateProductB() const override {
		return new ConcreteProductB2();
	}
};

/**
 * 客户端代码仅通过抽象类型处理工厂和产品：AbstractFactory 和 AbstractProduct。这使您可以将任何工厂或产品子类传递给客户端代码，而不会破坏它。
 */

void ClientCode(const AbstractFactory &factory) {
	const AbstractProductA *product_a = factory.CreateProductA();
	const AbstractProductB *product_b = factory.CreateProductB();
	std::cout << product_b->UseFuncB() << "\n";
	std::cout << product_b->AnotherUseFuncB(*product_a) << "\n";
	delete product_a;
	delete product_b;
}

int main() {
	std::cout << "Client: Testing client code with the first factory type:\n";
	ConcreteFactory1 *f1 = new ConcreteFactory1();
	ClientCode(*f1);
	delete f1;
	std::cout << std::endl;
	std::cout << "Client: Testing the same client code with the second factory type:\n";
	ConcreteFactory2 *f2 = new ConcreteFactory2();
	ClientCode(*f2);
	delete f2;
	return 0;
}

