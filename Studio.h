#include "Trainer.h"
#include "Action.h"
#include <unordered_map>

#ifndef STUDIO_H_
#define STUDIO_H_


class Studio{
public:
	Studio();
    Studio(const std::string &configFilePath);
    ~Studio();
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

private:
    bool open{};
    int next_customer_id{};
    int customer_id_backup{};
    int allocateNewCustomerId();
    void backupCustomerId();
    void restoreCustomerIdFromBackup();
    void mainLoop();
    bool handleInput();
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string, ActionType> action_prefixes;
};

#endif