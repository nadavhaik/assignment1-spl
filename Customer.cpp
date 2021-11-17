#include <algorithm>

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
    Workout *cheapest = nullptr;
    for(const Workout& w: workout_options) {
        if(cheapest == nullptr || w.getPrice() < cheapest->getPrice() ||
                (w.getPrice() == cheapest->getPrice() && w.getId() < cheapest->getId())) {
            //delete cheapest;
            cheapest = new Workout(w);
        }
    }

    if(cheapest == nullptr)
        return {};

    int id = cheapest->getId();
    //delete cheapest;

    return {id};
}

std::string CheapCustomer::toString() const {
    return "";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

bool compare_workouts_by_price_desc_and_id_asc(Workout &w1, Workout &w2) {
    if(w1.getPrice() == w2.getPrice())
        return w1.getId() < w2.getId();
    return w2.getPrice() < w1.getPrice();
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<Workout> options;
    std::vector<int> options_ids;

    for(const Workout& w : workout_options) {
        if(w.getType() == WorkoutType::ANAEROBIC)
            options.push_back(w);
    }
    std::sort(options.begin(), options.end(), compare_workouts_by_price_desc_and_id_asc);
    for(const Workout& w : options)
        options_ids.push_back(w.getId());

    return options_ids;
}

std::string HeavyMuscleCustomer::toString() const {
    return "";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    Workout *cheapest_cardio = nullptr;
    Workout *most_expensive_mixed = nullptr;
    Workout *cheapest_anaerobic = nullptr;
    for(const Workout &w : workout_options) {
        switch (w.getType()) {
            case WorkoutType::CARDIO:
                if (cheapest_cardio == nullptr || w.getPrice() < cheapest_cardio->getPrice() ||
                        (w.getPrice() == cheapest_cardio->getPrice() && w.getId() < cheapest_cardio->getId())) {
                    //delete cheapest_cardio;
                    cheapest_cardio = new Workout(w);
                }
                break;
            case WorkoutType::MIXED:
                if (most_expensive_mixed == nullptr || w.getPrice() > most_expensive_mixed->getPrice() ||
                        (w.getPrice() == most_expensive_mixed->getPrice() && w.getId() < most_expensive_mixed->getId())) {
                    //delete most_expensive_mixed;
                    most_expensive_mixed = new Workout(w);
                }
                break;
            case WorkoutType::ANAEROBIC:
                if (cheapest_anaerobic == nullptr || w.getPrice() < cheapest_anaerobic->getPrice() ||
                        (w.getPrice() == cheapest_anaerobic->getPrice() && w.getId() < cheapest_anaerobic->getId())) {
                    //delete cheapest_anaerobic;
                    cheapest_anaerobic = new Workout(w);
                }
                break;
        }
    }

    std::vector<int> options;
    if(cheapest_cardio != nullptr)
        options.push_back(cheapest_cardio->getId());
    if(most_expensive_mixed != nullptr)
        options.push_back(most_expensive_mixed->getId());
    if(cheapest_anaerobic != nullptr)
        options.push_back(cheapest_anaerobic->getId());

    //delete cheapest_cardio;
    //delete most_expensive_mixed;
    //delete cheapest_anaerobic;

    return options;
}

std::string FullBodyCustomer::toString() const {
    return "";
}


