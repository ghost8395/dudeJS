#include <v8.h>
#include <uv.h>

struct timer 
{
    uv_timer_t uvTimer;
};

uv_loop_t *loop;
class Timer 
{
    public:
        static void Initialize(uv_loop_t *evloop)
        {
            loop = evloop;
        }

        static void RelaxAndDoItDude(const v8::FunctionCallbackInfo<v8::Value> &args)
        {
            // isolate is our context on v8 and from isolate we get our context
            auto isolate = args.GetIsolate();
            auto context = isolate->GetCurrentContext();

            // Now we will get our parameters i.e. first argument `sleep` and second argument `interval` and we will try to print them
            int64_t sleep = args[0]->IntegerValue(context).ToChecked();
            int64_t interval = args[1]->IntegerValue(context).ToChecked();
            printf("sleep %lld, interval %lld\n", sleep, interval);

            // Now we will try to get third arg i.e. callback. first we parse it to string as Utf8Value.. then give name as callbackStr and get args and print that string
            v8::String::Utf8Value callbackStr(isolate, args[2]);
            printf("%s", *callbackStr);

            // Now the next part is Implementing a timeout function

            // instantiate the struct
            timer *timerWrap = new timer();

            // the `uv_timer_init` will take this `uvTimer` and initialize it which will pass later to the `uv_timer_start`
            // we will use `uv_timer_init` which initialize the timer and it takes event loop as input param
            uv_timer_init(loop, &timerWrap->uvTimer);
            uv_timer_start(&timerWrap->uvTimer, onTimerCallback, sleep, interval);
        }

        static void onTimerCallback(uv_timer_t *handle)
        {
            printf("onTimerCallback was called");
        }
};