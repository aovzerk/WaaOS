files:

hello_world:
db 1,0,1,6,"Hello World"
times(16-($-hello_world)) db 0

ls:
db 1,0,1,7,"ls"
times(16-($-ls)) db 0


gui:
db 1,0,2,8,"gui"
times(16-($-gui)) db 0

hello2:
db 1,0,5,10,"hello2"
times(16-($-hello2)) db 0

ls2:
db 1,0,5,15,"ls2"
times(16-($-ls2)) db 0

calc:
db 1,0,5,20,"calc"
times(16-($-calc)) db 0


f_info:
db 1,0,10,25,"f_info"
times(16-($-f_info)) db 0


txt:
db 2,0,1,35,"txt"
times(16-($-txt)) db 0

times(512-($-files)) db 0