cmake_minimum_required (VERSION 3.5)
project (Exersize)

# add the subdirectory containing the CMakeLists.txt for the library
add_subdirectory (lib) 
include_directories ("${PROJECT_SOURCE_DIR}/lib")

# add the executable
add_executable (TestRealisations test_realisations.c)
target_link_libraries (TestRealisations parallel_realisation SequentialRealisation)

# add the executable
add_executable (Testfile_helper test_file_helper.c)
target_link_libraries (Testfile_helper file_helper)

set(pathword1 "${PROJECT_SOURCE_DIR}/Test_Files/test1.txt")
set(pathword2 "${PROJECT_SOURCE_DIR}/Test_Files/test2.txt")
set(pathword3 "${PROJECT_SOURCE_DIR}/Test_Files/test3.txt")

# add a "test" target:
enable_testing()

add_test(
    NAME TestRealisations 
    COMMAND TestRealisations "${pathword3}"
)

add_test(
    NAME Testfile_helper 
    COMMAND Testfile_helper "${pathword1}" "${pathword2}" "${pathword3}"
)


