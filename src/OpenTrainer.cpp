#include "../include/Trainer.h"
#include "../include/Studio.h"
#include "../include/Action.h"

#include <string>
using namespace std;

OpenTrainer::OpenTrainer(int id, vector<Customer *> &customersList):
    BaseAction(), trainerId(id), customers(customersList) {
}

void OpenTrainer::act(Studio &studio) {
    // building the string - because the customers might be deleted from the heap later
    original_input_command = "open " + to_string(trainerId);
    for (Customer *c: customers)
        original_input_command += " " + c->toString();

    Trainer *t = studio.getTrainer(trainerId);
    if (t == nullptr || t->isOpen()) {
        for(Customer *c : customers) // Avoiding memory leaks
            studio.deleteCustomerAndRollbackId(c);
        customers.clear();
        error("Workout session does not exist or is already open.");
        return;
    }
    int counter = 0;
    for (Customer *c : customers) { // Adding only the first t.capacity customers - and deleting the rest
        if(counter < t->getCapacity())
            t->addCustomer(c);
        else // avoiding leaks
            studio.deleteCustomerAndRollbackId(c);
        counter++;
    }

    customers.clear();
    t->openTrainer();
    complete();
}

string OpenTrainer::toString() const {
    if(getStatus() == COMPLETED)
        return original_input_command + " Completed";
    return original_input_command + " Error: Workout session does not exist or is already open.";

}

BaseAction *OpenTrainer::clone() {
    return new OpenTrainer(*this);
}

OpenTrainer::OpenTrainer(OpenTrainer const &other): BaseAction(other), trainerId(other.trainerId), original_input_command(other.original_input_command) {

}
