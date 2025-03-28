; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@f = dso_local global void (i32*)* @foo, align 8, !dbg !0
@val = dso_local global i32 0, align 4, !dbg !5

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foo(i32* noundef %0) #0 !dbg !19 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !21, metadata !DIExpression()), !dbg !22
  %3 = load i32*, i32** %2, align 8, !dbg !23
  store i32 10, i32* %3, align 4, !dbg !24
  ret void, !dbg !25
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !26 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !32, metadata !DIExpression()), !dbg !33
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !34, metadata !DIExpression()), !dbg !35
  call void @llvm.dbg.declare(metadata i32** %6, metadata !36, metadata !DIExpression()), !dbg !37
  store i32* @val, i32** %6, align 8, !dbg !37
  %7 = load void (i32*)*, void (i32*)** @f, align 8, !dbg !38
  %8 = load i32*, i32** %6, align 8, !dbg !39
  call void %7(i32* noundef %8), !dbg !38
  ret i32 0, !dbg !40
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.ident = !{!13}
!llvm.module.flags = !{!14, !15, !16, !17, !18}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "f", scope: !2, file: !3, line: 7, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !4, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "source/main.c", directory: "/root/CS5890-6890-Program-Analysis/pa_template/benchmark/bench11", checksumkind: CSK_MD5, checksum: "c212f52122d1c71ddb4d7989997da3a0")
!4 = !{!0, !5}
!5 = !DIGlobalVariableExpression(var: !6, expr: !DIExpression())
!6 = distinct !DIGlobalVariable(name: "val", scope: !2, file: !3, line: 8, type: !7, isLocal: false, isDefinition: true)
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "FP", file: !3, line: 5, baseType: !9)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DISubroutineType(types: !11)
!11 = !{null, !12}
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!13 = !{!"clang version 14.0.6"}
!14 = !{i32 7, !"Dwarf Version", i32 5}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{i32 1, !"wchar_size", i32 4}
!17 = !{i32 7, !"uwtable", i32 1}
!18 = !{i32 7, !"frame-pointer", i32 2}
!19 = distinct !DISubprogram(name: "foo", scope: !3, file: !3, line: 3, type: !10, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !20)
!20 = !{}
!21 = !DILocalVariable(name: "x", arg: 1, scope: !19, file: !3, line: 3, type: !12)
!22 = !DILocation(line: 3, column: 15, scope: !19)
!23 = !DILocation(line: 3, column: 21, scope: !19)
!24 = !DILocation(line: 3, column: 23, scope: !19)
!25 = !DILocation(line: 3, column: 28, scope: !19)
!26 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 10, type: !27, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !20)
!27 = !DISubroutineType(types: !28)
!28 = !{!7, !7, !29}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64)
!31 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!32 = !DILocalVariable(name: "argc", arg: 1, scope: !26, file: !3, line: 10, type: !7)
!33 = !DILocation(line: 10, column: 14, scope: !26)
!34 = !DILocalVariable(name: "argv", arg: 2, scope: !26, file: !3, line: 10, type: !29)
!35 = !DILocation(line: 10, column: 27, scope: !26)
!36 = !DILocalVariable(name: "p", scope: !26, file: !3, line: 11, type: !12)
!37 = !DILocation(line: 11, column: 10, scope: !26)
!38 = !DILocation(line: 12, column: 5, scope: !26)
!39 = !DILocation(line: 12, column: 8, scope: !26)
!40 = !DILocation(line: 13, column: 5, scope: !26)
