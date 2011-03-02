// RUN: %clang_cc1 -fvisibility-inlines-hidden -emit-llvm -o - %s -O2 -disable-llvm-optzns | FileCheck %s

// The trickery with optimization in the run line is to get IR
// generation to emit available_externally function bodies, but not
// actually inline them (and thus remove the emitted bodies).

struct X0 {
  void __attribute__((visibility("default"))) f1() { }
  void f2() { }
  void f3();
  static void f5() { }
  virtual void f6() { }
};

inline void X0::f3() { }

template<typename T>
struct X1 {
  void __attribute__((visibility("default"))) f1() { }
  void f2() { }
  void f3();
  void f4();
  static void f5() { }
  virtual void f6() { }
};

template<typename T>
inline void X1<T>::f3() { }

template<>
inline void X1<int>::f4() { }

struct __attribute__((visibility("default"))) X2 {
  void f2() { }
};

extern template struct X1<float>;

void use(X0 *x0, X1<int> *x1, X2 *x2, X1<float> *x3) {
  // CHECK: define linkonce_odr void @_ZN2X02f1Ev
  x0->f1();
  // CHECK: define linkonce_odr hidden void @_ZN2X02f2Ev
  x0->f2();
  // CHECK: define linkonce_odr hidden void @_ZN2X02f3Ev
  x0->f3();
  // CHECK: define linkonce_odr hidden void @_ZN2X02f5Ev
  X0::f5();
  // CHECK: define linkonce_odr hidden void @_ZN2X02f6Ev
  x0->X0::f6();
  // CHECK: define linkonce_odr void @_ZN2X1IiE2f1Ev
  x1->f1();
  // CHECK: define linkonce_odr hidden void @_ZN2X1IiE2f2Ev
  x1->f2();
  // CHECK: define linkonce_odr hidden void @_ZN2X1IiE2f3Ev
  x1->f3();
  // CHECK: define linkonce_odr hidden void @_ZN2X1IiE2f4Ev
  x1->f4();
  // CHECK: define linkonce_odr hidden void @_ZN2X1IiE2f5Ev
  X1<int>::f5();
  // CHECK: define linkonce_odr hidden void @_ZN2X1IiE2f6Ev
  x1->X1::f6();
  // CHECK: define linkonce_odr hidden void @_ZN2X22f2Ev
  x2->f2();
  // CHECK: define available_externally void @_ZN2X1IfE2f2Ev
  x3->f2();
}

// rdar://problem/8614470
namespace test1 {
  struct __attribute__((visibility("default"))) A {
    inline void foo();
    ~A();
  };

  void test() {
    A a;
    a.foo();
  }
// CHECK: declare void @_ZN5test11A3fooEv
// CHECK: declare void @_ZN5test11AD1Ev
}