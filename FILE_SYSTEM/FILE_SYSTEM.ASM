files:

hello_world:
db 1,0,1,7,"Hello World"
times(16-($-hello_world)) db 0

times(512-($-files)) db 0