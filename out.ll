; ModuleID = 'deviant'
source_filename = "deviant"

@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

declare i32 @printf(ptr, ...)

define i32 @get42() {
entry:
  %printfCall = call i32 (ptr, ...) @printf(ptr @0, i32 42)
  ret i32 42
}

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 1, ptr %x, align 4
  %y = alloca i32, align 4
  store i32 32, ptr %y, align 4
  %0 = call i32 @get42()
  store i32 %0, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  store i32 %x1, ptr %y, align 4
  %printfCall = call i32 (ptr, ...) @printf(ptr @1, i32 1024)
  %y2 = load i32, ptr %y, align 4
  ret i32 %y2
}
