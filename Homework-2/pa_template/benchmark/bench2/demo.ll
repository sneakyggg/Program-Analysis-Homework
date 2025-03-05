; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !8 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !16, metadata !DIExpression()), !dbg !17
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !18, metadata !DIExpression()), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %6, metadata !20, metadata !DIExpression()), !dbg !21
  %7 = load i32, i32* %4, align 4, !dbg !22
  store i32 %7, i32* %6, align 4, !dbg !21
  %8 = load i32, i32* %6, align 4, !dbg !23
  %9 = add nsw i32 %8, 1, !dbg !24
  ret i32 %9, !dbg !25
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3, !4, !5, !6, !7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/home/cs6890/CS5890-6890-Program-Analysis/pa_template/benchmark/bench2", checksumkind: CSK_MD5, checksum: "d2d53e5b5846f4d2db44e2959a1d18de")
!2 = !{!"clang version 14.0.6"}
!3 = !{i32 7, !"Dwarf Version", i32 5}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 5, type: !9, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!9 = !DISubroutineType(types: !10)
!10 = !{!11, !11, !12}
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!14 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!15 = !{}
!16 = !DILocalVariable(name: "argc", arg: 1, scope: !8, file: !1, line: 5, type: !11)
!17 = !DILocation(line: 5, column: 14, scope: !8)
!18 = !DILocalVariable(name: "argv", arg: 2, scope: !8, file: !1, line: 5, type: !12)
!19 = !DILocation(line: 5, column: 26, scope: !8)
!20 = !DILocalVariable(name: "a", scope: !8, file: !1, line: 7, type: !11)
!21 = !DILocation(line: 7, column: 9, scope: !8)
!22 = !DILocation(line: 7, column: 13, scope: !8)
!23 = !DILocation(line: 8, column: 13, scope: !8)
!24 = !DILocation(line: 8, column: 15, scope: !8)
!25 = !DILocation(line: 8, column: 5, scope: !8)
