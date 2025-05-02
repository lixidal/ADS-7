// Copyright 2021 NNTU-CS
#include "train.h"

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
  bool allLightsOff = true;
  Car* current = first;

  do {
    if (current->light) {
      allLightsOff = false;
      break;
    }
    current = current->next;
    countOp++;
  } while (current != first);

  if (allLightsOff) {
    first->light = true;
    countOp++;

    Car* explorer = first->next;
    int length = 1;

    while (true) {
      countOp++;
      if (explorer->light) {
        explorer->light = false;
        countOp += length;
        for (int i = 0; i < length; ++i) {
          explorer = explorer->prev;
        }
        if (!explorer->light) {
          return length;
        } else {
          length = 1;
          explorer = explorer->next;
        }
      } else {
        length++;
        explorer = explorer->next;
      }
    }
  } else {
    Car* explorer = first;
    while (!explorer->light) {
      explorer = explorer->next;
      countOp++;
    }
    explorer->light = false;
    countOp++;

    int length = 1;
    Car* marker = explorer;
    explorer = explorer->next;

    while (true) {
      countOp++;
      if (explorer == marker) {
        return length;
      }
      if (explorer->light) {
        explorer->light = false;
        countOp += length;
        for (int i = 0; i < length; ++i) {
          explorer = explorer->prev;
        }
        length = 1;
        explorer = explorer->next;
      } else {
        length++;
        explorer = explorer->next;
      }
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
