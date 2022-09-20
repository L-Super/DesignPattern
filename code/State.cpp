//
// Created by Listening on 2022/9/20.
//
#include <iostream>

/**
 * State 基类声明了所有具体 State 都应该实现的方法，并且还提供了对与 State 关联的 Context 对象的反向引用。
 * State 可以使用此反向引用将 Context 转换为另一个 State。
 */
class Context;

class State {
	/**
	 * @var Context
	 */
 protected:
	Context *mContext;

 public:
	virtual ~State() = default;

	void SetContext(Context *context) {
		this->mContext = context;
	}

	virtual void Handle1() = 0;
	virtual void Handle2() = 0;
};

/**
 * 上下文定义了客户感兴趣的接口。它还维护对 State 子类实例的引用，该实例表示 Context 的当前状态。
 */
class Context {
	/**
	 * @var State 对上下文当前状态的引用。.
	 */
 private:
	State *mState;

 public:
	explicit Context(State *state) : mState(nullptr) {
		this->TransitionTo(state);
	}
	~Context() {
		delete mState;
	}
	/**
	 * Context 允许在运行时更改 State 对象。
	 */
	void TransitionTo(State *state) {
		std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
	 	if (this->mState != nullptr)
			delete this->mState;
		this->mState = state;
		this->mState->SetContext(this);
	}
	/**
	 * Context 将其部分行为委托给当前的 State 对象。
	 */
	void Request1() {
		this->mState->Handle1();
	}
	void Request2() {
		this->mState->Handle2();
	}
};

/**
 * 具体状态实现与上下文状态相关联的各种行为。
 */
class ConcreteStateA : public State {
 public:
	void Handle1() override;

	void Handle2() override {
		std::cout << "ConcreteStateA handles request2.\n";
	}
};

class ConcreteStateB : public State {
 public:
	void Handle1() override {
		std::cout << "ConcreteStateB handles request1.\n";
	}
	void Handle2() override {
		std::cout << "ConcreteStateB handles request2.\n";
		std::cout << "ConcreteStateB wants to change the state of the mContext.\n";
		this->mContext->TransitionTo(new ConcreteStateA);
	}
};

void ConcreteStateA::Handle1() {
		std::cout << "ConcreteStateA handles request1.\n";
		std::cout << "ConcreteStateA wants to change the state of the mContext.\n";

		this->mContext->TransitionTo(new ConcreteStateB);
}

int main() {
	Context *context = new Context(new ConcreteStateA);
	context->Request1();
	context->Request2();
	delete context;

	return 0;
}