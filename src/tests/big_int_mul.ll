declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@len = global i32 20
define i32 @main( ) {
bb2:
  %r100 = alloca i32
  %r101 = alloca i32
  %r102 = alloca i32
  %r103 = alloca i32
  %r104 = alloca i32
  %r105 = alloca [ 20 x i32 ]
  %r126 = alloca [ 20 x i32 ]
  %r147 = alloca i32
  %r149 = alloca i32
  %r151 = alloca [ 25 x i32 ]
  %r152 = alloca [ 25 x i32 ]
  %r153 = alloca [ 40 x i32 ]
  %r233 = alloca i32
  br label %bb1

bb1:
  call void @_sysy_starttime(i32 97)
  %r106 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 0
  store i32 1, i32* %r106
  %r107 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 1
  store i32 2, i32* %r107
  %r108 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 2
  store i32 3, i32* %r108
  %r109 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 3
  store i32 4, i32* %r109
  %r110 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 4
  store i32 5, i32* %r110
  %r111 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 5
  store i32 6, i32* %r111
  %r112 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 6
  store i32 7, i32* %r112
  %r113 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 7
  store i32 8, i32* %r113
  %r114 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 8
  store i32 9, i32* %r114
  %r115 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 9
  store i32 0, i32* %r115
  %r116 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 10
  store i32 1, i32* %r116
  %r117 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 11
  store i32 2, i32* %r117
  %r118 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 12
  store i32 3, i32* %r118
  %r119 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 13
  store i32 4, i32* %r119
  %r120 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 14
  store i32 5, i32* %r120
  %r121 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 15
  store i32 6, i32* %r121
  %r122 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 16
  store i32 7, i32* %r122
  %r123 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 17
  store i32 8, i32* %r123
  %r124 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 18
  store i32 9, i32* %r124
  %r125 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 19
  store i32 0, i32* %r125
  %r127 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 0
  store i32 2, i32* %r127
  %r128 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 1
  store i32 3, i32* %r128
  %r129 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 2
  store i32 4, i32* %r129
  %r130 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 3
  store i32 2, i32* %r130
  %r131 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 4
  store i32 5, i32* %r131
  %r132 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 5
  store i32 7, i32* %r132
  %r133 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 6
  store i32 9, i32* %r133
  %r134 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 7
  store i32 9, i32* %r134
  %r135 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 8
  store i32 0, i32* %r135
  %r136 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 9
  store i32 1, i32* %r136
  %r137 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 10
  store i32 9, i32* %r137
  %r138 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 11
  store i32 8, i32* %r138
  %r139 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 12
  store i32 7, i32* %r139
  %r140 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 13
  store i32 6, i32* %r140
  %r141 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 14
  store i32 4, i32* %r141
  %r142 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 15
  store i32 3, i32* %r142
  %r143 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 16
  store i32 2, i32* %r143
  %r144 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 17
  store i32 1, i32* %r144
  %r145 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 18
  store i32 2, i32* %r145
  %r146 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 19
  store i32 2, i32* %r146
  %r148 = load i32, i32* @len
  store i32 %r148, i32* %r147
  %r150 = load i32, i32* @len
  store i32 %r150, i32* %r149
  %r154 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 0
  store i32 0, i32* %r154
  %r155 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 1
  store i32 0, i32* %r155
  %r156 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 3
  store i32 0, i32* %r156
  %r157 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 5
  store i32 0, i32* %r157
  %r158 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 7
  store i32 0, i32* %r158
  %r159 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 9
  store i32 0, i32* %r159
  %r160 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 11
  store i32 0, i32* %r160
  %r161 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 13
  store i32 0, i32* %r161
  %r162 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 15
  store i32 0, i32* %r162
  %r163 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 17
  store i32 0, i32* %r163
  %r164 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 19
  store i32 0, i32* %r164
  %r165 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 21
  store i32 0, i32* %r165
  %r166 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 23
  store i32 0, i32* %r166
  %r167 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 25
  store i32 0, i32* %r167
  %r168 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 27
  store i32 0, i32* %r168
  %r169 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 29
  store i32 0, i32* %r169
  %r170 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 31
  store i32 0, i32* %r170
  %r171 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 33
  store i32 0, i32* %r171
  %r172 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 35
  store i32 0, i32* %r172
  %r173 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 37
  store i32 0, i32* %r173
  %r174 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 39
  store i32 0, i32* %r174
  store i32 0, i32* %r100
  br label %bb_while_4_20_cond

bb_while_4_20_cond:
  %r175 = load i32, i32* %r100
  %r176 = load i32, i32* %r147
  %r177 = icmp slt i32 %r175, %r176
  br i1 %r177, label %bb_while_4_20_whilestms, label %bb_while_4_20_bre

bb_while_4_20_whilestms:
  %r178 = load i32, i32* %r100
  %r179 = getelementptr [25 x i32 ], [25 x i32 ]* %r151, i32 0, i32 %r178
  %r180 = load i32, i32* %r100
  %r181 = getelementptr [20 x i32 ], [20 x i32 ]* %r105, i32 0, i32 %r180
  %r182 = load i32, i32* %r181
  store i32 %r182, i32* %r179
  %r183 = load i32, i32* %r100
  %r184 = add i32 %r183, 1
  store i32 %r184, i32* %r100
  br label %bb_while_4_20_cond

bb_while_4_20_bre:
  store i32 0, i32* %r100
  br label %bb_while_4_26_cond

bb_while_4_26_cond:
  %r185 = load i32, i32* %r100
  %r186 = load i32, i32* %r149
  %r187 = icmp slt i32 %r185, %r186
  br i1 %r187, label %bb_while_4_26_whilestms, label %bb_while_4_26_bre

bb_while_4_26_whilestms:
  %r188 = load i32, i32* %r100
  %r189 = getelementptr [25 x i32 ], [25 x i32 ]* %r152, i32 0, i32 %r188
  %r190 = load i32, i32* %r100
  %r191 = getelementptr [20 x i32 ], [20 x i32 ]* %r126, i32 0, i32 %r190
  %r192 = load i32, i32* %r191
  store i32 %r192, i32* %r189
  %r193 = load i32, i32* %r100
  %r194 = add i32 %r193, 1
  store i32 %r194, i32* %r100
  br label %bb_while_4_26_cond

bb_while_4_26_bre:
  %r195 = load i32, i32* %r147
  %r196 = load i32, i32* %r149
  %r197 = add i32 %r195, %r196
  %r198 = sub i32 %r197, 1
  store i32 %r198, i32* %r103
  store i32 0, i32* %r100
  br label %bb_while_4_34_cond

bb_while_4_34_cond:
  %r199 = load i32, i32* %r100
  %r200 = load i32, i32* %r103
  %r201 = icmp sle i32 %r199, %r200
  br i1 %r201, label %bb_while_4_34_whilestms, label %bb_while_4_34_bre

bb_while_4_34_whilestms:
  %r202 = load i32, i32* %r100
  %r203 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r202
  store i32 0, i32* %r203
  %r204 = load i32, i32* %r100
  %r205 = add i32 %r204, 1
  store i32 %r205, i32* %r100
  br label %bb_while_4_34_cond

bb_while_4_34_bre:
  store i32 0, i32* %r104
  %r206 = load i32, i32* %r149
  %r207 = sub i32 %r206, 1
  store i32 %r207, i32* %r100
  br label %bb_while_4_42_cond

bb_while_4_42_cond:
  %r208 = load i32, i32* %r100
  %r209 = sub i32 0, 1
  %r210 = icmp sgt i32 %r208, %r209
  br i1 %r210, label %bb_while_4_42_whilestms, label %bb_while_4_42_bre

bb_while_4_42_whilestms:
  %r211 = load i32, i32* %r100
  %r212 = getelementptr [25 x i32 ], [25 x i32 ]* %r152, i32 0, i32 %r211
  %r213 = load i32, i32* %r212
  store i32 %r213, i32* %r102
  %r214 = load i32, i32* %r147
  %r215 = sub i32 %r214, 1
  store i32 %r215, i32* %r101
  br label %bb_while_8_45_cond

bb_while_8_45_cond:
  %r216 = load i32, i32* %r101
  %r217 = sub i32 0, 1
  %r218 = icmp sgt i32 %r216, %r217
  br i1 %r218, label %bb_while_8_45_whilestms, label %bb_while_8_45_bre

bb_while_8_45_whilestms:
  %r219 = load i32, i32* %r103
  %r220 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r219
  %r221 = load i32, i32* %r220
  %r222 = load i32, i32* %r102
  %r223 = load i32, i32* %r101
  %r224 = getelementptr [25 x i32 ], [25 x i32 ]* %r151, i32 0, i32 %r223
  %r225 = load i32, i32* %r224
  %r226 = mul i32 %r222, %r225
  %r227 = add i32 %r221, %r226
  store i32 %r227, i32* %r104
  %r228 = load i32, i32* %r104
  %r229 = icmp sge i32 %r228, 10
  br i1 %r229, label %bb_if_12_47_true, label %bb_if_12_47_false

bb_if_12_47_true:
  %r230 = load i32, i32* %r103
  %r231 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r230
  %r232 = load i32, i32* %r104
  store i32 %r232, i32* %r231
  %r234 = load i32, i32* %r103
  %r235 = sub i32 %r234, 1
  store i32 %r235, i32* %r233
  %r236 = load i32, i32* %r233
  %r237 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r236
  %r238 = load i32, i32* %r233
  %r239 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r238
  %r240 = load i32, i32* %r239
  %r241 = load i32, i32* %r104
  %r242 = sdiv i32 %r241, 10
  %r243 = add i32 %r240, %r242
  store i32 %r243, i32* %r237
  br label %bb_if_12_47_end

bb_if_12_47_false:
  %r244 = load i32, i32* %r103
  %r245 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r244
  %r246 = load i32, i32* %r104
  store i32 %r246, i32* %r245
  br label %bb_if_12_47_end

bb_if_12_47_end:
  %r247 = load i32, i32* %r101
  %r248 = sub i32 %r247, 1
  store i32 %r248, i32* %r101
  %r249 = load i32, i32* %r103
  %r250 = sub i32 %r249, 1
  store i32 %r250, i32* %r103
  br label %bb_while_8_45_cond

bb_while_8_45_bre:
  %r251 = load i32, i32* %r103
  %r252 = load i32, i32* %r147
  %r253 = add i32 %r251, %r252
  %r254 = sub i32 %r253, 1
  store i32 %r254, i32* %r103
  %r255 = load i32, i32* %r100
  %r256 = sub i32 %r255, 1
  store i32 %r256, i32* %r100
  br label %bb_while_4_42_cond

bb_while_4_42_bre:
  %r257 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 0
  %r258 = load i32, i32* %r257
  %r259 = icmp ne i32 %r258, 0
  br i1 %r259, label %bb_if_4_62_true, label %bb_if_4_62_false

bb_if_4_62_true:
  %r260 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 0
  %r261 = load i32, i32* %r260
  call void @putint(i32 %r261)
  br label %bb_if_4_62_end

bb_if_4_62_false:
  br label %bb_if_4_62_end

bb_if_4_62_end:
  store i32 1, i32* %r100
  br label %bb_while_4_67_cond

bb_while_4_67_cond:
  %r262 = load i32, i32* %r100
  %r263 = load i32, i32* %r147
  %r264 = load i32, i32* %r149
  %r265 = add i32 %r263, %r264
  %r266 = sub i32 %r265, 1
  %r267 = icmp sle i32 %r262, %r266
  br i1 %r267, label %bb_while_4_67_whilestms, label %bb_while_4_67_bre

bb_while_4_67_whilestms:
  %r268 = load i32, i32* %r100
  %r269 = getelementptr [40 x i32 ], [40 x i32 ]* %r153, i32 0, i32 %r268
  %r270 = load i32, i32* %r269
  call void @putint(i32 %r270)
  %r271 = load i32, i32* %r100
  %r272 = add i32 %r271, 1
  store i32 %r272, i32* %r100
  br label %bb_while_4_67_cond

bb_while_4_67_bre:
  call void @_sysy_stoptime(i32 117)
  ret i32 0
}

