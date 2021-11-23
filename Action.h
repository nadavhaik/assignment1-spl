#ifndef ACTION_H_
#define ACTION_H_
#include <vector>
#include <string>
#include "Customer.h"
#include "Trainer.h"
//#include "Studio.cpp"


enum ActionStatus{
    COMPLETED, ERROR
};

enum ActionType{
    OPEN_TRAINER, ORDER, MOVE_CUSTOMER, CLOSE, CLOSE_ALL, PRINT_WORKOUT_OPTIONS,
    PRINT_TRAINER_STATUS, PRINT_ACTIONS_LOG, BACKUP_STUDIO, RESTORE_STUDIO
};

//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    BaseAction(const BaseAction &other);
    virtual ~BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
    virtual BaseAction *clone()=0;
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    OpenTrainer(OpenTrainer const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
	const int trainerId;
	std::vector<Customer *> customers;
    std::string original_input_command;
};


class Order : public BaseAction {
public:
    Order(int id);
    Order(Order const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    MoveCustomer(MoveCustomer const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    Close(Close const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    CloseAll(CloseAll const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    PrintWorkoutOptions(PrintWorkoutOptions const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    PrintTrainerStatus(PrintTrainerStatus const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
    const int trainerId{};
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    PrintActionsLog(PrintActionsLog const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    BackupStudio(BackupStudio const &other);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    RestoreStudio(ActionStatus status);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction *clone() override;
};


#endif