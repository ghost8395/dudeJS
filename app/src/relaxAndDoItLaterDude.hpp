#include <v8.h>
#include <uv.h>

struct timer 
{
    uv_timer_t uvTimer;
    v8::Isolate *isolate;
    v8::Global<v8::Function> callback;
};

uv_loop_t *loop;
class Timer 
{
    public:
        static void Initialize(uv_loop_t *evloop)
        {
            loop = evloop;
        }

        static void RelaxAndDoItLaterDude(const v8::FunctionCallbackInfo<v8::Value> &args)
        {
            // isolate is our context on v8 and from isolate we get our context
            auto isolate = args.GetIsolate();
            auto context = isolate->GetCurrentContext();

            // Now we will get our parameters i.e. first argument `sleep` and second argument `interval` and we will try to print them
            int64_t sleep = args[0]->IntegerValue(context).ToChecked();
            int64_t interval = args[1]->IntegerValue(context).ToChecked();
            // printf("sleep %lld, interval %lld\n", sleep, interval);

            // Now we will try to get third arg i.e. callback. first we parse it to string as Utf8Value.. then give name as callbackStr and get args and print that string
            // v8::String::Utf8Value callbackStr(isolate, args[2]);
            // printf("%s", *callbackStr);

            // Now the next part is Implementing a timeout function


            v8::Local<v8::Value> callback = args[2];
            // lets check if call back is function if not we will return 
            if(!callback->IsFunction()) 
            {
                printf("callback not declared!");
                return;
            }


            // instantiate the struct
            timer *timerWrap = new timer();
            // We will be resetting the instance of `struct` as it has instance by default. Also we are passing isolate  and callback 
            timerWrap->callback.Reset(isolate, callback.As<v8::Function>());

            // Now `uvTimer` has data proeprty where we need to pass the data that we created in our `struct` so we can do that by assigning `timerWrap` to `uvTimerd.data`
            timerWrap->uvTimer.data = (void *)timerWrap;
            timerWrap->isolate = isolate;
            

            // the `uv_timer_init` will take this `uvTimer` and initialize it which will pass later to the `uv_timer_start`
            // we will use `uv_timer_init` which initialize the timer and it takes event loop as input param
            uv_timer_init(loop, &timerWrap->uvTimer);
            uv_timer_start(&timerWrap->uvTimer, onTimerCallback, sleep, interval);
        }

        static void onTimerCallback(uv_timer_t *handle)
        {
            // We access this data in `onTimerCallback` by `handle` as its nothing but `uvTimer` and create pointer `*timerWrap` to access it
             timer *timerWrap = (timer *)handle->data;

            //  Also we access isolate same way as above
            v8::Isolate *isolate = timerWrap->isolate;

            // create a context
            v8::Local<v8::Context> context = isolate->GetCurrentContext();

            // we create ne function by New with our isolate and callback
            v8::Local<v8::Function> callback = v8::Local<v8::Function>::New(
                isolate,
                timerWrap->callback
            );

            // Now we call our callback

            // in order to call it we need to pass below
            v8::Local<v8::Value> result;
            v8::Handle<v8::Value> resultr [] = {
                v8::Undefined(isolate),
                v8_str("Call back being called successfully")
            };

            // callback->Call returns boolean so putting it in if loop
            if(callback->Call(
                context,
                v8::Undefined(isolate),
                2,
                resultr).ToLocal(&result)
            ) 
            {
                // OK, the callback succeeded
            }
            else 
            {
                // some exception happened
            }
        }

        static inline v8::Local<v8::String> v8_str(const char *x)
        {
            return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), x).ToLocalChecked();
        }
};