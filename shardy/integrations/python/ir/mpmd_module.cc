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

#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "mlir-c/BuiltinAttributes.h"
#include "mlir-c/IR.h"
#include "mlir-c/Support.h"
#include "mlir/Bindings/Python/NanobindAdaptors.h"  // IWYU pragma: keep
#include "nanobind/nanobind.h"
#include "nanobind/stl/optional.h"  // IWYU pragma: keep
#include "nanobind/stl/string.h"    // IWYU pragma: keep
#include "nanobind/stl/variant.h"   // IWYU pragma: keep
#include "nanobind/stl/vector.h"    // IWYU pragma: keep
#include "shardy/integrations/c/attributes_mpmd.h"
#include "shardy/integrations/c/dialect_mpmd.h"

namespace mlir {
namespace mpmd {

namespace {

namespace nb = nanobind;

// Returns a vector containing elements with type T extracted from an attribute
// using the two provided callbacks.
template <typename T>
std::vector<T> propertyVector(
    MlirAttribute attr, llvm::function_ref<intptr_t(MlirAttribute)> sizeFn,
    llvm::function_ref<T(MlirAttribute, intptr_t)> getFn) {
  std::vector<T> result;
  intptr_t size = sizeFn(attr);
  result.reserve(size);
  for (intptr_t i = 0; i < size; ++i) {
    result.push_back(getFn(attr, i));
  }
  return result;
}

nb::str toPyString(MlirStringRef mlirStringRef) {
  return nb::str(mlirStringRef.data, mlirStringRef.length);
}

MlirStringRef toStringRef(const std::string& s) {
  return mlirStringRefCreate(s.c_str(), s.size());
}

NB_MODULE(_mpmd, m) {
  m.doc() = "MPMD main Python extension";

  //
  // Dialects.
  //

  m.def(
      "register_dialect",
      [](MlirContext context, bool load) {
        MlirDialectHandle dialect = mlirGetDialectHandle__mpmd__();
        mlirDialectHandleRegisterDialect(dialect, context);
        if (load) {
          mlirDialectHandleLoadDialect(dialect, context);
        }
      },
      nb::arg("context"), nb::arg("load") = true);

  //
  // Attributes.
  //

  mlir::python::nanobind_adaptors::mlir_attribute_subclass(
      m, "NamedMeshAttr", mpmdAttributeIsANamedMeshAttr)
      .def_classmethod(
          "get",
          [](nb::object cls, const std::string& name,
            MlirAttribute meshAttr, MlirContext ctx) {
            return cls(mpmdNamedMeshAttrGet(ctx, toStringRef(name), meshAttr));
          },
          nb::arg("cls"), nb::arg("name"),
          nb::arg("mesh").none() = nb::none(),
          nb::arg("context").none() = nb::none(),
          "Creates an NamedMeshAttr with the given name and MeshAttr.")
      .def_property_readonly("name",
                             [](MlirAttribute self) {
                               return toPyString(mpmdNamedMeshAttrGetName(self));
                             })
      .def_property_readonly("mesh", [](MlirAttribute self) {
        return mpmdNamedMeshAttrGetMesh(self);
      });

  mlir::python::nanobind_adaptors::mlir_attribute_subclass(
      m, "TopologyAttr", mpmdAttributeIsATopologyAttr)
      .def_classmethod(
          "get",
          [](nb::object cls, const std::vector<MlirAttribute>& meshes,
             MlirContext ctx) {
            return cls(mpmdTopologyAttrGet(ctx, meshes.size(), meshes.data()));
          },
          nb::arg("cls"), nb::arg("meshes"),
          nb::arg("context").none() = nb::none(),
          "Creates a TopologyAttr with the given meshes.")
      .def_property_readonly("meshes",
                             [](MlirAttribute self) {
                               return propertyVector<MlirAttribute>(
                                   self, mpmdTopologyAttrGetMeshesSize,
                                   mpmdTopologyAttrGetMeshesElem);
                             })
      .def_property_readonly("size", [](MlirAttribute self) {
        return mpmdTopologyAttrGetMeshesSize(self);
      });

  mlir::python::nanobind_adaptors::mlir_attribute_subclass(
      m, "UserOriginAttr", mpmdAttributeIsAUserOriginAttr)
      .def_classmethod(
          "get",
          [](nb::object cls, MlirAttribute& userName, int64_t transposeCount,
             MlirContext ctx) {
            return cls(mpmdUserOriginAttrGet(ctx, userName, transposeCount));
          },
          nb::arg("cls"), nb::arg("user_name"),
          nb::arg("transpose_count") = 0,
          nb::arg("context").none() = nb::none(),
          "Creates a UserOriginAttr with the given user name and transpose count.")
      .def_property_readonly("user_name",
                             [](MlirAttribute self) {
                               return toPyString(mpmdUserOriginAttrGetUserName(self));
                             })
      .def_property_readonly("transpose_count", [](MlirAttribute self) {
        return mpmdUserOriginAttrGetTransposeCount(self);
      });

  mlir::python::nanobind_adaptors::mlir_attribute_subclass(
      m, "OriginAttr", mpmdAttributeIsAOriginAttr)
      .def_classmethod(
          "get",
          [](nb::object cls, const std::string& originLabel, MlirContext ctx) {
            return cls(mpmdOriginAttrGet(ctx, toStringRef(originLabel)));
          },
          nb::arg("cls"), nb::arg("origin_label"),
          nb::arg("context").none() = nb::none(),
          "Creates an OriginAttr with the given origin label.")
      .def_property_readonly("origin_label",
                             [](MlirAttribute self) {
                               return toPyString(mpmdOriginAttrGetOriginLabel(self));
                             });
}

}  // namespace
}  // namespace mpmd
}  // namespace mlir
