; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %struct._IO_codecvt*, %struct._IO_wide_data*, %struct._IO_FILE*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type opaque
%struct._IO_codecvt = type opaque
%struct._IO_wide_data = type opaque

@.str = private unnamed_addr constant [17 x i8] c"@@ start FuncA\0D\0A\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"test-%u\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"wb\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"value = %u \0D\0A\00", align 1
@.str.4 = private unnamed_addr constant [15 x i8] c"@@ end FuncA\0D\0A\00", align 1
@.str.5 = private unnamed_addr constant [17 x i8] c"@@ start FuncB\0D\0A\00", align 1
@.str.6 = private unnamed_addr constant [15 x i8] c"@@ end FuncB\0D\0A\00", align 1
@.str.7 = private unnamed_addr constant [16 x i8] c"@@ start main\0D\0A\00", align 1
@.str.8 = private unnamed_addr constant [14 x i8] c"@@ end main\0D\0A\00", align 1
@.str.9 = private unnamed_addr constant [16 x i8] c"@@ Value = %u\0D\0A\00", align 1
@.str.10 = private unnamed_addr constant [21 x i8] c"@@ start Getpasswd\0D\0A\00", align 1
@.str.1.11 = private unnamed_addr constant [19 x i8] c"@@ end Getpasswd\0D\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @FuncA(i8* noundef %0, i32 noundef %1) #0 !dbg !12 {
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca %struct._IO_FILE*, align 8
  %6 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 %1, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !21, metadata !DIExpression()), !dbg !22
  %7 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str, i64 0, i64 0)), !dbg !23
  %8 = load i8*, i8** %3, align 8, !dbg !24
  %9 = load i32, i32* %4, align 4, !dbg !25
  %10 = call i32 (i8*, i8*, ...) @sprintf(i8* noundef %8, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 noundef %9) #6, !dbg !26
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %5, metadata !27, metadata !DIExpression()), !dbg !88
  %11 = load i8*, i8** %3, align 8, !dbg !89
  %12 = call noalias %struct._IO_FILE* @fopen(i8* noundef %11, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i64 0, i64 0)), !dbg !90
  store %struct._IO_FILE* %12, %struct._IO_FILE** %5, align 8, !dbg !88
  call void @llvm.dbg.declare(metadata i32* %6, metadata !91, metadata !DIExpression()), !dbg !92
  %13 = call i64 @random() #6, !dbg !93
  %14 = trunc i64 %13 to i32, !dbg !94
  %15 = urem i32 %14, 18, !dbg !95
  store i32 %15, i32* %6, align 4, !dbg !92
  %16 = load i32, i32* %6, align 4, !dbg !96
  %17 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i64 0, i64 0), i32 noundef %16), !dbg !97
  %18 = bitcast i32* %6 to i8*, !dbg !98
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !99
  %20 = call i64 @fwrite(i8* noundef %18, i64 noundef 1, i64 noundef 4, %struct._IO_FILE* noundef %19), !dbg !100
  %21 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !101
  %22 = call i32 @fclose(%struct._IO_FILE* noundef %21), !dbg !102
  %23 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.4, i64 0, i64 0)), !dbg !103
  ret void, !dbg !104
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @printf(i8* noundef, ...) #2

; Function Attrs: nounwind
declare dso_local i32 @sprintf(i8* noundef, i8* noundef, ...) #3

declare dso_local noalias %struct._IO_FILE* @fopen(i8* noundef, i8* noundef) #2

; Function Attrs: nounwind
declare dso_local i64 @random() #3

declare dso_local i64 @fwrite(i8* noundef, i64 noundef, i64 noundef, %struct._IO_FILE* noundef) #2

