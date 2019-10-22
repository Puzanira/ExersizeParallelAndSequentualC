cmake_minimum_required (VERSION 3.5)
project (Exersize)

# add the subdirectory containing the CMakeLists.txt for the library
add_subdirectory (lib) 
include_directories ("${PROJECT_SOURCE_DIR}/lib")

# add the executable
add_executable (TestRealisations TestRealisations.c)
target_link_libraries (TestRealisations ParallelRealisation SequentialRealisation)

# add the executable
add_executable (TestFileHelper TestFileHelper.c)
target_link_libraries (TestFileHelper ParallelRealisation SequentialRealisation)

# add a "test" target:
enable_testing()

add_test(
    NAME TestRealisations 
    COMMAND TextMiningCompiler
)

add_test(
    NAME TestFileHelper 
    COMMAND TestFileHelper
)


