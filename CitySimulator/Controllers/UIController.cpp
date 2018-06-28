#include "UIController.h"
#include "CoreController.h"
#include "../Helpers/Constants.h"


UIController::UIController() : sfml(*CoreController::Instance()->SfmlController())
{
    nextDay = Button(Vector2f(105, 32), Vector2f(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34), WHITE, MOUSE_OVER_COLOR);
    nextDayText.setFont(CoreController::Instance()->GetFontController()->Monofur());
    nextDayText.setFillColor(BLACK);
    nextDayText.setCharacterSize(24);
    nextDayText.setPosition(WINDOW_WIDTH - 103, WINDOW_HEIGHT - 33);
    nextDayText.setString("Next Day");
        
       
    timeText.setFont(CoreController::Instance()->GetFontController()->Monofur());
    timeText.setFillColor(BLACK);
    timeText.setCharacterSize(24);
    timeText.setPosition(WINDOW_WIDTH - 88, WINDOW_HEIGHT - 33);
    
    timeRect.setSize(Vector2f(105, 32));
    timeRect.setPosition(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34);
    timeRect.setFillColor(WHITE);
    timeRect.setOutlineColor(BLACK);
    timeRect.setOutlineThickness(2);
    
    moneyText.setFont(CoreController::Instance()->GetFontController()->Monofur());
    moneyText.setFillColor(BLACK);
    moneyText.setCharacterSize(24);
    
    moneyRect.setSize(Vector2f(200, 32));
    moneyRect.setPosition(static_cast<float>(WINDOW_WIDTH) / 2 - 100,2);
    moneyRect.setFillColor(WHITE);
    moneyRect.setOutlineColor(BLACK);
    moneyRect.setOutlineThickness(2);
    
    InitSelection();
	Init_Satisfaction();
}




UIController::~UIController() = default;

/**
 * \brief Renders UI
 */
void UIController::RenderUI()
{
    Time();
    Money();
    Selection();
	Satisfaction();
}

void UIController::RenderInterDayUI()
{
    NextDayButton();    
    Money();
    Selection();
}


/**
 * \brief Button to advance to next day
 */
void UIController::NextDayButton()
{
    nextDay.Draw();
    sfml.DrawString(nextDayText);
}


/**
 * \brief Game Clock 
 */
void UIController::Time()
{
    timeText.setString(CoreController::Instance()->GetTime().ToShortString());
    sfml.DrawRect(timeRect, true);
    sfml.DrawString(timeText);
}



/**
 * \brief Game Clock 
 */
void UIController::Money()
{
    moneyText.setString("$" + std::to_string(static_cast<int>(Government::TaxDollars())));
    const sf::FloatRect bounds = moneyText.getLocalBounds();
    moneyText.setPosition(static_cast<float>(WINDOW_WIDTH - bounds.width) / 2, 2);
    sfml.DrawRect(moneyRect, true);
    sfml.DrawString(moneyText);
}

void UIController::Selection()
{
    sfml.DrawRect(selectionBackGround, true);
    food.Draw();
    bank.Draw();
    work.Draw();
    home.Draw();
    
    sfml.DrawString(foodText);
    sfml.DrawString(bankText);
    sfml.DrawString(workText);
    sfml.DrawString(homeText);
    
    sfml.DrawCircle(foodCirc, true);
    sfml.DrawCircle(bankCirc, true);
    sfml.DrawCircle(workCirc, true);
    sfml.DrawCircle(homeCirc, true);
}
void UIController::Satisfaction()
{
	if (scoreList.Count() > 0)
	{
		if (scoreList[0] <= 0.3)
		{
			food_S_Shape.setFillColor(UNSATISFIED_COLOR);
		}
		else if((scoreList[0] > 0.3)&& (scoreList[0] <= 0.7))
		{
			food_S_Shape.setFillColor(SATISFIED_COLOR);
		}
		else
		{
			food_S_Shape.setFillColor(SUPER_SATIFIED_COLOR);
		}
		food_S_Shape.setSize(Vector2f((150.f*scoreList[0]), 32.f));
	}
	else
	{
		food_S_Shape.setSize(Vector2f((153.f), 36.f));
	}
	sfml.DrawRect(food_S_Shape);
}
void UIController::InitSelection()
{
    selectionBackGround.setSize(Vector2f(152, 400));
    selectionBackGround.setPosition(WINDOW_WIDTH - 153, 2);
    selectionBackGround.setFillColor(WHITE);
    selectionBackGround.setOutlineColor(BLACK);
    selectionBackGround.setOutlineThickness(2);   
    
   
    int y = 2;
    InitSelectionButton(home, homeText, homeCirc, y, "Home", HOME_COLOR);
    InitSelectionButton(food, foodText, foodCirc, y, "Food", FOOD_COLOR);
    InitSelectionButton(work, workText, workCirc, y, "Work", WORK_COLOR);
    InitSelectionButton(bank, bankText, bankCirc, y, "Bank", BANK_COLOR);
}


void UIController::InitSelectionButton(Button& button, sf::Text& text, sf::CircleShape& circ, int& y, const std::string& str, const Color color)
{
    button = Button(Vector2f(150.f, 32.f), Vector2f(WINDOW_WIDTH - 152.f, float(y)), WHITE, MOUSE_OVER_COLOR);
    text.setFont(CoreController::Instance()->GetFontController()->Monofur());
    text.setFillColor(BLACK);
    text.setCharacterSize(24U);
    text.setPosition(WINDOW_WIDTH - 100.f, float(y));
    text.setString(str); 
    
    circ.setPosition(WINDOW_WIDTH - 146.f, y + 4.f);
    circ.setRadius(12.f);
    circ.setFillColor(color);
    circ.setOutlineColor(BLACK);
    circ.setOutlineThickness(1.f);
    
    y += 72;     
}
void UIController::Init_Satisfaction()
{
	int y = 110;
	//TODO: Setting 1
	//width shold be 153
	/*
	food_S_Shape.setSize(Vector2f(153.f, 36.f));
	food_S_Shape.setFillColor(BLACK);
	food_S_Shape.setPosition(WINDOW_WIDTH - 153.f, float(y)-2);
	*/
	
	//setting2 : width 150
	food_S_Shape.setSize(Vector2f(150.f, 32.f));
	food_S_Shape.setFillColor(BLACK);
	food_S_Shape.setPosition(WINDOW_WIDTH - 152.f, float(y));

	y += 36;
	return;
}
