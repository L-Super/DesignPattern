cmake_minimum_required(VERSION 3.22)
project(DesignPattern)

set(CMAKE_CXX_STANDARD 17)

set(SRC
#        main.cpp
#        Flyweight.cpp
#        Factory.cpp
#        AbstractFactory.cpp
#        Observer.cpp
#        State.cpp
#        Builder.cpp
#        Proxy.cpp
        Adapter.cpp)

# Factory 工厂模式
add_executable(Factory Factory.cpp)

# AbstractFactory 抽象工厂模式
add_executable(AbstractFactory AbstractFactory.cpp)

# Flyweight 享元模式
add_executable(Flyweight Flyweight.cpp)

# Observer 观察者模式
add_executable(Observer Observer.cpp)
# State 状态模式
add_executable(State State.cpp)
# Builder 建造者模式
add_executable(Builder Builder.cpp)
# Proxy 代理模式
add_executable(Proxy Proxy.cpp)


# Proxy 代理模式
add_executable(Proxy Proxy.cpp)

# Adapter 适配器模式
add_executable(Adapter Adapter.cpp)



# TemplateMethod 模板方法
add_executable(TemplateMethod TemplateMethod.cpp)

# Strategy 策略模式
add_executable(Strategy Strategy.cpp)