declare dso_local i32 @fclose(%struct._IO_FILE* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @FuncB(i8 noundef zeroext %0) #0 !dbg !105 {
  %2 = alloca i8, align 1
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i8 %0, i8* %2, align 1
  call void @llvm.dbg.declare(metadata i8* %2, metadata !109, metadata !DIExpression()), !dbg !110
  %5 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.5, i64 0, i64 0)), !dbg !111
  call void @llvm.dbg.declare(metadata i32* %3, metadata !112, metadata !DIExpression()), !dbg !113
  store i32 0, i32* %3, align 4, !dbg !113
  call void @llvm.dbg.declare(metadata i32* %4, metadata !114, metadata !DIExpression()), !dbg !115
  %6 = load i8, i8* %2, align 1, !dbg !116
  %7 = zext i8 %6 to i32, !dbg !116
  %8 = load i8, i8* %2, align 1, !dbg !117
  %9 = zext i8 %8 to i32, !dbg !117
  %10 = mul nsw i32 %7, %9, !dbg !118
  %11 = load i8, i8* %2, align 1, !dbg !119
  %12 = zext i8 %11 to i32, !dbg !119
  %13 = mul nsw i32 5, %12, !dbg !120
  %14 = add nsw i32 %10, %13, !dbg !121
  %15 = sub nsw i32 %14, 100, !dbg !122
  store i32 %15, i32* %4, align 4, !dbg !115
  %16 = load i32, i32* %4, align 4, !dbg !123
  switch i32 %16, label %21 [
    i32 0, label %17
    i32 65535, label %18
    i32 999999, label %19
  ], !dbg !124

17:                                               ; preds = %1
  store i32 0, i32* %3, align 4, !dbg !125
  br label %24, !dbg !128

18:                                               ; preds = %1
  store i32 2, i32* %3, align 4, !dbg !129
  br label %24, !dbg !131

19:                                               ; preds = %1
  %20 = call i32 @Getpasswd(i8 noundef zeroext 4), !dbg !132
  store i32 %20, i32* %3, align 4, !dbg !134
  br label %24, !dbg !135

21:                                               ; preds = %1
  %22 = call i32 @Getpasswd(i8 noundef zeroext 4), !dbg !136
  store i32 %22, i32* %3, align 4, !dbg !138
  %23 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.6, i64 0, i64 0)), !dbg !139
  call void @exit(i32 noundef 0) #7, !dbg !140
  unreachable, !dbg !140

24:                                               ; preds = %19, %18, %17
  %25 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.6, i64 0, i64 0)), !dbg !141
  %26 = load i32, i32* %3, align 4, !dbg !142
  ret i32 %26, !dbg !143
}

; Function Attrs: noreturn nounwind
declare dso_local void @exit(i32 noundef) #4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !144 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca [32 x i8], align 16
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !148, metadata !DIExpression()), !dbg !149
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !150, metadata !DIExpression()), !dbg !151
  %10 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.7, i64 0, i64 0)), !dbg !152
  %11 = load i32, i32* %4, align 4, !dbg !153
  %12 = icmp eq i32 %11, 1, !dbg !155
  br i1 %12, label %13, label %24, !dbg !156

13:                                               ; preds = %2
  call void @llvm.dbg.declare(metadata i32* %6, metadata !157, metadata !DIExpression()), !dbg !159
  store i32 0, i32* %6, align 4, !dbg !159
  call void @llvm.dbg.declare(metadata [32 x i8]* %7, metadata !160, metadata !DIExpression()), !dbg !164
  br label %14, !dbg !165

14:                                               ; preds = %17, %13
  %15 = load i32, i32* %6, align 4, !dbg !166
  %16 = icmp slt i32 %15, 32, !dbg !167
  br i1 %16, label %17, label %22, !dbg !165

17:                                               ; preds = %14
  %18 = getelementptr inbounds [32 x i8], [32 x i8]* %7, i64 0, i64 0, !dbg !168
  %19 = load i32, i32* %6, align 4, !dbg !170
  call void @FuncA(i8* noundef %18, i32 noundef %19), !dbg !171
  %20 = load i32, i32* %6, align 4, !dbg !172
  %21 = add nsw i32 %20, 1, !dbg !172
  store i32 %21, i32* %6, align 4, !dbg !172
  br label %14, !dbg !165, !llvm.loop !173

22:                                               ; preds = %14
  %23 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.8, i64 0, i64 0)), !dbg !176
  store i32 0, i32* %3, align 4, !dbg !177
  br label %47, !dbg !177

