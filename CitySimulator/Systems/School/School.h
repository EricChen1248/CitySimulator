#pragma once
#include "../Base/Base.h"

class SchoolRule;
/**
* \brief School Class that handles the School plots of our city
*/
class School : public Base
{
	friend class SchoolSystem;
	friend class SchoolRule;

public:
	School(Plot* plot);
	~School();
	std::string ContentString() override;

	void NewDay() override;
	void EndDay() override;
    bool IsFull() const;
	int Destroy() override;
	void NewStudent(Citizen* citizen);
	void Graduation(Citizen* citizen);
private:
	LinkedList<Citizen*> students;
	int studentCount;
	int lateStudents;
	int operatingCost;//daily operating cost
    int studentLimit;
	bool isPremium;
    int tuition;
    
	void Enter() override;
};