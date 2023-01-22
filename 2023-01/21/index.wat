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

    (func (export "simdAddVec4args") 
        (param $x1 f32)
        (param $y1 f32)
        (param $z1 f32)
        (param $w1 f32)
        (param $x2 f32)
        (param $y2 f32)
        (param $z2 f32)
        (param $w2 f32)
        
        i32.const 0 ;; location for store at the end

        f32.const 0
        f32x4.splat
    
        local.get $x1
        f32x4.replace_lane 0

        local.get $y1
        f32x4.replace_lane 1

        local.get $z1
        f32x4.replace_lane 2

        local.get $w1
        f32x4.replace_lane 3

        f32.const 0
        f32x4.splat
    
        local.get $x2
        f32x4.replace_lane 0

        local.get $y2
        f32x4.replace_lane 1

        local.get $z2
        f32x4.replace_lane 2

        local.get $w2
        f32x4.replace_lane 3

        f32x4.add  

        v128.store
    )
)