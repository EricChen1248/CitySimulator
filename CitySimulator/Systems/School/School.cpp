#include "School.h"
#include "SchoolRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"

using helper::Time;

School::School(Plot* plot) : Base(plot, SCHOOL), studentCount(0), lateStudents(0)
{
	if (isPremium == true)
	{
		cost = 500;
		operatingCost = 50;
	}
	else
	{
		cost = 400;
		operatingCost = 40;
	}
	color = SCHOOL_COLOR;
}

School::~School()
= default;

std::string School::ContentString()
{
	std::stringstream ss;
	if (isPremium == true)
	{
		ss << "Premium School" << std::endl;
	}
	else
	{
		ss << "General School" << std::endl;
	}

	if (lateStudents > 0)
	{
		ss << lateStudents  << " students" << std::endl << "were late." << std::endl << std::endl;
	}
	else
	{
		ss << "Today was an" << std::endl << "excellent day." << std::endl << std::endl;
	}

	ss << "Students: " << studentCount << " people"
		<< std::endl << "Late: " << lateStudents << " people"
		<< std::endl << "Operating cost: " << operatingCost;
	
	return ss.str();
}

void School::NewDay()
{
	studentCount = 0;
	lateStudents = 0;
	Government::AddTax(-operatingCost);
}

void School::EndDay()
{
	score = 0;
}

/**
* \brief New entry ( +score )
*/
void School::Enter()
{
	Government::AddTax(-cost);

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