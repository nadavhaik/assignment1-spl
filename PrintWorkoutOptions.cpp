#include "Action.h"
//#include "studio.h"

using namespace std;

PrintWorkoutOptions::PrintWorkoutOptions(): BaseAction() {}

void PrintWorkoutOptions::act(Studio &studio) {
    for(const Workout& w: studio.getWorkoutOptions()){
        if(w.getType() == ANAEROBIC)
            cout<<w.getName() << ", Anaerobic, " << w.getPrice()<<endl;
        else if(w.getType() == MIXED)
            cout<< w.getName() << ", Mixed, " << w.getPrice() <<endl;
        else if(w.getType() == CARDIO)
            cout<<w.getName() << ", Cardio, " << w.getPrice()<<endl;
    }
    complete();
}

std::string PrintWorkoutOptions::toString() const {
    return "workout_options Completed";
}

BaseAction *PrintWorkoutOptions::clone() {
    return new PrintWorkoutOptions();
}