24:                                               ; preds = %2
  call void @llvm.dbg.declare(metadata i32* %8, metadata !178, metadata !DIExpression()), !dbg !179
  %25 = load i8**, i8*** %5, align 8, !dbg !180
  %26 = getelementptr inbounds i8*, i8** %25, i64 1, !dbg !180
  %27 = load i8*, i8** %26, align 8, !dbg !180
  %28 = call i32 @atoi(i8* noundef %27) #8, !dbg !181
  store i32 %28, i32* %8, align 4, !dbg !179
  call void @llvm.dbg.declare(metadata i32* %9, metadata !182, metadata !DIExpression()), !dbg !183
  store i32 0, i32* %9, align 4, !dbg !183
  %29 = load i32, i32* %8, align 4, !dbg !184
  %30 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.9, i64 0, i64 0), i32 noundef %29), !dbg !185
  %31 = load i32, i32* %8, align 4, !dbg !186
  %32 = icmp uge i32 %31, 4, !dbg !188
  br i1 %32, label %33, label %40, !dbg !189

33:                                               ; preds = %24
  %34 = load i32, i32* %8, align 4, !dbg !190
  %35 = icmp ule i32 %34, 16, !dbg !191
  br i1 %35, label %36, label %40, !dbg !192

36:                                               ; preds = %33
  %37 = load i32, i32* %8, align 4, !dbg !193
  %38 = trunc i32 %37 to i8, !dbg !193
  %39 = call i32 @Getpasswd(i8 noundef zeroext %38), !dbg !195
  store i32 %39, i32* %9, align 4, !dbg !196
  br label %44, !dbg !197

40:                                               ; preds = %33, %24
  %41 = load i32, i32* %8, align 4, !dbg !198
  %42 = trunc i32 %41 to i8, !dbg !198
  %43 = call i32 @FuncB(i8 noundef zeroext %42), !dbg !200
  store i32 %43, i32* %9, align 4, !dbg !201
  br label %44

44:                                               ; preds = %40, %36
  %45 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.8, i64 0, i64 0)), !dbg !202
  %46 = load i32, i32* %9, align 4, !dbg !203
  store i32 %46, i32* %3, align 4, !dbg !204
  br label %47, !dbg !204

47:                                               ; preds = %44, %22
  %48 = load i32, i32* %3, align 4, !dbg !205
  ret i32 %48, !dbg !205
}

; Function Attrs: nounwind readonly willreturn
declare dso_local i32 @atoi(i8* noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @Getpasswd(i8 noundef zeroext %0) #0 !dbg !206 {
  %2 = alloca i8, align 1
  %3 = alloca i32, align 4
  store i8 %0, i8* %2, align 1
  call void @llvm.dbg.declare(metadata i8* %2, metadata !207, metadata !DIExpression()), !dbg !208
  %4 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.10, i64 0, i64 0)), !dbg !209
  call void @llvm.dbg.declare(metadata i32* %3, metadata !210, metadata !DIExpression()), !dbg !211
  %5 = load i8, i8* %2, align 1, !dbg !212
  %6 = zext i8 %5 to i32, !dbg !212
  switch i32 %6, label %52 [
    i32 4, label %7
    i32 8, label %17
    i32 16, label %32
  ], !dbg !213

7:                                                ; preds = %1
  %8 = call i64 @random() #6, !dbg !214
  %9 = srem i64 %8, 4, !dbg !217
  %10 = trunc i64 %9 to i32, !dbg !218
  %11 = shl i32 3, %10, !dbg !218
  %12 = call i64 @random() #6, !dbg !219
  %13 = srem i64 %12, 2, !dbg !220
  %14 = trunc i64 %13 to i32, !dbg !221
  %15 = shl i32 4, %14, !dbg !221
  %16 = or i32 %11, %15, !dbg !222
  store i32 %16, i32* %3, align 4, !dbg !223
  br label %56, !dbg !224

17:                                               ; preds = %1
  %18 = call i64 @random() #6, !dbg !225
  %19 = srem i64 %18, 8, !dbg !227
  %20 = trunc i64 %19 to i32, !dbg !228
  %21 = shl i32 2, %20, !dbg !228
  %22 = call i64 @random() #6, !dbg !229
  %23 = srem i64 %22, 4, !dbg !230
  %24 = trunc i64 %23 to i32, !dbg !231
  %25 = shl i32 3, %24, !dbg !231
  %26 = or i32 %21, %25, !dbg !232
  %27 = call i64 @random() #6, !dbg !233
  %28 = srem i64 %27, 2, !dbg !234
  %29 = trunc i64 %28 to i32, !dbg !235
  %30 = shl i32 4, %29, !dbg !235
  %31 = or i32 %26, %30, !dbg !236
  store i32 %31, i32* %3, align 4, !dbg !237
  br label %56, !dbg !238

