(module
    (import "env" "printString" (func $printString (param i32)))
    (import "env" "buffer" (memory 1))
    (global $startIndex (import "env" "startIndex") i32)
    (global $stringLen i32 (i32.const 13))
    (data (global.get $startIndex) "Hello, World!")
    (func (export "helloWorld")
        (call $printString (global.get $stringLen))
    )
)