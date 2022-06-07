//
// Created by Listening on 2022/6/7.
// 工厂方法
//
#include <iostream>
#include <string>

/**
 * Product 接口声明了所有具体产品必须实现的操作。
 */
class Product {
 public:
	virtual ~Product() {}
	virtual std::string Operation() const = 0;
};

/**
 * 具体产品提供了产品接口的各种实现
 */
class ConcreteProduct1 : public Product {
 public:
	std::string Operation() const override {
		return "{ConcreteProduct1}";
	}
};
class ConcreteProduct2 : public Product {
 public:
	std::string Operation() const override {
		return "{ConcreteProduct2}";
	}
};

/**
 * Creator 类声明了应该返回 Product 类对象的工厂方法。 Creator 的子类通常提供此方法的实现
 */
class Creator {
	/**
	 * 注意，Creator 还可能提供工厂方法的一些默认实现。
	 */
 public:
	virtual ~Creator(){};
	virtual Product* FactoryMethod() const = 0;
	/**
	 * 注意，Creator 的主要责任不是创造产品。通常，它包含一些依赖于 Product 对象的核心业务逻辑，由工厂方法返回。
	 * 子类可以通过重写工厂方法并从中返回不同类型的产品来间接更改该业务逻辑。
	 */
	std::string SomeOperation() const {
		// 调用工厂方法创建 Product 对象
		Product* product = this->FactoryMethod();
		// Now, use the product.
		std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
		delete product;
		return result;
	}
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
class ConcreteCreator1 : public Creator {
	/**
	 * Note that the signature of the method still uses the abstract product type,
	 * even though the concrete product is actually returned from the method. This
	 * way the Creator can stay independent of concrete product classes.
	 */
 public:
	Product* FactoryMethod() const override {
		return new ConcreteProduct1();
	}
};

class ConcreteCreator2 : public Creator {
 public:
	Product* FactoryMethod() const override {
		return new ConcreteProduct2();
	}
};

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void ClientCode(const Creator& creator) {
	// ...
	std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
			  << creator.SomeOperation() << std::endl;
	// ...
}

/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */

int main() {
	std::cout << "App: Launched with the ConcreteCreator1.\n";
	Creator* creator = new ConcreteCreator1();
	ClientCode(*creator);
	std::cout << std::endl;
	std::cout << "App: Launched with the ConcreteCreator2.\n";
	Creator* creator2 = new ConcreteCreator2();
	ClientCode(*creator2);

	delete creator;
	delete creator2;
	return 0;
}

