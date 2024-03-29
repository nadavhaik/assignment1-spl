#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include "Workout.h"
#include <vector>

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual Customer *clone()=0;
    virtual ~Customer();
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;
};

class SweatyCustomer : public Customer {
public:
	SweatyCustomer(std::string name, int id);
    Customer *clone() override;
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
    Customer *clone() override;
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
private:
};


class HeavyMuscleCustomer : public Customer {
public:
	HeavyMuscleCustomer(std::string name, int id);
    Customer *clone() override;
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
private:
};


class FullBodyCustomer : public Customer {
public:
	FullBodyCustomer(std::string name, int id);
    Customer *clone() override;
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
private:
};


#endif