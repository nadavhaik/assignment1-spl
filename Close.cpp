#include "Action.h"
#include "Studio.h"
using namespace std;

Close::Close(int id) : BaseAction(), trainerId(id) {

}

void Close::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if(t == nullptr || !t->isOpen()) {
        error("Trainer does not exist or is not open");
        return;
    }

    cout<< "Trainer "<< trainerId << " closed. Salary "  << t->getSalary()<< "NIS"<< endl;
    t->closeTrainer();
    complete();

}

std::string Close::toString() const {
    if(getStatus() == COMPLETED)
        return "close " + to_string(trainerId) + " Completed";
    return "close " + to_string(trainerId) + " Error: Trainer does not exist or is not open";
}
