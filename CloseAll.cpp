#pragma once
#include "Action.h"
using namespace std;

CloseAll::CloseAll(): BaseAction() {

}

void CloseAll::act(Studio &studio) {

}

std::string CloseAll::toString() const {
    return std::string();
}
