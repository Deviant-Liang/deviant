; ModuleID = 'deviant'
source_filename = "deviant"

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
  %a = alloca i32, align 4
  store i32 2, ptr %a, align 4
  br i1 true, label %then, label %else2

then:                                             ; preds = %entry
  store i32 2, ptr %b, align 4
  store i32 0, ptr %a, align 4
  br i1 true, label %then1, label %else

then1:                                            ; preds = %then
  store i32 1, ptr %a, align 4
  store i32 1, ptr %b, align 4
  br label %merge

else:                                             ; preds = %then
  br label %merge

merge:                                            ; preds = %else, %then1
  br label %merge3

else2:                                            ; preds = %entry
  br label %merge3

merge3:                                           ; preds = %else2, %merge
}
