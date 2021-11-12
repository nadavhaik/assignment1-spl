#include "Action.h"
#include <string>
#include <iostream>

using namespace std;

BaseAction::BaseAction() : status(ERROR) {
    errorMsg = "Error: <error_message>";
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete(){
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg){
    status = ERROR;
    cout << errorMsg << std::endl;
}


string BaseAction::getErrorMsg() const {
    return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList): trainerId(id), customers(customersList){}

void OpenTrainer::act(Studio &studio) {

}
