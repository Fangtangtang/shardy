# Shardy MLIR Common

add_mlir_library(SdyCommonFileUtils
  file_utils.cc
  logging.cc
  save_module_op.cc

  DEPENDS
  SdyDialect

  LINK_LIBS PUBLIC
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRSupport
  SdyDialect
)
