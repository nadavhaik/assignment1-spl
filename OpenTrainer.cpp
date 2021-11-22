#include "Trainer.h"
#include "Studio.h"
#include <string>
using namespace std;

OpenTrainer::OpenTrainer(int id, vector<Customer *> &customersList):
    BaseAction(), trainerId(id), customers(customersList) {
}

void OpenTrainer::act(Studio &studio) {

    // building the string - because the customers might be deleted from the heap later
    s = "open " + to_string(trainerId);
    for(Customer *c : customers)
        s+= " " + c->toString();

    Trainer *t = studio.getTrainer(trainerId);
    if(t == nullptr || t->isOpen()) {
        for(Customer *c : customers) // Avoiding memory leaks
            delete c;
        error("Workout session does not exist or is already open.");
        return;
    }

    if(customers.size() > t->getCapacity()) // Shouldn't happen - should be handled in handleInput
        throw invalid_argument("Trainer " + to_string(trainerId) + " with capacity " + to_string(t->getCapacity())
            + " cannot accept " + to_string(customers.size()) + " customers!");

    for(Customer *c : customers)
        t->addCustomer(c);

    t->openTrainer();
    complete();
}

string OpenTrainer::toString() const {
    if(getStatus() == COMPLETED)
        return s + " Completed";
    return s + " Error: Workout session does not exist or is already open.";

}
