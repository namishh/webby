simple web server in c.

status: kinda stable


https://github.com/chadcat7/webby/assets/68964499/1c9316c6-8bbf-421a-b996-80f9aeb34938

### usage 

```bash
$ make 
$ ./build/main.out
```

### so what is good about this server 
- [x] it does not crash 
- [x] it can serve html, css, js, images, etc
- [x] it can reply with json as well
- [x] can handle CRUD operations
- [x] static routing

### what is bad about this server
- [ ] no dynamic routing
- [ ] not multi-threaded
- [ ] a somewhat bad implementation of the routing

### todo / future plans
- [x] fix the life of the server
- [x] get requests 
- [x] get it to render bytes
- [x] post requests 
- [x] fix getting content-length
- [x] somehow send json data
- [x] get css and js working


- [x] todo front end 
- [x] todo back end 
- [x] some how connect the front end and back end

### credits 
- my friend [DitherWither](https://github.com/DitherWither) for helping me out with the code and his amazing [repo](https://github.com/DitherWither/etchteateapee/) 
- [Beej's guide to network programming](https://beej.us/guide/bgnet/html/) 
- Eric O Meehan's [yt channel](https://www.youtube.com/@eom-dev)
- [dev.to tutorial](https://dev.to/jeffreythecoder/how-i-built-a-simple-http-server-from-scratch-using-c-739) by [jeffreythecoder](https://dev.to/jeffreythecoder)
