aux_source_directory(. DIR_SRCS)

add_subdirectory(algo)
add_subdirectory(fitness)
add_subdirectory(problems)
add_subdirectory(replacement)
add_subdirectory(selection)
add_subdirectory(VaritionOp)

add_library(MOEASRCS ${DIR_SRCS})


