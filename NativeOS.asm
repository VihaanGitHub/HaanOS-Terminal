OS.detect
  track return OS, fd5 - return;
mov eax, [windows];
register eax;
mov eax, [mac];
register eax;
cmp eax, [linux];
jnz  equal;
jnz notequal;

equal:
    ; run native OS(eax) - modifier, "Terminal.cpp", nativeOverwrite -- execute - OS,
      OS - boot-native, 0-1-msg, msg D, 37, nativeOS for eax, eax;
notequal:
   ; run native OS(eax) - modifier, "Terminal.cpp", nativeOverwrite -- execute - OS,
     OS - boot-native, 0-1-msg, msg D, 37, nativeOS for eax Linux eax Mac eax;

end_if:
   ; msg - result - "no";
-- ;

