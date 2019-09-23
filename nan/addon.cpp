#include <nan.h>

#define MAX_DEPTH 5

using namespace v8;
using namespace std;

static string *get_string_from_item(Isolate* isolate, Local<Context> context, Local<Value> item) {
    size_t      len;
    char       *buff;

    if(!item->IsString()) {
        return NULL;
    }
    MaybeLocal<String> maybe_str = item->ToString(context);
    if (maybe_str.IsEmpty()) {
        return NULL;
    }
    // at this point we should be safe with this string
    Local<String> str = maybe_str.ToLocalChecked();
#if NODE_MAJOR_VERSION <= 10
    len = str->Utf8Length();
#else
    len = str->Utf8Length(isolate);
#endif
    buff = (char *) malloc(len + 1);
    if(!buff) {
        return NULL;
    }
    int res;
#if NODE_MAJOR_VERSION <= 10
    res = str->WriteUtf8(buff, len + 1, NULL, 0);
#else
    res = str->WriteUtf8(isolate, buff, len, NULL, 0);
#endif
    if (!res) {
        free(buff);
        return NULL;
    }
    try {
        string *result = new string(buff);
        free(buff);
        return result;
    }
    catch(...) {
        free(buff);
        return NULL;
    }
}

void get_string_length(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    Isolate        *isolate     = info.GetIsolate();
    Local<Context>  context     = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        Nan::ThrowTypeError("inspect expect 1 argument");
        return;
    }

    string *result = get_string_from_item(isolate, context, info[0]);
    if(result == NULL) {
        Nan::ThrowTypeError("Something went wrong.");
        return;
    }
    Local<Number> response = Nan::New(static_cast<uint32_t>(result->length()));
    info.GetReturnValue().Set(response);
}
NAN_MODULE_INIT(Init) {
        Nan::Set(target,
                 Nan::New<String>("get_string_length").ToLocalChecked(),
                 Nan::GetFunction(Nan::New<FunctionTemplate>(get_string_length)).ToLocalChecked()
        );
}
NODE_MODULE(addon, Init)
