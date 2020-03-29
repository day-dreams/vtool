//
// Created by day-dreams on 2020-03-29.
//

#ifndef VTOOL_FUNCTION_H
#define VTOOL_FUNCTION_H


#include "BaseRunnable.h"
#include <functional>

class Function : public BaseRunnable {
private:
    std::function<void(void)> handle;
public:
    Function(std::function<void(void)> handle);

    void Run() override;
};


#endif //VTOOL_FUNCTION_H
