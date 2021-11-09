
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

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> options;
    for(const Workout& w : workout_options) {
        if(w.getType() == WorkoutType::CARDIO)
            options.push_back(w.getId());
    }
    return options;
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    size_t cheapest_index = 0;
    for(size_t i = 1; i<workout_options.size(); i++) {
        if(workout_options[i].getPrice() < workout_options[cheapest_index].getPrice())
            cheapest_index = i;
    }

    return {workout_options[cheapest_index].getId()};
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}


