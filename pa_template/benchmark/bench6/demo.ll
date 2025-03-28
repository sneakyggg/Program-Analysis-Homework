; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @add(i32* noundef %0) #0 !dbg !8 {
  %2 = alloca i32*, align 8
  %3 = alloca i32, align 4
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !14, metadata !DIExpression()), !dbg !15
  call void @llvm.dbg.declare(metadata i32* %3, metadata !16, metadata !DIExpression()), !dbg !17
  %4 = load i32*, i32** %2, align 8, !dbg !18
  %5 = load i32, i32* %4, align 4, !dbg !19
  store i32 %5, i32* %3, align 4, !dbg !17
  %6 = load i32, i32* %3, align 4, !dbg !20
  %7 = add nsw i32 %6, 1, !dbg !21
  ret i32 %7, !dbg !22
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !23 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !29, metadata !DIExpression()), !dbg !30
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !31, metadata !DIExpression()), !dbg !32
  call void @llvm.dbg.declare(metadata i32* %6, metadata !33, metadata !DIExpression()), !dbg !34
  %7 = load i32, i32* %4, align 4, !dbg !35
  store i32 %7, i32* %6, align 4, !dbg !34
  %8 = call i32 @add(i32* noundef %6), !dbg !36
  ret i32 %8, !dbg !37
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3, !4, !5, !6, !7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/root/CS5890-6890-Program-Analysis/pa_template/benchmark/bench6", checksumkind: CSK_MD5, checksum: "9293625437c45e4e46efba8c06a1e55e")
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
!16 = !DILocalVariable(name: "a", scope: !8, file: !1, line: 5, type: !11)
!17 = !DILocation(line: 5, column: 9, scope: !8)
!18 = !DILocation(line: 5, column: 14, scope: !8)
!19 = !DILocation(line: 5, column: 13, scope: !8)
!20 = !DILocation(line: 6, column: 12, scope: !8)
!21 = !DILocation(line: 6, column: 13, scope: !8)
!22 = !DILocation(line: 6, column: 5, scope: !8)
!23 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 9, type: !24, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!24 = !DISubroutineType(types: !25)
!25 = !{!11, !11, !26}
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64)
!28 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!29 = !DILocalVariable(name: "argc", arg: 1, scope: !23, file: !1, line: 9, type: !11)
!30 = !DILocation(line: 9, column: 14, scope: !23)
!31 = !DILocalVariable(name: "argv", arg: 2, scope: !23, file: !1, line: 9, type: !26)
!32 = !DILocation(line: 9, column: 26, scope: !23)
!33 = !DILocalVariable(name: "a", scope: !23, file: !1, line: 11, type: !11)
!34 = !DILocation(line: 11, column: 9, scope: !23)
!35 = !DILocation(line: 11, column: 13, scope: !23)
!36 = !DILocation(line: 12, column: 12, scope: !23)
!37 = !DILocation(line: 12, column: 5, scope: !23)
