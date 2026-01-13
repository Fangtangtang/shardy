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

#include "shardy/integrations/c/attributes_mpmd.h"

#include <cstdint>
#include <optional>

#include "mlir-c/IR.h"
#include "mlir-c/Support.h"
#include "mlir/CAPI/IR.h"
#include "mlir/CAPI/Support.h"
#include "mlir/IR/Attributes.h"
#include "mlir/Support/LLVM.h"
#include "shardy/dialect/mpmd/ir/dialect.h"

namespace {

namespace mpmd = ::mlir::mpmd;

template <typename AttrTy>
AttrTy unwrapAttr(MlirAttribute attr) {
  return mlir::cast<AttrTy>(unwrap(attr));
}

template <typename AttrTy>
mlir::ArrayRef<AttrTy> unwrapAttrs(const MlirAttribute* attrs,
                                   intptr_t nAttrs) {
  return mlir::ArrayRef(reinterpret_cast<const AttrTy*>(attrs), nAttrs);
}

}  // namespace

extern "C" {

//===----------------------------------------------------------------------===//
// NamedMeshAttr
//===----------------------------------------------------------------------===//

bool mpmdAttributeIsANamedMeshAttr(MlirAttribute attr) {
  return mlir::isa<mpmd::NamedMeshAttr>(unwrap(attr));
}

MlirAttribute mpmdNamedMeshAttrGet(MlirContext ctx, MlirStringRef name, MlirAttribute mesh) {
  return wrap(mpmd::NamedMeshAttr::get(unwrap(ctx), unwrap(name), unwrapAttr<mlir::sdy::MeshAttr>(mesh)));
}

MlirStringRef mpmdNamedMeshAttrGetName(MlirAttribute attr) {
  return wrap(unwrapAttr<mpmd::NamedMeshAttr>(attr).getName());
}

MlirAttribute mpmdNamedMeshAttrGetMesh(MlirAttribute attr) {
  mlir::sdy::MeshAttr mesh = unwrapAttr<mpmd::NamedMeshAttr>(attr).getMesh();
  return wrap(mesh);
}

//===----------------------------------------------------------------------===//
// TopologyAttr
//===----------------------------------------------------------------------===//

bool mpmdAttributeIsATopologyAttr(MlirAttribute attr) {
  return mlir::isa<mpmd::TopologyAttr>(unwrap(attr));
}

MlirAttribute mpmdTopologyAttrGet(MlirContext ctx, intptr_t nMeshes, const MlirAttribute* meshes) {
  return wrap(mpmd::TopologyAttr::get(
      unwrap(ctx), unwrapAttrs<mpmd::NamedMeshAttr>(meshes, nMeshes)));
}

int64_t mpmdTopologyAttrGetMeshesSize(MlirAttribute attr) {
  return unwrapAttr<mpmd::TopologyAttr>(attr).getMeshes().size();
}

MlirAttribute mpmdTopologyAttrGetMeshesElem(MlirAttribute attr, int64_t pos) {
  return wrap(unwrapAttr<mpmd::TopologyAttr>(attr).getMeshes()[pos]);
}

//===----------------------------------------------------------------------===//
// UserOriginAttr
//===----------------------------------------------------------------------===//

bool mpmdAttributeIsAUserOriginAttr(MlirAttribute attr) {
  return mlir::isa<mpmd::UserOriginAttr>(unwrap(attr));
}

MlirAttribute mpmdUserOriginAttrGet(MlirContext ctx, MlirAttribute userName, int64_t transposeCount) {
  return wrap(mpmd::UserOriginAttr::get(unwrap(ctx), unwrapAttr<mlir::StringAttr>(userName), transposeCount));
}

MlirStringRef mpmdUserOriginAttrGetUserName(MlirAttribute attr) {
  return wrap(unwrapAttr<mpmd::UserOriginAttr>(attr).getUserName().getValue());
}

int64_t mpmdUserOriginAttrGetTransposeCount(MlirAttribute attr) {
  return unwrapAttr<mpmd::UserOriginAttr>(attr).getTransposeCount();
}

//===----------------------------------------------------------------------===//
// OriginAttr
//===----------------------------------------------------------------------===//

bool mpmdAttributeIsAOriginAttr(MlirAttribute attr) {
  return mlir::isa<mpmd::OriginAttr>(unwrap(attr));
}

MlirAttribute mpmdOriginAttrGet(MlirContext ctx, MlirStringRef originLabel) {
  return wrap(mpmd::OriginAttr::get(unwrap(ctx), unwrap(originLabel)));
}

MlirStringRef mpmdOriginAttrGetOriginLabel(MlirAttribute attr) {
  return wrap(unwrapAttr<mpmd::OriginAttr>(attr).getOriginLabel());
}

}  // extern "C"
