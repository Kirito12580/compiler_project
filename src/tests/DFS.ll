declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@n = global i32 0
@m = global i32 0
@to = global [ 5005 x i32 ] zeroinitializer
@next = global [ 5005 x i32 ] zeroinitializer
@head = global [ 1005 x i32 ] zeroinitializer
@cnt = global i32 0
@vis = global [ 1005 x i32 ] zeroinitializer
define i32 @quickread( ) {
bb7:
  %r100 = alloca i32
  %r102 = alloca i32
  %r103 = alloca i32
  br label %bb1

bb1:
  %r101 = call i32 @getch()
  store i32 %r101, i32* %r100
  store i32 0, i32* %r102
  store i32 0, i32* %r103
  br label %bb_while_4_5_cond

bb_while_4_5_cond:
  %r104 = load i32, i32* %r100
  %r105 = icmp slt i32 %r104, 48
  br i1 %r105, label %bb_while_4_5_whilestms, label %bb24_5checksecond

bb24_5checksecond:
  %r106 = load i32, i32* %r100
  %r107 = icmp sgt i32 %r106, 57
  br i1 %r107, label %bb_while_4_5_whilestms, label %bb_while_4_5_bre

bb_while_4_5_whilestms:
  %r108 = load i32, i32* %r100
  %r109 = icmp eq i32 %r108, 45
  br i1 %r109, label %bb_if_8_6_true, label %bb_if_8_6_false

bb_if_8_6_true:
  store i32 1, i32* %r103
  br label %bb_if_8_6_end

bb_if_8_6_false:
  br label %bb_if_8_6_end

bb_if_8_6_end:
  %r110 = call i32 @getch()
  store i32 %r110, i32* %r100
  br label %bb_while_4_5_cond

bb_while_4_5_bre:
  br label %bb_while_4_11_cond

bb_while_4_11_cond:
  %r111 = load i32, i32* %r100
  %r112 = icmp sge i32 %r111, 48
  br i1 %r112, label %bb25_11checksecond, label %bb_while_4_11_bre

bb25_11checksecond:
  %r113 = load i32, i32* %r100
  %r114 = icmp sle i32 %r113, 57
  br i1 %r114, label %bb_while_4_11_whilestms, label %bb_while_4_11_bre

bb_while_4_11_whilestms:
  %r115 = load i32, i32* %r102
  %r116 = mul i32 %r115, 10
  %r117 = load i32, i32* %r100
  %r118 = add i32 %r116, %r117
  %r119 = sub i32 %r118, 48
  store i32 %r119, i32* %r102
  %r120 = call i32 @getch()
  store i32 %r120, i32* %r100
  br label %bb_while_4_11_cond

bb_while_4_11_bre:
  %r121 = load i32, i32* %r103
  %r122 = icmp ne i32 %r121, 0
  br i1 %r122, label %bb_if_4_15_true, label %bb_if_4_15_false

bb_if_4_15_true:
  %r123 = load i32, i32* %r102
  %r124 = sub i32 0, %r123
  ret i32 %r124
bb_if_4_15_false:
  %r125 = load i32, i32* %r102
  ret i32 %r125
bb_if_4_15_end:
  ret i32 -1
}

