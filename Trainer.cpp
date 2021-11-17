#include "Trainer.h"
#include "Customer.cpp"


Trainer::Trainer(int t_capacity): capacity(t_capacity) {}

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
