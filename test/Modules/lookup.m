
// lookup_left.h: expected-note{{using}}
// lookup_right.h: expected-note{{also found}}
@import lookup_left_objc;
@import lookup_right_objc;

void test(id x) {
  [x method]; // expected-warning{{multiple methods named 'method' found}}
}

// RUN: rm -rf %t
// RUN: %clang_cc1 -fmodules -fmodules-cache-path=%t -emit-module -x objective-c -fmodule-name=lookup_left_objc %S/Inputs/module.map
// RUN: %clang_cc1 -fmodules -fmodules-cache-path=%t -emit-module -x objective-c -fmodule-name=lookup_right_objc %S/Inputs/module.map
// RUN: %clang_cc1 -fmodules -x objective-c -fmodules-cache-path=%t -verify %s
// RUN: %clang_cc1 -fmodules -ast-print -x objective-c -fmodules-cache-path=%t %s | FileCheck -check-prefix=CHECK-PRINT %s

// CHECK-PRINT: - (int) method;
// CHECK-PRINT: - (double) method
// CHECK-PRINT: void test(id x)

