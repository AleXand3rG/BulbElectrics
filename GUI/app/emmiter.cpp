#include "emmiter.h"

void Emmiter::setSavedState(bool s) {
    saved_ = s;
}

void Emmiter::setSavedStateAndEmit(bool s) {
    saved_ = s;
    emit savedStateChanged(s);
}
