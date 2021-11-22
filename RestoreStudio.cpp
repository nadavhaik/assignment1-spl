#include "Action.h"

using namespace std;

RestoreStudio::RestoreStudio() {

}

void RestoreStudio::act(Studio &studio) {

}

std::string RestoreStudio::toString() const {
    if(getStatus() == COMPLETED)
        return "restore Completed";
    return "restore Error: No backup available";
}
