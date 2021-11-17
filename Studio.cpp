#include "Customer.cpp"
#include "MoveCustomer.cpp"
#include "CloseAll.cpp"
#include "PrintWorkoutOptions.cpp"
#include "PrintTrainerStatus.cpp"
#include "PrintActionsLog.cpp"
#include "BackupStudio.cpp"
#include "RestoreStudio.cpp"
Studio::Studio() {}

Studio::Studio(const std::string &configFilePath) {
    open = false;
    next_customer_id = 0;
    customer_id_backup = -1;

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

void Studio::handleInput() {
    std::string input_command;
    BaseAction *action;
    ActionType actionType;
    std::string substr;

    getline(cin, input_command);
    std::stringstream ss(input_command);


    if(input_command.rfind(' ') == -1)
        substr = input_command;
    else
        getline(ss, substr, ' ');

    if (substr == "open")
        actionType = ActionType::OPEN_TRAINER;
    else if (substr == "order")
        actionType = ActionType::ORDER;
    else if (substr == "move")
        actionType = ActionType::MOVE_CUSTOMER;
    else if (substr == "close")
        actionType = ActionType::CLOSE;
    else if (substr == "closeall")
        actionType = ActionType::CLOSE_ALL;
    else if (substr == "workout_options")
        actionType = ActionType::PRINT_WORKOUT_OPTIONS;
    else if (substr == "status")
        actionType = ActionType::PRINT_TRAINER_STATUS;
    else if (substr == "log")
        actionType = ActionType::PRINT_ACTIONS_LOG;
    else if (substr == "backup")
        actionType = ActionType::BACKUP_STUDIO;
    else if (substr == "restore")
        actionType = ActionType::RESTORE_STUDIO;


    // variables for switch-case:
    int trainer_id;
    int source_id;
    int dest_id;
    int customer_id;
    std::vector<Customer *> customerList;

    switch(actionType) {
        case OPEN_TRAINER:
            backupCustomerId(); // for case of failure - we'll want to roll back the ids allocation
            getline(ss, substr, ' ');
            trainer_id = std::stoi(substr);
            while (ss.good()) {
                getline(ss, substr, ' ');
                Customer *c;
                std::string customer_name;
                std::string strategy;
                getline(ss, customer_name, ',');
                getline(ss, strategy, ' ');
                if (strategy == "swt")
                    c = new SweatyCustomer(customer_name, allocateNewCustomerId());
                else if (strategy == "chp")
                    c = new CheapCustomer(customer_name, allocateNewCustomerId());
                else if (strategy == "mcl")
                    c = new HeavyMuscleCustomer(customer_name, allocateNewCustomerId());
                else if (strategy == "fbd")
                    c = new FullBodyCustomer(customer_name, allocateNewCustomerId());
                customerList.push_back(c);
            }

            action = new OpenTrainer(trainer_id, customerList);
            break;
        case ORDER:
            getline(ss, substr, ' ');
            trainer_id = std::stoi(substr);

            action = new Order(trainer_id);
            break;
        case MOVE_CUSTOMER:
            getline(ss, substr, ' ');
            source_id = std::stoi(substr);
            getline(ss, substr, ' ');
            dest_id = std::stoi(substr);
            getline(ss, substr, ' ');
            customer_id = std::stoi(substr);

            action = new MoveCustomer(source_id, dest_id, customer_id);
            break;
        case CLOSE:
            getline(ss, substr, ' ');
            trainer_id = std::stoi(substr);

            action = new Close(trainer_id);
            break;
        case CLOSE_ALL:
            action = new CloseAll();
            break;
        case PRINT_WORKOUT_OPTIONS:
            action = new PrintWorkoutOptions();
            break;
        case PRINT_TRAINER_STATUS:
            getline(ss, substr, ' ');
            trainer_id = std::stoi(substr);

            action = new PrintTrainerStatus(trainer_id);
            break;
        case PRINT_ACTIONS_LOG:
            action = new PrintActionsLog();
            break;
        case BACKUP_STUDIO:
            action = new BackupStudio();
            break;
        case RESTORE_STUDIO:
            action = new RestoreStudio();
            break;
    }

    action->act(*this);
    switch(action->getStatus()) {
        case COMPLETED:
            break;
        case ERROR:
            if(actionType == OPEN_TRAINER)
                restoreCustomerIdFromBackup(); // to make customer ids consistent even if fails
            break;
    }
}

void Studio::mainLoop() {
    while(true) {
        handleInput();
        if (trainers.empty())
            break;
    }
}

void Studio::backupCustomerId() {
    customer_id_backup = next_customer_id;
}

void Studio::restoreCustomerIdFromBackup() {
    int temp = customer_id_backup;
    customer_id_backup = -1;
    next_customer_id = temp;
}


