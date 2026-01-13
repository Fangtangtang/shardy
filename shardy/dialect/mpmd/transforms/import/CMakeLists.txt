# Shardy MLIR MPMD Transforms Import Passes and Pipeline

set(LLVM_TARGET_DEFINITIONS passes.td)
mlir_tablegen(passes.h.inc -gen-pass-decls -name=MpmdImport)
add_public_tablegen_target(MpmdTransformsImportPassesIncGen)
add_dependencies(mlir-headers MpmdTransformsImportPassesIncGen)

add_mlir_library(MpmdTransformsImportMeshAssignmentMap
  mesh_assignment_map.cc

  LINK_LIBS PUBLIC
  LLVMSupport
)

add_mlir_library(MpmdTransformsImportMeshInferenceOrigins
  mesh_inference_origins.cc

  DEPENDS
  MpmdDialect

  LINK_LIBS PUBLIC
  MpmdDialect
  LLVMSupport
  MLIRIR
  MLIRPass
  MLIRSupport
)

add_mlir_library(MpmdTransformsImportMeshesWithOrigins
  meshes_with_origins.cc

  DEPENDS
  MpmdDialect
  MpmdTransformsImportMeshInferenceOrigins

  LINK_LIBS PUBLIC
  MpmdDialect
  MpmdTransformsImportMeshInferenceOrigins
  LLVMSupport
  MLIRIR
  MLIRSupport
)


add_mlir_library(MpmdTransformsImportMeshInferenceUtils
  mesh_inference_utils.cc

  DEPENDS
  MpmdTransformsImportMeshesWithOrigins
  MpmdDialect
  MpmdTransformsCommonUtils
  SdyDialect

  LINK_LIBS PUBLIC
  MpmdTransformsImportMeshesWithOrigins
  MpmdDialect
  MpmdTransformsCommonUtils
  SdyDialect
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRSupport
)

add_mlir_library(MpmdTransformsImportShardingConstraints
  sharding_constraints.cc

  LINK_LIBS PUBLIC
  LLVMSupport
)

add_mlir_library(MpmdTransformsImportPasses
  copy_topology_from_main.cc
  enforce_equisharding.cc
  import_pipeline.cc
  infer_mesh_assignment.cc
  infer_mesh_validation.cc
  insert_nameless_clones_of_negligible_ops.cc
  introduce_transfers.cc
  map_input_output_to_mesh.cc
  map_named_ops_to_mpmd_ops.cc
  simplify_named_computations.cc
  validate_named_ops_in_mpmd_func.cc
  generate_sdy_meshes_from_topology_pass.cc

  DEPENDS
  MpmdTransformsImportMeshAssignmentMap
  MpmdTransformsImportMeshInferenceOrigins
  MpmdTransformsImportMeshInferenceUtils
  MpmdTransformsImportMeshesWithOrigins
  MpmdTransformsImportPassesIncGen
  MpmdTransformsImportShardingConstraints
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  MpmdTransformsCommonSimplifyRegionOpBase
  SdyDialect

  LINK_LIBS PUBLIC
  MpmdTransformsImportMeshAssignmentMap
  MpmdTransformsImportMeshInferenceOrigins
  MpmdTransformsImportMeshInferenceUtils
  MpmdTransformsImportMeshesWithOrigins
  MpmdTransformsImportShardingConstraints
  MpmdDialect
  MpmdTransformsCommonDistributedFunctionPass
  MpmdTransformsCommonPasses
  MpmdTransformsCommonUtils
  MpmdTransformsCommonSimplifyRegionOpBase
  SdyDialect
  LLVMSupport
  MLIRFuncDialect
  MLIRIR
  MLIRPass
  MLIRRewrite
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransforms
  MLIRTransformUtils
  StablehloOps
  StablehloPasses
  StablehloOptimizationPasses
)