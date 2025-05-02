// Copyright 2021 NNTU-CS
#include "train.h"
#include <vector>

Train::Train() : countOp(0), first(nullptr) {
  std::srand(std::time(0));
}
Train::~Train() {
  if (!first) return;
  Car* current = first->next;
  while (current != first) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }
  delete first;
}
void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
  initialLights.push_back(light);
}
int Train::getLength() {
  if (!first) return 0;
  countOp = 0;
  Car* current = first;
  while (true) {
    if (current->light) {
      current->light = false;
      countOp++;
      for (int steps = 1; ; steps++) {
        current = current->next;
        countOp++;
        if (current->light) {
          current->light = false;
          countOp += steps;
          for (int i = 0; i < steps; i++) {
            current = current->prev;
          }
          break;
        }
      }
      if (!current->light) {
        return countOp / 2;
      }
    } else {
      current = current->next;
      countOp++;
    }
  }
}
int Train::getOpCount() const {
  return countOp;
}
void Train::resetTrain(const std::vector<bool>& lights) {
  if (first) {
    Car* current = first->next;
    while (current != first) {
      Car* temp = current;
      current = current->next;
      delete temp;
    }
    delete first;
    first = nullptr;
  }
  initialLights.clear();
  for (bool light : lights) {
    addCar(light);
  }
}
