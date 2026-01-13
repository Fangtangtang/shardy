# Shardy MLIR MPMD Transforms Optimize

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=MpmdOptimize)
add_public_tablegen_target(MpmdTransformsOptimizePassesIncGen)
add_dependencies(mlir-headers MpmdTransformsOptimizePassesIncGen)

add_mlir_library(MpmdTransformsOptimizeUtils
  utils.cc

  DEPENDS
  MpmdDialect
  MpmdTransformsCommonUtils

  LINK_LIBS PUBLIC
  MpmdDialect
  MpmdTransformsCommonUtils
  LLVMSupport
  MLIRIR
  MLIRSupport
)

add_mlir_library(MpmdTransformsOptimizePipelineSchedule
  pipeline_schedule.cc

  DEPENDS
  MpmdTransformsOptimizeUtils
  MpmdDialect
  MpmdTransformsCommonUtils

  LINK_LIBS PUBLIC
  MpmdTransformsOptimizeUtils
  MpmdDialect
  MpmdTransformsCommonUtils
  LLVMSupport
  MLIRIR
  MLIRSupport
)

add_mlir_library(MpmdTransformsOptimizePasses
  optimize_pipeline.cc
  remat_fragment.cc
  scheduler.cc
  rule_based_schedule.cc

  DEPENDS
  MpmdTransformsOptimizePassesIncGen
  MpmdTransformsOptimizePipelineSchedule
  MpmdTransformsOptimizeUtils
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdFragmentExecutionRules
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils

  LINK_LIBS PUBLIC
  MpmdTransformsOptimizePipelineSchedule
  MpmdTransformsOptimizeUtils
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdFragmentExecutionRules
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  LLVMSupport
  MLIRAnalysis
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRSupport
  MLIRTransforms
  MLIRTransformUtils
)
