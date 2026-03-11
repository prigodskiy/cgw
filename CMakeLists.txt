cmake_minimum_required(VERSION 3.10)
project(ModularGraphicsApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 1. Пути к заголовкам (ВАЖНО!)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/modules
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/include
)

# 2. Пути к библиотекам
link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

# 3. Поиск всех исходных файлов
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# 4. Создаём исполняемый файл
add_executable(app ${SOURCE_FILES} ${HEADER_FILES})

# 5. Подключаем библиотеки
target_link_libraries(app
    freeglut.lib
    opengl32.lib
    glu32.lib
)

# 6. Копируем DLL после сборки (чтобы программа запускалась)
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/lib/freeglut.dll"
    $<TARGET_FILE_DIR:app>
)