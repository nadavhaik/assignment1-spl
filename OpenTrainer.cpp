#include "Studio.h"
#include "Trainer.h"
using namespace std;


OpenTrainer::OpenTrainer(int id, vector<Customer *> &customersList) : trainerId(id) {
    customers = {};
}

void OpenTrainer::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    t->open();
}

string OpenTrainer::toString() const {
    return "";
}
