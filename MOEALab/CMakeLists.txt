cmake_minimum_required(VERSION 2.8)

project(MOEA)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules" )



set (MOEA_VERSION_MAJOR 1)
set (MOEA_VERSION_MINOR 0)


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



find_package(Paradiseo COMPONENTS moeo eo es eoutils REQUIRED)
include_directories(${PARADISEO_INCLUDE_DIR})

add_subdirectory(src/problems)

add_executable(MOEA
        src/algo/moeaMOEAD.h
        src/subproblem/moeaSubProblem.h
        src/subproblem/moeaWeightInit.h
        src/subproblem/moeaNeighborhoodInit.h
        src/global.h
        src/extremePoint/moeaExtremePoint.h
        src/VariationOp/moeaSBXCrossover.h
        src/VariationOp/PolynomialMutation.h
        src/VariationOp/moeaRepairOp.h
        src/fitness/moeaTCHFitnessAssignment.h
        src/fitness/moeaPBIFitnessAssignment.h
        src/fitness/moeaConicalAreaFitnessAssignment.h
        src/fitness/moeaHypervolumeFitnessAssignment.h
        src/fitness/moeaSubProblemFitnessAssignment.h
        src/replacement/moeaNeighborReplacement.h
        src/replacement/replacement.h
        src/replacement/moeaConicalReplacement.h
        src/selection/moeaNeighborhoodSelect.h
        src/extremePoint/moeaExtremePointManager.h
        src/extremePoint/moeaReferencePointUpdate.h
        src/extremePoint/moeaUtopianPointUpdate.h
        src/Timer.h
        src/extremePoint/moeaNadirPointUpdate.h
        src/extremePoint/moeaAnchorPointUpdate.h
        src/problems/problems.h
        src/selection/moeaSelectIndex.h
        src/VariationOp/moeaRecombination.h
        src/selection/moeaDiffSeclect.h
        src/VariationOp/moeaDiffXover.h
        src/VariationOp/moeaDiffRecombination.h
        src/VariationOp/moeaQuadRecombination.h
        src/moea.h
        src/VariationOp/VariationOp.h
        src/subproblem/subproblem.h
        src/selection/selection.h
        src/fitness/fitness.h
        src/extremePoint/extremePoint.h
        src/algo/algo.h
        src/subproblem/moeaSubProblemMapping.h
        src/subproblem/moeaSubProblemMappingUpdate.h
        src/fitness/moeaConicalAreaComparator.h
        src/extremePoint/moeaNormalized.h
        src/extremePoint/moeaNadirNormalized.h
        src/extremePoint/moeaAnchorNormalized.h
        src/fitness/moeaConicalComparator.h
        src/fitness/moeaConicalHyperVolumeComparator.h
        src/subproblem/moeaVicinityInit.h
        src/selection/moeaConicalTournamentSelect.h
        src/selection/moeaConicalSpecialSelect.h
        test/runMOEAD.h
        test/runCAEA.h
        test/runCHEA.h
        test/test.cpp
)

target_link_libraries(MOEA PROBLEMS ${PARADISEO_LIBRARIES})
