#include "Hospital.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/HelperFunctions.h"

Hospital::Hospital(Plot* plot) : Base(plot, HOSPITAL), citizenCount(0)
{
    cost = 6000;
    medicalCost = RandomInt(350, 450);
    capacity = RandomInt(30, 70);
	comfortableCapacity = int(capacity * 0.9);
    color = HOSPITAL_COLOR;
}

void Hospital::EndDay()
{
    Government::AddTax(-dailyCost);
}

/**
 * \brief New entry ( +score )
 */
void Hospital::Enter() const
{
    Government::AddTax(medicalCost * 0.08f);
}

void Hospital::NewMember(Citizen* citizen)
{
	members.InsertLast(citizen);
}

void Hospital::MemberDied(Citizen* citizen)
{
	members.Remove(citizen);
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
		<< "(Crowded if more than" << std::endl << " 90% full)" << std::endl << "Costs per day: " << dailyCost;
    
	return ss.str();
}
