/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef builtin_SIMD_h
#define builtin_SIMD_h

#include "jsapi.h"
#include "jsobj.h"

#include "builtin/TypedObject.h"
#include "js/Conversions.h"
#include "vm/GlobalObject.h"

/*
 * JS SIMD functions.
 * Spec matching polyfill:
 * https://github.com/johnmccutchan/ecmascript_simd/blob/master/src/ecmascript_simd.js
 */

#define FLOAT32X4_UNARY_FUNCTION_LIST(V)                                            \
  V(abs, (UnaryFunc<Float32x4, Abs, Float32x4>), 1, 0)                              \
  V(fromInt32x4, (FuncConvert<Int32x4, Float32x4> ), 1, 0)                          \
  V(fromInt32x4Bits, (FuncConvertBits<Int32x4, Float32x4>), 1, 0)                   \
  V(neg, (UnaryFunc<Float32x4, Neg, Float32x4>), 1, 0)                              \
  V(not, (CoercedUnaryFunc<Float32x4, Int32x4, Not, Float32x4>), 1, 0)              \
  V(reciprocal, (UnaryFunc<Float32x4, Rec, Float32x4>), 1, 0)                       \
  V(reciprocalSqrt, (UnaryFunc<Float32x4, RecSqrt, Float32x4>), 1, 0)               \
  V(splat, (FuncSplat<Float32x4>), 1, 0)                                            \
  V(sqrt, (UnaryFunc<Float32x4, Sqrt, Float32x4>), 1, 0)

#define FLOAT32X4_BINARY_FUNCTION_LIST(V)                                           \
  V(add, (BinaryFunc<Float32x4, Add, Float32x4>), 2, 0)                             \
  V(and, (CoercedBinaryFunc<Float32x4, Int32x4, And, Float32x4>), 2, 0)             \
  V(div, (BinaryFunc<Float32x4, Div, Float32x4>), 2, 0)                             \
  V(equal, (CompareFunc<Float32x4, Equal>), 2, 0)                                   \
  V(greaterThan, (CompareFunc<Float32x4, GreaterThan>), 2, 0)                       \
  V(greaterThanOrEqual, (CompareFunc<Float32x4, GreaterThanOrEqual>), 2, 0)         \
  V(lessThan, (CompareFunc<Float32x4, LessThan>), 2, 0)                             \
  V(lessThanOrEqual, (CompareFunc<Float32x4, LessThanOrEqual>), 2, 0)               \
  V(load,    (Load<Float32x4, 4>), 2, 0)                                            \
  V(loadXYZ, (Load<Float32x4, 3>), 2, 0)                                            \
  V(loadXY,  (Load<Float32x4, 2>), 2, 0)                                            \
  V(loadX,   (Load<Float32x4, 1>), 2, 0)                                            \
  V(max, (BinaryFunc<Float32x4, Maximum, Float32x4>), 2, 0)                         \
  V(maxNum, (BinaryFunc<Float32x4, MaxNum, Float32x4>), 2, 0)                       \
  V(min, (BinaryFunc<Float32x4, Minimum, Float32x4>), 2, 0)                         \
  V(minNum, (BinaryFunc<Float32x4, MinNum, Float32x4>), 2, 0)                       \
  V(mul, (BinaryFunc<Float32x4, Mul, Float32x4>), 2, 0)                             \
  V(notEqual, (CompareFunc<Float32x4, NotEqual>), 2, 0)                             \
  V(or, (CoercedBinaryFunc<Float32x4, Int32x4, Or, Float32x4>), 2, 0)               \
  V(store,    (Store<Float32x4, 4>), 3, 0)                                          \
  V(storeXYZ, (Store<Float32x4, 3>), 3, 0)                                          \
  V(storeXY,  (Store<Float32x4, 2>), 3, 0)                                          \
  V(storeX,   (Store<Float32x4, 1>), 3, 0)                                          \
  V(sub, (BinaryFunc<Float32x4, Sub, Float32x4>), 2, 0)                             \
  V(withX, (FuncWith<Float32x4, WithX>), 2, 0)                                      \
  V(withY, (FuncWith<Float32x4, WithY>), 2, 0)                                      \
  V(withZ, (FuncWith<Float32x4, WithZ>), 2, 0)                                      \
  V(withW, (FuncWith<Float32x4, WithW>), 2, 0)                                      \
  V(xor, (CoercedBinaryFunc<Float32x4, Int32x4, Xor, Float32x4>), 2, 0)

#define FLOAT32X4_TERNARY_FUNCTION_LIST(V)                                          \
  V(bitselect, BitSelect<Float32x4>, 3, 0)                                          \
  V(clamp, Float32x4Clamp, 3, 0)                                                    \
  V(select, Select<Float32x4>, 3, 0)

