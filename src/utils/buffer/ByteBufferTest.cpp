//
// Created by JackyWoo on 2022/4/19.
//

#include "ByteBuffer.h"

using namespace DB;

int32_t main() {

    auto bb1 = std::make_unique<ByteBuffer>(30);
    auto bb2 = std::make_unique<ByteBuffer>();

    bb1->printPosition();
    printf("bb1 bytes Remaining: %i\n", bb1->bytesRemaining());
    bb1->put(0xDE);
    bb1->put(0xAD);
    bb1->put(0xBA);
    bb1->put(0xBE);
    bb1->printPosition();
    printf("bb1 bytes Remaining: %i\n", bb1->bytesRemaining());

    bb1->printHex();
    bb1->printPosition();

    int32_t f0 = -1, f1 = -1, f2 = -1;
    f0 = bb1->find((uint16_t) 0xBEBA);
    f1 = bb1->find((uint8_t) 0xBA);

    uint8_t t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 1;
    t1 = bb1->get();
    t2 = bb1->get();
    t3 = bb1->get();
    t4 = bb1->get();
    t5 = bb1->get();

    f2 = bb1->find((uint8_t) 0xDE, bb1->getReadPos());

    std::printf("t1 = %x, t2 = %x, t3 = %x, t4 = %x, t5 = %x\n", t1, t2, t3, t4, t5);
    std::printf("f0 = %i, f1 = %i, f2 = %i\n", f0, f1, f2);
    bb1->printPosition();

    std::string test = "TesTtest2";
    bb2->putBytes(test.c_str(), test.size());
    bb2->printHex();
    bb2->printAscii();

    return 0;
}
