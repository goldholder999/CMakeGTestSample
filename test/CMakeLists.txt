cmake_minimum_required (VERSION 3.10)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # vcpackage
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")

endif()



find_package(GTest REQUIRED)
if(GTest_FOUND)
    SET(GTEST_LINK_LIB GTest::GTest)
else()
    # gtest download 
    configure_file(gtestCMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
      include_directories("${gtest_SOURCE_DIR}/include")
    endif()
    SET(GTEST_LINK_LIB gtest_main)
endif()



set(SRC_FILES_WITHOUT_MAIN 
	${PROJECT_SOURCE_DIR}/src/example.cpp
	${PROJECT_SOURCE_DIR}/src/example.h
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
target_link_libraries(${TEST_BIN_NAME}    ${GTEST_LINK_LIB} )


add_test(
     NAME ${TEST_BIN_NAME} 
     COMMAND ${TEST_BIN_NAME} 
)
