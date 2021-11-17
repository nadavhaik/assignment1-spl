#include <string>
#include <iostream>
#include "Trainer.h"


Trainer::Trainer(int t_capacity): capacity(t_capacity) {}

void Trainer::open() {
    this->open = true;
}

void Trainer::close() {
    this->open = false;
}

bool Trainer::isOpen(){
    return open;
}

void Trainer::addCustomer(Customer* customer){
    customersList.push_back(customer);
}
void Trainer::removeCustomer(int id){
    for(std::size_t i = 0; i<customersList.size();i++) {
        Customer *c = customersList[i];
        if(c->getId() == id) {
            // only deleting *FROM THE LIST*
            customersList.erase(customersList.begin() + i);
            break;
        }
    }
    for(size_t i = 0; i<orderList.size(); i++) {
        OrderPair p = orderList[i];
        if(id == p.first)
            orderList.erase(orderList.begin() + i);
    }
}

int Trainer::getCapacity() const {
    return capacity;
}

//should we throw an invalid argument error ? - not mentioned
Customer *Trainer::getCustomer(int id) {
    Customer* required_cus;
    bool found = false;
    for (Customer* c : customersList) {
        if(c->getId() == id) {
            required_cus = c;
            found = true;
        }
    }
    if(!found)
        throw std::invalid_argument("no such customer!");
    return required_cus;
}

//shouldn't we check if the workout was completed ? - not mentioned
int Trainer::getSalary() {
    int salary = 0;
    for (OrderPair p : orderList){
        salary += p.second.getPrice();
    }
    return salary;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int id: workout_ids) {
        OrderPair p = std::make_pair(customer_id, workout_options[id]);
        orderList.push_back(p);
    }
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}
