#include <vector>
#include <string>
#include <fstream>
#include <sstream>

Studio::Studio() {

}

Studio::Studio(const std::string &configFilePath): open(false) {
    //this->open = false;
//    this->trainers;
//    this->workout_options;
//    this->actionsLog;

    int number_of_trainers = -1; // default value
    int next_workout_id = 0;
    std::ifstream file;
    file.open(configFilePath);
    //file.open(configFilePath, std::ios::out);
    if(!file.is_open()) {
        throw std::invalid_argument("file couldn't be opened!");
    }
    std::string line;
    getline(file, line);
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
    while(true) {
        //std::cin.getline(input);
    }
}