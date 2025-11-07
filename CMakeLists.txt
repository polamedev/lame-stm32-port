cmake_minimum_required(VERSION 3.21)

# Основные настройки проекта
project(
    lame
    VERSION 1.0.0
    DESCRIPTION
        "Embedded lame lib port for stm32"
    LANGUAGES C
)

# Определяем является ли текущий проектом верхнего уровня. Для fetch проектов, gitsubmodule или просто вложенных проектов это неверно
# string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
# Но в новых версиях 3.21 можно использовать ${PROJECT_IS_TOP_LEVEL}

# -----------------------------------------------------------------------------------------------------------------------------------
# Настройка сборки библиотеки
# -----------------------------------------------------------------------------------------------------------------------------------

# Опции сборки
# option(LAME_BUILD_TESTS       "Build lame tests"            OFF)  # Нужно ли собирать тесты для библиотеки
# option(LAME_BUILD_MOCKS       "Build  lame mocks lib"       OFF)  # Нужно ли собирать мок-объекты библиотеки
# option(LAME_BUILD_MOCKS_TESTS "Build tests lame::mocks lib" OFF)  # Нужно ли собирать тесты для библиотеки мок-объектов, также опция определяется в самой библиотеки тестов

# Установка типа сборки
if(NOT CMAKE_BUILD_TYPE)
    # Установить переменную CMAKE_BUILD_TYPE и сохранить в кэше
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")
    # Устанавливаем для CMAKE_BUILD_TYPE возможные значения, которые можно будет выбрать через cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


# Добавление суфикса в имя дебажной библиотеки, нужно чтобы установить различия в названии. Возможно от этого стоит отказаться
set(CMAKE_DEBUG_POSTFIX -dev)

# -----------------------------------------------------------------------------------------------------------------------------------
# Настройка таргета библиотеки
# -----------------------------------------------------------------------------------------------------------------------------------

# Добавление библиотеки
add_library(lame-stm32 STATIC)

# Добавляем alias для библиотеки, полезно для избежания конфликта имен
add_library(lame::lame-stm32 ALIAS lame-stm32)

# VERSION - Устанавливаем версию библиотеки из версии проекта
# SOVERSION - Версия совместимости - определяет версию API стоит изменять, когда меняется API, поведение или используемый интерфейс
set_target_properties(
    lame-stm32
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_sources(lame-stm32
    PRIVATE 
    src/drivers/Pin.c
)


target_include_directories(lame-stm32
    # Пути включения доступные только библиотеке
    PRIVATE 
    src 
    include/lame/drivers

    # Пути включения доступные самой библиотеке и пользователям
    PUBLIC
    # Используется выражения генератора
    # При сборке BUILD_INTERFACE заменится на include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    # При установке INSTALL_INTERFACE заменится на католог включения при установки
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(lame-stm32
    PUBLIC
    lame::lame
    PRIVATE
    STM32_Drivers 
)

# -----------------------------------------------------------------------------------------------------------------------------------
# Добавление других таргетов
# -----------------------------------------------------------------------------------------------------------------------------------

# set(LAME_BUILD_TESTS ON)

# if(LAME_BUILD_TESTS)
#     # Для тестов необходимы моки объектов для этого установим переменную
#     set(LAME_BUILD_MOCKS ON)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

# if(LAME_BUILD_MOCKS)
#     add_subdirectory(mocks)
# endif()
