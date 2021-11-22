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
}

std::string PrintTrainerStatus::toString() const {
    string s;
    if(this->getStatus() == COMPLETED)
        s = "PrintTrainerStatus " + to_string(trainerId) + " Completed";
    else
        s = "PrintTrainerStatus " + to_string(trainerId) + " Error";
    return s;
}
