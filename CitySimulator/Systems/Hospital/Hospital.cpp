#include "Hospital.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/HelperFunctions.h"

Hospital::Hospital(Plot* plot) : Base(plot, HOSPITAL), citizenCount(0)
{
    cost = 1000;
    medicalCost = RandomInt(50, 100);
    capacity = RandomInt(50, 100); // TODO : capacity
	comfortableCapacity = int(capacity * 0.9); // TODO : double limitation
    color = HOSPITAL_COLOR;
}

/**
 * \brief New entry ( +score )
 */
void Hospital::Enter() const
{
    Government::AddTax(medicalCost * 0.1f);
}

void Hospital::NewMember(Citizen* citizen)
{
	members.InsertLast(citizen);
}

int Hospital::Destroy()
{
	for (auto && member : members)
	{
		member->Die();
	}
	Base::Destroy();
	return Cost();
}


std::string Hospital::ContentString()
{
	std::stringstream ss;

	if (members.Count() >= capacity)
	{
		ss << "It's totally full." << std::endl << std::endl;
	}
	else if (members.Count() >= comfortableCapacity)
	{
		ss << "It's too crowded." << std::endl << std::endl;
	}
	else
	{
		ss << "Environment here" << std::endl << "is comfortable." << std::endl << std::endl;
	}

	ss << "Members: " << members.Count() << " people" << std::endl << "Limitation: " << capacity << " people" << std::endl
		<< "(Crowded if more than" << std::endl << " 90% full)";
	return ss.str();

	// TODO : 90%?
}
