#include "CronTime.cc"
#include <include/cronjob.hh>
#include <napi.h>

class Cronjob : public Napi::ObjectWrap<Cronjob> {
private:
    Napi::Value wait(const Napi::CallbackInfo& info);

public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Cronjob(const Napi::CallbackInfo& info);
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);
};

Cronjob::Cronjob(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Cronjob>(info)
{
    Napi::Env env = info.Env();
    auto obj = info[0].As<Napi::Object>();
}

Napi::Object Cronjob::Init(Napi::Env env, Napi::Object exports)
{
    auto methods = {
        Napi::ObjectWrap<Cronjob>::InstanceMethod("wait", &Cronjob::wait),
    };

    Napi::Function func = Napi::ObjectWrap<Cronjob>::DefineClass(env, "Cronjob", methods);

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("Cronjob", func);
    env.SetInstanceData<Napi::FunctionReference>(constructor);
    return exports;
}

//...

Napi::Value Cronjob::wait(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), 20);
}

Napi::Object InitCronjob(Napi::Env env, Napi::Object exports)
{
    CronTime::Init(env, exports);
    Cronjob::Init(env, exports);
    return exports;
}

Napi::Value Cronjob::CreateNewItem(const Napi::CallbackInfo& info)
{
    Napi::FunctionReference* constructor = info.Env().GetInstanceData<Napi::FunctionReference>();

    return constructor->New({ CronTime::CreateNewItem(info) });
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitCronjob)
