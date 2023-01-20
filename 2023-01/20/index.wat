(module
    (import "env" "memory" (memory 1))
    (func (export "simulate") (param $numBalls i32) (param $width f32) (param $height f32)
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
            local.tee $bi

            ;; load object
            f32.load
            local.set $x

            local.get $bi
            i32.const 4
            i32.add
            f32.load
            local.set $y

            local.get $bi
            i32.const 8
            i32.add
            f32.load
            local.set $r

            local.get $bi
            i32.const 12
            i32.add
            f32.load
            local.set $vx

            local.get $bi
            i32.const 16
            i32.add
            f32.load
            local.set $vy

            ;; update x
            local.get $x
            local.get $vx
            f32.add
            local.tee $x

            ;; if x < r
            local.get $r
            f32.lt

            if
                local.get $r
                local.set $x
                local.get $vx
                f32.const -1
                f32.mul
                local.set $vx
            end

            ;; if x + r > width
            local.get $x
            local.get $r
            f32.add
            local.get $width
            f32.gt
            
            if 
                local.get $width
                local.get $r
                f32.sub
                local.set $x

                local.get $vx
                f32.const -1
                f32.mul
                local.set $vx
            end

            ;; update y
            local.get $y
            local.get $vy
            f32.add
            local.tee $y

            ;; if y < r
            local.get $r
            f32.lt

            if
                local.get $r
                local.set $y
                local.get $vy
                f32.const -1
                f32.mul
                local.set $vy
            end

            ;; if y + r > height
            local.get $y
            local.get $r
            f32.add
            local.get $height
            f32.gt
            
            if 
                local.get $height
                local.get $r
                f32.sub
                local.set $y

                local.get $vy
                f32.const -1
                f32.mul
                local.set $vy
            end

            ;; store results
            local.get $bi
            local.get $x
            f32.store

            local.get $bi
            i32.const 4
            i32.add
            local.get $y
            f32.store

            local.get $bi
            i32.const 12
            i32.add
            local.get $vx
            f32.store

            local.get $bi
            i32.const 16
            i32.add
            local.get $vy
            f32.store

            ;; update i and loop
            local.get $i
            i32.const 1
            i32.add
            local.set $i
            br $loop
        end
        end
    ) 
)