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
void Train::moveForward(int steps) {
  if (!current) current = first;
  while (steps-- > 0) {
    current = current->next;
    countOp++;
  }
}
int Train::getLength() {
  if (!first) return 0;
  resetPosition();
  int length = 0;
  bool markerCreated = false;
  if (!isLightOn()) {
    turnLightOn();
    countOp++;
    markerCreated = true;
  }
  do {
    moveForward();
    length++;
    if (isLightOn() && length > 1) {
      turnLightOff();
      countOp++;
    }
  } while (!(isLightOn() && length > 1) || (markerCreated && length == 1));
  if (markerCreated) {
    turnLightOff();
    countOp++;
  }
  return length;
}
int Train::getOpCount() {
  return countOp;
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
}
void Train::resetPosition() {
  current = first;
}
