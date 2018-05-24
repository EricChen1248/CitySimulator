#pragma once
#include <string>
#include <iomanip>
#include <sstream>

namespace helper
{
    struct Time
    {
        int Hour;
        int Minute;
        int Micro;
    
        Time(const int h = 0, const int m = 0) : Hour(h), Minute(m), Micro(0) {};
    
        void IncreaseTime(const float deltaTime)
        {
            // TODO : adjust deltaTime to time diff
            Micro += static_cast<int>(deltaTime * 1000);
            while (Micro >= 100)
            {
                ++Minute;
                Micro -= 100;
            }
            
            while (Minute >= 60)
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
        
        std::string ToString() const;
        std::string ToShortString() const;
    };

    inline std::string Time::ToString() const
    {
        return this->ToShortString() + ":" + std::to_string(Micro);
    }
    
    inline std::string Time::ToShortString() const
    {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw (2) << Hour << ":" << std::setw(2) << Minute;
        return ss.str();
    }
}