#define FLOAT32X4_SHUFFLE_FUNCTION_LIST(V)                                          \
  V(swizzle, Swizzle<Float32x4>, 2, 0)                                              \
  V(shuffle, Shuffle<Float32x4>, 3, 0)

#define FLOAT32X4_FUNCTION_LIST(V)                                                  \
  FLOAT32X4_UNARY_FUNCTION_LIST(V)                                                  \
  FLOAT32X4_BINARY_FUNCTION_LIST(V)                                                 \
  FLOAT32X4_TERNARY_FUNCTION_LIST(V)                                                \
  FLOAT32X4_SHUFFLE_FUNCTION_LIST(V)

#define INT32X4_UNARY_FUNCTION_LIST(V)                                              \
  V(fromFloat32x4, (FuncConvert<Float32x4, Int32x4>), 1, 0)                         \
  V(fromFloat32x4Bits, (FuncConvertBits<Float32x4, Int32x4>), 1, 0)                 \
  V(neg, (UnaryFunc<Int32x4, Neg, Int32x4>), 1, 0)                                  \
  V(not, (UnaryFunc<Int32x4, Not, Int32x4>), 1, 0)                                  \
  V(splat, (FuncSplat<Int32x4>), 0, 0)

#define INT32X4_BINARY_FUNCTION_LIST(V)                                             \
  V(add, (BinaryFunc<Int32x4, Add, Int32x4>), 2, 0)                                 \
  V(and, (BinaryFunc<Int32x4, And, Int32x4>), 2, 0)                                 \
  V(equal, (CompareFunc<Int32x4, Equal>), 2, 0)                                     \
  V(greaterThan, (CompareFunc<Int32x4, GreaterThan>), 2, 0)                         \
  V(greaterThanOrEqual, (CompareFunc<Int32x4, GreaterThanOrEqual>), 2, 0)           \
  V(lessThan, (CompareFunc<Int32x4, LessThan>), 2, 0)                               \
  V(lessThanOrEqual, (CompareFunc<Int32x4, LessThanOrEqual>), 2, 0)                 \
  V(load,    (Load<Int32x4, 4>), 2, 0)                                              \
  V(loadXYZ, (Load<Int32x4, 3>), 2, 0)                                              \
  V(loadXY,  (Load<Int32x4, 2>), 2, 0)                                              \
  V(loadX,   (Load<Int32x4, 1>), 2, 0)                                              \
  V(mul, (BinaryFunc<Int32x4, Mul, Int32x4>), 2, 0)                                 \
  V(notEqual, (CompareFunc<Int32x4, NotEqual>), 2, 0)                               \
  V(or, (BinaryFunc<Int32x4, Or, Int32x4>), 2, 0)                                   \
  V(sub, (BinaryFunc<Int32x4, Sub, Int32x4>), 2, 0)                                 \
  V(shiftLeftByScalar, (Int32x4BinaryScalar<ShiftLeft>), 2, 0)                      \
  V(shiftRightArithmeticByScalar, (Int32x4BinaryScalar<ShiftRight>), 2, 0)          \
  V(shiftRightLogicalByScalar, (Int32x4BinaryScalar<ShiftRightLogical>), 2, 0)      \
  V(store,    (Store<Int32x4, 4>), 3, 0)                                            \
  V(storeXYZ, (Store<Int32x4, 3>), 3, 0)                                            \
  V(storeXY,  (Store<Int32x4, 2>), 3, 0)                                            \
  V(storeX,   (Store<Int32x4, 1>), 3, 0)                                            \
  V(withX, (FuncWith<Int32x4, WithX>), 2, 0)                                        \
  V(withY, (FuncWith<Int32x4, WithY>), 2, 0)                                        \
  V(withZ, (FuncWith<Int32x4, WithZ>), 2, 0)                                        \
  V(withW, (FuncWith<Int32x4, WithW>), 2, 0)                                        \
  V(xor, (BinaryFunc<Int32x4, Xor, Int32x4>), 2, 0)

#define INT32X4_TERNARY_FUNCTION_LIST(V)                                            \
  V(bitselect, BitSelect<Int32x4>, 3, 0)                                            \
  V(select, Select<Int32x4>, 3, 0)

#define INT32X4_QUARTERNARY_FUNCTION_LIST(V)                                        \
  V(bool, Int32x4Bool, 4, 0)

#define INT32X4_SHUFFLE_FUNCTION_LIST(V)                                            \
  V(swizzle, Swizzle<Int32x4>, 2, 0)                                                \
  V(shuffle, Shuffle<Int32x4>, 3, 0)

