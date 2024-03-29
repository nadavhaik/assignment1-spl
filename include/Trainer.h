#include "Workout.h"
#include "Customer.h"
#include <unordered_map>

#ifndef TRAINER_H_
#define TRAINER_H_

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    ~Trainer();
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    bool canAcceptAnotherCustomer();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    int getSalary();
    bool isOpen();
    void openTrainer();
    void closeTrainer();
    Trainer* clone();
    void clear();
    Trainer(Trainer const &other);
    void clearAllOrders();

private:
    int capacity;
    bool open{};
    std::vector<Customer*> customersList;
    std::unordered_map<int, Customer*> customer_by_id_index;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif