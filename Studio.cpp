#include <unordered_map>
#include "Customer.cpp"
#include "MoveCustomer.cpp"
#include "Close.cpp"
#include "CloseAll.cpp"
#include "PrintWorkoutOptions.cpp"
#include "PrintTrainerStatus.cpp"
#include "PrintActionsLog.cpp"
#include "BackupStudio.cpp"
#include "RestoreStudio.cpp"
#include "OpenTrainer.cpp"
#include "Order.cpp"
#include "BaseAction.cpp"
#include "Studio.h"


using namespace std;

Studio::Studio() {}

Studio::Studio(const std::string &configFilePath): open(false), next_customer_id(0) {
    //                     Prefix:               Action:
    action_prefixes = {{"open",            OPEN_TRAINER},
                       {"order",           ORDER},
                       {"move",            MOVE_CUSTOMER},
                       {"close",           CLOSE},
                       {"closeall",        CLOSE_ALL},
                       {"workout_options", PRINT_WORKOUT_OPTIONS},
                       {"status",          PRINT_TRAINER_STATUS},
                       {"log",             PRINT_ACTIONS_LOG},
                       {"backup",          BACKUP_STUDIO},
                       {"restore",         RESTORE_STUDIO}};

    int number_of_trainers = -1; // default value
    int next_workout_id = 0;
    ifstream file;
    file.open(configFilePath);
    if(!file.is_open()) {
        throw std::invalid_argument("file couldn't be opened!");
    }
    string line;
    while(getline(file, line)){
        if(line.find_first_of('#') != 0 && !line.empty()) {
            if(number_of_trainers == -1)
                number_of_trainers = stoi(line);
            else if(trainers.empty()) {
                stringstream ss(line);
                string substr;
                while(ss.good()) {
                    getline(ss, substr, ',');
                    int capacity = std::stoi(substr);
                    trainers.push_back(new Trainer(capacity));
                }
            } else {
                stringstream ss(line);
                string word;
                getline(ss, word, ',');
                string workout_name(word);
                getline(ss, word, ',');
                string workout_type(word.substr(1));
                getline(ss, word);
                word = word.substr(1);
                int workout_price = stoi(word);

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
    file.close();
}

int Studio::getNumOfTrainers() const {
    return (int)trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    if(tid >= trainers.size())
        return nullptr;
    return trainers[tid];
}

const vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

void Studio::start() {
    this->open = true;
    cout << "Studio is now open!" << std::endl;
    mainLoop();
}

int Studio::allocateNewCustomerId() {
    next_customer_id++;
    return next_customer_id-1;
}

bool Studio::handleInput() {
    // variables
    string input_command;
    BaseAction *action;
    string substr;
    getline(cin, input_command);
    stringstream ss(input_command);

    // reading the first word
    if(input_command.rfind(' ') == -1)
        substr = input_command;
    else
        getline(ss, substr, ' ');

    ActionType actionType = action_prefixes[substr];
    // variables for switch-case:
    int trainer_id;
    int source_id;
    int dest_id;
    int customer_id;
    vector<Customer *> customerList;
    switch(actionType) {
        case OPEN_TRAINER:
            getline(ss, substr, ' ');
            trainer_id = stoi(substr);
            while (ss.good()) {
                Customer *c;
                string customer_name;
                string strategy;
                getline(ss, customer_name, ',');
                getline(ss, strategy, ' ');

                // creating a new customer by strategy
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
            trainer_id = stoi(substr);

            action = new Order(trainer_id);
            break;
        case MOVE_CUSTOMER:
            getline(ss, substr, ' ');
            source_id = stoi(substr);
            getline(ss, substr, ' ');
            dest_id = stoi(substr);
            getline(ss, substr, ' ');
            customer_id = stoi(substr);

            action = new MoveCustomer(source_id, dest_id, customer_id);
            break;
        case CLOSE:
            getline(ss, substr, ' ');
            trainer_id = stoi(substr);

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
            trainer_id = stoi(substr);

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
    actionsLog.insert(actionsLog.begin(), action);
    return actionType != CLOSE_ALL; // breaks mainLoop when actionType is closeall, which triggers destructors
}

void Studio::mainLoop() {
    while(handleInput());
}


Studio::~Studio() {
    clear();
}

void Studio::clear() {
    for(BaseAction *action : actionsLog)
        delete action;
    actionsLog.clear();
    for(Trainer *t : trainers) {
        delete t;
    }
    trainers.clear();
    workout_options.clear();
    action_prefixes.clear();
}

bool Studio::hasBackup() {
    return backup != nullptr;
}


// copy constructor
Studio::Studio(const Studio &other): open(other.open), next_customer_id(other.next_customer_id),
        workout_options(other.workout_options),
        action_prefixes(other.action_prefixes) {

    for(Trainer *t : other.trainers)
        trainers.push_back(t->clone());
    for(BaseAction *b: other.actionsLog)
        actionsLog.push_back(b->clone());
}

// copy assignment operator
Studio &Studio::operator=(const Studio &other) {
   if(this == &other)
       return *this;
    clear();

    open = other.open;
    next_customer_id = other.next_customer_id;
    action_prefixes = other.action_prefixes;
    for(const Workout& w : other.workout_options) {
        workout_options.push_back(w);
    }
    for(BaseAction *action : other.actionsLog) {
        actionsLog.push_back(action->clone());
    }
    for(Trainer *t : other.trainers) {
        trainers.push_back(t->clone());
    }

    return *this;
}

// move constructor
Studio::Studio(Studio &&other): open(other.open), next_customer_id(other.next_customer_id),
        workout_options(other.workout_options), action_prefixes(other.action_prefixes),
        actionsLog(other.actionsLog), trainers(other.trainers) {}


// move assignment
Studio &Studio::operator=(Studio &&other) noexcept {
    if(this == &other)
        return *this;
    cout << "move assignment!" << endl;
    clear();
    open = other.open;
    next_customer_id = other.next_customer_id;
    actionsLog = other.actionsLog;
    trainers = other.trainers;

    return *this;
}

void Studio::deleteCustomerAndRollbackId(Customer *c) {
    delete c;
    next_customer_id--;
}




