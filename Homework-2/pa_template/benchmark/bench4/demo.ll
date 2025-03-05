; ModuleID = 'demo.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"C\0A\00", align 1
@func = dso_local global void (...)* bitcast (void ()* @B to void (...)*), align 8, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @B() #0 !dbg !14 {
  call void @C(), !dbg !18
  ret void, !dbg !19
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @C() #0 !dbg !20 {
  %1 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0)), !dbg !21
  ret void, !dbg !22
}

declare dso_local i32 @printf(i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 !dbg !23 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  store i32 %0, i32* %3, align 4
  call void @llvm.dbg.declare(metadata i32* %3, metadata !30, metadata !DIExpression()), !dbg !31
  store i8** %1, i8*** %4, align 8
  call void @llvm.dbg.declare(metadata i8*** %4, metadata !32, metadata !DIExpression()), !dbg !33
  %5 = load void (...)*, void (...)** @func, align 8, !dbg !34
  call void (...) %5(), !dbg !34
  ret i32 0, !dbg !35
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.ident = !{!8}
!llvm.module.flags = !{!9, !10, !11, !12, !13}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "func", scope: !2, file: !3, line: 13, type: !5, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !4, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "source/main.c", directory: "/home/cs6890/CS5890-6890-Program-Analysis/pa_template/benchmark/bench4", checksumkind: CSK_MD5, checksum: "8b2f794a699b44b08fe43609128946f1")
!4 = !{!0}
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!6 = !DISubroutineType(types: !7)
!7 = !{null, null}
!8 = !{!"clang version 14.0.6"}
!9 = !{i32 7, !"Dwarf Version", i32 5}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{i32 7, !"uwtable", i32 1}
!13 = !{i32 7, !"frame-pointer", i32 2}
!14 = distinct !DISubprogram(name: "B", scope: !3, file: !3, line: 8, type: !15, scopeLine: 9, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !17)
!15 = !DISubroutineType(types: !16)
!16 = !{null}
!17 = !{}
!18 = !DILocation(line: 10, column: 5, scope: !14)
!19 = !DILocation(line: 11, column: 1, scope: !14)
!20 = distinct !DISubprogram(name: "C", scope: !3, file: !3, line: 3, type: !15, scopeLine: 4, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !17)
!21 = !DILocation(line: 5, column: 5, scope: !20)
!22 = !DILocation(line: 6, column: 1, scope: !20)
!23 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 15, type: !24, scopeLine: 16, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !17)
!24 = !DISubroutineType(types: !25)
!25 = !{!26, !26, !27}
!26 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64)
!29 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!30 = !DILocalVariable(name: "argc", arg: 1, scope: !23, file: !3, line: 15, type: !26)
!31 = !DILocation(line: 15, column: 14, scope: !23)
!32 = !DILocalVariable(name: "argv", arg: 2, scope: !23, file: !3, line: 15, type: !27)
!33 = !DILocation(line: 15, column: 26, scope: !23)
!34 = !DILocation(line: 17, column: 5, scope: !23)
!35 = !DILocation(line: 18, column: 1, scope: !23)
