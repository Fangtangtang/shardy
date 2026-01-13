# Shardy MLIR Transform Export Passes and Pipeline

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=SdyExport)
add_public_tablegen_target(SdyExportPassesIncGen)
add_dependencies(mlir-headers SdyExportPassesIncGen)
add_mlir_doc(passes SdyTransformsExportPasses ./ -gen-pass-doc)

add_mlir_library(SdyExplicitReshardsUtil
  explicit_reshards_util.cc

  DEPENDS
  SdyCommonFileUtils
  SdyAxisListRef
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
  SdyTransformsPropagationOpShardingRuleRegistry
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyTransformsPropagationDebuggingSourceSharding

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRRewrite
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransformUtils
  StablehloOps
  SdyCommonFileUtils
  SdyAxisListRef
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
  SdyTransformsPropagationOpShardingRuleRegistry
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyTransformsPropagationDebuggingSourceSharding
)

add_mlir_library(SdyTransformsExportPasses
  close_shardings.cc
  constant_or_scalar_merger.cc
  drop_sharding_rules.cc
  export_pipeline.cc
  insert_explicit_reshards.cc
  remove_ag_rs_for_cmv1.cc
  remove_propagation_debug_info.cc
  remove_sharding_groups.cc
  reshard_to_collectives.cc
  sharding_constraint_to_reshard.cc
  sink_data_flow_edges.cc
  update_non_divisible_input_output_shardings.cc

  DEPENDS
  SdyExplicitReshardsUtil
  SdyExportPassesIncGen
  SdyCommonFileUtils
  SdyAxisListRef
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
  SdyTransformsPropagationOpShardingRuleRegistry
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyTransformsPropagationDebuggingSourceSharding
  SdyTransformsImportPasses

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRRewrite
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransformUtils
  StablehloOps
  SdyCommonFileUtils
  SdyAxisListRef
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
  SdyTransformsPropagationOpShardingRuleRegistry
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyTransformsPropagationDebuggingSourceSharding
  SdyExplicitReshardsUtil
  SdyTransformsImportPasses
)

target_include_directories(SdyTransformsExportPasses INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

target_include_directories(SdyExplicitReshardsUtil INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)
