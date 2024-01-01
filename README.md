<p align="center">
  <img src="https://github.com/ghost8395/dudeJS/assets/56686391/c7713b9a-b388-40b4-a069-ab28621004da" />
</p>

I have created my own JavaScript Runtime using V8, Libuv, and more. dudeJS is a JavaScript runtime built on top of [V8 Javascript Engine](https://github.com/v8/v8) and [Libuv](https://github.com/libuv/libuv). This repo is about recreating the mighty Node.js from Scratch using V8, Libuv, and C++



## Overview
- I wanted to create a nodejs platform from scratch, compile the libraries and write the C++ source code myself to confirm whether the nodejs concepts I learned were correct (they weren't 😂). This was very necessary as there's a lot of content for beginners but not so much for advanced/deep learning. Building Node.js from scratch really helped me wash away many misconceptions and gain a deeper level of understanding of how node actually even works.

- Ever wondered why there are so many javascript runtimes popping up suddenly recently such as Bun, Deno, cloudfare workers, and so on? This has become so popular that to an extent there is a community that provides a space for JS runtimes to collaborate on API interoperability which is https://wintercg.org/ .
- Nodejs is just a proxy for v8 that extends its behavior. So that extension of the behavior is where the difference lies and that's why so many JS runtimes. To build nodejs it is important to understand what nodejs is in the first place. We all know that V8 is responsible for interpreting your code and executing it but it does more than that, it converts your JS code into C++ object instances. And that is one of the things which I have tried doing it. Interesting fact is that neither console.log, setTimeout nor setInterval part of JS specs, JS only knows ECMA.
- As part of this project I have tried implementing these functionalities. 
  - Such as for console.log, the Print. So whenever we call this function from js file the engine will take it as a JS function and call the C++ function that we have written for it. And that is how the things Crypto, FS, Child processes are only exists in Nodejs, they are implemented on top of V8. That's where runtimes Bun & Deno excel as they handle stuff like this differently.
  - Like I said functions like setTimeout, setInterval, and setImmidiate are not part of JS and as they are async in nature they handled by whole another library i.e. libuv. This library is mainly responsible for Async functions, Child Processes, Threads, Timers, & Event Loop. Libuv enables us to run these functions in the background and call the callback function we provided once done.
