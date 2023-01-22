(module
    (import "env" "memory" (memory 1))
    (global $vOffset (import "env" "velocityByteOffset") i32)
    (global $rOffset (import "env" "radiusByteOffset") i32)
    (func (export "simulate") (param $numBalls i32) (param $width f32) (param $height f32)
        (local $i i32)
        (local $pi i32)
        (local $vi i32)
        (local $ri i32)
        (local $p v128)
        (local $v v128)

        i32.const 0
        local.set $i

        block $break
        loop $loop
            local.get $i
            local.get $numBalls
            i32.ge_u
            br_if $break

            local.get $i
            i32.const 8 ;; 2 elements * 4 bytes
            i32.mul
            local.tee $pi

            v128.load
            local.set $p 

            local.get $pi
            global.get $vOffset
            i32.add
            local.tee $vi

            v128.load
            local.set $v

            local.get $p
            local.get $v
            f32x4.add
            local.set $p

            local.get $pi
            local.get $p
            v128.store

            ;; update i and loop
            local.get $i
            i32.const 2
            i32.add
            local.set $i
            br $loop
        end
        end
    ) 
)