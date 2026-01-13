# Shardy MLIR Transforms Import Passes and Pipeline

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=SdyImport)
add_public_tablegen_target(SdyTransformsImportPassesIncGen)
add_dependencies(mlir-headers SdyTransformsImportPassesIncGen)
add_mlir_doc(passes SdyTransformsImportPasses ./ -gen-pass-doc)

add_mlir_library(SdyTransformsImportPasses
  add_data_flow_edges.cc
  apply_sharding_constraints.cc
  constant_or_scalar_splitter.cc
  import_pipeline.cc
  inline_meshes.cc
  lift_inlined_meshes.cc
  manual_axes_cleanup.cc
  remove_size_one_axes.cc
  sharding_group_import.cc

  DEPENDS
  SdyTransformsImportPassesIncGen
  SdyCommonFileUtils
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRRewrite
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransformUtils
  MLIRTransforms
  StablehloOps
  SdyCommonFileUtils
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
)

target_include_directories(SdyTransformsImportPasses INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)
