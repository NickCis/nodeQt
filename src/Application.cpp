#include <node/v8.h>
#include <node/node.h>

#include <QWidget>
#include <QApplication>

#include "Application.hpp"

using namespace v8;


struct Baton {
    // libuv's request struct.
    uv_work_t request;

    // This handle holds the callback function we'll call after the work request
    // has been completed in a threadpool thread. It's persistent so that V8
    // doesn't garbage collect it away while our request waits to be processed.
    // This means that we'll have to dispose of it later ourselves.
    Persistent<Function> callback;


    // Tracking errors that happened in the worker function. You can use any
    // variables you want. E.g. in some cases, it might be useful to report
    // an error number.
    bool error;
    std::string error_message;

    // Custom data you can pass through.
	Application* Appli;
};

Persistent<FunctionTemplate> Application::constructor;

void Application::Init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	Local<String> name = String::NewSymbol("Application");

	constructor = Persistent<FunctionTemplate>::New(tpl);
	// ObjectWrap uses the first internal field to store the wrapped pointer.
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(name);

	// Add all prototype methods, getters and setters here.

	// This has to be last, otherwise the properties won't show up on the
	// object in JavaScript.
	target->Set(name, constructor->GetFunction());
}

Application::Application(): ObjectWrap() {}


Handle<Value> Application::New(const Arguments& args) {
	HandleScope scope;
    if (!args[0]->IsFunction()) {
        return ThrowException(Exception::TypeError(
            String::New("First argument must be a callback function")));
    }

	// Creates a new instance object of this type and wraps it.
	Application* obj = new Application();

    Local<Function> callback = Local<Function>::Cast(args[0]);
    // This creates our work request, including the libuv struct.
    Baton* baton = new Baton();
    baton->request.data = baton;
    baton->callback = Persistent<Function>::New(callback);
    baton->Appli = obj;
    int status = uv_queue_work(uv_default_loop(), &baton->request, AsyncWork, AsyncAfter);
    assert(status == 0);

	obj->Wrap(args.This());
	return args.This();
}

void AsyncWork(uv_work_t* req) {
    Baton* baton = static_cast<Baton*>(req->data);

    // Do work in threadpool here.

	baton->Appli->app = new QApplication(0, NULL);
	//The idea is to call gui widgets here. How to do that?, God knows.
	QWidget* qwidget = new QWidget();
	qwidget->resize(200,200);
	qwidget->show();
	baton->Appli->app->exec();

    // If the work we do fails, set baton->error_message to the error string
    // and baton->error to true.
}

void AsyncAfter(uv_work_t* req) {
    HandleScope scope;
    Baton* baton = static_cast<Baton*>(req->data);

    if (baton->error) {
        Local<Value> err = Exception::Error(String::New(baton->error_message.c_str()));

        // Prepare the parameters for the callback function.
        const unsigned argc = 1;
        Local<Value> argv[argc] = { err };

        // Wrap the callback function call in a TryCatch so that we can call
        // node's FatalException afterwards. This makes it possible to catch
        // the exception from JavaScript land using the
        // process.on('uncaughtException') event.
        TryCatch try_catch;
        baton->callback->Call(Context::GetCurrent()->Global(), argc, argv);
        if (try_catch.HasCaught()) {
            node::FatalException(try_catch);
        }
    } else {
        // In case the operation succeeded, convention is to pass null as the
        // first argument before the result arguments.
        // In case you produced more complex data, this is the place to convert
        // your plain C++ data structures into JavaScript/V8 data structures.
        const unsigned argc =1 ;
        Local<Value> argv[argc] = {
            Local<Value>::New(Null())//,
//            Local<Value>::New(Integer::New(baton->result))
        };

        // Wrap the callback function call in a TryCatch so that we can call
        // node's FatalException afterwards. This makes it possible to catch
        // the exception from JavaScript land using the
        // process.on('uncaughtException') event.
        TryCatch try_catch;
        baton->callback->Call(Context::GetCurrent()->Global(), argc, argv);
        if (try_catch.HasCaught()) {
            node::FatalException(try_catch);
        }
    }

    // The callback is a permanent handle, so we have to dispose of it manually.
    baton->callback.Dispose();
    delete baton;
}

