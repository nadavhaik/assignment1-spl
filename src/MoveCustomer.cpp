#include "../include/Action.h"
#include "../include/Studio.h"
using namespace std;

MoveCustomer::MoveCustomer(int src, int dst, int customerId): BaseAction(), srcTrainer(src), dstTrainer(dst), id(customerId) {

}

void MoveCustomer::act(Studio &studio) {
    Trainer *source = studio.getTrainer(srcTrainer);
    Trainer *dest = studio.getTrainer(dstTrainer);
    Customer *c = (source == nullptr) ? nullptr : source->getCustomer(id);
    if(source == nullptr || dest == nullptr  || c == nullptr
            || !source->isOpen() || !dest->isOpen() || !dest->canAcceptAnotherCustomer()) {
        error("Cannot move customer");
        return;
    }

    source->removeCustomer(id); // updates old salary
    dest->addCustomer(c);

    // triggering order to update the salary for specific customer only
    vector<int> workout_ids = c->order(studio.getWorkoutOptions());
    dest->order(c->getId(), workout_ids, studio.getWorkoutOptions());

    if(source->getCustomers().empty()) { // also triggering Close
        Close close_action = Close(srcTrainer);
        close_action.act(studio);
    }

    complete();

}

std::string MoveCustomer::toString() const {
    string s = "move " + to_string(srcTrainer) + " " + to_string(dstTrainer) + " " + to_string(id);
    if(getStatus() == COMPLETED)
        return s + " Completed";

    return s + " Error: Cannot move customer";
}

BaseAction *MoveCustomer::clone() {
    return new MoveCustomer(*this);
}

MoveCustomer::MoveCustomer(const MoveCustomer &other): BaseAction(other), srcTrainer(other.srcTrainer),
        dstTrainer(other.dstTrainer), id(other.id) {
}
