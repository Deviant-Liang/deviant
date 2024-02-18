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
  %0 = call i32 @monkey()
  %printfCall = call i32 (ptr, ...) @printf(ptr @0, i32 %0)
  ret i32 0
}
