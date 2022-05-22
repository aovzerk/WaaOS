files:

hello_world:
db 1,0,1,6,"Hello World"
times(16-($-hello_world)) db 0

ls:
db 1,0,1,7,"ls"
times(16-($-ls)) db 0

hello2:
db 1,0,6,8,"hello2"
times(16-($-hello2)) db 0

ls2:
db 1,0,6,14,"ls2"
times(16-($-ls2)) db 0

calc:
db 1,0,7,20,"calc"
times(16-($-calc)) db 0


f_info:
db 1,0,11,27,"f_info"
times(16-($-f_info)) db 0


txt:
db 2,0,1,38,"txt"
times(16-($-txt)) db 0

gui2:
db 1,0,11,39,"gui2"
times(16-($-gui2)) db 0

poff:
db 1,0,5,50,"poweroff"
times(16-($-poff)) db 0

cmd:
db 1,0,11,55,"cmd"
times(16-($-cmd)) db 0

d_bmp:
db 1,0,7,66,"d_bmp"
times(16-($-d_bmp)) db 0

test_bmp:
db 2,0,4,73,"test_bmp"
times(16-($-test_bmp)) db 0

test2_bmp:
db 2,0,4,77,"test2_bmp"
times(16-($-test2_bmp)) db 0

times(512-($-files)) db 0