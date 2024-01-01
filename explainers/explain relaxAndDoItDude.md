`setTimeout` is one the functionality is implimented in node and not in js. So we will try to impliment our own and we will call it as `relaxAndDoItDude`

`setTimeout(sleep, interval, () => {})` we will try creating something like this.

- Step1) create class in `app/src` and create class file `relaxAndDoItDude.hpp`
  - Then add headers as ![Alt text](image.png)
  - To do anything first we need event loop i.e. `uv_loop_t`
  - Then we will add `Initialize` method and assign event loop to local `loop`. This will be static method.![Alt text](image-1.png)
  - Then we need to define our custom CPP `RelaxAndDoItDude` method. This also will be static.
    - We will take reference of `SayThatDude` from `app\src\dudeJS.hpp` for what the signature of that function should look like![Alt text](image-2.png)
    - And craete a similer function signature for `RelaxAndDoItDude` ![Alt text](image-3.png)
  - Now we will bind our CPP `RelaxAndDoItDude` with `relaxAndDoItDude` keyword like how we did for `sayThatDude` in `app\src\dudeJS.hpp`
    - include the header of `relaxAndDoItDude.hpp`  in `app\src\dudeJS.hpp` ![Alt text](image-4.png)
    - and then bind keyword `relaxAndDoItDude` with `RelaxAndDoItDude` by adding Bindings wo global object
      - first we create instance by ![Alt text](image-6.png).
      - Then initialize the loop with default loop ![Alt text](image-7.png)
      - Then add bindings ![Alt text](image-8.png)
    - Now to test this lets try running by running `make build` and `make run` ![Alt text](image-9.png) 
    - You will see the output that means it is correctly binded. ![Alt text](image-10.png)
    - Now we will Get arguments using isolate, context, and parameters
      - isolate is our context on v8 and from isolate we get our context ![Alt text](image-11.png)
      - Now we will get our parameters i.e. first argument `sleep` and second argument `interval` and we will try to print them![Alt text](image-12.png)
      - Try rerunning by ![Alt text](image-14.png)
      - We will see output as ![Alt text](image-13.png) that means we are getting args as we needed.
      - Now we will try to get third arg i.e. callback. first we parse it to string as Utf8Value.. then give name as callbackStr and get args and print that string.  ![Alt text](image-17.png)
      - lets try running index.js with this example ![Alt text](image-15.png)
      - You'll see output as ![Alt text](image-16.png)
    - Now the next part is Implementing a timeout function
      - Lets create `struct` which kind of like a class and `uvTimer` as one of its property ![Alt text](image-18.png)
      - instantiate that `struct` ![Alt text](image-19.png)
      - the `uv_timer_init` will take this `uvTimer` and initialize it which will pass later to the `uv_timer_start`
      - ![Alt text](image-20.png)
      - we will use `uv_timer_init` which initialize the timer and it takes event loop as input param and uvTimer of type `uv_timer_t`
      - `uv_timer_start` which starts the timer and it takes the callback which to be called, how much time it should sleep for and the interval
      - Now if we run this example in index.js ![Alt text](image-21.png)
      - you'll see it'll first print ![Alt text](image-22.png) and after it'll print ![Alt text](image-23.png) That means timer is working fine..Its not calling our callback but the onTimerCallback![Alt text](image-24.png)
    - Now lets try working on our calling our own callback function that we pass
      - 