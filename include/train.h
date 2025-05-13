// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <vector>

class Train {
 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;
  };

  int countOp;
  Car* first;

 public:
  Train();
  ~Train();
  void addCar(bool light);
  int getLength();
  int getOpCount() const;
  void resetTrain(const std::vector<bool>& lights);
};
#endif  // INCLUDE_TRAIN_H_
