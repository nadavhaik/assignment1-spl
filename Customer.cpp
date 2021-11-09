
#include <algorithm>
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

std::string SweatyCustomer::toString() const {
    return "";
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

std::string CheapCustomer::toString() const {
    return "";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

bool compare_by_price_desc (Workout &w1, Workout &w2) { return (w2.getPrice() < w1.getPrice()); }

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<Workout> options;
    std::vector<int> options_ids;

    for(const Workout& w : workout_options) {
        if(w.getType() == WorkoutType::ANAEROBIC)
            options.push_back(w);
    }
    std::sort(options.begin(), options.end(), compare_by_price_desc);
    for(const Workout& w : workout_options)
        options_ids.push_back(w.getId());

    return options_ids;
}

std::string HeavyMuscleCustomer::toString() const {
    return "";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    size_t cheapest_cardio_index;
    bool found_cheapest_cardio = false;
    size_t most_expensive_mixed_index;
    bool found_most_expensive_mixed = false;
    size_t cheapest_anaerobic_index;
    bool found_cheapest_anaerobic = false;

    for(size_t i = 0; i < workout_options.size(); i++) {
        const Workout &w = workout_options[i];
        if(w.getType() == WorkoutType::CARDIO &&
                (!found_cheapest_cardio || w.getPrice() < workout_options[cheapest_cardio_index].getPrice())) {
            found_cheapest_cardio = true;
            cheapest_cardio_index = i;
        } else if(w.getType() == WorkoutType::MIXED &&
                (!found_most_expensive_mixed || w.getPrice() > workout_options[most_expensive_mixed_index].getPrice())) {
            found_most_expensive_mixed = true;
            most_expensive_mixed_index = i;
        } else if(w.getType() == WorkoutType::ANAEROBIC &&
                (!found_cheapest_anaerobic || w.getPrice() < workout_options[cheapest_anaerobic_index].getPrice())) {
            found_cheapest_anaerobic = true;
            cheapest_anaerobic_index = i;
        }
    }

    std::vector<int> options;
    if(found_cheapest_cardio)
        options.push_back(workout_options[cheapest_cardio_index].getId());
    if(found_most_expensive_mixed)
        options.push_back(workout_options[most_expensive_mixed_index].getId());
    if(found_cheapest_anaerobic)
        options.push_back(workout_options[cheapest_anaerobic_index].getId());

    return options;
}

std::string FullBodyCustomer::toString() const {
    return "";
}


