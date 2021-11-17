#include "Action.h"
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

