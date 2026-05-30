// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
    struct Car {
        bool light;
        Car *next;
        Car *prev;
    };

    int operationCount;   // количество перемещений между вагонами
    Car *startCar;        // точка входа в поезд

 public:
    Train();
    ~Train();

    Train(const Train&) = delete;
    Train& operator=(const Train&) = delete;

    void addCar(bool light);
    int  getLength();
    int  getOpCount() const;
};

#endif  // INCLUDE_TRAIN_H_
