#include <include/CronTime.hh>
#include <napi.h>

class CronTime : public Napi::ObjectWrap<CronTime> {
private:
    Cron::CronTime cronTime;
    Napi::Value GetWeaks(const Napi::CallbackInfo& info);
    Napi::Value GetDays(const Napi::CallbackInfo& info);
    Napi::Value GetHours(const Napi::CallbackInfo& info);
    Napi::Value GetMinutes(const Napi::CallbackInfo& info);
    Napi::Value GetSeconds(const Napi::CallbackInfo& info);

    Napi::Value SetWeaks(const Napi::CallbackInfo& info);
    Napi::Value SetDays(const Napi::CallbackInfo& info);
    Napi::Value SetHours(const Napi::CallbackInfo& info);
    Napi::Value SetMinutes(const Napi::CallbackInfo& info);
    Napi::Value SetSeconds(const Napi::CallbackInfo& info);

public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    CronTime(const Napi::CallbackInfo& info);
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);
};

Napi::Object CronTime::Init(Napi::Env env, Napi::Object exports)
{
    auto methods = {
        InstanceMethod<&CronTime::GetWeaks>("GetWeaks", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::GetDays>("GetDays", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::GetHours>("GetHour", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::GetMinutes>("GetMinutes", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::GetSeconds>("GetSeconds", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),

        InstanceMethod<&CronTime::SetWeaks>("SetWeaks", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::SetDays>("SetDays", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::SetHours>("SetHour", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::SetMinutes>("SetMinutes", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&CronTime::SetSeconds>("SetSeconds", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
    };
    Napi::Function func = DefineClass(env, "CronTime", methods);

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("CronTime", func);
    env.SetInstanceData<Napi::FunctionReference>(constructor);
    return exports;
}

CronTime::CronTime(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CronTime>(info)
{
    Napi::Env env = info.Env();
    Cron::CronTime time;
    this->cronTime = time;
}

Napi::Value CronTime::GetWeaks(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->cronTime.GetWeaks());
}

Napi::Value CronTime::GetDays(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->cronTime.GetDays());
}

Napi::Value CronTime::GetHours(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->cronTime.GetHours());
}

Napi::Value CronTime::GetMinutes(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->cronTime.GetMinutes());
}

Napi::Value CronTime::GetSeconds(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->cronTime.GetSeconds());
}

Napi::Value CronTime::SetWeaks(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->cronTime.SetWeaks(value.Int32Value());
    return info.This();
}

Napi::Value CronTime::SetDays(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->cronTime.SetDays(value.Int32Value());
    return info.This();
}

Napi::Value CronTime::SetHours(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->cronTime.SetHours(value.Int32Value());
    return info.This();
}

Napi::Value CronTime::SetMinutes(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->cronTime.SetMinutes(value.Int32Value());
    return info.This();
}

Napi::Value CronTime::SetSeconds(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->cronTime.SetSeconds(value.Int32Value());
    return info.This();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    CronTime::Init(env, exports);
    return exports;
}

Napi::Value CronTime::CreateNewItem(const Napi::CallbackInfo& info)
{
    Napi::FunctionReference* constructor = info.Env().GetInstanceData<Napi::FunctionReference>();
    return constructor->New({});
}

// NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
