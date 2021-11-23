#include "Action.h"

using namespace std;

BackupStudio::BackupStudio(): BaseAction() {

}

void BackupStudio::act(Studio &studio) {
    for(BaseAction *a: studio.getActionsLog())
        a->clone();
}

std::string BackupStudio::toString() const {
    return "backup Completed";
}

BaseAction *BackupStudio::clone() {
    return new BackupStudio();
}
