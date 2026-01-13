# Shardy MLIR dialect.

set(LLVM_TARGET_DEFINITIONS dialect.td)
mlir_tablegen(dialect.h.inc -gen-dialect-decls -dialect=sdy)
mlir_tablegen(dialect.cc.inc -gen-dialect-defs -dialect=sdy)
add_public_tablegen_target(SdyDialectIncGen)
add_dependencies(mlir-headers SdyDialectIncGen)
add_mlir_doc(dialect SdyDialect src/autogen/md/Dialect/ -gen-dialect-doc)

set(LLVM_TARGET_DEFINITIONS ops.td)
mlir_tablegen(ops.h.inc -gen-op-decls)
mlir_tablegen(ops.cc.inc -gen-op-defs)
add_public_tablegen_target(SdyOpsIncGen)
add_dependencies(mlir-headers SdyOpsIncGen)

set(LLVM_TARGET_DEFINITIONS attrs.td)
mlir_tablegen(attrs.h.inc -gen-attrdef-decls)
mlir_tablegen(attrs.cc.inc -gen-attrdef-defs)
add_public_tablegen_target(SdyAttrsIncGen)
add_dependencies(mlir-headers SdyAttrsIncGen)

set(LLVM_TARGET_DEFINITIONS enums.td)
mlir_tablegen(enums.h.inc -gen-enum-decls)
mlir_tablegen(enums.cc.inc -gen-enum-defs)
add_public_tablegen_target(SdyEnumsIncGen)
add_dependencies(mlir-headers SdyEnumsIncGen)

set(LLVM_TARGET_DEFINITIONS op_interface.td)
mlir_tablegen(op_interface.h.inc -gen-op-interface-decls)
mlir_tablegen(op_interface.cc.inc -gen-op-interface-defs)
add_public_tablegen_target(SdyOpInterfaceIncGen)
add_dependencies(mlir-headers SdyOpInterfaceIncGen)

set(LLVM_TARGET_DEFINITIONS canonicalization.td)
mlir_tablegen(canonicalization.cc.inc -gen-rewriters)
add_public_tablegen_target(SdyCanonicalizationIncGen)
add_dependencies(mlir-headers SdyCanonicalizationIncGen)

set(LLVM_TARGET_DEFINITIONS bytecode.td)
mlir_tablegen(bytecode.cc.inc -gen-bytecode -bytecode-dialect=sdy)
add_public_tablegen_target(SdyBytecodeIncGen)
add_dependencies(mlir-headers SdyBytecodeIncGen)

add_mlir_dialect_library(SdyDialect
  bytecode.cc
  canonicalization.cc
  dialect.cc
  extensions/stablehlo_extensions.cc
  parsers.cc
  printers.cc
  utils.cc
  verifiers.cc

  DEPENDS
  SdyDialectIncGen
  SdyOpsIncGen
  SdyAttrsIncGen
  SdyEnumsIncGen
  SdyOpInterfaceIncGen
  SdyCanonicalizationIncGen
  SdyBytecodeIncGen

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
)

target_include_directories(SdyDialect INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

add_mlir_dialect_library(SdyRegister
  register.cc

  LINK_LIBS PUBLIC
  SdyDialect
  MLIRFuncDialect
  MLIRFuncAllExtensions
  MLIRIR
  StablehloOps
)

target_include_directories(SdyRegister INTERFACE
  $<BUILD_INTERFACE:${SHARDY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${SHARDY_BINARY_DIR}>
)

add_mlir_dialect_library(SdyAxisListRef
  axis_list_ref.cc

  LINK_LIBS PUBLIC
  SdyDialect
  LLVMSupport
  MLIRSupport
)
