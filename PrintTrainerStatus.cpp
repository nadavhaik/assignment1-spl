#include "Action.h"

using namespace std;
PrintTrainerStatus::PrintTrainerStatus(int id): BaseAction(), trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if(t == nullptr)
        return;
    int t_salary = 0;
    string status = t->isOpen() ? "open" : "closed";

    cout<< "Trainer "<< trainerId << " status: "<< status<< endl;
    if(!studio.getTrainer(trainerId)->isOpen()) {
        return;
    }
    cout<<"Costumers:"<<endl;
    for(const Customer* c: studio.getTrainer(trainerId)->getCustomers()){
        cout<<c->getId() << " " << c->getName()<< endl;
    }
    cout<<"Orders:"<< endl;
    for(const OrderPair& pair: studio.getTrainer(trainerId)->getOrders()) {
        cout<<pair.second.getName() << " " << pair.second.getPrice() << "NIS "<<  pair.first<< endl;
        t_salary += pair.second.getPrice();
    }
    cout<<"Current Trainer's Salary: " << t_salary<< "NIS"<<endl;
    complete();
}

std::string PrintTrainerStatus::toString() const {
    return "status " + to_string(trainerId) + " Completed";
}

BaseAction *PrintTrainerStatus::clone() {
    return new PrintTrainerStatus(*this);
}

PrintTrainerStatus::PrintTrainerStatus(const PrintTrainerStatus &other): BaseAction(other), trainerId(other.trainerId) {

}
