//
// Created by day-dreams on 2020-03-29.
//

#include "Function.h"

Function::Function(std::function<void(void)> handle) {
    this->handle = handle;
}

void Function::Run() {
    this->handle();
}
