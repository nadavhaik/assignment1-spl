#include "Action.h"

using namespace std;

BackupStudio::BackupStudio(): BaseAction() {

}

void BackupStudio::act(Studio &studio) {

}

std::string BackupStudio::toString() const {
    return "backup Completed";
}

BaseAction *BackupStudio::clone() {
    return new BackupStudio();
}
