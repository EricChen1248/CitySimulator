#pragma once
namespace helper
{
    struct Time
    {
        int Hour;
        int Minute;
    
        Time(const int h = 0, const int m = 0) : Hour(h), Minute(m) {};
    
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
            Hour -= 24;
        }
    
        int operator-(const Time &laterTime) const
        {
            int h = laterTime.Hour - Hour;
            if (h < 0)
            {
                h += 24;
            }
        
            int m = laterTime.Minute - Minute;
            if (m < 0)
            {
                m += 60;
            }
            return h * 60 + m;
        }
    };
}