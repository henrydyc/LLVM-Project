; ModuleID = 'all.bc'
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.10.0"

%struct.timeval = type { i64, i32 }

@.str = private unnamed_addr constant [19 x i8] c"Temp variable: %d\0A\00", align 1
@.str1 = private unnamed_addr constant [28 x i8] c"Run time: %lu microseconds\0A\00", align 1

; Function Attrs: nounwind ssp uwtable
define i32 @use_var(i32 %a, i32 %b) #0 {
entry:
  %add = add nsw i32 %b, %a
  ret i32 %add
}

; Function Attrs: nounwind ssp uwtable
define i32 @reassociate(i32 %num1, i32 %num2, i32 %dead_arg) #0 {
entry:
  %sub4 = add i32 %num2, %num1
  ret i32 %sub4
}

; Function Attrs: nounwind ssp uwtable
define i32 @main() #0 {
entry:
  %start_time = alloca %struct.timeval, align 8
  %end_time = alloca %struct.timeval, align 8
  %dead_arr = alloca [100 x [100 x i32]], align 16
  %call = call i32 @gettimeofday(%struct.timeval* %start_time, i8* null)
  br label %for.cond

for.cond:                                         ; preds = %for.inc19, %entry
  %i.0 = phi i64 [ 0, %entry ], [ %inc20, %for.inc19 ]
  %temp.0 = phi i32 [ undef, %entry ], [ %temp.1.lcssa, %for.inc19 ]
  %exitcond9 = icmp ne i64 %i.0, 10000
  br i1 %exitcond9, label %for.body, label %for.end21

for.body:                                         ; preds = %for.cond
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc16, %for.body
  %lsr.iv14 = phi i32 [ %lsr.iv.next15, %for.inc16 ], [ 30, %for.body ]
  %lsr.iv10 = phi [100 x [100 x i32]]* [ %1, %for.inc16 ], [ %dead_arr, %for.body ]
  %indvars.iv4 = phi i64 [ %indvars.iv.next5, %for.inc16 ], [ 0, %for.body ]
  %temp.1 = phi i32 [ %temp.0, %for.body ], [ %temp.2.lcssa, %for.inc16 ]
  %exitcond8 = icmp ne i64 %indvars.iv4, 100
  br i1 %exitcond8, label %for.body3, label %for.end18

for.body3:                                        ; preds = %for.cond1
  br label %for.cond4

for.cond4:                                        ; preds = %for.inc, %for.body3
  %lsr.iv16 = phi i32 [ %lsr.iv.next17, %for.inc ], [ %lsr.iv14, %for.body3 ]
  %lsr.iv11 = phi [100 x [100 x i32]]* [ %0, %for.inc ], [ %lsr.iv10, %for.body3 ]
  %lsr.iv = phi i64 [ %lsr.iv.next, %for.inc ], [ 100, %for.body3 ]
  %temp.2 = phi i32 [ %temp.1, %for.body3 ], [ %lsr.iv16, %for.inc ]
  %lsr.iv1113 = bitcast [100 x [100 x i32]]* %lsr.iv11 to i32*
  %exitcond = icmp ne i64 %lsr.iv, 0
  br i1 %exitcond, label %for.body7, label %for.end

for.body7:                                        ; preds = %for.cond4
  store i32 %lsr.iv16, i32* %lsr.iv1113, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body7
  %lsr.iv.next = add i64 %lsr.iv, -1
  %scevgep12 = getelementptr [100 x [100 x i32]]* %lsr.iv11, i64 0, i64 0, i64 1
  %0 = bitcast i32* %scevgep12 to [100 x [100 x i32]]*
  %lsr.iv.next17 = add nuw i32 %lsr.iv16, 8
  br label %for.cond4

for.end:                                          ; preds = %for.cond4
  %temp.2.lcssa = phi i32 [ %temp.2, %for.cond4 ]
  br label %for.inc16

for.inc16:                                        ; preds = %for.end
  %indvars.iv.next5 = add nuw nsw i64 %indvars.iv4, 1
  %scevgep = getelementptr [100 x [100 x i32]]* %lsr.iv10, i64 0, i64 1, i64 0
  %1 = bitcast i32* %scevgep to [100 x [100 x i32]]*
  %lsr.iv.next15 = add nuw i32 %lsr.iv14, 4
  br label %for.cond1

for.end18:                                        ; preds = %for.cond1
  %temp.1.lcssa = phi i32 [ %temp.1, %for.cond1 ]
  br label %for.inc19

for.inc19:                                        ; preds = %for.end18
  %inc20 = add nsw i64 %i.0, 1
  br label %for.cond

for.end21:                                        ; preds = %for.cond
  %temp.0.lcssa = phi i32 [ %temp.0, %for.cond ]
  %call22 = call i32 @gettimeofday(%struct.timeval* %end_time, i8* null)
  %tv_sec = getelementptr inbounds %struct.timeval* %end_time, i32 0, i32 0
  %2 = load i64* %tv_sec, align 8
  %conv = sitofp i64 %2 to double
  %mul23 = fmul double 1.000000e+06, %conv
  %tv_usec = getelementptr inbounds %struct.timeval* %end_time, i32 0, i32 1
  %3 = load i32* %tv_usec, align 4
  %conv24 = sitofp i32 %3 to double
  %add25 = fadd double %mul23, %conv24
  %tv_sec26 = getelementptr inbounds %struct.timeval* %start_time, i32 0, i32 0
  %4 = load i64* %tv_sec26, align 8
  %conv27 = sitofp i64 %4 to double
  %mul28 = fmul double 1.000000e+06, %conv27
  %tv_usec29 = getelementptr inbounds %struct.timeval* %start_time, i32 0, i32 1
  %5 = load i32* %tv_usec29, align 4
  %conv30 = sitofp i32 %5 to double
  %add31 = fadd double %mul28, %conv30
  %sub = fsub double %add25, %add31
  %conv32 = fptosi double %sub to i64
  %call33 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([19 x i8]* @.str, i32 0, i32 0), i32 %temp.0.lcssa)
  %call34 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([28 x i8]* @.str1, i32 0, i32 0), i64 %conv32)
  ret i32 0
}

declare i32 @gettimeofday(%struct.timeval*, i8*) #1

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind ssp uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (tags/RELEASE_350/final)"}
