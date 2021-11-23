#include "Action.h"

using namespace std;
extern Studio *backup;

RestoreStudio::RestoreStudio() {

}

void RestoreStudio::act(Studio &studio) {
    if(backup == nullptr) {
        error("No backup available");
        return;
    }


    backup = nullptr;
    complete();
}

std::string RestoreStudio::toString() const {
    if(getStatus() == COMPLETED)
        return "restore Completed";
    return "restore Error: No backup available";
}

BaseAction *RestoreStudio::clone() {
    return new RestoreStudio(*this);
}

RestoreStudio::RestoreStudio(const RestoreStudio &other) {

}
