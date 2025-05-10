cmake_minimum_required(VERSION 3.16)
project(WeatherApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем путь к QtCharts
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}:/usr/lib64/cmake")

# Подключаем Qt6 модули
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Charts)

# Создаём исполняемый файл
add_executable(weatherapp
    main.cpp
)

# Линкуем библиотеки
target_link_libraries(weatherapp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Charts
)
