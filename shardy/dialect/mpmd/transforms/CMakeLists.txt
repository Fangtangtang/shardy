# Shardy MLIR MPMD Transforms Passes

add_subdirectory(common)
add_subdirectory(export)
add_subdirectory(import)
add_subdirectory(optimize)
add_subdirectory(sharding_propagation)

add_mlir_library(MpmdTransformsPasses
  passes.cc

  DEPENDS
  MpmdTransformsCommonPasses
  MpmdTransformsExportPasses
  MpmdTransformsImportPasses
  MpmdTransformsOptimizePasses
  MpmdTransformsShardingPropagationPasses

  LINK_LIBS PUBLIC
  MLIRPass
  MpmdTransformsCommonPasses
  MpmdTransformsExportPasses
  MpmdTransformsImportPasses
  MpmdTransformsOptimizePasses
  MpmdTransformsShardingPropagationPasses
)

target_include_directories(MpmdTransformsPasses INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)
