#include "School.h"
#include "SchoolRule.h"
#include "SchoolSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"

using helper::Time;

School::School(Plot* plot) : Base(plot, SCHOOL), studentCount(0), lateStudents(0)
{
	if (SchoolSystem::isPremium)
	{
		cost = 8000;
		operatingCost = 500;
		isPremium = true;
	    tuition = 25;
	}
	else
	{
		cost = 6000;
		operatingCost = 150;
		isPremium = false;
	    tuition = 12;
	}
    studentLimit = RandomInt(30, 40);
	color = SCHOOL_COLOR;
}

School::~School()
= default;

std::string School::ContentString()
{
	std::stringstream ss;
	if (isPremium)
	{
		ss << "Premium School" << std::endl;
	}
	else
	{
		ss << "General School" << std::endl;
	}

	ss               << "Capacity: " << studentLimit << " people"
        << std::endl << "Students: " << students.Count() << " people"
		<< std::endl << "Late:     " << lateStudents << " people"
        << std::endl << "Missing:  " << students.Count() - studentCount << " people"
		<< std::endl << "Operating cost: " << operatingCost + studentCount * tuition;
	
	return ss.str();
}

void School::NewDay()
{
	studentCount = 0;
	lateStudents = 0;
}

void School::EndDay()
{
	Government::AddTax(float(-operatingCost));
}

bool School::IsFull() const
{
    return students.Count() >= studentLimit;
}

/**
* \brief New entry ( +score )
*/
void School::Enter()
{
	Government::AddTax(float(-tuition));

	studentCount += 1;
	const Time currentTime = CoreController::Instance()->GetTime();
	if (currentTime > 8)
	{
		lateStudents += 1;
	}
}

int School::Destroy()
{
	for (auto && student : students)
	{
		SchoolRule* schoolRule = dynamic_cast<SchoolRule*>(student->FindRule(SCHOOL));
		schoolRule->assignedSchool = nullptr;
	}
	Base::Destroy();
	return cost;
}

void School::NewStudent(Citizen* citizen)
{
	students.InsertLast(citizen);
}

void School::Graduation(Citizen* citizen)
{
	students.Remove(citizen);
}