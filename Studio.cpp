#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Studio.h"

extern Studio* backup;

Studio::Studio() {}

Studio::Studio(const std::string &configFilePath): open(false) {
    next_customer_id = 0;

    int number_of_trainers = -1; // default value
    int next_workout_id = 0;
    std::ifstream file;
    file.open(configFilePath);
    if(!file.is_open()) {
        throw std::invalid_argument("file couldn't be opened!");
    }
    std::string line;
    while(getline(file, line)){
        if(line.find_first_of('#') != 0 && !line.empty()) {
            if(number_of_trainers == -1)
                number_of_trainers = std::stoi(line);
            else if(this->trainers.empty()) {
                std::stringstream ss(line);
                std::string substr;
                while(ss.good()) {
                    getline(ss, substr, ',');
                    int capacity = std::stoi(substr);
                    this->trainers.push_back(new Trainer(capacity));
                }
            } else {
                std::stringstream ss(line);
                std::string word;
                getline(ss, word, ',');
                std::string workout_name(word);
                getline(ss, word, ',');
                std::string workout_type(word.substr(1));
                getline(ss, word);
                word = word.substr(1);
                int workout_price = std::stoi(word);

                WorkoutType t;
                if(workout_type == "Anaerobic")
                    t = WorkoutType::ANAEROBIC;
                else if(workout_type == "Mixed")
                    t = WorkoutType::MIXED;
                else // "Cardio"
                    t = WorkoutType::CARDIO;

                Workout w = Workout(next_workout_id, workout_name, workout_price, t);
                next_workout_id++;
                workout_options.push_back(w);
            }
        }
    }
}

int Studio::getNumOfTrainers() const {
    return (int)trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    return this->trainers[tid];
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

void Studio::start() {
    this->open = true;
    std::cout << "Studio is now open!" << std::endl;
    std::string input;
    mainLoop();
}

int Studio::allocateNewCustomerId() {
    next_customer_id++;
    return next_customer_id-1;
}

void Studio::mainLoop() {
    std::string input;
    while(true) {
        std::cin >> input;
        if(input.rfind("open",0) == 0)
            openTrainer(input);
        else if(input == "closeall") {
            closeAll();
            break;
        }


    }
}

void Studio::closeAll() {

}

void Studio::openTrainer(std::string command) {
    command = command.substr(5); // without "open"
    std::stringstream ss(command);
    std::string substr;
    Trainer *t = nullptr;
    std::vector<std::string> names;
    std::vector<std::string> codes;
    while(ss.good()) {
        getline(ss, substr, ' ');
        if(t == nullptr) {
            int trainer_id = std::stoi(substr);
            t = getTrainerById(trainer_id);
        }
        else {
            std::string customer_name;
            std::string strategy;
            getline(ss, customer_name, ',');
            getline(ss, strategy, ' ');
            names.push_back(customer_name);
            codes.push_back(strategy);
        }
    }

    Customer *c;
    std::string strategy, customer_name;
    int customer_id = allocateNewCustomerId();
    if(strategy == "swt")
        c = new SweatyCustomer(customer_name, customer_id);
    else if (strategy == "chp")
        c = new CheapCustomer(customer_name, customer_id);
    else if (strategy == "mcl")
        c = new HeavyMuscleCustomer(customer_name, customer_id);
    else if (strategy == "fbd")
        c = new FullBodyCustomer(customer_name, customer_id);
    else
        throw std::invalid_argument("Illegal code: " + strategy);
}

Trainer *Studio::getTrainerById(int id) {
    if(trainers.size() <= id)
        throw std::invalid_argument("no such trainer!");
    return trainers[id];
}
