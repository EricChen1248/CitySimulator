#pragma once
#include <string>
#include <iomanip>
#include <sstream>

namespace helper
{
    /**
     * \brief Time class of our game. All time related simulations should use this class for proper speed and time appropriation
     */
    struct Time
    {
        int Hour;
        int Minute;
        int Micro;
    
        Time(const int h = 0, const int m = 0) : Hour(h), Minute(m), Micro(0) {};
    
        
        /**
         * \brief 
         * \param deltaTime Time to increase by
         */
        void IncreaseTime(const float deltaTime)
        {
            Micro += static_cast<int>(deltaTime * 60000);
            while (Micro >= 1000)
            {
                ++Minute;
                Micro -= 1000;
            }
            
            while (Minute >= 60)
            {
                Minute -= 60;
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
    
        int operator-(const Time &earlierTime) const
        {
            const int h = Hour - earlierTime.Hour;
            const int m = Minute - earlierTime.Minute ;
            
            return h * 60 + m;
        }
        
        bool operator==(const Time &other) const
        {
            return Hour == other.Hour && Minute == other.Minute;
        }
        
		bool operator>(const Time &other) const
		{
			if (Hour > other.Hour)
			{
				return true;
			}

			if (Hour == other.Hour && Minute > other.Minute)
			{
				return true;
			}

			return false;
		}
        
        bool operator<(const Time &other) const
        {
            return other > *this || other == *this;
        }

		std::string ToString() const;
        std::string ToShortString() const;
    };

    /**
     * \brief Returns the time as HH:MM:SSSS format
     * \return Time as string
     */
    inline std::string Time::ToString() const
    {
        return this->ToShortString() + "." + std::to_string(Micro);
    }
    
    /**
     * \brief Returns the time as HH:MM format
     * \return Time as string
     */
    inline std::string Time::ToShortString() const
    {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw (2) << Hour << ":" << std::setw(2) << Minute;
        return ss.str();
    }
}
