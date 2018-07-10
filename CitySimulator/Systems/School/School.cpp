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
		operatingCost = 100;
		isPremium = true;
	    tuition = 10;
	}
	else
	{
		cost = 6000;
		operatingCost = 80;
		isPremium = false;
	    tuition = 8;
	}
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
	Government::AddTax(-operatingCost);
}

/**
* \brief New entry ( +score )
*/
void School::Enter()
{
	Government::AddTax(-tuition);

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