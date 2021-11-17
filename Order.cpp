#include "Trainer.h"
#include "Action.h"
#include "Studio.h"


using namespace std;


Order::Order(int id) : BaseAction(), trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if(!t->isOpen())
        return;
    vector<Customer*> customers = t->getCustomers();
    const vector<Workout> &workoutOptions = studio.getWorkoutOptions();
    for(Customer *c : customers) {
        vector<int> customerOrder = c->order(workoutOptions);
        t->order(c->getId(), customerOrder, workoutOptions);
    }
    complete();
}

std::string Order::toString() const {
    return "";
}
