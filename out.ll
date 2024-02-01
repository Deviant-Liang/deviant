; ModuleID = 'deviant'
source_filename = "deviant"

@0 = private unnamed_addr constant [15 x i8] c"Hello, world!\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @0, ptr @0)
  ret i32 0
}