32:                                               ; preds = %1
  %33 = call i64 @random() #6, !dbg !239
  %34 = srem i64 %33, 16, !dbg !241
  %35 = trunc i64 %34 to i32, !dbg !242
  %36 = shl i32 1, %35, !dbg !242
  %37 = call i64 @random() #6, !dbg !243
  %38 = srem i64 %37, 8, !dbg !244
  %39 = trunc i64 %38 to i32, !dbg !245
  %40 = shl i32 2, %39, !dbg !245
  %41 = or i32 %36, %40, !dbg !246
  %42 = call i64 @random() #6, !dbg !247
  %43 = srem i64 %42, 4, !dbg !248
  %44 = trunc i64 %43 to i32, !dbg !249
  %45 = shl i32 3, %44, !dbg !249
  %46 = or i32 %41, %45, !dbg !250
  %47 = call i64 @random() #6, !dbg !251
  %48 = srem i64 %47, 2, !dbg !252
  %49 = trunc i64 %48 to i32, !dbg !253
  %50 = shl i32 4, %49, !dbg !253
  %51 = or i32 %46, %50, !dbg !254
  store i32 %51, i32* %3, align 4, !dbg !255
  br label %56, !dbg !256

52:                                               ; preds = %1
  %53 = load i8, i8* %2, align 1, !dbg !257
  %54 = zext i8 %53 to i32, !dbg !257
  %55 = shl i32 %54, 3, !dbg !259
  store i32 %55, i32* %3, align 4, !dbg !260
  br label %56, !dbg !261

56:                                               ; preds = %52, %32, %17, %7
  %57 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.1.11, i64 0, i64 0)), !dbg !262
  %58 = load i32, i32* %3, align 4, !dbg !263
  ret i32 %58, !dbg !264
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nounwind }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind readonly willreturn }