define void @addedge( i32 %r126, i32 %r128 ) {
bb8:
  %r127 = alloca i32
  %r129 = alloca i32
  br label %bb2

bb2:
  store i32 %r126, i32* %r127
  store i32 %r128, i32* %r129
  %r130 = load i32, i32* @cnt
  %r131 = getelementptr [5005 x i32 ], [5005 x i32 ]* @to, i32 0, i32 %r130
  %r132 = load i32, i32* %r129
  store i32 %r132, i32* %r131
  %r133 = load i32, i32* @cnt
  %r134 = getelementptr [5005 x i32 ], [5005 x i32 ]* @next, i32 0, i32 %r133
  %r135 = load i32, i32* %r127
  %r136 = getelementptr [1005 x i32 ], [1005 x i32 ]* @head, i32 0, i32 %r135
  %r137 = load i32, i32* %r136
  store i32 %r137, i32* %r134
  %r138 = load i32, i32* %r127
  %r139 = getelementptr [1005 x i32 ], [1005 x i32 ]* @head, i32 0, i32 %r138
  %r140 = load i32, i32* @cnt
  store i32 %r140, i32* %r139
  %r141 = load i32, i32* @cnt
  %r142 = add i32 %r141, 1
  store i32 %r142, i32* @cnt
  %r143 = load i32, i32* @cnt
  %r144 = getelementptr [5005 x i32 ], [5005 x i32 ]* @to, i32 0, i32 %r143
  %r145 = load i32, i32* %r127
  store i32 %r145, i32* %r144
  %r146 = load i32, i32* @cnt
  %r147 = getelementptr [5005 x i32 ], [5005 x i32 ]* @next, i32 0, i32 %r146
  %r148 = load i32, i32* %r129
  %r149 = getelementptr [1005 x i32 ], [1005 x i32 ]* @head, i32 0, i32 %r148
  %r150 = load i32, i32* %r149
  store i32 %r150, i32* %r147
  %r151 = load i32, i32* %r129
  %r152 = getelementptr [1005 x i32 ], [1005 x i32 ]* @head, i32 0, i32 %r151
  %r153 = load i32, i32* @cnt
  store i32 %r153, i32* %r152
  %r154 = load i32, i32* @cnt
  %r155 = add i32 %r154, 1
  store i32 %r155, i32* @cnt
  ret void
}

define void @init( ) {
bb9:
  %r156 = alloca i32
  br label %bb3

bb3:
  store i32 0, i32* %r156
  br label %bb_while_4_43_cond

bb_while_4_43_cond:
  %r157 = load i32, i32* %r156
  %r158 = icmp slt i32 %r157, 1005
  br i1 %r158, label %bb_while_4_43_whilestms, label %bb_while_4_43_bre

bb_while_4_43_whilestms:
  %r159 = load i32, i32* %r156
  %r160 = getelementptr [1005 x i32 ], [1005 x i32 ]* @head, i32 0, i32 %r159
  %r161 = sub i32 0, 1
  store i32 %r161, i32* %r160
  %r162 = load i32, i32* %r156
  %r163 = add i32 %r162, 1
  store i32 %r163, i32* %r156
  br label %bb_while_4_43_cond

bb_while_4_43_bre:
  ret void
}

define void @clear( ) {
bb10:
  %r164 = alloca i32
  br label %bb4

bb4:
  store i32 1, i32* %r164
  br label %bb_while_4_51_cond

bb_while_4_51_cond:
  %r165 = load i32, i32* %r164
  %r166 = load i32, i32* @n
  %r167 = icmp sle i32 %r165, %r166
  br i1 %r167, label %bb_while_4_51_whilestms, label %bb_while_4_51_bre

bb_while_4_51_whilestms:
  %r168 = load i32, i32* %r164
  %r169 = getelementptr [1005 x i32 ], [1005 x i32 ]* @vis, i32 0, i32 %r168
  store i32 0, i32* %r169
  %r170 = load i32, i32* %r164
  %r171 = add i32 %r170, 1
  store i32 %r171, i32* %r164
  br label %bb_while_4_51_cond

bb_while_4_51_bre:
  ret void
}

