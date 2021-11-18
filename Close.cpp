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

    s.append("Trainer ");
    s.append(to_string(trainerId));
    s.append(" closed. Salary ");
    s.append(to_string(t->getSalary()));
    s.append("NIS\r");
    t->closeTrainer();
    complete();

}

std::string Close::toString() const {
    return s;
}
