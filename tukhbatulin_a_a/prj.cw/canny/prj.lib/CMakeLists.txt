add_library(canny canny.cpp include/canny/canny.hpp)
set_property(TARGET canny PROPERTY CXX_STANDARD 20)
target_include_directories(canny PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(canny ${OpenCV_LIBS})
install(TARGETS canny)

add_subdirectory(ctikz)