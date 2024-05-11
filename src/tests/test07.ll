declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
define i32 @main( ) {
bb2:
  %r100 = alloca i32
  %r101 = alloca i32
  %r102 = alloca i32
  %r109 = alloca i32
  br label %bb1

bb1:
  call void @_sysy_starttime(i32 2)
  store i32 0, i32* %r100
  %r103 = icmp slt i32 1, 9
  br i1 %r103, label %bb27_4checksecond, label %bb16_4false

bb27_4checksecond:
  %r104 = load i32, i32* %r100
  %r105 = icmp sgt i32 %r104, 0
  br i1 %r105, label %bb16_4true, label %bb16_4false

bb16_4true:
  store i32 1, i32* %r102
  br label %bb16_4end

bb16_4false:
  store i32 0, i32* %r102
  br label %bb16_4end

bb16_4end:
  %r106 = load i32, i32* %r102
  store i32 %r106, i32* %r101
  br label %bb_while_4_5_cond

bb_while_4_5_cond:
  %r107 = load i32, i32* %r100
  %r108 = icmp slt i32 %r107, 1000000
  br i1 %r108, label %bb_while_4_5_whilestms, label %bb_while_4_5_bre

bb_while_4_5_whilestms:
  store i32 0, i32* %r109
  %r110 = load i32, i32* %r100
  %r111 = add i32 %r110, 1
  store i32 %r111, i32* %r100
  br label %bb_while_4_5_cond

bb_while_4_5_bre:
  %r112 = load i32, i32* %r101
  call void @putint(i32 %r112)
  call void @_sysy_stoptime(i32 10)
  ret i32 0
}

