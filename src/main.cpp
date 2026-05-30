// Copyright 2022 NNTU-CS
// src/main.cpp
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "train.h"

int main() {
    std::cout << "n\tall_off\tall_on\trandom\n";

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int n = 10; n <= 200; n += 10) {
        // 1. Все лампочки выключены
        Train trainOff;
        for (int i = 0; i < n; ++i) {
            trainOff.addCar(false);
        }
        trainOff.getLength();
        int opsOff = trainOff.getOpCount();

        // 2. Все лампочки включены
        Train trainOn;
        for (int i = 0; i < n; ++i) {
            trainOn.addCar(true);
        }
        trainOn.getLength();
        int opsOn = trainOn.getOpCount();

        // 3. Случайное состояние
        Train trainRand;
        for (int i = 0; i < n; ++i) {
            trainRand.addCar(std::rand() % 2);
        }
        trainRand.getLength();
        int opsRand = trainRand.getOpCount();

        std::cout << n << "\t" << opsOff << "\t" << opsOn << "\t" << opsRand << "\n";
    }

    return 0;
}
