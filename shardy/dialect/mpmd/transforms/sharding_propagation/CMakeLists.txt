# Shardy MLIR MPMD Transforms Sharding Propagation

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=MpmdShardingPropagation)
add_public_tablegen_target(MpmdTransformsShardingPropagationPassesIncGen)
add_dependencies(mlir-headers MpmdTransformsShardingPropagationPassesIncGen)

add_mlir_library(MpmdTransformsShardingPropagationPasses
  convert_sdy_constants.cc
  convert_sdy_shardings_to_mpmd_types.cc
  enforce_user_shardings.cc
  extract_reshards_from_inter_mesh_transfers.cc
  sharding_propagation_pipeline.cc

  DEPENDS
  MpmdTransformsShardingPropagationPassesIncGen
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  SdyDialect
  SdyExplicitReshardsUtil
  SdyTransformsPropagationPasses

  LINK_LIBS PUBLIC
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  SdyDialect
  SdyExplicitReshardsUtil
  SdyTransformsPropagationPasses
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRRewrite
  MLIRSupport
  MLIRTransformUtils
  StablehloOps
)
