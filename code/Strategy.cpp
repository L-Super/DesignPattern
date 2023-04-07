//
// Created by Listening on 2023/4/7.
// 策略模式
#include <iostream>
#include <string>
#include <memory>
#include <string_view>
#include <algorithm>
/**
 * Strategy接口声明某些算法的所有受支持版本通用的操作。
 *
 * Context使用此接口调用具体策略定义的算法。
 */
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

/**
 * Context 定义客户端感兴趣的接口
 */
class Context
{
    /**
     * @var Strategy Context 维护对其中一个策略对象的引用。上下文不知道策略的具体类别。它应该通过策略界面与所有策略一起使用。
     */
private:
    std::unique_ptr<Strategy> strategy_;
    /**
     * 通常，Context通过构造函数接受策略，但也提供一个setter在运行时更改它。
     */
public:
    explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy))
    {
    }
    /**
     * 通常，Context允许在运行时替换策略对象。
     */
    void set_strategy(std::unique_ptr<Strategy> &&strategy)
    {
        strategy_ = std::move(strategy);
    }
    /**
     * Context将一些工作委托给 Strategy 对象，而不是自行实现算法的 +多个版本。
     */
    void doSomeBusinessLogic() const
    {
        if (strategy_) {
            std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        }
        else {
            std::cout << "Context: Strategy isn't set\n";
        }
    }
};

/**
 * 具体策略在遵循基本策略界面的同时实现算法。该接口使它们在上下文中可互换。
 */
class ConcreteStrategyA : public Strategy
{
public:
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};

/**
 * 客户端代码选取一个具体的策略并将其传递给上下文。客户应该意识到策略之间的差异，以便做出正确的选择。
 */
void clientCode()
{
    Context context(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

int main()
{
    clientCode();
    return 0;
}