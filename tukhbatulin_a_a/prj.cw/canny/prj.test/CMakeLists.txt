add_executable (contours.path contours.cpp )
target_link_libraries(contours.path ${OpenCV_LIBS} canny ctikz)
add_test(NAME contours.path COMMAND contours.path)

add_executable (contours.test contours.test.cpp)
target_link_libraries(contours.test ${OpenCV_LIBS} canny ctikz)
add_test(NAME contours.test COMMAND contours.test)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../tests DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc_doxygen DESTINATION ./bin.rel)