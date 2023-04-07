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

# Adapter 适配器模式
add_executable(Adapter Adapter.cpp)

# Factory 工厂模式
add_executable(Factory Factory.cpp)

# TemplateMethod 模板方法
add_executable(TemplateMethod TemplateMethod.cpp)

# Strategy 策略模式
add_executable(Strategy Strategy.cpp)