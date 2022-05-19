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


t:
db 1,0,5,25,"t"
times(16-($-t)) db 0


mytxt:
db 2,0,1,30,"txt"
times(16-($-mytxt)) db 0

times(512-($-files)) db 0