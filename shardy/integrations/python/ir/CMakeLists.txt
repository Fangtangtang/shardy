# Shardy MLIR Module

declare_mlir_python_sources(SdyPythonSources)
declare_mlir_python_sources(SdyPythonSources.Dialects
  ADD_TO_PARENT SdyPythonSources
)

declare_mlir_dialect_python_bindings(
  ADD_TO_PARENT SdyPythonSources.Dialects
  ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  TD_FILE dialects/sdy_ops.td
  GEN_ENUM_BINDINGS ON
  GEN_ENUM_BINDINGS_TD_FILE dialects/sdy_enums.td
  SOURCES dialects/sdy.py
  DIALECT_NAME sdy
)

declare_mlir_python_sources(SdyPythonExtensions)
declare_mlir_python_extension(SdyPythonExtensions.Main
  MODULE_NAME _sdy
  ADD_TO_PARENT SdyPythonExtensions
  PYTHON_BINDINGS_LIBRARY nanobind
  SOURCES
    sdy_module.cc
  EMBED_CAPI_LINK_LIBS
    SdyCAPI
  PRIVATE_LINK_LIBS
    SdyCAPI
    LLVMSupport
)

declare_mlir_python_sources(MpmdPythonSources)
declare_mlir_python_sources(MpmdPythonSources.Dialects
  ADD_TO_PARENT MpmdPythonSources
)

declare_mlir_dialect_python_bindings(
  ADD_TO_PARENT MpmdPythonSources.Dialects
  ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  TD_FILE dialects/mpmd_ops.td
  GEN_ENUM_BINDINGS ON
  GEN_ENUM_BINDINGS_TD_FILE dialects/mpmd_enums.td
  SOURCES dialects/mpmd.py
  DIALECT_NAME mpmd
)

declare_mlir_python_sources(MpmdPythonExtensions)
declare_mlir_python_extension(MpmdPythonExtensions.Main
  MODULE_NAME _mpmd
  ADD_TO_PARENT MpmdPythonExtensions
  PYTHON_BINDINGS_LIBRARY nanobind
  SOURCES
    mpmd_module.cc
  EMBED_CAPI_LINK_LIBS
    MpmdCAPI
  PRIVATE_LINK_LIBS
    MpmdCAPI
    LLVMSupport
)
