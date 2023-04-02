; function "__init" with 0 parameters and 0 local vars
__init:
    floadc 0               ; 3.5
    fstoreg 0              ; y = 3.5;
    bloadc 1               ; true
    bstoreg 1              ; b = true;
    iloadc 2               ; 10
    istoreg 2              ; z = 10;
    return                 ; return;

; imported fun "printInt" at index 0
; imported fun "printFloat" at index 1
; imported fun "scanInt" at index 2
; imported fun "scanFloat" at index 3
; imported fun "printSpaces" at index 4
; imported fun "printNewlines" at index 5
; exported var "y" at index 0
; global var "b" at index 1
; function "main" with 1 parameters and 0 local vars
main:
                           ; parameter "x" at index 0
    isrg                   ; printFloat
    floadg 0               ; y
    jsre 1                 ; printFloat(y)
    isrg                   ; printNewlines
    iloadc 3               ; 1
    jsre 5                 ; printNewlines(1)
    isrg                   ; printInt
    iloadg 2               ; z
    jsre 0                 ; printInt(z)
    iloadc 4               ; 0
    ireturn                ; return 0;

; global var "z" at index 2
; function "foo" with 0 parameters and 0 local vars
foo:
    return                 ; return;

.const float 3.5           ; index 0
.const bool true           ; index 1
.const int 10              ; index 2
.const int 1               ; index 3
.const int 0               ; index 4
.exportfun "__init" void __init
.exportvar "y" 0
.exportfun "main" int int main
.global float
.global bool
.global int
.importfun "printInt" void int
.importfun "printFloat" void float
.importfun "scanInt" int
.importfun "scanFloat" float
.importfun "printSpaces" void int
.importfun "printNewlines" void int
