# Shardy MLIR MPMD Transforms Common

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=MpmdCommon)
add_public_tablegen_target(MpmdTransformsCommonPassesIncGen)
add_dependencies(mlir-headers MpmdTransformsCommonPassesIncGen)

add_mlir_library(MpmdTransformsCommonUtils
  utils.cc

  DEPENDS
  MpmdDialect

  LINK_LIBS PUBLIC
  MpmdDialect
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRTransformUtils
  MLIRSupport
  MLIRPass
  MLIRTransforms
)

add_mlir_library(MpmdTransformsCommonSimplifyRegionOpBase
  simplify_region_op_base.cc

  DEPENDS
  MpmdTransformsCommonUtils

  LINK_LIBS PUBLIC
  MpmdTransformsCommonUtils
  LLVMSupport
  MLIRIR
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransformUtils
)

add_mlir_library(MpmdTransformsCommonDistributedFunctionPass
  distributed_function_pass.cc

  DEPENDS
  MpmdDialect

  LINK_LIBS PUBLIC
  MpmdDialect
  MLIRFuncDialect
  MLIRPass
)

add_mlir_library(MpmdTransformsCommonPasses
  absorb_inferred_fragments.cc
  call_rewrites.cc
  copy_constants.cc
  fragment_dce.cc
  fragment_dedup.cc
  merge_fragments.cc
  merge_transfers.cc
  remove_transfer_cycles.cc
  rule_based_merge.cc
  split_bwd_fragments.cc
  uniquify_function_inputs_outputs.cc
  unroll_for_loops.cc
  scheduler_preprocess.cc

  DEPENDS
  MpmdTransformsCommonPassesIncGen
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonUtils

  LINK_LIBS PUBLIC
  LLVMSupport
  StablehloOps
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonUtils
  MLIRAnalysis
  MLIRDataLayoutInterfaces
  MLIRFuncDialect
  MLIRIR
  MLIRTransformUtils
  MLIRLoopLikeInterface
  MLIRPass
  MLIRRewrite
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransforms
)
