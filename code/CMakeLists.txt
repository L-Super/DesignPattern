cmake_minimum_required(VERSION 3.22)
project(DesignPattern)

set(CMAKE_CXX_STANDARD 17)

#
# 创建型模式
#

# Factory 工厂模式
add_executable(Factory Factory.cpp)

# AbstractFactory 抽象工厂模式
add_executable(AbstractFactory AbstractFactory.cpp)

# Builder 建造者模式
add_executable(Builder Builder.cpp)

# Prototype 原型模式
add_executable(Prototype Prototype.cpp)

#
# 结构型模式
#

# Proxy 代理模式
add_executable(Proxy Proxy.cpp)

# Adapter 适配器模式
add_executable(Adapter Adapter.cpp)

# Flyweight 享元模式
add_executable(Flyweight Flyweight.cpp)

# Facade 外观模式
add_executable(Facade Facade.cpp)

# Decorator 装饰模式
add_executable(Decorator Decorator.cpp)

# Bridge 桥接模式
add_executable(Bridge Bridge.cpp)

#
# 行为模式
#

# Observer 观察者模式
add_executable(Observer Observer.cpp)

# State 状态模式
add_executable(State State.cpp)

# TemplateMethod 模板方法
add_executable(TemplateMethod TemplateMethod.cpp)

# Strategy 策略模式
add_executable(Strategy Strategy.cpp)

# chain-of-responsibility 职责链模式
add_executable(ChainOfResponsibility ChainOfResponsibility.cpp)

# Visitor 访问者模式
add_executable(Visitor Visitor.cpp)

# Command 命令模式
add_executable(Command Command.cpp)