#include <string>
#include <iostream>
#include "Trainer.h"
#include "Trainer.h"

Trainer::Trainer(int t_capacity): capacity(t_capacity) {}

bool Trainer::isOpen(){
    return open;
}

void Trainer::addCustomer(Customer* customer){
    customersList.push_back(customer);
    customer_by_id_index.insert({customer->getId(), customer});
}

void Trainer::removeCustomer(int id){
    customer_by_id_index.erase(id); // deleting from the index
    for(std::size_t i = 0; i<customersList.size();i++) {
        Customer *c = customersList[i];
        if(c->getId() == id) {
            // only deleting *FROM THE LIST*
            customersList.erase(customersList.begin() + i);
            break;
        }
    }

    // Deleting all orders
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
    if(customer_by_id_index.find(id) == customer_by_id_index.end()) // id doesn't exist
        return nullptr;
    return customer_by_id_index.at(id);
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

void Trainer::openTrainer() {
   open = true;
}

void Trainer::closeTrainer() {
    for(Customer *c : customersList)
        delete c;
    open = false;
}

bool Trainer::canAcceptAnotherCustomer() {
    return customersList.size() < capacity;
}

Trainer::~Trainer() {
    if(isOpen())
        closeTrainer();
}

Trainer *Trainer::clone() {
    return new Trainer(*this);

}

Trainer::Trainer(const Trainer &other): capacity(other.capacity), open(other.open) {
    for(Customer* c: other.customersList){
        Customer* cloned_c = c->clone();
        customersList.push_back(cloned_c);
        customer_by_id_index.insert({cloned_c->getId(), cloned_c});
    }
    for(const OrderPair& p : other.orderList){
        OrderPair cloned_p = std::make_pair(p.first,p.second);
        orderList.push_back(cloned_p);
    }
}




