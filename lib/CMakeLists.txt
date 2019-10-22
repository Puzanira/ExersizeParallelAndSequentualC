# add the library
add_library (FileHelper FileHelper.c FileHelper.h)
add_library (ParallelRealisation FileHelper ParallelRealisation.c ParallelRealisation.h)
add_library (SequentialRealisation FileHelper SequentualRealisation.c SequentualRealisation.h) 
