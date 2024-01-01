<p align="center">
  <img src="https://github.com/ghost8395/dudeJS/assets/56686391/c7713b9a-b388-40b4-a069-ab28621004da" />
</p>

Introducing dudeJS, my very own JavaScript Runtime! Powered by the incredible V8 Javascript Engine and Libuv, this runtime is a labor of love. With a foundation built on V8, Libuv, and C++, I've set out to recreate the powerful Node.js from scratch. Join me on this exciting journey as we dive deep into the world of JavaScript runtime development.


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
- `index.js` is the file where you can utilize the function that I have created and play around with it.. Be careful though its very awesome.😁

### Running on local
- For running on local you need to compile the binaries by yourself. I have left the instructions in `explainers\explain create binaries yourself.md`

## Understand how things work and how I have built it.
- I have left detailed explainers in `explainers` folder. You can use Gitpod snapshot to try your own thing.



## Why I have created this
- You see, I've always had this burning desire to dive deep into NodeJS and truly understand its inner workings. I wanted to go beyond the beginner level and explore the advanced concepts. So, I decided to create my own NodeJS platform from scratch.
- I started by compiling the necessary libraries and writing the C++ source code myself. Let me tell you, it was no easy task. Along the way, I realized that some of the concepts I had learned about NodeJS were actually misconceptions. But hey, that's all part of the learning process, right? 😂
- Building NodeJS from scratch allowed me to gain a deeper level of understanding. I got to see firsthand how NodeJS works and how it extends the behavior of V8, the JavaScript runtime. It's fascinating to think about all the different JavaScript runtimes out there, like Bun, Deno, and Cloudflare workers. They all create their own JS runtimes from scratch, each with their own unique twist. This has become so popular that to an extent there is a community that provides a space for JS runtimes to collaborate on API interoperability which is https://wintercg.org/ .
- Nodejs is just a proxy for v8 that extends its behavior. So that extension of the behavior is where the difference lies and that's why so many JS runtimes. To build nodejs it is important to understand what nodejs is in the first place. We all know that V8 is responsible for interpreting your code and executing it but it does more than that, it converts your JS code into C++ object instances. And that is one of the things which I have tried doing it. Interesting fact is that neither console.log, setTimeout nor setInterval part of JS specs, JS only knows ECMA.
- As part of this project I have tried implementing these functionalities.
  - For instance, consider the usage of console.log, the `sayThatDude` function. Whenever we invoke this function from a JavaScript file, the engine recognizes it as a JavaScript function and executes the corresponding C++ function. This is how functionalities like Crypto, FS, and Child processes exist solely in Node.js, as they are built on top of the V8 engine. However, when it comes to runtimes like Bun and Deno, they excel in handling such tasks in a distinct manner.
  - I've developed a function called `relaxAndDoItLaterDude` that accepts parameters such as `sleep`, `interval`, and a callback method. Unlike JavaScript's built-in functions like setTimeout, setInterval, and setImmediate, which are asynchronous in nature, they are actually handled by a separate library called libuv. This powerful library, known for its capabilities in handling async functions, child processes, threads, timers, and event loops, allows us to run these functions in the background and execute the provided callback function once they are completed.