!llvm.dbg.cu = !{!0, !4}
!llvm.ident = !{!6, !6}
!llvm.module.flags = !{!7, !8, !9, !10, !11}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/home/cs6890/CS5890-6890-Program-Analysis/pa_template/benchmark/bench1", checksumkind: CSK_MD5, checksum: "65035faacb3cd875471b956cc13ca609")
!2 = !{!3}
!3 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!4 = distinct !DICompileUnit(language: DW_LANG_C99, file: !5, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!5 = !DIFile(filename: "source/Passwd.c", directory: "/home/cs6890/CS5890-6890-Program-Analysis/pa_template/benchmark/bench1", checksumkind: CSK_MD5, checksum: "d1964cb69b9bbc9f0eca6373886e2e72")
!6 = !{!"clang version 14.0.6"}
!7 = !{i32 7, !"Dwarf Version", i32 5}
!8 = !{i32 2, !"Debug Info Version", i32 3}
!9 = !{i32 1, !"wchar_size", i32 4}
!10 = !{i32 7, !"uwtable", i32 1}
!11 = !{i32 7, !"frame-pointer", i32 2}
!12 = distinct !DISubprogram(name: "FuncA", scope: !1, file: !1, line: 6, type: !13, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !18)
!13 = !DISubroutineType(types: !14)
!14 = !{null, !15, !17}
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64)
!16 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!17 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!18 = !{}
!19 = !DILocalVariable(name: "SEED", arg: 1, scope: !12, file: !1, line: 6, type: !15)
!20 = !DILocation(line: 6, column: 18, scope: !12)
!21 = !DILocalVariable(name: "Index", arg: 2, scope: !12, file: !1, line: 6, type: !17)
!22 = !DILocation(line: 6, column: 33, scope: !12)
!23 = !DILocation(line: 8, column: 5, scope: !12)
!24 = !DILocation(line: 9, column: 14, scope: !12)
!25 = !DILocation(line: 9, column: 31, scope: !12)
!26 = !DILocation(line: 9, column: 5, scope: !12)
!27 = !DILocalVariable(name: "F", scope: !12, file: !1, line: 11, type: !28)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !30, line: 7, baseType: !31)
!30 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types/FILE.h", directory: "", checksumkind: CSK_MD5, checksum: "571f9fb6223c42439075fdde11a0de5d")
!31 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !32, line: 49, size: 1728, elements: !33)
!32 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h", directory: "", checksumkind: CSK_MD5, checksum: "1bad07471b7974df4ecc1d1c2ca207e6")
!33 = !{!34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !49, !51, !52, !53, !57, !59, !61, !65, !68, !70, !73, !76, !77, !79, !83, !84}
!34 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !31, file: !32, line: 51, baseType: !17, size: 32)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !31, file: !32, line: 54, baseType: !15, size: 64, offset: 64)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !31, file: !32, line: 55, baseType: !15, size: 64, offset: 128)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !31, file: !32, line: 56, baseType: !15, size: 64, offset: 192)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !31, file: !32, line: 57, baseType: !15, size: 64, offset: 256)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !31, file: !32, line: 58, baseType: !15, size: 64, offset: 320)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !31, file: !32, line: 59, baseType: !15, size: 64, offset: 384)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !31, file: !32, line: 60, baseType: !15, size: 64, offset: 448)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !31, file: !32, line: 61, baseType: !15, size: 64, offset: 512)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !31, file: !32, line: 64, baseType: !15, size: 64, offset: 576)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !31, file: !32, line: 65, baseType: !15, size: 64, offset: 640)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !31, file: !32, line: 66, baseType: !15, size: 64, offset: 704)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !31, file: !32, line: 68, baseType: !47, size: 64, offset: 768)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !32, line: 36, flags: DIFlagFwdDecl)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !31, file: !32, line: 70, baseType: !50, size: 64, offset: 832)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !31, file: !32, line: 72, baseType: !17, size: 32, offset: 896)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !31, file: !32, line: 73, baseType: !17, size: 32, offset: 928)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !31, file: !32, line: 74, baseType: !54, size: 64, offset: 960)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !55, line: 152, baseType: !56)
!55 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!56 = !DIBasicType(name: "long", size: 64, encoding: DW_ATE_signed)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !31, file: !32, line: 77, baseType: !58, size: 16, offset: 1024)
!58 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !31, file: !32, line: 78, baseType: !60, size: 8, offset: 1040)
!60 = !DIBasicType(name: "signed char", size: 8, encoding: DW_ATE_signed_char)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !31, file: !32, line: 79, baseType: !62, size: 8, offset: 1048)
!62 = !DICompositeType(tag: DW_TAG_array_type, baseType: !16, size: 8, elements: !63)
!63 = !{!64}
!64 = !DISubrange(count: 1)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !31, file: !32, line: 81, baseType: !66, size: 64, offset: 1088)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !32, line: 43, baseType: null)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !31, file: !32, line: 89, baseType: !69, size: 64, offset: 1152)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !55, line: 153, baseType: !56)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_codecvt", scope: !31, file: !32, line: 91, baseType: !71, size: 64, offset: 1216)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64)
!72 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_codecvt", file: !32, line: 37, flags: DIFlagFwdDecl)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_wide_data", scope: !31, file: !32, line: 92, baseType: !74, size: 64, offset: 1280)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64)
!75 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_wide_data", file: !32, line: 38, flags: DIFlagFwdDecl)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_freeres_list", scope: !31, file: !32, line: 93, baseType: !50, size: 64, offset: 1344)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "_freeres_buf", scope: !31, file: !32, line: 94, baseType: !78, size: 64, offset: 1408)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !31, file: !32, line: 95, baseType: !80, size: 64, offset: 1472)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !81, line: 46, baseType: !82)
!81 = !DIFile(filename: "tools/build/lib/clang/14.0.6/include/stddef.h", directory: "/home/cs6890", checksumkind: CSK_MD5, checksum: "2499dd2361b915724b073282bea3a7bc")
!82 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !31, file: !32, line: 96, baseType: !17, size: 32, offset: 1536)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !31, file: !32, line: 98, baseType: !85, size: 160, offset: 1568)
!85 = !DICompositeType(tag: DW_TAG_array_type, baseType: !16, size: 160, elements: !86)
!86 = !{!87}
!87 = !DISubrange(count: 20)
!88 = !DILocation(line: 11, column: 11, scope: !12)
!89 = !DILocation(line: 11, column: 22, scope: !12)
!90 = !DILocation(line: 11, column: 15, scope: !12)
!91 = !DILocalVariable(name: "value", scope: !12, file: !1, line: 12, type: !3)
!92 = !DILocation(line: 12, column: 14, scope: !12)
!93 = !DILocation(line: 12, column: 32, scope: !12)
!94 = !DILocation(line: 12, column: 22, scope: !12)
!95 = !DILocation(line: 12, column: 41, scope: !12)
!96 = !DILocation(line: 13, column: 32, scope: !12)
!97 = !DILocation(line: 13, column: 5, scope: !12)
!98 = !DILocation(line: 14, column: 13, scope: !12)
!99 = !DILocation(line: 14, column: 43, scope: !12)
!100 = !DILocation(line: 14, column: 5, scope: !12)
!101 = !DILocation(line: 15, column: 12, scope: !12)
!102 = !DILocation(line: 15, column: 5, scope: !12)
!103 = !DILocation(line: 16, column: 5, scope: !12)
!104 = !DILocation(line: 17, column: 1, scope: !12)
!105 = distinct !DISubprogram(name: "FuncB", scope: !1, file: !1, line: 20, type: !106, scopeLine: 21, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !18)
!106 = !DISubroutineType(types: !107)
!107 = !{!3, !108}
!108 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!109 = !DILocalVariable(name: "Value", arg: 1, scope: !105, file: !1, line: 20, type: !108)
!110 = !DILocation(line: 20, column: 31, scope: !105)
!111 = !DILocation(line: 22, column: 5, scope: !105)
!112 = !DILocalVariable(name: "Pwd", scope: !105, file: !1, line: 23, type: !3)
!113 = !DILocation(line: 23, column: 14, scope: !105)
!114 = !DILocalVariable(name: "FValue", scope: !105, file: !1, line: 25, type: !3)
!115 = !DILocation(line: 25, column: 14, scope: !105)
!116 = !DILocation(line: 25, column: 23, scope: !105)
!117 = !DILocation(line: 25, column: 30, scope: !105)
!118 = !DILocation(line: 25, column: 29, scope: !105)
!119 = !DILocation(line: 25, column: 40, scope: !105)
!120 = !DILocation(line: 25, column: 39, scope: !105)
!121 = !DILocation(line: 25, column: 36, scope: !105)
!122 = !DILocation(line: 25, column: 46, scope: !105)
!123 = !DILocation(line: 26, column: 13, scope: !105)
!124 = !DILocation(line: 26, column: 5, scope: !105)
!125 = !DILocation(line: 30, column: 17, scope: !126)
!126 = distinct !DILexicalBlock(scope: !127, file: !1, line: 29, column: 9)
!127 = distinct !DILexicalBlock(scope: !105, file: !1, line: 27, column: 5)
!128 = !DILocation(line: 31, column: 13, scope: !126)
!129 = !DILocation(line: 35, column: 17, scope: !130)
!130 = distinct !DILexicalBlock(scope: !127, file: !1, line: 34, column: 9)
!131 = !DILocation(line: 36, column: 13, scope: !130)
!132 = !DILocation(line: 40, column: 19, scope: !133)
!133 = distinct !DILexicalBlock(scope: !127, file: !1, line: 39, column: 9)
!134 = !DILocation(line: 40, column: 17, scope: !133)
!135 = !DILocation(line: 41, column: 13, scope: !133)
!136 = !DILocation(line: 45, column: 19, scope: !137)
!137 = distinct !DILexicalBlock(scope: !127, file: !1, line: 44, column: 9)
!138 = !DILocation(line: 45, column: 17, scope: !137)
!139 = !DILocation(line: 46, column: 13, scope: !137)
!140 = !DILocation(line: 47, column: 13, scope: !137)
!141 = !DILocation(line: 50, column: 5, scope: !105)
!142 = !DILocation(line: 51, column: 12, scope: !105)
!143 = !DILocation(line: 51, column: 5, scope: !105)
!144 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 55, type: !145, scopeLine: 56, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !18)
!145 = !DISubroutineType(types: !146)
!146 = !{!17, !17, !147}
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64)
!148 = !DILocalVariable(name: "argc", arg: 1, scope: !144, file: !1, line: 55, type: !17)
!149 = !DILocation(line: 55, column: 14, scope: !144)
!150 = !DILocalVariable(name: "argv", arg: 2, scope: !144, file: !1, line: 55, type: !147)
!151 = !DILocation(line: 55, column: 28, scope: !144)
!152 = !DILocation(line: 57, column: 5, scope: !144)
!153 = !DILocation(line: 58, column: 9, scope: !154)
!154 = distinct !DILexicalBlock(scope: !144, file: !1, line: 58, column: 9)
!155 = !DILocation(line: 58, column: 14, scope: !154)
!156 = !DILocation(line: 58, column: 9, scope: !144)
!157 = !DILocalVariable(name: "Index", scope: !158, file: !1, line: 60, type: !17)
!158 = distinct !DILexicalBlock(scope: !154, file: !1, line: 59, column: 5)
!159 = !DILocation(line: 60, column: 13, scope: !158)
!160 = !DILocalVariable(name: "SEED", scope: !158, file: !1, line: 61, type: !161)
!161 = !DICompositeType(tag: DW_TAG_array_type, baseType: !16, size: 256, elements: !162)
!162 = !{!163}
!163 = !DISubrange(count: 32)
!164 = !DILocation(line: 61, column: 14, scope: !158)
!165 = !DILocation(line: 63, column: 9, scope: !158)
!166 = !DILocation(line: 63, column: 16, scope: !158)
!167 = !DILocation(line: 63, column: 22, scope: !158)
!168 = !DILocation(line: 65, column: 20, scope: !169)
!169 = distinct !DILexicalBlock(scope: !158, file: !1, line: 64, column: 9)
!170 = !DILocation(line: 65, column: 26, scope: !169)
!171 = !DILocation(line: 65, column: 13, scope: !169)
!172 = !DILocation(line: 66, column: 18, scope: !169)
!173 = distinct !{!173, !165, !174, !175}
!174 = !DILocation(line: 67, column: 9, scope: !158)
!175 = !{!"llvm.loop.mustprogress"}
!176 = !DILocation(line: 69, column: 9, scope: !158)
!177 = !DILocation(line: 70, column: 9, scope: !158)
!178 = !DILocalVariable(name: "Value", scope: !144, file: !1, line: 73, type: !3)
!179 = !DILocation(line: 73, column: 14, scope: !144)
!180 = !DILocation(line: 73, column: 37, scope: !144)
!181 = !DILocation(line: 73, column: 32, scope: !144)
!182 = !DILocalVariable(name: "Pwd", scope: !144, file: !1, line: 74, type: !3)
!183 = !DILocation(line: 74, column: 14, scope: !144)
!184 = !DILocation(line: 76, column: 34, scope: !144)
!185 = !DILocation(line: 76, column: 5, scope: !144)
!186 = !DILocation(line: 77, column: 9, scope: !187)
!187 = distinct !DILexicalBlock(scope: !144, file: !1, line: 77, column: 9)
!188 = !DILocation(line: 77, column: 15, scope: !187)
!189 = !DILocation(line: 77, column: 20, scope: !187)
!190 = !DILocation(line: 77, column: 23, scope: !187)
!191 = !DILocation(line: 77, column: 29, scope: !187)
!192 = !DILocation(line: 77, column: 9, scope: !144)
!193 = !DILocation(line: 79, column: 26, scope: !194)
!194 = distinct !DILexicalBlock(scope: !187, file: !1, line: 78, column: 5)
!195 = !DILocation(line: 79, column: 15, scope: !194)
!196 = !DILocation(line: 79, column: 13, scope: !194)
!197 = !DILocation(line: 80, column: 5, scope: !194)
!198 = !DILocation(line: 83, column: 22, scope: !199)
!199 = distinct !DILexicalBlock(scope: !187, file: !1, line: 82, column: 5)
!200 = !DILocation(line: 83, column: 15, scope: !199)
!201 = !DILocation(line: 83, column: 13, scope: !199)
!202 = !DILocation(line: 86, column: 5, scope: !144)
!203 = !DILocation(line: 87, column: 12, scope: !144)
!204 = !DILocation(line: 87, column: 5, scope: !144)
!205 = !DILocation(line: 88, column: 1, scope: !144)
!206 = distinct !DISubprogram(name: "Getpasswd", scope: !5, file: !5, line: 4, type: !106, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !4, retainedNodes: !18)
!207 = !DILocalVariable(name: "Key", arg: 1, scope: !206, file: !5, line: 4, type: !108)
!208 = !DILocation(line: 4, column: 35, scope: !206)
!209 = !DILocation(line: 6, column: 5, scope: !206)
!210 = !DILocalVariable(name: "Pwd", scope: !206, file: !5, line: 7, type: !3)
!211 = !DILocation(line: 7, column: 14, scope: !206)
!212 = !DILocation(line: 8, column: 13, scope: !206)
!213 = !DILocation(line: 8, column: 5, scope: !206)
!214 = !DILocation(line: 12, column: 27, scope: !215)
!215 = distinct !DILexicalBlock(scope: !216, file: !5, line: 11, column: 9)
!216 = distinct !DILexicalBlock(scope: !206, file: !5, line: 9, column: 5)
!217 = !DILocation(line: 12, column: 36, scope: !215)
!218 = !DILocation(line: 12, column: 22, scope: !215)
!219 = !DILocation(line: 12, column: 52, scope: !215)
!220 = !DILocation(line: 12, column: 61, scope: !215)
!221 = !DILocation(line: 12, column: 47, scope: !215)
!222 = !DILocation(line: 12, column: 42, scope: !215)
!223 = !DILocation(line: 12, column: 17, scope: !215)
!224 = !DILocation(line: 13, column: 13, scope: !215)
!225 = !DILocation(line: 17, column: 27, scope: !226)
!226 = distinct !DILexicalBlock(scope: !216, file: !5, line: 16, column: 9)
!227 = !DILocation(line: 17, column: 36, scope: !226)
!228 = !DILocation(line: 17, column: 22, scope: !226)
!229 = !DILocation(line: 17, column: 52, scope: !226)
!230 = !DILocation(line: 17, column: 61, scope: !226)
!231 = !DILocation(line: 17, column: 47, scope: !226)
!232 = !DILocation(line: 17, column: 42, scope: !226)
!233 = !DILocation(line: 17, column: 77, scope: !226)
!234 = !DILocation(line: 17, column: 86, scope: !226)
!235 = !DILocation(line: 17, column: 72, scope: !226)
!236 = !DILocation(line: 17, column: 67, scope: !226)
!237 = !DILocation(line: 17, column: 17, scope: !226)
!238 = !DILocation(line: 18, column: 13, scope: !226)
!239 = !DILocation(line: 22, column: 26, scope: !240)
!240 = distinct !DILexicalBlock(scope: !216, file: !5, line: 21, column: 9)
!241 = !DILocation(line: 22, column: 35, scope: !240)
!242 = !DILocation(line: 22, column: 22, scope: !240)
!243 = !DILocation(line: 22, column: 51, scope: !240)
!244 = !DILocation(line: 22, column: 60, scope: !240)
!245 = !DILocation(line: 22, column: 46, scope: !240)
!246 = !DILocation(line: 22, column: 41, scope: !240)
!247 = !DILocation(line: 22, column: 76, scope: !240)
!248 = !DILocation(line: 22, column: 85, scope: !240)
!249 = !DILocation(line: 22, column: 71, scope: !240)
!250 = !DILocation(line: 22, column: 66, scope: !240)
!251 = !DILocation(line: 22, column: 101, scope: !240)
!252 = !DILocation(line: 22, column: 110, scope: !240)
!253 = !DILocation(line: 22, column: 96, scope: !240)
!254 = !DILocation(line: 22, column: 91, scope: !240)
!255 = !DILocation(line: 22, column: 17, scope: !240)
!256 = !DILocation(line: 23, column: 13, scope: !240)
!257 = !DILocation(line: 27, column: 19, scope: !258)
!258 = distinct !DILexicalBlock(scope: !216, file: !5, line: 26, column: 9)
!259 = !DILocation(line: 27, column: 23, scope: !258)
!260 = !DILocation(line: 27, column: 17, scope: !258)
!261 = !DILocation(line: 29, column: 5, scope: !216)
!262 = !DILocation(line: 31, column: 5, scope: !206)
!263 = !DILocation(line: 32, column: 12, scope: !206)
!264 = !DILocation(line: 32, column: 5, scope: !206)
