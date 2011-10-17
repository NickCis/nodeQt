#include <node/v8.h>
#include <node/node.h>

#include "Widget.hpp"
#include "pushButton.hpp"
#include "Application.hpp"
#include "nodeQt.hpp"

using namespace v8;

void RegisterModule(Handle<Object> target) {
    PushButton::Init(target);
    Widget::Init(target);
    Application::Init(target);
}

NODE_MODULE(nodeQt, RegisterModule);
