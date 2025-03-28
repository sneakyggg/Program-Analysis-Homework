; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foo(i32* noundef %0) #0 !dbg !8 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !14, metadata !DIExpression()), !dbg !15
  %3 = load i32*, i32** %2, align 8, !dbg !16
  store i32 10, i32* %3, align 4, !dbg !17
  ret void, !dbg !18
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @bar(i32* noundef %0) #0 !dbg !19 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !20, metadata !DIExpression()), !dbg !21
  %3 = load i32*, i32** %2, align 8, !dbg !22
  store i32 20, i32* %3, align 4, !dbg !23
  ret void, !dbg !24
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @execute(void (i32*)* noundef %0, i32* noundef %1) #0 !dbg !25 {
  %3 = alloca void (i32*)*, align 8
  %4 = alloca i32*, align 8
  store void (i32*)* %0, void (i32*)** %3, align 8
  call void @llvm.dbg.declare(metadata void (i32*)** %3, metadata !29, metadata !DIExpression()), !dbg !30
  store i32* %1, i32** %4, align 8
  call void @llvm.dbg.declare(metadata i32** %4, metadata !31, metadata !DIExpression()), !dbg !32
  %5 = load void (i32*)*, void (i32*)** %3, align 8, !dbg !33
  %6 = load i32*, i32** %4, align 8, !dbg !34
  call void %5(i32* noundef %6), !dbg !33
  ret void, !dbg !35
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !36 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca void (i32*)*, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !39, metadata !DIExpression()), !dbg !40
  store i32 5, i32* %2, align 4, !dbg !40
  call void @llvm.dbg.declare(metadata i32* %3, metadata !41, metadata !DIExpression()), !dbg !42
  store i32 15, i32* %3, align 4, !dbg !42
  call void @llvm.dbg.declare(metadata void (i32*)** %4, metadata !43, metadata !DIExpression()), !dbg !45
  store void (i32*)* @foo, void (i32*)** %4, align 8, !dbg !45
  %5 = load void (i32*)*, void (i32*)** %4, align 8, !dbg !46
  call void @execute(void (i32*)* noundef %5, i32* noundef %2), !dbg !47
  store void (i32*)* @bar, void (i32*)** %4, align 8, !dbg !48
  %6 = load void (i32*)*, void (i32*)** %4, align 8, !dbg !49
  call void @execute(void (i32*)* noundef %6, i32* noundef %3), !dbg !50
  ret i32 0, !dbg !51
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3, !4, !5, !6, !7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "source/main.c", directory: "/root/CS5890-6890-Program-Analysis/pa_template/benchmark/bench8", checksumkind: CSK_MD5, checksum: "bbb5b0f754c91938356ca96d71b6feed")
!2 = !{!"clang version 14.0.6"}
!3 = !{i32 7, !"Dwarf Version", i32 5}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = distinct !DISubprogram(name: "foo", scope: !1, file: !1, line: 3, type: !9, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!9 = !DISubroutineType(types: !10)
!10 = !{null, !11}
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64)
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !{}
!14 = !DILocalVariable(name: "x", arg: 1, scope: !8, file: !1, line: 3, type: !11)
!15 = !DILocation(line: 3, column: 15, scope: !8)
!16 = !DILocation(line: 3, column: 21, scope: !8)
!17 = !DILocation(line: 3, column: 23, scope: !8)
!18 = !DILocation(line: 3, column: 28, scope: !8)
!19 = distinct !DISubprogram(name: "bar", scope: !1, file: !1, line: 5, type: !9, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!20 = !DILocalVariable(name: "x", arg: 1, scope: !19, file: !1, line: 5, type: !11)
!21 = !DILocation(line: 5, column: 15, scope: !19)
!22 = !DILocation(line: 5, column: 21, scope: !19)
!23 = !DILocation(line: 5, column: 23, scope: !19)
!24 = !DILocation(line: 5, column: 28, scope: !19)
!25 = distinct !DISubprogram(name: "execute", scope: !1, file: !1, line: 7, type: !26, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!26 = !DISubroutineType(types: !27)
!27 = !{null, !28, !11}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!29 = !DILocalVariable(name: "fptr", arg: 1, scope: !25, file: !1, line: 7, type: !28)
!30 = !DILocation(line: 7, column: 21, scope: !25)
!31 = !DILocalVariable(name: "y", arg: 2, scope: !25, file: !1, line: 7, type: !11)
!32 = !DILocation(line: 7, column: 40, scope: !25)
!33 = !DILocation(line: 8, column: 5, scope: !25)
!34 = !DILocation(line: 8, column: 10, scope: !25)
!35 = !DILocation(line: 9, column: 1, scope: !25)
!36 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 12, type: !37, scopeLine: 12, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!37 = !DISubroutineType(types: !38)
!38 = !{!12}
!39 = !DILocalVariable(name: "a", scope: !36, file: !1, line: 13, type: !12)
!40 = !DILocation(line: 13, column: 9, scope: !36)
!41 = !DILocalVariable(name: "b", scope: !36, file: !1, line: 13, type: !12)
!42 = !DILocation(line: 13, column: 16, scope: !36)
!43 = !DILocalVariable(name: "f", scope: !36, file: !1, line: 14, type: !44)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "FP", file: !1, line: 11, baseType: !28)
!45 = !DILocation(line: 14, column: 8, scope: !36)
!46 = !DILocation(line: 15, column: 13, scope: !36)
!47 = !DILocation(line: 15, column: 5, scope: !36)
!48 = !DILocation(line: 16, column: 7, scope: !36)
!49 = !DILocation(line: 17, column: 13, scope: !36)
!50 = !DILocation(line: 17, column: 5, scope: !36)
!51 = !DILocation(line: 18, column: 5, scope: !36)
