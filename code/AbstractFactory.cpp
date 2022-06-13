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
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductB1 : public AbstractProductB {
 public:
	std::string UseFuncB() const override {
		return "The result of the product B1.";
	}
	/**
	 * The variant, Product B1, is only able to work correctly with the variant,
	 * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
	 * argument.
	 */
	std::string AnotherUseFuncB(const AbstractProductA &collaborator) const override {
		const std::string result = collaborator.UseFuncA();
		return "The result of the B1 collaborating with ( " + result + " )";
	}
};

class ConcreteProductB2 : public AbstractProductB {
 public:
	std::string UseFuncB() const override {
		return "The result of the product B2.";
	}
	/**
	 * The variant, Product B2, is only able to work correctly with the variant,
	 * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
	 * argument.
	 */
	std::string AnotherUseFuncB(const AbstractProductA &collaborator) const override {
		const std::string result = collaborator.UseFuncA();
		return "The result of the B2 collaborating with ( " + result + " )";
	}
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory {
 public:
	virtual AbstractProductA *CreateProductA() const = 0;
	virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
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
 * Each Concrete Factory has a corresponding product variant.
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
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
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

