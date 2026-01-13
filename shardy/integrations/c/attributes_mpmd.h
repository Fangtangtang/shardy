/* Copyright 2025 The Shardy Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef SHARDY_INTEGRATIONS_C_ATTRIBUTES_MPMD_H_
#define SHARDY_INTEGRATIONS_C_ATTRIBUTES_MPMD_H_

#include <stdint.h>
#include <sys/types.h>

#include "mlir-c/IR.h"
#include "mlir-c/Support.h"

#ifdef __cplusplus
extern "C" {
#endif

//===----------------------------------------------------------------------===//
// NamedMeshAttr
//===----------------------------------------------------------------------===//

MLIR_CAPI_EXPORTED bool mpmdAttributeIsANamedMeshAttr(MlirAttribute attr);

MLIR_CAPI_EXPORTED MlirAttribute mpmdNamedMeshAttrGet(MlirContext ctx,
                                                    MlirStringRef name,
                                                    MlirAttribute mesh);

MLIR_CAPI_EXPORTED MlirStringRef mpmdNamedMeshAttrGetName(MlirAttribute attr);

MLIR_CAPI_EXPORTED MlirAttribute mpmdNamedMeshAttrGetMesh(MlirAttribute attr);

//===----------------------------------------------------------------------===//
// TopologyAttr
//===----------------------------------------------------------------------===//

MLIR_CAPI_EXPORTED bool mpmdAttributeIsATopologyAttr(MlirAttribute attr);

MLIR_CAPI_EXPORTED MlirAttribute mpmdTopologyAttrGet(MlirContext ctx,
                                                    intptr_t nMeshes,
                                                    const MlirAttribute* meshes);

MLIR_CAPI_EXPORTED int64_t mpmdTopologyAttrGetMeshesSize(MlirAttribute attr);

MLIR_CAPI_EXPORTED MlirAttribute mpmdTopologyAttrGetMeshesElem(MlirAttribute attr,
                                                              int64_t pos);

//===----------------------------------------------------------------------===//
// UserOriginAttr
//===----------------------------------------------------------------------===//

MLIR_CAPI_EXPORTED bool mpmdAttributeIsAUserOriginAttr(MlirAttribute attr);

MLIR_CAPI_EXPORTED MlirAttribute mpmdUserOriginAttrGet(MlirContext ctx, MlirAttribute userName, int64_t transposeCount);

MLIR_CAPI_EXPORTED MlirStringRef mpmdUserOriginAttrGetUserName(MlirAttribute attr);

MLIR_CAPI_EXPORTED int64_t mpmdUserOriginAttrGetTransposeCount(MlirAttribute attr);

//===----------------------------------------------------------------------===//
// OriginAttr
//===----------------------------------------------------------------------===//

MLIR_CAPI_EXPORTED bool mpmdAttributeIsAOriginAttr(MlirAttribute attr);

MLIR_CAPI_EXPORTED MlirAttribute mpmdOriginAttrGet(MlirContext ctx, MlirStringRef originLabel);

MLIR_CAPI_EXPORTED MlirStringRef mpmdOriginAttrGetOriginLabel(MlirAttribute attr);

#ifdef __cplusplus
}
#endif

#endif  // SHARDY_INTEGRATIONS_C_ATTRIBUTES_MPMD_H_
