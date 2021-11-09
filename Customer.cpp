
#include "Customer.h"

Customer::Customer(std::string c_name, int c_id) :
        id(c_id), name(c_name) {}

int Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> options;
    for(Workout w : workout_options) {

    }
    return options;
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}


