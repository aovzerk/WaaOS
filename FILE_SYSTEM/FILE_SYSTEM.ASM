files:

point = 1

kernel:
size = 2
db 1,0,size,point,"kernel"
point = point + size
times(16-($-kernel)) db 0

hello_world:
size = 1
db 1,0,size,point,"Hello World"
point = point + size
times(16-($-hello_world)) db 0

hello2:
size = 4
db 1,0,size,point,"hello2"
point = point + size
times(16-($-hello2)) db 0

ls:
size = 4
db 1,0,size,point,"ls"
point = point + size
times(16-($-ls)) db 0

calc:
size = 4
db 1,0,size,point,"calc"
point = point + size
times(16-($-calc)) db 0

f_info:
size = 6
db 1,0,size,point,"f_info"
point = point + size
times(16-($-f_info)) db 0

txt:
size = 1
db 2,0,size,point,"txt"
point = point + size
times(16-($-txt)) db 0

gui:
size = 7
db 1,0,size,point,"gui"
point = point + size
times(16-($-gui)) db 0

poff:
size = 4
db 1,0,size,point,"poweroff"
point = point + size
times(16-($-poff)) db 0

cmd:
size = 6
db 1,0,size,point,"cmd"
point = point + size
times(16-($-cmd)) db 0

d_bmp:
size = 6
db 1,0,size,point,"d_bmp"
point = point + size
times(16-($-d_bmp)) db 0

test_bmp:
size = 2
db 3,0,size,point,"test_bmp"
point = point + size
times(16-($-test_bmp)) db 0

test2_bmp:
size = 2
db 3,0,size,point,"test2_bmp"
point = point + size
times(16-($-test2_bmp)) db 0

; test3_bmp:
; size = 49
; db 3,0,size,point,"test3_bmp"
; point = point + size
; times(16-($-test3_bmp)) db 0

vmg:
size = 4
db 1,0,size,point,"vmg"
point = point + size
times(16-($-vmg)) db 0

times(1024-($-files)) db 0