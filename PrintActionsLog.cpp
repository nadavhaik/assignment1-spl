#include "Action.h"
using namespace std;


PrintActionsLog::PrintActionsLog(): BaseAction() {

}

void PrintActionsLog::act(Studio &studio) {
    for(BaseAction *a: studio.getActionsLog())
        cout << a->toString() << endl;
}

std::string PrintActionsLog::toString() const {
    return "log Completed";
}
