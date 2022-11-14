//
// Created by Listening on 2022/11/14.
// 代理模式
#include <iostream>
#include <memory>
/**
 * Subject 接口声明了 RealSubject 和 Proxy 的通用操作。
 * 只要客户端使用此接口与 RealSubject 一起工作，就可以向它传递代理而不是真实的subject。
 */
class Subject {
 public:
	virtual void Request() const = 0;
};
/**
 * RealSubject 包含一些核心业务逻辑。
 * 通常，RealSubjects 能够做一些有用的工作，这些工作也可能非常缓慢或敏感 -
 * 例如。修正输入数据。
 * 代理可以解决这些问题，而无需对 RealSubject 的代码进行任何更改。
 */
class RealSubject : public Subject {
 public:
	void Request() const override
	{
		std::cout << "RealSubject: Handling request.\n";
	}
};
/**
 * Proxy 具有与 RealSubject 相同的接口。
 */
class Proxy : public Subject {
	/**
	 * @var RealSubject
	 */
 private:
	RealSubject* real_subject_;

	bool CheckAccess() const
	{
		// Some real checks should go here.
		std::cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}
	void LogAccess() const
	{
		std::cout << "Proxy: Logging the time of request.\n";
	}

	/**
	 * Proxy 维护对 RealSubject 类对象的引用。它可以延迟加载，也可以由客户机传递给代理。
	 */
 public:
	Proxy(RealSubject* real_subject)
		: real_subject_(new RealSubject(*real_subject))
	{
	}

	~Proxy()
	{
		delete real_subject_;
	}
	/**
	 * 代理模式最常见的应用是延迟加载、缓存、控制访问、日志记录等。
	 * Proxy 可以执行其中一项操作，然后根据结果将执行传递给链接的 RealSubject 对象中的相同方法.
	 */
	void Request() const override
	{
		if (this->CheckAccess())
		{
			this->real_subject_->Request();
			this->LogAccess();
		}
	}
};
/**
 * 客户端代码应该通过 Subject 接口与所有对象（主体和代理）一起工作，以支持真实的主体和代理。
 * 然而，在现实生活中，客户大多直接与他们的真实 subjects 工作。
 * 在这种情况下，为了更容易地实现该模式，您可以从真实 subject 的类中扩展您的代理。
 */
void ClientCode(const Subject& subject)
{
	// ...
	subject.Request();
	// ...
}

int main()
{
	std::cout << "Client: Executing the client code with a real subject:\n";
	std::unique_ptr<RealSubject> real_subject = std::make_unique<RealSubject>();
	ClientCode(*real_subject);

	std::cout << "\n";
	std::cout << "Client: Executing the same client code with a proxy:\n";
	std::unique_ptr<Proxy> proxy = std::make_unique<Proxy>(real_subject.get());
	ClientCode(*proxy);

	return 0;
}
