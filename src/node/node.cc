#include <napi.h>

class CronTime : public Napi::ObjectWrap<CronTime> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    CronTime(const Napi::CallbackInfo& info);
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

private:
    double _value;
    Napi::Value GetValue(const Napi::CallbackInfo& info);
    Napi::Value SetValue(const Napi::CallbackInfo& info);
};

Napi::Object CronTime::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "CronTime", {
                                                           InstanceMethod<&CronTime::GetValue>("GetValue", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
                                                           InstanceMethod<&CronTime::SetValue>("SetValue", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
                                                           StaticMethod<&CronTime::CreateNewItem>("CreateNewItem", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
                                                       });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("CronTime", func);
}

CronTime::CronTime(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CronTime>(info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->_value = value.DoubleValue();
}

Napi::Value CronTime::GetValue(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_value);
}

Napi::Value CronTime::SetValue(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->_value = value.DoubleValue();
    return this->GetValue(info);
}

// Initialize native add-on
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    CronTime::Init(env, exports);
    return exports;
}

// Create a new item using the constructor stored during Init.
Napi::Value CronTime::CreateNewItem(const Napi::CallbackInfo& info)
{
    Napi::FunctionReference* constructor = info.Env().GetInstanceData<Napi::FunctionReference>();
    return constructor->New({ Napi::Number::New(info.Env(), 42) });
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
