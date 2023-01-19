(module
    (import "env" "memory" (memory 1))
    (func (export "simulate") (param $numBalls i32) (param $width i32) (param $height i32)
        (local $i i32)
        (local $bi i32)
        (local $x f32)
        (local $y f32)
        (local $r f32)
        (local $vx f32)
        (local $vy f32)

        i32.const 0
        local.set $i

        block $break
        loop $loop
            local.get $i
            local.get $numBalls
            i32.ge_u
            br_if $break

            local.get $i
            i32.const 20 ;; 5 elements * 4 bytes
            i32.mul
            local.set $bi

            local.get $i
            i32.const 1
            i32.add
            local.set $i
            br $loop
        end
        end
    ) 
)