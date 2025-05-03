cmake_minimum_required(VERSION 3.5)
project(MyQtApp)

# Настройка пути к Qt (если CMake не находит автоматически)
set(CMAKE_PREFIX_PATH "C:\msys64\mingw64\bin")

# Поиск Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Включение автоматического moc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Добавление исходников
add_executable(MyApp
    ../main.cpp
    ../mainwindow.cpp
    ../mainwindow.h
)

# Подключение Qt6 модулей
target_link_libraries(MyApp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)