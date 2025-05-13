// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr), current(nullptr) {}

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
  resetPosition();
  int length = 0;
  bool anyLightOn = false;
  Car* start = first;
  do {
    if (isLightOn()) {
      anyLightOn = true;
      break;
    }
    moveForward();
  } while (current != start);
  if (!anyLightOn) {
    turnLightOn();
    countOp++;
  }
  while (!isLightOn()) {
    moveForward();
  }
  turnLightOff();
  countOp++;
  moveForward();
  length = 1;
  while (true) {
    if (isLightOn()) {
      turnLightOff();
      countOp++;
      length += getOpCount();
      resetPosition();
      moveForward(length);
      countOp = length;
    } else {
      moveForward();
    }
    if (!isLightOn() && getOpCount() == length) {
      break;
    }
  }
  return length;
}
int Train::getOpCount() {
  return countOp;
}
void Train::moveForward() {
  if (!current) current = first;
  current = current->next;
  countOp++;
}

void Train::moveBackward() {
  if (!current) current = first;
  current = current->prev;
  countOp++;
}
bool Train::isLightOn() {
  if (!current) return first->light;
  return current->light;
}
void Train::turnLightOn() {
  if (!current) first->light = true;
  else current->light = true;
}
void Train::turnLightOff() {
  if (!current) first->light = false;
  else current->light = false;
}
void Train::resetPosition() {
  current = first;
}
