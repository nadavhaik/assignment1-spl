#include "Action.h"

using namespace std;
PrintTrainerStatus::PrintTrainerStatus(int id): BaseAction(), trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
//    if(!studio.getTrainer(trainerId)->isOpen()) {
//        error("this trainer is close");
//        return;
//    }
    int t_salary = 0;
    cout<< "Trainer "<< trainerId << " status: "<< studio.getTrainer(trainerId)->isOpen()<< endl;
    cout<<"Costumers:"<<endl;
    for(const Customer* c: studio.getTrainer(trainerId)->getCustomers()){
        cout<<c->getId() << " " << c->getName()<< endl;
    }
    cout<<"Orders:"<< endl;
    for(const OrderPair& pair: studio.getTrainer(trainerId)->getOrders()) {
        cout<<pair.second.getName() << " " << pair.second.getPrice() << " "<<  pair.first<< endl;
        t_salary += pair.second.getPrice();
    }
    cout<<"Current Trainer's Salary: " << t_salary<< "NIS"<<endl;
}

std::string PrintTrainerStatus::toString() const {
    return std::string();
}
