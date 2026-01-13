add_mlir_public_c_api_library(SdyCAPI
  PARTIAL_SOURCES_INTENDED
  attributes_sdy.cc
  dialect_sdy.cc
  passes_sdy.cc

  DEPENDS
  SdyDialect
  SdyTransformsPasses

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRBytecodeOpInterface
  MLIRFuncDialect
  MLIRIR
  MLIRInferTypeOpInterface
  MLIRTransformUtils
  MLIRShapeDialect
  MLIRSideEffectInterfaces
  MLIRSupport
  StablehloAssemblyFormat
  StablehloOps
  StablehloTypeInference
  SdyDialect
  SdyTransformsPasses
)

add_mlir_public_c_api_library(MpmdCAPI
  PARTIAL_SOURCES_INTENDED
  passes_mpmd.cc
  dialect_mpmd.cc
  attributes_mpmd.cc

  DEPENDS
  MpmdDialect
  MpmdTransformsPasses

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRBytecodeOpInterface
  MLIRFuncDialect
  MLIRIR
  MLIRInferTypeOpInterface
  MLIRTransformUtils
  MLIRShapeDialect
  MLIRSideEffectInterfaces
  MLIRSupport
  StablehloAssemblyFormat
  StablehloOps
  StablehloTypeInference
  MpmdDialect
  MpmdTransformsPasses
)
