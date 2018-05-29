#pragma once

const float PI = 3.1415926f;
const float COS60 = 0.5f;
const float COS30 = 0.86602f;
const float SIN60 = 0.86602f;
const float SIN30 = 0.5f;

    
#ifdef _DEBUG
    const int LEFT = -15;
    const int RIGHT = 16;
#else
    const int LEFT = -20;
    const int RIGHT = 21;
#endif