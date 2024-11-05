//
// Created by LMR on 24-11-5.
// 命令模式

#include <iostream>
#include <string>

/**
 * Command接口声明了一个执行命令的方法。
 */
class Command {
public:
    virtual ~Command() {}
    virtual void Execute() const = 0;
};

/**
 * 一些命令可以在它们自己内部实现简单的操作。
 */
class SimpleCommand : public Command {
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {}
    void Execute() const override
    {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
    }
};

/**
 * Receiver 接收者类包含一些重要的业务逻辑。它们知道如何执行与请求相关的各种操作。实际上，任何类都可以作为接收者。
 */
class Receiver {
public:
    void DoSomething(const std::string& a)
    {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }
    void DoSomethingElse(const std::string& b)
    {
        std::cout << "Receiver: Also working on (" << b << ".)\n";
    }
};

/**
 * 然而，一些命令可以将更复杂的操作委托给其他对象，称为“接收者”。
 */
class ComplexCommand : public Command {
private:
    Receiver* receiver_;
    /**
     * 用于启动接收者方法的上下文数据。
     */
    std::string a_;
    std::string b_;

public:
    /**
     * 复杂命令可以通过构造函数接受一个或多个接收者对象以及任何上下文数据。
     */
    ComplexCommand(Receiver* receiver, const std::string& a, const std::string& b) : receiver_(receiver), a_(a), b_(b) {}
    /**
     * Commands 命令可以委托给接收者的任何方法。
     */
    void Execute() const override
    {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};

/**
 * 调用者与一个或多个命令关联。它向命令发送请求。
 */
class Invoker {
private:
    Command* on_start_;
    Command* on_finish_;

public:
    ~Invoker()
    {
        delete on_start_;
        delete on_finish_;
    }

    void SetOnStart(Command* command)
    {
        this->on_start_ = command;
    }
    void SetOnFinish(Command* command)
    {
        this->on_finish_ = command;
    }
    /**
     * 调用者不依赖于具体的命令或接收者类。调用者通过执行命令间接地将请求传递给接收者。
     */
    void DoSomethingImportant()
    {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};

/**
 * 客户端代码可以用任何命令参数化调用者。
 */
int main()
{
    Invoker* invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver* receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;

    return 0;
}