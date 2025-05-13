// Copyright 2021 NNTU-CS
#include "train.h"
#include <vector>
#include <cstdlib>
#include <ctime>

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
}

int Train::getLength() {
  if (!first) return 0;
  countOp = 0;
  Car* current = first;
  while (!current->light && countOp < 100000) {
    current = current->next;
    countOp++;
    if (current == first) break;
  }
  if (!current->light) {
    first->light = true;
    countOp++;
    current = first;
  }
  current->light = false;
  countOp++;
  int length = 1;
  Car* marker = current;
  current = current->next;

  while (true) {
    countOp++;
    if (current == marker) {
      return length;
    }
    if (current->light) {
      current->light = false;
      countOp += length;
      // Возвращаемся назад
      for (int i = 0; i < length; i++) {
        current = current->prev;
      }
      length = 1;
      current = current->next;
    } else {
      length++;
      current = current->next;
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
  for (bool light : lights) {
    addCar(light);
  }
}
