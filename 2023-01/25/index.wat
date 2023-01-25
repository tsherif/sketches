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
        (local $r v128)
        (local $dim v128)
        (local $dimBound v128)
        (local $lowerBound v128)
        (local $upperBound v128)

        i32.const 0
        local.set $i

        ;; create a vec4 for canvas boundary check
        f32.const 0
        f32x4.splat

        local.get $width
        f32x4.replace_lane 0

        local.get $height
        f32x4.replace_lane 1

        local.get $width
        f32x4.replace_lane 2

        local.get $height
        f32x4.replace_lane 3

        local.set $dim

        block $break
        loop $loop
            ;; check index
            local.get $i
            local.get $numBalls
            i32.ge_u
            br_if $break

            local.get $i
            i32.const 8 ;; 2 elements * 4 bytes
            i32.mul
            local.tee $pi

            ;; load position for 2 balls
            v128.load
            local.set $p 

            ;; load velocity for 2 balls
            local.get $pi
            global.get $vOffset
            i32.add
            local.tee $vi

            v128.load
            local.set $v

            ;; load radius for 2 balls (r is repeated to simplify simd ops)
            local.get $pi
            global.get $rOffset
            i32.add
            local.tee $ri

            v128.load
            local.set $r

            ;; p += v
            local.get $p
            local.get $v
            f32x4.add
            local.set $p

            ;; p < r
            local.get $p
            local.get $r
            f32x4.lt
            local.set $lowerBound ;; lowerBounds lanes will be all 1s for true, all 0s for false

            ;; p > dim - r
            local.get $p
            local.get $dim
            local.get $r
            f32x4.sub
            local.tee $dimBound ;; save for clamping later
            f32x4.gt
            local.set $upperBound ;; upperBound lanes will be all 1s for true, all 0s for false

            ;; p < r || p > dim -r
            local.get $lowerBound
            local.get $upperBound
            v128.or

            (;
                After the last operation, lanes in which the position is 
                out of bounds will contain 0xFFFFFFFF for positions 
                that are out of bounds, then next few steps:
                1. Keeps the highest order bit for the lanes that are out
                    of bounds.
                2. Uses these values to toggle the sign bits in the 
                    velocities.
            ;)

            ;; set highest order bit for lanes that are out of bounds
            i32.const 0x80000000
            i32x4.splat
            v128.and

            ;; toggle sign bit in v if out of bounds
            local.get $v
            v128.xor
            local.set $v

            ;; clamp p to canvas bounds
            local.get $p
            local.get $r
            f32x4.max
            local.get $dimBound
            f32x4.min
            local.set $p
            
            ;; save updated values
            local.get $pi
            local.get $p
            v128.store

            local.get $vi
            local.get $v
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