define i32 @same( i32 %r172, i32 %r174 ) {
bb11:
  %r173 = alloca i32
  %r175 = alloca i32
  %r181 = alloca i32
  %r188 = alloca i32
  br label %bb5

bb5:
  store i32 %r172, i32* %r173
  store i32 %r174, i32* %r175
  %r176 = load i32, i32* %r173
  %r177 = getelementptr [1005 x i32 ], [1005 x i32 ]* @vis, i32 0, i32 %r176
  store i32 1, i32* %r177
  %r178 = load i32, i32* %r173
  %r179 = load i32, i32* %r175
  %r180 = icmp eq i32 %r178, %r179
  br i1 %r180, label %bb_if_4_59_true, label %bb_if_4_59_false

bb_if_4_59_true:
  ret i32 1
bb_if_4_59_false:
  br label %bb_if_4_59_end

bb_if_4_59_end:
  %r182 = load i32, i32* %r173
  %r183 = getelementptr [1005 x i32 ], [1005 x i32 ]* @head, i32 0, i32 %r182
  %r184 = load i32, i32* %r183
  store i32 %r184, i32* %r181
  br label %bb_while_4_63_cond

bb_while_4_63_cond:
  %r185 = load i32, i32* %r181
  %r186 = sub i32 0, 1
  %r187 = icmp ne i32 %r185, %r186
  br i1 %r187, label %bb_while_4_63_whilestms, label %bb_while_4_63_bre

bb_while_4_63_whilestms:
  %r189 = load i32, i32* %r181
  %r190 = getelementptr [5005 x i32 ], [5005 x i32 ]* @to, i32 0, i32 %r189
  %r191 = load i32, i32* %r190
  store i32 %r191, i32* %r188
  %r192 = load i32, i32* %r188
  %r193 = getelementptr [1005 x i32 ], [1005 x i32 ]* @vis, i32 0, i32 %r192
  %r194 = load i32, i32* %r193
  %r195 = icmp eq i32 %r194, 0
  br i1 %r195, label %bb25_65checksecond, label %bb_if_8_65_false

bb25_65checksecond:
  %r196 = load i32, i32* %r188
  %r197 = load i32, i32* %r175
  %r198 = call i32 @same(i32 %r196, i32 %r197)
  %r199 = icmp ne i32 %r198, 0
  br i1 %r199, label %bb_if_8_65_true, label %bb_if_8_65_false

bb_if_8_65_true:
  ret i32 1
bb_if_8_65_false:
  br label %bb_if_8_65_end

bb_if_8_65_end:
  %r200 = load i32, i32* %r181
  %r201 = getelementptr [5005 x i32 ], [5005 x i32 ]* @next, i32 0, i32 %r200
  %r202 = load i32, i32* %r201
  store i32 %r202, i32* %r181
  br label %bb_while_4_63_cond

bb_while_4_63_bre:
  ret i32 0
}

define i32 @main( ) {
bb12:
  %r205 = alloca i32
  %r206 = alloca i32
  %r207 = alloca i32
  br label %bb6

bb6:
  %r203 = call i32 @quickread()
  store i32 %r203, i32* @n
  %r204 = call i32 @quickread()
  store i32 %r204, i32* @m
  call void @init()
  store i32 0, i32* %r205
  store i32 0, i32* %r206
  store i32 0, i32* %r207
  br label %bb_while_4_79_cond

bb_while_4_79_cond:
  %r208 = load i32, i32* @m
  %r209 = icmp ne i32 %r208, 0
  br i1 %r209, label %bb_while_4_79_whilestms, label %bb_while_4_79_bre

bb_while_4_79_whilestms:
  %r210 = call i32 @getch()
  store i32 %r210, i32* %r205
  br label %bb_while_8_81_cond

bb_while_8_81_cond:
  %r211 = load i32, i32* %r205
  %r212 = icmp ne i32 %r211, 81
  br i1 %r212, label %bb27_81checksecond, label %bb_while_8_81_bre

bb27_81checksecond:
  %r213 = load i32, i32* %r205
  %r214 = icmp ne i32 %r213, 85
  br i1 %r214, label %bb_while_8_81_whilestms, label %bb_while_8_81_bre

bb_while_8_81_whilestms:
  %r215 = call i32 @getch()
  store i32 %r215, i32* %r205
  br label %bb_while_8_81_cond

bb_while_8_81_bre:
  %r216 = load i32, i32* %r205
  %r217 = icmp eq i32 %r216, 81
  br i1 %r217, label %bb_if_8_84_true, label %bb_if_8_84_false

bb_if_8_84_true:
  %r218 = call i32 @quickread()
  store i32 %r218, i32* %r206
  %r219 = call i32 @quickread()
  store i32 %r219, i32* %r207
  call void @clear()
  %r220 = load i32, i32* %r206
  %r221 = load i32, i32* %r207
  %r222 = call i32 @same(i32 %r220, i32 %r221)
  call void @putint(i32 %r222)
  call void @putch(i32 10)
  br label %bb_if_8_84_end

bb_if_8_84_false:
  %r223 = call i32 @quickread()
  store i32 %r223, i32* %r206
  %r224 = call i32 @quickread()
  store i32 %r224, i32* %r207
  %r225 = load i32, i32* %r206
  %r226 = load i32, i32* %r207
  call void @addedge(i32 %r225, i32 %r226)
  br label %bb_if_8_84_end

bb_if_8_84_end:
  %r227 = load i32, i32* @m
  %r228 = sub i32 %r227, 1
  store i32 %r228, i32* @m
  br label %bb_while_4_79_cond

bb_while_4_79_bre:
  ret i32 0
}

