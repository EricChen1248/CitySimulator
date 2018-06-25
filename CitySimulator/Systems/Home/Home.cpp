#include "Home.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
//class HomeRule;


Home::Home(Plot* plot):Base(plot, HOME)
{
	homeCapacity = RandomInt(10, 20);
	color = HOME_COLOR;
	score = 0;
}
void Home::Register(Citizen* citizen)
{
	//Citizen need to register it's home in this function
	//Citizen->register(*this);
	Residents.InsertLast(citizen);
}
void Home::EndDay()
{
	//need to implement something
}
bool Home::Full()const
{
	return (homeCapacity < Residents.Count());
}
void Home::Enter()
{
	score += 5;
}
Plot* Home::GetPlot()
{
	return plot;
}