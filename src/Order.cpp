#include "../include/Trainer.h"
#include "../include/Action.h"
#include "../include/Studio.h"

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
    t->clearAllOrders();

    // ordering each customer
    for(Customer *c : customers) {
        vector<int> customerOrder = c->order(workoutOptions);
        t->order(c->getId(), customerOrder, workoutOptions);
    }

    // building the string
    for(const OrderPair &p : t->getOrders()) {
        const string customer_name = t->getCustomer(p.first)->getName();
        const string activity_name = p.second.getName();
        cout << customer_name << " Is Doing "  << activity_name << endl;
    }

    complete();
}

std::string Order::toString() const {
    string s = "order " + to_string(trainerId);
    if(getStatus() == COMPLETED)
        return s + " Completed";
    return s + " Error: Trainer does not exist or is not open";
}

BaseAction *Order::clone() {
    return new Order(*this);
}

Order::Order(const Order &other): BaseAction(other), trainerId(other.trainerId) {}
