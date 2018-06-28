#include "UIController.h"
#include "CoreController.h"
#include "../Helpers/Constants.h"


UIController::UIController() : sfml(*CoreController::Instance()->SfmlController())
{
}

UIController::~UIController()
{
    selectionButtons.Dispose();
}

void UIController::Initialize()
{
    nextDay = Button(Vector2f(105, 32), Vector2f(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34), WHITE, MOUSE_OVER_COLOR);
    nextDayText.setFont(FontController::Monofur());
    nextDayText.setFillColor(BLACK);
    nextDayText.setCharacterSize(24);
    nextDayText.setPosition(WINDOW_WIDTH - 103, WINDOW_HEIGHT - 33);
    nextDayText.setString("Next Day");
        
    timeText.setFont(FontController::Monofur());
    timeText.setFillColor(BLACK);
    timeText.setCharacterSize(24);
    timeText.setPosition(WINDOW_WIDTH - 88, WINDOW_HEIGHT - 33);
    
    timeRect.setSize(Vector2f(105, 32));
    timeRect.setPosition(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34);
    timeRect.setFillColor(WHITE);
    timeRect.setOutlineColor(BLACK);
    timeRect.setOutlineThickness(2);
    
    moneyText.setFont(FontController::Monofur());
    moneyText.setFillColor(BLACK);
    moneyText.setCharacterSize(24);
    
    moneyRect.setSize(Vector2f(200, 32));
    moneyRect.setPosition(static_cast<float>(WINDOW_WIDTH) / 2 - 100,2);
    moneyRect.setFillColor(WHITE);
    moneyRect.setOutlineColor(BLACK);
    moneyRect.setOutlineThickness(2);
    
    InitSelection();
	InitSatisfaction();
}


/**
 * \brief Renders UI
 */
void UIController::RenderUI()
{
    Time();
    Money();
    DrawSelection();
	DrawSatisfaction();
}

void UIController::RenderInterDayUI()
{
    NextDayButton();    
    Money();
    DrawSelection();
    DrawSatisfaction();
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

void UIController::DrawSelection()
{
    sfml.DrawRect(selectionBackGround, true);
    for (auto && selectionButton : selectionButtons)
    {
        selectionButton->Draw(sfml);
    }
    
}
void UIController::DrawSatisfaction()
{
	if (scoreList.Count() > 0)
	{
		homeSatisShape.setFillColor(Satisfy(scoreList[0]));
		foodSatisShape.setFillColor(Satisfy(scoreList[1]));
		homeSatisShape.setSize(Vector2f((150.f*scoreList[0]), 32.f));
		foodSatisShape.setSize(Vector2f((150.f*scoreList[1]), 32.f));

	}
	else
	{
		homeSatisShape.setSize(Vector2f((153.f), 36.f));
		foodSatisShape.setSize(Vector2f((153.f), 36.f));
	}
	sfml.DrawRect(homeSatisShape);
	sfml.DrawRect(foodSatisShape);

}
void UIController::InitSelection()
{
    selectionBackGround.setSize(Vector2f(152, 500));
    selectionBackGround.setPosition(WINDOW_WIDTH - 153, 2);
    selectionBackGround.setFillColor(WHITE);
    selectionBackGround.setOutlineColor(BLACK);
    selectionBackGround.setOutlineThickness(2);   
    
    int y = 2;
    
    // NONE,    FOOD,	WORK,	BANK,	HOME,	STORE, 	SCHOOL,    HOSPITAL
    const int systemCount = 7;
    std::string strings[systemCount]{ "Food", "Work", "Bank", "Home", "Store", "School", "Hospital"};
    Color colors[systemCount]{ FOOD_COLOR,	WORK_COLOR,	BANK_COLOR,	HOME_COLOR, STORE_COLOR, SCHOOL_COLOR, HOSPITAL_COLOR};
    for (int i = 0; i < systemCount; ++i)
    {
        selectionButtons.InsertLast(InitSelectionButton(y, strings[i], colors[i]));
    }
}

sf::Color UIController::Satisfy(float ratio) const
{
	if (ratio < 0.3)
		return UNSATISFIED_COLOR;
	else if ((ratio >= 0.3) && (ratio < 0.7))
		return SATISFIED_COLOR;
	else
		return SUPER_SATIFIED_COLOR;
}

void UIController::InitSatisfaction()
{
	int y = 38;

	//TODO: Setting 1
	//width shold be 153
	/*
	food_S_Shape.setSize(Vector2f(153.f, 36.f));
	food_S_Shape.setFillColor(BLACK);
	food_S_Shape.setPosition(WINDOW_WIDTH - 153.f, float(y)-2);
	*/
	
	//setting2 : width 150
	homeSatisShape.setSize(Vector2f(150.f, 32.f));
	homeSatisShape.setFillColor(WHITE);
	homeSatisShape.setPosition(WINDOW_WIDTH - 152.f, 38);

	foodSatisShape.setSize(Vector2f(150.f, 32.f));
	foodSatisShape.setFillColor(WHITE);
	foodSatisShape.setPosition(WINDOW_WIDTH - 152.f, 110);




	y += 72;

	return;
}

SelectionButton* UIController::InitSelectionButton(int& y, const std::string& str, const Color color)
{
    const auto button = new SelectionButton(Vector2f(150.f, 32.f), Vector2f(WINDOW_WIDTH - 152.f, float(y)), WHITE,
                                      MOUSE_OVER_COLOR, str, y, color);
    y += 72;
    return button;
}
