#include <iostream>

#include "HttpTimeSync.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    HttpTimeSync synchronizer;
    synchronizer.setUrl("http://192.168.0.166/abot");
    synchronizer.setDetectTimes(10000);
    synchronizer.runTimeDetect();
}
