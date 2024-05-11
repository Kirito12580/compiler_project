declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@ascii_0 = global i32 48
define i32 @my_getint( ) {
bb5:
  %r100 = alloca i32
  %r101 = alloca i32
  br label %bb1

bb1:
  store i32 0, i32* %r100
  br label %bb_while_4_7_cond

bb_while_4_7_cond:
  %r102 = icmp sgt i32 1, 0
  br i1 %r102, label %bb_while_4_7_whilestms, label %bb_while_4_7_bre

bb_while_4_7_whilestms:
  %r103 = call i32 @getch()
  %r104 = load i32, i32* @ascii_0
  %r105 = sub i32 %r103, %r104
  store i32 %r105, i32* %r101
  %r106 = load i32, i32* %r101
  %r107 = icmp slt i32 %r106, 0
  br i1 %r107, label %bb_if_8_9_true, label %bb21_9checksecond

bb21_9checksecond:
  %r108 = load i32, i32* %r101
  %r109 = icmp sgt i32 %r108, 9
  br i1 %r109, label %bb_if_8_9_true, label %bb_if_8_9_false

bb_if_8_9_true:
  br label %bb_while_4_7_cond

bb_if_8_9_false:
  br label %bb_while_4_7_bre

bb_if_8_9_end:
  br label %bb_while_4_7_cond

bb_while_4_7_bre:
  %r110 = load i32, i32* %r101
  store i32 %r110, i32* %r100
  br label %bb_while_4_17_cond

bb_while_4_17_cond:
  %r111 = icmp sgt i32 1, 0
  br i1 %r111, label %bb_while_4_17_whilestms, label %bb_while_4_17_bre

bb_while_4_17_whilestms:
  %r112 = call i32 @getch()
  %r113 = load i32, i32* @ascii_0
  %r114 = sub i32 %r112, %r113
  store i32 %r114, i32* %r101
  %r115 = load i32, i32* %r101
  %r116 = icmp sge i32 %r115, 0
  br i1 %r116, label %bb22_19checksecond, label %bb_if_8_19_false

bb22_19checksecond:
  %r117 = load i32, i32* %r101
  %r118 = icmp sle i32 %r117, 9
  br i1 %r118, label %bb_if_8_19_true, label %bb_if_8_19_false

bb_if_8_19_true:
  %r119 = load i32, i32* %r100
  %r120 = mul i32 %r119, 10
  %r121 = load i32, i32* %r101
  %r122 = add i32 %r120, %r121
  store i32 %r122, i32* %r100
  br label %bb_if_8_19_end

bb_if_8_19_false:
  br label %bb_while_4_17_bre

bb_if_8_19_end:
  br label %bb_while_4_17_cond

bb_while_4_17_bre:
  %r123 = load i32, i32* %r100
  ret i32 %r123
}

define i32 @mod( i32 %r124, i32 %r126 ) {
bb6:
  %r125 = alloca i32
  %r127 = alloca i32
  br label %bb2

bb2:
  store i32 %r124, i32* %r125
  store i32 %r126, i32* %r127
  %r128 = load i32, i32* %r125
  %r129 = load i32, i32* %r125
  %r130 = load i32, i32* %r127
  %r131 = sdiv i32 %r129, %r130
  %r132 = load i32, i32* %r127
  %r133 = mul i32 %r131, %r132
  %r134 = sub i32 %r128, %r133
  ret i32 %r134
}

define void @my_putint( i32 %r135 ) {
bb7:
  %r136 = alloca i32
  %r137 = alloca [ 16 x i32 ]
  %r138 = alloca i32
  br label %bb3

bb3:
  store i32 %r135, i32* %r136
  store i32 0, i32* %r138
  br label %bb_while_4_38_cond

bb_while_4_38_cond:
  %r139 = load i32, i32* %r136
  %r140 = icmp sgt i32 %r139, 0
  br i1 %r140, label %bb_while_4_38_whilestms, label %bb_while_4_38_bre

bb_while_4_38_whilestms:
  %r141 = load i32, i32* %r138
  %r142 = getelementptr [16 x i32 ], [16 x i32 ]* %r137, i32 0, i32 %r141
  %r143 = load i32, i32* %r136
  %r144 = call i32 @mod(i32 %r143, i32 10)
  %r145 = load i32, i32* @ascii_0
  %r146 = add i32 %r144, %r145
  store i32 %r146, i32* %r142
  %r147 = load i32, i32* %r136
  %r148 = sdiv i32 %r147, 10
  store i32 %r148, i32* %r136
  %r149 = load i32, i32* %r138
  %r150 = add i32 %r149, 1
  store i32 %r150, i32* %r138
  br label %bb_while_4_38_cond

bb_while_4_38_bre:
  br label %bb_while_4_43_cond

bb_while_4_43_cond:
  %r151 = load i32, i32* %r138
  %r152 = icmp sgt i32 %r151, 0
  br i1 %r152, label %bb_while_4_43_whilestms, label %bb_while_4_43_bre

bb_while_4_43_whilestms:
  %r153 = load i32, i32* %r138
  %r154 = sub i32 %r153, 1
  store i32 %r154, i32* %r138
  %r155 = load i32, i32* %r138
  %r156 = getelementptr [16 x i32 ], [16 x i32 ]* %r137, i32 0, i32 %r155
  %r157 = load i32, i32* %r156
  call void @putch(i32 %r157)
  br label %bb_while_4_43_cond

bb_while_4_43_bre:
  ret void
}

define i32 @main( ) {
bb8:
  %r158 = alloca i32
  %r162 = alloca i32
  br label %bb4

bb4:
  %r159 = call i32 @my_getint()
  store i32 %r159, i32* %r158
  br label %bb_while_4_52_cond

bb_while_4_52_cond:
  %r160 = load i32, i32* %r158
  %r161 = icmp sgt i32 %r160, 0
  br i1 %r161, label %bb_while_4_52_whilestms, label %bb_while_4_52_bre

bb_while_4_52_whilestms:
  %r163 = call i32 @my_getint()
  store i32 %r163, i32* %r162
  %r164 = load i32, i32* %r162
  call void @my_putint(i32 %r164)
  call void @putch(i32 10)
  %r165 = load i32, i32* %r158
  %r166 = sub i32 %r165, 1
  store i32 %r166, i32* %r158
  br label %bb_while_4_52_cond

bb_while_4_52_bre:
  ret i32 0
}

