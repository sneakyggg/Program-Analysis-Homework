; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @add(i32* noundef %0) #0 !dbg !8 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !14, metadata !DIExpression()), !dbg !15
  %3 = load i32*, i32** %2, align 8, !dbg !16
  %4 = load i32, i32* %3, align 4, !dbg !17
  ret i32 %4, !dbg !18
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !19 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32 (i32*)*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !25, metadata !DIExpression()), !dbg !26
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !27, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata i32 (i32*)** %6, metadata !29, metadata !DIExpression()), !dbg !32
  store i32 (i32*)* @add, i32 (i32*)** %6, align 8, !dbg !32
  %7 = load i32 (i32*)*, i32 (i32*)** %6, align 8, !dbg !33
  %8 = call i32 %7(i32* noundef %4), !dbg !33
  ret i32 %8, !dbg !34
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3, !4, !5, !6, !7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/home/cs6890/CS5890-6890-Program-Analysis/pa_template/benchmark/bench7", checksumkind: CSK_MD5, checksum: "e367161fca6bdccc6ec504ffa9726eb6")
!2 = !{!"clang version 14.0.6"}
!3 = !{i32 7, !"Dwarf Version", i32 5}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = distinct !DISubprogram(name: "add", scope: !1, file: !1, line: 3, type: !9, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!9 = !DISubroutineType(types: !10)
!10 = !{!11, !12}
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!13 = !{}
!14 = !DILocalVariable(name: "x", arg: 1, scope: !8, file: !1, line: 3, type: !12)
!15 = !DILocation(line: 3, column: 15, scope: !8)
!16 = !DILocation(line: 5, column: 13, scope: !8)
!17 = !DILocation(line: 5, column: 12, scope: !8)
!18 = !DILocation(line: 5, column: 5, scope: !8)
!19 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 10, type: !20, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!20 = !DISubroutineType(types: !21)
!21 = !{!11, !11, !22}
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64)
!24 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!25 = !DILocalVariable(name: "argc", arg: 1, scope: !19, file: !1, line: 10, type: !11)
!26 = !DILocation(line: 10, column: 14, scope: !19)
!27 = !DILocalVariable(name: "argv", arg: 2, scope: !19, file: !1, line: 10, type: !22)
!28 = !DILocation(line: 10, column: 26, scope: !19)
!29 = !DILocalVariable(name: "f", scope: !19, file: !1, line: 12, type: !30)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "FP", file: !1, line: 8, baseType: !31)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!32 = !DILocation(line: 12, column: 8, scope: !19)
!33 = !DILocation(line: 13, column: 12, scope: !19)
!34 = !DILocation(line: 13, column: 5, scope: !19)
