; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !8 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32*, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !13, metadata !DIExpression()), !dbg !14
  store i32 5, i32* %2, align 4, !dbg !14
  call void @llvm.dbg.declare(metadata i32* %3, metadata !15, metadata !DIExpression()), !dbg !16
  store i32 1, i32* %3, align 4, !dbg !16
  call void @llvm.dbg.declare(metadata i32** %4, metadata !17, metadata !DIExpression()), !dbg !19
  store i32* %2, i32** %4, align 8, !dbg !20
  store i32* %3, i32** %4, align 8, !dbg !21
  %5 = load i32*, i32** %4, align 8, !dbg !22
  %6 = load i32, i32* %5, align 4, !dbg !23
  ret i32 %6, !dbg !24
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3, !4, !5, !6, !7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/root/CS5890-6890-Program-Analysis/pa_template/benchmark/bench9", checksumkind: CSK_MD5, checksum: "fb7f6b2eb99bf1fc951d353a13e727a7")
!2 = !{!"clang version 14.0.6"}
!3 = !{i32 7, !"Dwarf Version", i32 5}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !9, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !12)
!9 = !DISubroutineType(types: !10)
!10 = !{!11}
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !{}
!13 = !DILocalVariable(name: "a", scope: !8, file: !1, line: 4, type: !11)
!14 = !DILocation(line: 4, column: 9, scope: !8)
!15 = !DILocalVariable(name: "b", scope: !8, file: !1, line: 4, type: !11)
!16 = !DILocation(line: 4, column: 16, scope: !8)
!17 = !DILocalVariable(name: "p", scope: !8, file: !1, line: 5, type: !18)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!19 = !DILocation(line: 5, column: 10, scope: !8)
!20 = !DILocation(line: 7, column: 7, scope: !8)
!21 = !DILocation(line: 8, column: 7, scope: !8)
!22 = !DILocation(line: 9, column: 13, scope: !8)
!23 = !DILocation(line: 9, column: 12, scope: !8)
!24 = !DILocation(line: 9, column: 5, scope: !8)
