declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
define i32 @canJump( i32* %r100, i32 %r101 ) {
bb3:
  %r102 = alloca i32
  %r110 = alloca [ 10 x i32 ]
  %r111 = alloca i32
  %r120 = alloca i32
  %r130 = alloca i32
  br label %bb1

bb1:
  store i32 %r101, i32* %r102
  %r103 = load i32, i32* %r102
  %r104 = icmp eq i32 %r103, 1
  br i1 %r104, label %bb_if_4_2_true, label %bb_if_4_2_false

bb_if_4_2_true:
  ret i32 1
bb_if_4_2_false:
  br label %bb_if_4_2_end

bb_if_4_2_end:
  %r105 = getelementptr i32, i32* %r100, i32 0
  %r106 = load i32, i32* %r105
  %r107 = load i32, i32* %r102
  %r108 = sub i32 %r107, 2
  %r109 = icmp sgt i32 %r106, %r108
  br i1 %r109, label %bb_if_4_6_true, label %bb_if_4_6_false

bb_if_4_6_true:
  ret i32 1
bb_if_4_6_false:
  br label %bb_if_4_6_end

bb_if_4_6_end:
  store i32 0, i32* %r111
  br label %bb_while_4_13_cond

bb_while_4_13_cond:
  %r112 = load i32, i32* %r111
  %r113 = load i32, i32* %r102
  %r114 = sub i32 %r113, 1
  %r115 = icmp slt i32 %r112, %r114
  br i1 %r115, label %bb_while_4_13_whilestms, label %bb_while_4_13_bre

bb_while_4_13_whilestms:
  %r116 = load i32, i32* %r111
  %r117 = getelementptr [10 x i32 ], [10 x i32 ]* %r110, i32 0, i32 %r116
  store i32 0, i32* %r117
  %r118 = load i32, i32* %r111
  %r119 = add i32 %r118, 1
  store i32 %r119, i32* %r111
  br label %bb_while_4_13_cond

bb_while_4_13_bre:
  %r121 = load i32, i32* %r102
  %r122 = sub i32 %r121, 1
  store i32 %r122, i32* %r120
  %r123 = load i32, i32* %r120
  %r124 = getelementptr [10 x i32 ], [10 x i32 ]* %r110, i32 0, i32 %r123
  store i32 1, i32* %r124
  %r125 = load i32, i32* %r102
  %r126 = sub i32 %r125, 2
  store i32 %r126, i32* %r111
  br label %bb_while_4_20_cond

bb_while_4_20_cond:
  %r127 = load i32, i32* %r111
  %r128 = sub i32 0, 1
  %r129 = icmp sgt i32 %r127, %r128
  br i1 %r129, label %bb_while_4_20_whilestms, label %bb_while_4_20_bre

bb_while_4_20_whilestms:
  %r131 = load i32, i32* %r111
  %r132 = getelementptr i32, i32* %r100, i32 %r131
  %r133 = load i32, i32* %r132
  %r134 = load i32, i32* %r102
  %r135 = sub i32 %r134, 1
  %r136 = load i32, i32* %r111
  %r137 = sub i32 %r135, %r136
  %r138 = icmp slt i32 %r133, %r137
  br i1 %r138, label %bb_if_8_22_true, label %bb_if_8_22_false

bb_if_8_22_true:
  %r139 = load i32, i32* %r111
  %r140 = getelementptr i32, i32* %r100, i32 %r139
  %r141 = load i32, i32* %r140
  store i32 %r141, i32* %r130
  br label %bb_if_8_22_end

bb_if_8_22_false:
  %r142 = load i32, i32* %r102
  %r143 = sub i32 %r142, 1
  %r144 = load i32, i32* %r111
  %r145 = sub i32 %r143, %r144
  store i32 %r145, i32* %r130
  br label %bb_if_8_22_end

bb_if_8_22_end:
  br label %bb_while_8_29_cond

bb_while_8_29_cond:
  %r146 = load i32, i32* %r130
  %r147 = sub i32 0, 1
  %r148 = icmp sgt i32 %r146, %r147
  br i1 %r148, label %bb_while_8_29_whilestms, label %bb_while_8_29_bre

bb_while_8_29_whilestms:
  %r149 = load i32, i32* %r111
  %r150 = load i32, i32* %r130
  %r151 = add i32 %r149, %r150
  store i32 %r151, i32* %r120
  %r152 = load i32, i32* %r120
  %r153 = getelementptr [10 x i32 ], [10 x i32 ]* %r110, i32 0, i32 %r152
  %r154 = load i32, i32* %r153
  %r155 = icmp ne i32 %r154, 0
  br i1 %r155, label %bb_if_12_31_true, label %bb_if_12_31_false

bb_if_12_31_true:
  %r156 = load i32, i32* %r111
  %r157 = getelementptr [10 x i32 ], [10 x i32 ]* %r110, i32 0, i32 %r156
  store i32 1, i32* %r157
  br label %bb_if_12_31_end

bb_if_12_31_false:
  br label %bb_if_12_31_end

bb_if_12_31_end:
  %r158 = load i32, i32* %r130
  %r159 = sub i32 %r158, 1
  store i32 %r159, i32* %r130
  br label %bb_while_8_29_cond

bb_while_8_29_bre:
  %r160 = load i32, i32* %r111
  %r161 = sub i32 %r160, 1
  store i32 %r161, i32* %r111
  br label %bb_while_4_20_cond

bb_while_4_20_bre:
  %r162 = getelementptr [10 x i32 ], [10 x i32 ]* %r110, i32 0, i32 0
  %r163 = load i32, i32* %r162
  ret i32 %r163
}

define i32 @main( ) {
bb4:
  %r164 = alloca i32
  %r165 = alloca [ 10 x i32 ]
  br label %bb2

bb2:
  %r166 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 0
  store i32 3, i32* %r166
  %r167 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 1
  store i32 3, i32* %r167
  %r168 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 2
  store i32 9, i32* %r168
  %r169 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 3
  store i32 0, i32* %r169
  %r170 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 4
  store i32 0, i32* %r170
  %r171 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 5
  store i32 1, i32* %r171
  %r172 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 6
  store i32 1, i32* %r172
  %r173 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 7
  store i32 5, i32* %r173
  %r174 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 8
  store i32 7, i32* %r174
  %r175 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 9
  store i32 8, i32* %r175
  store i32 10, i32* %r164
  %r176 = getelementptr [10 x i32 ], [10 x i32 ]* %r165, i32 0, i32 0
  %r177 = load i32, i32* %r164
  %r178 = call i32 @canJump(i32* %r176, i32 %r177)
  store i32 %r178, i32* %r164
  %r179 = load i32, i32* %r164
  ret i32 %r179
}

