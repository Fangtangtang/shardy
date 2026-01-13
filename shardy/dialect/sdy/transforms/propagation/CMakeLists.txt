# Shardy MLIR Transform Propagation System

add_subdirectory(debugging)

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=SdyPropagation)
add_public_tablegen_target(SdyTransformsPropagationPassesIncGen)
add_dependencies(mlir-headers SdyTransformsPropagationPassesIncGen)
add_mlir_doc(passes SdyTransformsPropagationPasses ./ -gen-pass-doc)

add_mlir_library(SdyTransformsPropagationPasses
  aggressive_propagation.cc
  basic_propagation.cc
  op_priority_propagation.cc
  populate_op_sharding_rules.cc
  propagation_pipeline.cc
  user_priority_propagation.cc

  DEPENDS
  SdyTransformsPropagationAggressiveFactorPropagation
  SdyTransformsPropagationAutoPartitionerRegistry
  SdyTransformsPropagationBasicFactorPropagation
  SdyTransformsPropagationOpShardingRuleBuilder
  SdyTransformsPropagationOpShardingRuleRegistry
  SdyTransformsPropagationPassesIncGen
  SdyTransformsPropagationShardingGroupMap
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyCommonFileUtils
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
  SdyTransformsExportPasses
  SdyTransformsImportPasses
  SdyTransformsPropagationDebuggingSourceSharding

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRBufferizationDialect
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRRewrite
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransformUtils
  StablehloOps
  SdyTransformsPropagationAggressiveFactorPropagation
  SdyTransformsPropagationAutoPartitionerRegistry
  SdyTransformsPropagationBasicFactorPropagation
  SdyTransformsPropagationOpShardingRuleBuilder
  SdyTransformsPropagationOpShardingRuleRegistry
  SdyTransformsPropagationShardingGroupMap
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyCommonFileUtils
  SdyDialect
  SdyTransformsCommonOpProperties
  SdyTransformsCommonShardingWalker
  SdyTransformsExportPasses
  SdyTransformsImportPasses
  SdyTransformsPropagationDebuggingSourceSharding
)

target_include_directories(SdyTransformsPropagationPasses INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

add_mlir_library(SdyTransformsPropagationOpShardingRuleBuilder
  op_sharding_rule_builder.cc

  DEPENDS
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRIR
  MLIRSupport
  StablehloOps
  SdyDialect
)

add_mlir_library(SdyTransformsPropagationOpShardingRuleRegistry
  op_sharding_rule_registry.cc

  DEPENDS
  SdyTransformsPropagationOpShardingRuleBuilder
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRSupport
  StablehloOps
  SdyTransformsPropagationOpShardingRuleBuilder
  SdyDialect
)

add_mlir_library(SdyTransformsPropagationShardingGroupMap
  sharding_group_map.cc

  DEPENDS
  SdyTransformsPropagationUtils
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRIR
  MLIRSupport
  SdyTransformsPropagationUtils
  SdyDialect
)

add_mlir_library(SdyTransformsPropagationShardingProjection
  sharding_projection.cc

  DEPENDS
  SdyTransformsPropagationUtils
  SdyAxisListRef
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRIR
  MLIRSupport
  SdyTransformsPropagationUtils
  SdyAxisListRef
  SdyDialect
)

add_mlir_library(SdyTransformsPropagationAutoPartitionerRegistry
  auto_partitioner_registry.cc

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRIR
  MLIRPass
)

add_mlir_library(SdyTransformsPropagationUtils
  utils.cc

  DEPENDS
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRSupport
  SdyDialect
)

add_mlir_library(SdyTransformsPropagationBasicFactorPropagation
  basic_factor_propagation.cc

  DEPENDS
  SdyTransformsPropagationShardingProjection
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRIR
  MLIRSupport
  SdyTransformsPropagationShardingProjection
  SdyDialect
)

add_mlir_library(SdyTransformsPropagationAggressiveFactorPropagation
  aggressive_factor_propagation.cc

  DEPENDS
  SdyTransformsPropagationBasicFactorPropagation
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyDialect
  SdyTransformsCommonOpProperties

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRIR
  MLIRSupport
  SdyTransformsPropagationBasicFactorPropagation
  SdyTransformsPropagationShardingProjection
  SdyTransformsPropagationUtils
  SdyDialect
  SdyTransformsCommonOpProperties
)
