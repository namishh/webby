simple web server in c.

status: kinda stable

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
- [ ] a somewhat bad implmentation of the routing

### todo / future plans
- [x] fix the life of the server
- [x] get requests 
- [x] get it to render bytes
- [x] post requests 
- [x] fix getting content-length
- [x] somehow send json data
- [x] get css and js working

after that i would probably seem to make it a functional web app out of it. <br>
something like a todo app. after deciding i will update this todo list for further goals.

### credits 
- my friend [DitherWither](https://github.com/DitherWither) for helping me out with the code and his amazing [repo](https://github.com/DitherWither/etchteateapee/)/
- [Beej's guide to network programming](https://beej.us/guide/bgnet/html/) 
- Eric O Meehan's [yt channel](https://www.youtube.com/@eom-dev)
- [dev.to tutorial](https://dev.to/jeffreythecoder/how-i-built-a-simple-http-server-from-scratch-using-c-739) by [jeffreythecoder](https://dev.to/jeffreythecoder)
