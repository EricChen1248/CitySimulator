#pragma once
struct Time
{
    int Hour;
    int Minute;
    
    void IncreaseTime(const int minute)
    {
        Minute += minute;
        if (Minute >= 60)
        {
            Minute = 0;
            ++Hour;
        }
    }
    
    bool EndDay() const
    {
        return Hour >= 24;
    }
    
    void ResetDay()
    {
        Hour = 0;
        Minute = 0;
    }
    
    
};