; ModuleID = 'deviant'
source_filename = "deviant"

declare i32 @print(ptr, ...)

define i32 @get42() {
entry:
  ret i32 42
}

define i32 @main() {
entry:
  %0 = call i32 @get42()
  ret i32 0
}
