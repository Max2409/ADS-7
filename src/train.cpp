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
        // вставка перед начальным вагоном
        newCar->next = startCar;
        newCar->prev = startCar->prev;
        startCar->prev->next = newCar;
        startCar->prev = newCar;
    }
}

int Train::getLength() {
    if (!startCar) return 0;

    startCar->light = true;          // включаем свет в исходном вагоне

    Car *current = startCar;
    int distance = 1;

    bool finished = false;
    while (!finished) {
        // проходим вперёд distance шагов, везде гасим свет
        for (int i = 0; i < distance; ++i) {
            current = current->next;
            ++operationCount;
            current->light = false;
        }
        // возвращаемся обратно на distance шагов
        for (int i = 0; i < distance; ++i) {
            current = current->prev;
            ++operationCount;
        }
        // если в начальном вагоне свет погас – обошли весь поезд
        if (!current->light) {
            finished = true;
        } else {
            distance *= 2;           // увеличиваем дальность обхода
        }
    }

    // Все лампочки выключены. Зажигаем начальный вагон.
    current->light = true;

    // Считаем шаги до первой горящей лампы – это длина поезда
    int length = 0;
    do {
        current = current->next;
        ++operationCount;
        ++length;
    } while (!current->light);

    return length;
}

int Train::getOpCount() const {
    return operationCount;
}
