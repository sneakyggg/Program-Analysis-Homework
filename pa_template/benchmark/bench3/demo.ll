; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @sum(i32 noundef %0) #0 !dbg !8 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !13, metadata !DIExpression()), !dbg !14
  call void @llvm.dbg.declare(metadata i32* %3, metadata !15, metadata !DIExpression()), !dbg !16
  store i32 0, i32* %3, align 4, !dbg !16
  %5 = load i32, i32* %2, align 4, !dbg !17
  %6 = icmp sgt i32 %5, 0, !dbg !19
  br i1 %6, label %7, label %10, !dbg !20

7:                                                ; preds = %1
  %8 = load i32, i32* %2, align 4, !dbg !21
  %9 = mul nsw i32 %8, 2, !dbg !23
  store i32 %9, i32* %2, align 4, !dbg !24
  br label %13, !dbg !25

10:                                               ; preds = %1
  %11 = load i32, i32* %2, align 4, !dbg !26
  %12 = sub nsw i32 %11, 1, !dbg !28
  store i32 %12, i32* %2, align 4, !dbg !29
  br label %13

13:                                               ; preds = %10, %7
  call void @llvm.dbg.declare(metadata i32* %4, metadata !30, metadata !DIExpression()), !dbg !32
  store i32 0, i32* %4, align 4, !dbg !32
  br label %14, !dbg !33

14:                                               ; preds = %22, %13
  %15 = load i32, i32* %4, align 4, !dbg !34
  %16 = load i32, i32* %2, align 4, !dbg !36
  %17 = icmp slt i32 %15, %16, !dbg !37
  br i1 %17, label %18, label %25, !dbg !38

18:                                               ; preds = %14
  %19 = load i32, i32* %2, align 4, !dbg !39
  %20 = load i32, i32* %3, align 4, !dbg !40
  %21 = add nsw i32 %20, %19, !dbg !40
  store i32 %21, i32* %3, align 4, !dbg !40
  br label %22, !dbg !41

22:                                               ; preds = %18
  %23 = load i32, i32* %4, align 4, !dbg !42
  %24 = add nsw i32 %23, 1, !dbg !42
  store i32 %24, i32* %4, align 4, !dbg !42
  br label %14, !dbg !43, !llvm.loop !44

25:                                               ; preds = %14
  %26 = load i32, i32* %3, align 4, !dbg !47
  ret i32 %26, !dbg !48
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !49 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !55, metadata !DIExpression()), !dbg !56
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !57, metadata !DIExpression()), !dbg !58
  call void @llvm.dbg.declare(metadata i32* %6, metadata !59, metadata !DIExpression()), !dbg !60
  %7 = load i32, i32* %4, align 4, !dbg !61
  store i32 %7, i32* %6, align 4, !dbg !60
  %8 = load i32, i32* %6, align 4, !dbg !62
  %9 = call i32 @sum(i32 noundef %8), !dbg !63
  ret i32 %9, !dbg !64
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3, !4, !5, !6, !7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/root/CS5890-6890-Program-Analysis/pa_template/benchmark/bench3", checksumkind: CSK_MD5, checksum: "5c884e5813e3821c9819b81dcace403a")
!2 = !{!"clang version 14.0.6"}
!3 = !{i32 7, !"Dwarf Version", i32 5}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = distinct !DISubprogram(name: "sum", scope: !1, file: !1, line: 3, type: !9, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !12)
!9 = !DISubroutineType(types: !10)
!10 = !{!11, !11}
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !{}
!13 = !DILocalVariable(name: "x", arg: 1, scope: !8, file: !1, line: 3, type: !11)
!14 = !DILocation(line: 3, column: 14, scope: !8)
!15 = !DILocalVariable(name: "sum", scope: !8, file: !1, line: 5, type: !11)
!16 = !DILocation(line: 5, column: 9, scope: !8)
!17 = !DILocation(line: 7, column: 9, scope: !18)
!18 = distinct !DILexicalBlock(scope: !8, file: !1, line: 7, column: 9)
!19 = !DILocation(line: 7, column: 11, scope: !18)
!20 = !DILocation(line: 7, column: 9, scope: !8)
!21 = !DILocation(line: 9, column: 13, scope: !22)
!22 = distinct !DILexicalBlock(scope: !18, file: !1, line: 8, column: 5)
!23 = !DILocation(line: 9, column: 15, scope: !22)
!24 = !DILocation(line: 9, column: 11, scope: !22)
!25 = !DILocation(line: 10, column: 5, scope: !22)
!26 = !DILocation(line: 13, column: 13, scope: !27)
!27 = distinct !DILexicalBlock(scope: !18, file: !1, line: 12, column: 5)
!28 = !DILocation(line: 13, column: 15, scope: !27)
!29 = !DILocation(line: 13, column: 11, scope: !27)
!30 = !DILocalVariable(name: "i", scope: !31, file: !1, line: 16, type: !11)
!31 = distinct !DILexicalBlock(scope: !8, file: !1, line: 16, column: 5)
!32 = !DILocation(line: 16, column: 14, scope: !31)
!33 = !DILocation(line: 16, column: 10, scope: !31)
!34 = !DILocation(line: 16, column: 21, scope: !35)
!35 = distinct !DILexicalBlock(scope: !31, file: !1, line: 16, column: 5)
!36 = !DILocation(line: 16, column: 25, scope: !35)
!37 = !DILocation(line: 16, column: 23, scope: !35)
!38 = !DILocation(line: 16, column: 5, scope: !31)
!39 = !DILocation(line: 17, column: 16, scope: !35)
!40 = !DILocation(line: 17, column: 13, scope: !35)
!41 = !DILocation(line: 17, column: 9, scope: !35)
!42 = !DILocation(line: 16, column: 29, scope: !35)
!43 = !DILocation(line: 16, column: 5, scope: !35)
!44 = distinct !{!44, !38, !45, !46}
!45 = !DILocation(line: 17, column: 16, scope: !31)
!46 = !{!"llvm.loop.mustprogress"}
!47 = !DILocation(line: 18, column: 12, scope: !8)
!48 = !DILocation(line: 18, column: 5, scope: !8)
!49 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 21, type: !50, scopeLine: 22, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !12)
!50 = !DISubroutineType(types: !51)
!51 = !{!11, !11, !52}
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64)
!54 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!55 = !DILocalVariable(name: "argc", arg: 1, scope: !49, file: !1, line: 21, type: !11)
!56 = !DILocation(line: 21, column: 14, scope: !49)
!57 = !DILocalVariable(name: "argv", arg: 2, scope: !49, file: !1, line: 21, type: !52)
!58 = !DILocation(line: 21, column: 26, scope: !49)
!59 = !DILocalVariable(name: "a", scope: !49, file: !1, line: 23, type: !11)
!60 = !DILocation(line: 23, column: 9, scope: !49)
!61 = !DILocation(line: 23, column: 13, scope: !49)
!62 = !DILocation(line: 24, column: 16, scope: !49)
!63 = !DILocation(line: 24, column: 12, scope: !49)
!64 = !DILocation(line: 24, column: 5, scope: !49)
