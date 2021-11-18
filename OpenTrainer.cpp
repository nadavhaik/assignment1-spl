#include "Action.h"
#include "Trainer.h"
#include "Studio.h"
#include <string>
using namespace std;

OpenTrainer::OpenTrainer(int id, vector<Customer *> &customersList):
    BaseAction(), trainerId(id), customers(customersList) {
}

void OpenTrainer::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if(t == nullptr || t->isOpen() || t->getCapacity() <= customers.size()) {
        for(Customer *c : customers)
            delete c;
        error("Workout session does not exist or is already open.");
        return;
    }
    for(Customer *c : customers)
        t->addCustomer(c);
    t->openTrainer();
    complete();
}

string OpenTrainer::toString() const {
    return "";
}
