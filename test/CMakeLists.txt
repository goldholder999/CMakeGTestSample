cmake_minimum_required (VERSION 3.8)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

enable_testing()

find_package(GTest REQUIRED)


set(SRC_FILES_WITHOUT_MAIN 
	../src/example.cpp
	../src/example.h
)


set(TEST_BIN_NAME "UnitTestExecutor")

set(SRC_FILES_TEST
	test_main.cpp
)


INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src )
add_executable(	${TEST_BIN_NAME} 
	
	${SRC_FILES_WITHOUT_MAIN}
    ${SRC_FILES_TEST} 

)
target_link_libraries(${TEST_BIN_NAME}   GTest::GTest  )


