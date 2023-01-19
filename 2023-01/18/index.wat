(module
    (func (export "add") (param $x i32) (param $y i32) (result i32)
        local.get $x
        local.get $y
        i32.add
    )
    (func (export "abs") (param $x i32) (result i32)
        local.get $x
        i32.const 0
        i32.lt_s

        if
            local.get $x
            i32.const -1
            i32.mul
            return
        end

        local.get $x
    )

    (func (export "fact") (param $x i32) (result i32)
        (local $result i32)
        i32.const 1
        local.set $result

        loop $loop
            local.get $result
            local.get $x
            i32.mul
            local.set $result

            local.get $x
            i32.const 1
            i32.sub
            local.tee $x

            i32.const 0
            i32.gt_s
            br_if $loop
        end

        local.get $result
    )

    (func (export "fib") (param $n i32) (result i32)
        (local $prev i32)
        (local $curr i32)
        (local $i i32)
        i32.const 1
        local.tee $prev
        local.set $curr
        i32.const 1
        local.set $i

        block $break
        loop $loop
            local.get $i
            local.get $n
            i32.ge_s

            br_if $break

            local.get $prev
            local.get $curr
            i32.add
            local.get $curr
            local.set $prev
            local.set $curr
            
            local.get $i
            i32.const 1
            i32.add
            local.set $i

            br $loop
        end
        end

        local.get $curr
    )
)