#define INT32X4_FUNCTION_LIST(V)                                                    \
  INT32X4_UNARY_FUNCTION_LIST(V)                                                    \
  INT32X4_BINARY_FUNCTION_LIST(V)                                                   \
  INT32X4_TERNARY_FUNCTION_LIST(V)                                                  \
  INT32X4_QUARTERNARY_FUNCTION_LIST(V)                                              \
  INT32X4_SHUFFLE_FUNCTION_LIST(V)

#define FOREACH_INT32X4_SIMD_OP(_)   \
    _(fromFloat32x4)                 \
    _(fromFloat32x4Bits)             \
    _(shiftLeftByScalar)             \
    _(shiftRightArithmeticByScalar)  \
    _(shiftRightLogicalByScalar)
#define FOREACH_FLOAT32X4_SIMD_OP(_) \
    _(abs)                           \
    _(sqrt)                          \
    _(reciprocal)                    \
    _(reciprocalSqrt)                \
    _(fromInt32x4)                   \
    _(fromInt32x4Bits)               \
    _(div)                           \
    _(max)                           \
    _(min)                           \
    _(maxNum)                        \
    _(minNum)
#define FOREACH_COMMONX4_SIMD_OP(_)  \
    _(add)                           \
    _(sub)                           \
    _(mul)                           \
    _(lessThan)                      \
    _(lessThanOrEqual)               \
    _(equal)                         \
    _(notEqual)                      \
    _(greaterThan)                   \
    _(greaterThanOrEqual)            \
    _(and)                           \
    _(or)                            \
    _(xor)                           \
    _(bitselect)                     \
    _(select)                        \
    _(swizzle)                       \
    _(shuffle)                       \
    _(splat)                         \
    _(withX)                         \
    _(withY)                         \
    _(withZ)                         \
    _(withW)                         \
    _(not)                           \
    _(neg)                           \
    _(load)                          \
    _(store)
#define FORALL_SIMD_OP(_)            \
    FOREACH_INT32X4_SIMD_OP(_)       \
    FOREACH_FLOAT32X4_SIMD_OP(_)     \
    FOREACH_COMMONX4_SIMD_OP(_)

namespace js {

class SIMDObject : public JSObject
{
  public:
    static const Class class_;
    static JSObject* initClass(JSContext* cx, Handle<GlobalObject*> global);
    static bool toString(JSContext* cx, unsigned int argc, jsval* vp);
};

// These classes exist for use with templates below.

struct Float32x4 {
    typedef float Elem;
    static const unsigned lanes = 4;
    static const SimdTypeDescr::Type type = SimdTypeDescr::TYPE_FLOAT32;

    static TypeDescr& GetTypeDescr(GlobalObject& global) {
        return global.float32x4TypeDescr().as<TypeDescr>();
    }
    static Elem toType(Elem a) {
        return a;
    }
    static bool toType(JSContext* cx, JS::HandleValue v, Elem* out) {
        *out = v.toNumber();
        return true;
    }
    static void setReturn(CallArgs& args, Elem value) {
        args.rval().setDouble(JS::CanonicalizeNaN(value));
    }
};

struct Int32x4 {
    typedef int32_t Elem;
    static const unsigned lanes = 4;
    static const SimdTypeDescr::Type type = SimdTypeDescr::TYPE_INT32;

    static TypeDescr& GetTypeDescr(GlobalObject& global) {
        return global.int32x4TypeDescr().as<TypeDescr>();
    }
    static Elem toType(Elem a) {
        return JS::ToInt32(a);
    }
    static bool toType(JSContext* cx, JS::HandleValue v, Elem* out) {
        return ToInt32(cx, v, out);
    }
    static void setReturn(CallArgs& args, Elem value) {
        args.rval().setInt32(value);
    }
};

template<typename V>
JSObject* CreateSimd(JSContext* cx, typename V::Elem* data);

template<typename V>
bool IsVectorObject(HandleValue v);

template<typename V>
bool ToSimdConstant(JSContext* cx, HandleValue v, jit::SimdConstant* out);

#define DECLARE_SIMD_FLOAT32X4_FUNCTION(Name, Func, Operands, Flags) \
extern bool                                                          \
simd_float32x4_##Name(JSContext* cx, unsigned argc, Value* vp);
FLOAT32X4_FUNCTION_LIST(DECLARE_SIMD_FLOAT32X4_FUNCTION)
#undef DECLARE_SIMD_FLOAT32X4_FUNCTION

#define DECLARE_SIMD_INT32x4_FUNCTION(Name, Func, Operands, Flags)   \
extern bool                                                          \
simd_int32x4_##Name(JSContext* cx, unsigned argc, Value* vp);
INT32X4_FUNCTION_LIST(DECLARE_SIMD_INT32x4_FUNCTION)
#undef DECLARE_SIMD_INT32x4_FUNCTION

}  /* namespace js */

JSObject*
js_InitSIMDClass(JSContext* cx, js::HandleObject obj);

#endif /* builtin_SIMD_h */
