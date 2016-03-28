#ifndef FOV_DANCE_H_INCLUDED
#define FOV_DANCE_H_INCLUDED

struct FOVdance
{
    void
    update ( float& FOV )
    {
        if ( inc )
        {
            FOV += incAmount;
            if ( FOV > MAX ) inc = false;
        }
        else
        {
            FOV -= incAmount;
            if ( FOV < MIN ) inc = true;
        }
    }

private:
    bool inc { true };

    constexpr
    static
    unsigned    MAX { 179 },
                MIN { 1   };

    constexpr
    static
    float       incAmount { 0.2 };
};

#endif // FOV_DANCE_H_INCLUDED
