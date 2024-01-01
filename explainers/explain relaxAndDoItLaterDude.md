`setTimeout` is one the functionality is implimented in node and not in js. So we will try to impliment our own and we will call it as `relaxAndDoItLaterDude`

`relaxAndDoItLaterDude(sleep, interval, () => {})` we will try creating something like this.


# What and how was my thought process 
- create class in `app/src` and create class file `relaxAndDoItLaterDude.hpp`
- Then add headers as ![Alt text](image.png)
- To do anything first we need event loop i.e. `uv_loop_t`
- Then we will add `Initialize` method and assign event loop to local `loop`. This will be static method.![Alt text](image-1.png)
- Then we need to define our custom CPP `RelaxAndDoItLaterDude` method. This also will be static.
  - We will take reference of `SayThatDude` from `app\src\dudeJS.hpp` for what the signature of that function should look like![Alt text](image-2.png)
  - And craete a similer function signature for `RelaxAndDoItLaterDude` ![Alt text](image-3.png)
- Now we will bind our CPP `RelaxAndDoItLaterDude` with `relaxAndDoItLaterDude` keyword like how we did for `sayThatDude` in `app\src\dudeJS.hpp`
  - include the header of `relaxAndDoItLaterDude.hpp`  in `app\src\dudeJS.hpp` ![Alt text](image-4.png)
  - and then bind keyword `relaxAndDoItLaterDude` with `RelaxAndDoItLaterDude` by adding Bindings wo global object
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
    - We need to store the function that we pass and execute it. For this we will need to create context for it also.
    - So we create isolate and place to store the function for that we need global state cause if we dont use it v8 will remove it. We will do this in `struct`![Alt text](image-25.png)
    - We will be resetting the instance of `struct` as it has instance by default. Also we wont use this ![Alt text](image-26.png) we creted before so can comment it. We will create new variable for storing the callback function from 3rd argument by `v8::Local<v8::Value> callback = args[2];` `Local` indicates that it will only work on local context ![Alt text](image-27.png)
    - Also lets check if call back is function if not we will return ![Alt text](image-28.png)
    - Notice while resetting we are casting callback to function ![Alt text](image-29.png) 
    - Now `uvTimer` has data proeprty where we need to pass the data that we created in our `struct` so we can do that by assigning `timerWrap` to `uvTimerd.data`![Alt text](image-30.png)
    - We access this data in `onTimerCallback` by `handle` as its nothing but `uvTimer` and create pointer `*timerWrap` to access it ![Alt text](image-31.png)
    - Also we access isolate same way as above and create a context ![Alt text](image-32.png)
    - we create ne function by `New` with our isolate and callback![Alt text](image-33.png)
    - Now we call our callback
      - in order to call it we need to pass ![Alt text](image-34.png)
      - we call it like this![Alt text](image-35.png) and it returns a boolean so we add it in if loop
      - ![Alt text](image-36.png)
    - Now if we run below example in index.js ![Alt text](image-37.png)
    - It will call the actual call back function that we send![Alt text](image-38.png)
    - We can run nested examples as well like these ![Alt text](image-39.png)


## We can create our own setTimeout
- `setTimeout` is nothing but `relaxAndDoItLaterDude` with 0 interval. So defination looks like this
- `setInterval` is nothign but sleep of 0 
- ![Alt text](image-40.png)
