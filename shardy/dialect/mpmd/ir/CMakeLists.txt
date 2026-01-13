# Shardy MLIR MPMD dialect.

set(LLVM_TARGET_DEFINITIONS dialect.td)
mlir_tablegen(dialect.h.inc -gen-dialect-decls -dialect=mpmd)
mlir_tablegen(dialect.cc.inc -gen-dialect-defs -dialect=mpmd)
add_public_tablegen_target(MpmdDialectIncGen)
add_dependencies(mlir-headers MpmdDialectIncGen)
add_mlir_doc(dialect MpmdDialect src/autogen/md/Dialect/ -gen-dialect-doc)

set(LLVM_TARGET_DEFINITIONS canonicalization.td)
mlir_tablegen(canonicalization.cc.inc -gen-rewriters)
add_public_tablegen_target(MpmdCanonicalizationIncGen)
add_dependencies(mlir-headers MpmdCanonicalizationIncGen)

set(LLVM_TARGET_DEFINITIONS ops.td)
mlir_tablegen(ops.h.inc -gen-op-decls)
mlir_tablegen(ops.cc.inc -gen-op-defs)
add_public_tablegen_target(MpmdOpsIncGen)
add_dependencies(mlir-headers MpmdOpsIncGen)

set(LLVM_TARGET_DEFINITIONS types.td)
mlir_tablegen(types.h.inc -gen-typedef-decls)
mlir_tablegen(types.cc.inc -gen-typedef-defs)
add_public_tablegen_target(MpmdTypesIncGen)
add_dependencies(mlir-headers MpmdTypesIncGen)

set(LLVM_TARGET_DEFINITIONS attrs.td)
mlir_tablegen(attrs.h.inc -gen-attrdef-decls)
mlir_tablegen(attrs.cc.inc -gen-attrdef-defs)
add_public_tablegen_target(MpmdAttrsIncGen)
add_dependencies(mlir-headers MpmdAttrsIncGen)

set(LLVM_TARGET_DEFINITIONS enums.td)
mlir_tablegen(enums.h.inc -gen-enum-decls)
mlir_tablegen(enums.cc.inc -gen-enum-defs)
add_public_tablegen_target(MpmdEnumsIncGen)
add_dependencies(mlir-headers MpmdEnumsIncGen)

add_mlir_dialect_library(MpmdDialect
  dialect.cc
  utils.cc

  DEPENDS
  MpmdDialectIncGen
  MpmdOpsIncGen
  MpmdAttrsIncGen
  MpmdEnumsIncGen
  MpmdTypesIncGen
  MpmdCanonicalizationIncGen

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
  StablehloBase
  StablehloOps
  StablehloTypeInference
)

target_include_directories(MpmdDialect INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

add_mlir_dialect_library(MpmdRegister
  register.cc

  LINK_LIBS PUBLIC
  MpmdDialect
  MLIRFuncDialect
  MLIRFuncAllExtensions
  MLIRIR
  StablehloOps
)

target_include_directories(MpmdRegister INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

add_mlir_dialect_library(MpmdFragmentExecutionRules
  fragment_execution_rules.cc

  LINK_LIBS PUBLIC
  MpmdDialect
  MpmdTransformsCommonUtils
  LLVMSupport
  MLIRIR
  MLIRSupport
  MLIRParser
)

target_include_directories(MpmdFragmentExecutionRules INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

