# Shardy MLIR Transforms Passes

add_subdirectory(common)
add_subdirectory(export)
add_subdirectory(import)
add_subdirectory(propagation)

add_mlir_library(SdyTransformsPasses
  passes.cc

  DEPENDS
  SdyTransformsExportPasses
  SdyTransformsImportPasses
  SdyTransformsPropagationPasses

  LINK_LIBS PUBLIC
  MLIRPass
  SdyTransformsExportPasses
  SdyTransformsImportPasses
  SdyTransformsPropagationPasses
)

target_include_directories(SdyTransformsPasses INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)
