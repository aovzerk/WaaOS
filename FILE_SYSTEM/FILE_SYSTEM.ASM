files:

hello_world:
db 1,0,1,7,"Hello World"
times(16-($-hello_world)) db 0

ls:
db 1,0,1,8,"ls"
times(16-($-ls)) db 0


gui:
db 1,0,2,9,"gui"
times(16-($-gui)) db 0

hello2:
db 1,0,1,11,"hello2"
times(16-($-hello2)) db 0

times(512-($-files)) db 0