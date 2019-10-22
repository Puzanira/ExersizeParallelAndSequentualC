cmake_minimum_required (VERSION 3.5)
project (Exersize)

# add the subdirectory containing the CMakeLists.txt for the library
add_subdirectory (lib) 
include_directories ("${PROJECT_SOURCE_DIR}/lib")

# add a "test" target:
enable_testing()

# add the executable
add_executable (TestRealisations Test/TestRealisations.c)
target_link_libraries (TestRealisations FileHelper ParallelRealisation SequentialRealisation)
add_test(
    NAME TestRealisations 
    COMMAND TextMiningCompiler
)

# add the executable
add_executable (TestFileHelper Test/TestFileHelper.c)
target_link_libraries (TestFileHelper FileHelper ParallelRealisation SequentialRealisation)
add_test(
    NAME TestFileHelper 
    COMMAND TestFileHelper
)


