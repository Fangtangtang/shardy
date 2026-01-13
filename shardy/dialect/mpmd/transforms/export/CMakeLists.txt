# Shardy MLIR MPMD Transform Export Passes and Pipeline

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=MpmdExport)
add_public_tablegen_target(MpmdTransformsExportPassesIncGen)
add_dependencies(mlir-headers MpmdTransformsExportPassesIncGen)

add_mlir_library(MpmdTransformsExportUtils
  utils.cc

  DEPENDS
  MpmdDialect

  LINK_LIBS PUBLIC
  MpmdDialect
  MLIRAnalysis
  MLIRFuncDialect
  MLIRIR
  MLIRSupport
)

add_mlir_library(MpmdTransformsExportNamingUtils
  naming_utils.cc

  DEPENDS
  MpmdDialect
  MpmdTransformsCommonUtils

  LINK_LIBS PUBLIC
  MpmdDialect
  MpmdTransformsCommonUtils
  MLIRFuncDialect
  MLIRPass
  LLVMSupport
  MLIRIR
  MLIRSupport
)

add_mlir_library(MpmdTransformsExportPasses
  export_pipeline.cc
  lower_to_fragment_calls.cc
  mark_aliasing_and_donation.cc
  mark_fragment_reserved_memory.cc
  mark_input_output_with_layouts.cc
  mark_offloaded_input_output.cc
  reschedule_ops.cc

  DEPENDS
  MpmdDialect
  MpmdTransformsExportPassesIncGen
  MpmdTransformsExportNamingUtils
  MpmdTransformsExportUtils
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  SdyDialect

  LINK_LIBS PUBLIC
  MpmdTransformsExportNamingUtils
  MpmdTransformsExportUtils
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  SdyDialect
  LLVMSupport
  MLIRAnalysis
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRSupport
  MLIRTransformUtils
  MLIRTransforms
  StablehloOps
)
