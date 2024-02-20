; ModuleID = 'deviant'
source_filename = "deviant"

@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

declare i32 @printf(ptr, ...)

define i32 @monkey() {
entry:
  %x = alloca i32, align 4
  store i32 12345, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  ret i32 %x1
}

define i32 @main() {
entry:
  %b = alloca i32, align 4
  store i32 1, ptr %b, align 4
  br i1 true, label %then, label %else
  %printfCall = call i32 (ptr, ...) @printf(ptr @0, i32 %b1)
  ret i32 0

then:                                             ; preds = %entry
  store i32 2, ptr %b, align 4
  br label %merge

else:                                             ; preds = %entry
  store i32 3, ptr %b, align 4
  br label %merge

merge:                                            ; preds = %else, %then
  %b1 = load i32, ptr %b, align 4
}
