# Shardy MLIR Transforms Propagation Debugging System

add_mlir_library(SdyTransformsPropagationDebuggingSourceSharding
  source_sharding.cc

  DEPENDS
  SdyDialect
  SdyTransformsPropagationShardingProjection

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRSupport
  SdyDialect
  SdyTransformsPropagationShardingProjection
)
