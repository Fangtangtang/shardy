# Shardy MLIR Transforms Common

add_mlir_library(SdyTransformsCommonOpProperties
  op_properties.cc

  DEPENDS
  SdyDialect

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRSupport
  StablehloBase
  StablehloOps
  SdyDialect
)

add_mlir_library(SdyTransformsCommonShardingWalker
  sharding_walker.cc

  DEPENDS
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRSupport
  SdyDialect
)
