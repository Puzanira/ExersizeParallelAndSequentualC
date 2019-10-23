# add the library
add_library (file_helper file_helper.c file_helper.h)
add_library (parallel_realisation file_helper parallel_realisation.c parallel_realisation.h)
add_library (SequentialRealisation file_helper sequentual_realisation.c sequentual_realisation.h) 
