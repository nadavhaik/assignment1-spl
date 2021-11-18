#include "Trainer.h"
#include "Action.h"
#include "Studio.h"

using namespace std;


Order::Order(int id) : BaseAction(), trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if(t == nullptr || !t->isOpen()) {
        error("Trainer does not exist or is not open");
        return;
    }
    vector<Customer*> customers = t->getCustomers();
    const vector<Workout> &workoutOptions = studio.getWorkoutOptions();

    // ordering each customer
    for(Customer *c : customers) {
        vector<int> customerOrder = c->order(workoutOptions);
        t->order(c->getId(), customerOrder, workoutOptions);
    }

    // building the string
    for(const OrderPair &p : t->getOrders()) {
        const string customer_name = t->getCustomer(p.first)->getName();
        const string activity_name = p.second.getName();
        s.append(customer_name);
        s.append(" Is Doing ");
        s.append(activity_name);
        s.append("\n");
    }

    complete();
}

std::string Order::toString() const {
    return s;
}
