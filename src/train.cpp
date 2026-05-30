// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : operationCount(0), startCar(nullptr) {}

Train::~Train() {
    if (startCar) {
        Car *p = startCar;
        do {
            Car *tmp = p;
            p = p->next;
            delete tmp;
        } while (p != startCar);
    }
}

void Train::addCar(bool light) {
    Car *newCar = new Car{light, nullptr, nullptr};
    if (!startCar) {
        startCar = newCar;
        startCar->next = startCar;
        startCar->prev = startCar;
    } else {
        newCar->next = startCar;
        newCar->prev = startCar->prev;
        startCar->prev->next = newCar;
        startCar->prev = newCar;
    }
}

int Train::getLength() {
    if (!startCar) return 0;

    bool initialLight = startCar->light;

    if (!initialLight) {
        // Случай: начальная лампа выключена -> быстрый метод за 2n
        startCar->light = true;
        Car *cur = startCar;

        // Первый проход: выключаем все лампы, возвращаемся в начало
        do {
            cur = cur->next;
            ++operationCount;
            cur->light = false;
        } while (cur != startCar);

        // Второй проход: считаем шаги до первой горящей лампы
        startCar->light = true;
        int length = 0;
        cur = startCar;
        do {
            cur = cur->next;
            ++operationCount;
            ++length;
        } while (!cur->light);

        return length;
    } else {
        // Случай: начальная лампа включена -> метод с возвратами (сумма 2k)
        int k = 1;
        while (true) {
            Car *cur = startCar;
            // Проходим k шагов вперёд, гасим свет
            for (int i = 0; i < k; ++i) {
                cur = cur->next;
                ++operationCount;
                cur->light = false;
            }
            // Возвращаемся на k шагов назад
            for (int i = 0; i < k; ++i) {
                cur = cur->prev;
                ++operationCount;
            }
            // Если начальный вагон погас — длина равна k
            if (!startCar->light) {
                break;
            }
            ++k;
        }
        return k;
    }
}

int Train::getOpCount() const {
    return operationCount;
}
