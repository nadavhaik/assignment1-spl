#include "Action.h"

using namespace std;
extern Studio *backup;

BackupStudio::BackupStudio(): BaseAction() {

}

void BackupStudio::act(Studio &studio) {
    delete backup;
    backup = new Studio(studio);
    complete();
}

std::string BackupStudio::toString() const {
    return "backup Completed";
}

BaseAction *BackupStudio::clone() {
    return new BackupStudio();
}
