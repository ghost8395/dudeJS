<p align="center">
  <img src="https://github.com/ghost8395/dudeJS/assets/56686391/c7713b9a-b388-40b4-a069-ab28621004da" />
</p>

I have created my own JavaScript Runtime using V8, Libuv, and more. dudeJS is a JavaScript runtime built on top of [V8 Javascript Engine](https://github.com/v8/v8) and [Libuv](https://github.com/libuv/libuv). This repo is about recreating the mighty Node.js from Scratch using V8, Libuv, and C++


## What I have built
- I have created my own implimentation of `console.log` as its not part of ECMA, its something that we build on top of v8. I'm calling it `sayThatDude` and works similer as that of console log.
- I have created my own implimentation of `setTimeOut` as its not part of ECMA, its something that we build on top of v8. I'm calling it `relaxAndDoItLaterDude` and it takes `sleep`, `interval` and a callback method as an argument.

## How to run and try these things
- You can skip all the hastle of dependancy installation and use the [Gitpod snapshot](https://gitpod.io#snapshot/b2764759-2f5f-4c71-a69a-748155040914). Its like running my VS code in cloud. You need to login with your github account. Dont worry its free 😅
- Click HERE 👉 [Gitpod snapshot](https://gitpod.io#snapshot/b2764759-2f5f-4c71-a69a-748155040914)
- Signing in step
- 
https://github.com/ghost8395/dudeJS/assets/56686391/f02c6bdf-edc8-4528-8a34-e3e5ed2e6bc0

- open snapshot

https://github.com/ghost8395/dudeJS/assets/56686391/66891d32-5c98-4c82-aa61-24bd4f9173d7

- Run `make build` and then run `make run`

https://github.com/ghost8395/dudeJS/assets/56686391/8bcac816-e9e0-487b-ad28-56579b40ad99


- navigate to `index.js` where I have left few examples to play with.
- `make run` internally runs `nodemon -e cc,h,js,cpp,hpp --exec "make recompile && ./bin/dudeJS index.js"` watches all the files with cc,h,js,cpp,hpp and recompiles the project

### Running on local
- For running on local you need to compile the binaries by yourself. I have left the instructions in `explainers\explain create binaries yourself.md`

## Understand how things work and how I have built it.
- I have left detailed explainers in `explainers` folder. You can use Gitpod snapshot to try your own thing.



## Why I have created this
- I wanted to create a nodejs platform from scratch, compile the libraries and write the C++ source code myself to confirm whether the nodejs concepts I learned were correct (they weren't 😂). This was very necessary as there's a lot of content for beginners but not so much for advanced/deep learning. Building Node.js from scratch really helped me wash away many misconceptions and gain a deeper level of understanding of how node actually even works.

- Ever wondered why there are so many javascript runtimes popping up suddenly recently such as Bun, Deno, cloudfare workers, and so on? This has become so popular that to an extent there is a community that provides a space for JS runtimes to collaborate on API interoperability which is https://wintercg.org/ .
- Nodejs is just a proxy for v8 that extends its behavior. So that extension of the behavior is where the difference lies and that's why so many JS runtimes. To build nodejs it is important to understand what nodejs is in the first place. We all know that V8 is responsible for interpreting your code and executing it but it does more than that, it converts your JS code into C++ object instances. And that is one of the things which I have tried doing it. Interesting fact is that neither console.log, setTimeout nor setInterval part of JS specs, JS only knows ECMA.
- As part of this project I have tried implementing these functionalities.
  - Such as for console.log, the `sayThatDude`. So whenever we call this function from js file the engine will take it as a JS function and call the C++ function that we have written for it. And that is how the things Crypto, FS, Child processes are only exists in Nodejs, they are implemented on top of V8. That's where runtimes Bun & Deno excel as they handle stuff like this differently.
  - I have created `relaxAndDoItLaterDude` which takes `sleep`, `interval` and a callback method as an argument. Functions like setTimeout, setInterval, and setImmidiate are not part of JS and as they are async in nature they handled by whole another library i.e. libuv. This library is mainly responsible for Async functions, Child Processes, Threads, Timers, & Event Loop. Libuv enables us to run these functions in the background and call the callback function we provided once done.
  
