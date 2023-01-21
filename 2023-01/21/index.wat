(module
    (import "env" "memory" (memory 1))
    (func (export "simdAddVec4")
        i32.const 32

        i32.const 0
        v128.load

        i32.const 16
        v128.load
        f32x4.add  

        v128.store
    ) 
)