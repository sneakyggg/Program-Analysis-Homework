; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@f = dso_local global void (i32*)* null, align 8, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foo(i32* noundef %0) #0 !dbg !17 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !19, metadata !DIExpression()), !dbg !20
  %3 = load i32*, i32** %2, align 8, !dbg !21
  store i32 10, i32* %3, align 4, !dbg !22
  ret void, !dbg !23
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @run(void (i32*)* noundef %0, i32 noundef %1) #0 !dbg !24 {
  %3 = alloca void (i32*)*, align 8
  %4 = alloca i32, align 4
  store void (i32*)* %0, void (i32*)** %3, align 8
  call void @llvm.dbg.declare(metadata void (i32*)** %3, metadata !27, metadata !DIExpression()), !dbg !28
  store i32 %1, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !29, metadata !DIExpression()), !dbg !30
  %5 = load void (i32*)*, void (i32*)** %3, align 8, !dbg !31
  call void %5(i32* noundef %4), !dbg !31
  ret void, !dbg !32
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !33 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !39, metadata !DIExpression()), !dbg !40
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !41, metadata !DIExpression()), !dbg !42
  call void @llvm.dbg.declare(metadata i32** %6, metadata !43, metadata !DIExpression()), !dbg !44
  store i32* %4, i32** %6, align 8, !dbg !44
  store void (i32*)* @foo, void (i32*)** @f, align 8, !dbg !45
  %7 = load void (i32*)*, void (i32*)** @f, align 8, !dbg !46
  %8 = load i32*, i32** %6, align 8, !dbg !47
  %9 = load i32, i32* %8, align 4, !dbg !48
  call void @run(void (i32*)* noundef %7, i32 noundef %9), !dbg !49
  ret i32 0, !dbg !50
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.ident = !{!11}
!llvm.module.flags = !{!12, !13, !14, !15, !16}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "f", scope: !2, file: !3, line: 6, type: !5, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !4, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "source/main.c", directory: "/root/CS5890-6890-Program-Analysis/pa_template/benchmark/bench12", checksumkind: CSK_MD5, checksum: "422408437440c61c72b083fa6b9dee77")
!4 = !{!0}
!5 = !DIDerivedType(tag: DW_TAG_typedef, name: "FP", file: !3, line: 5, baseType: !6)
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !{!"clang version 14.0.6"}
!12 = !{i32 7, !"Dwarf Version", i32 5}
!13 = !{i32 2, !"Debug Info Version", i32 3}
!14 = !{i32 1, !"wchar_size", i32 4}
!15 = !{i32 7, !"uwtable", i32 1}
!16 = !{i32 7, !"frame-pointer", i32 2}
!17 = distinct !DISubprogram(name: "foo", scope: !3, file: !3, line: 3, type: !7, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !18)
!18 = !{}
!19 = !DILocalVariable(name: "x", arg: 1, scope: !17, file: !3, line: 3, type: !9)
!20 = !DILocation(line: 3, column: 15, scope: !17)
!21 = !DILocation(line: 3, column: 21, scope: !17)
!22 = !DILocation(line: 3, column: 23, scope: !17)
!23 = !DILocation(line: 3, column: 28, scope: !17)
!24 = distinct !DISubprogram(name: "run", scope: !3, file: !3, line: 8, type: !25, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !18)
!25 = !DISubroutineType(types: !26)
!26 = !{null, !5, !10}
!27 = !DILocalVariable(name: "fi", arg: 1, scope: !24, file: !3, line: 8, type: !5)
!28 = !DILocation(line: 8, column: 14, scope: !24)
!29 = !DILocalVariable(name: "v", arg: 2, scope: !24, file: !3, line: 8, type: !10)
!30 = !DILocation(line: 8, column: 22, scope: !24)
!31 = !DILocation(line: 10, column: 5, scope: !24)
!32 = !DILocation(line: 11, column: 1, scope: !24)
!33 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 13, type: !34, scopeLine: 13, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !18)
!34 = !DISubroutineType(types: !35)
!35 = !{!10, !10, !36}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64)
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64)
!38 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!39 = !DILocalVariable(name: "argc", arg: 1, scope: !33, file: !3, line: 13, type: !10)
!40 = !DILocation(line: 13, column: 14, scope: !33)
!41 = !DILocalVariable(name: "argv", arg: 2, scope: !33, file: !3, line: 13, type: !36)
!42 = !DILocation(line: 13, column: 27, scope: !33)
!43 = !DILocalVariable(name: "p", scope: !33, file: !3, line: 14, type: !9)
!44 = !DILocation(line: 14, column: 10, scope: !33)
!45 = !DILocation(line: 15, column: 7, scope: !33)
!46 = !DILocation(line: 17, column: 10, scope: !33)
!47 = !DILocation(line: 17, column: 14, scope: !33)
!48 = !DILocation(line: 17, column: 13, scope: !33)
!49 = !DILocation(line: 17, column: 5, scope: !33)
!50 = !DILocation(line: 18, column: 5, scope: !33)
