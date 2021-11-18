#pragma once
#include "Action.h"

using namespace std;

CloseAll::CloseAll(): BaseAction() {

}

void CloseAll::act(Studio &studio) {
    // closing each
    for(int i = 0; i < studio.getNumOfTrainers(); i++) {
        Trainer *t = studio.getTrainer(i);
        if(t->isOpen()){
            Close close_action(i);
            close_action.act(studio);
            s.append(close_action.toString());
        }
    }
    complete();
}

std::string CloseAll::toString() const {
    return s;
}
