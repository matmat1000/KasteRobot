cmake_minimum_required(VERSION 3.5)

project(ColourFilters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package ( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(ColourFilters main.cpp)
target_link_libraries(ColourFilters ${OpenCV_LIBS})
include(GNUInstallDirs)
install(TARGETS ColourFilters
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
