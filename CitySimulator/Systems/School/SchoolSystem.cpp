#include "SchoolSystem.h"
#include "SchoolRule.h"
#include "School.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"


class SchoolRule;

SchoolSystem::SchoolSystem() : BaseSystem(SCHOOL)
{
	toggleable = true;
	SchoolRule::schoolStartTime = helper::Time(8, 0);
	SchoolRule::schoolEndTime = helper::Time(16, 0);
}


SchoolSystem::~SchoolSystem() = default;

/**
 * \brief Registers a new school plot in the system
 * \param plot Plot to be registered
 */
int SchoolSystem::Register(Plot* plot)
{
    (*plot).Register(new School(plot));
    BaseSystem::Register(plot);
    return 0;
}

/**
 * \brief Updates school system. Tally scores for school plots
 */
void SchoolSystem::Update()
{
}


float SchoolSystem::GetSatisfaction() const
{
	int totalStudents = 0;
	int totalLateStudents= 0;
	int total = 0;
	int totalLearningTime = 0;
	
	for (auto&& plot : plots)
	{
		const auto school = dynamic_cast<School*>(plot->GetPlotType());
		totalStudents += school->studentCount;
		totalLateStudents += school->lateStudents;
		total += school->students.Count();
	}

	if (total == 0) return 1.f;
	float satisfaction = totalLearningTime / (total * 4 * 2);

	satisfaction = Clamp(satisfaction, 0.f, 1.f);
	return satisfaction;
}


/**
 * \brief Resets the day (clears log & resets plots)
 */
void SchoolSystem::EndDay()
{
    for (auto && plot : plots)
    {
        plot->GetPlotType()->EndDay();
    }
}

void SchoolSystem::Toggle()
{
	isPremium = !isPremium;
}

int SchoolSystem::Cost() const
{
	if (isPremium)
	{
		return 500;
	}
	return 400;
}

std::string SchoolSystem::ContentString()
{
	std::stringstream ss;

	int total = 0;
	int totalStudents = 0;
	int totalLateStudents = 0;
	for (auto&& plot : plots)
	{
		const auto school = dynamic_cast<School*>(plot->GetPlotType());
		total += school->students.Count();
		totalStudents += school->studentCount;
		totalLateStudents += school->lateStudents;
	}

	if (totalLateStudents == 0 && totalStudents == total * 2)
	{
		ss << "Everyone was on time" << std::endl;
	}
	else
	{
		if (totalLateStudents != 0)
		{
			ss << totalLateStudents << " of " << total << " students" << std::endl << "were late to school" << std::endl;
		}
	}

	return ss.str();
}