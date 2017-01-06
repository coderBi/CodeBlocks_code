#ifndef DATAMODEL_H_INCLUDED
#define DATAMODEL_H_INCLUDED
#include <string>
using namespace std;

struct Grade
{
    int math;
    int chinese;
    int English;
};

struct DataModel
{
    int id;
    string name;
    string address;
    struct Grade grade;
    struct DataModel* next;
};

#endif // DATAMODEL_H_INCLUDED
