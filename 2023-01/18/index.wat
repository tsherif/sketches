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
)