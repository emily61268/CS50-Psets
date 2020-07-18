// Helper functions for music

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = fraction[0] - '0';
    int y = fraction[2] - '0';
    return x * (8 / y);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter;
    int octave;
    int f;
    int a;
    float freq;
    // Determine the locations of each charatcer in the string if the string is 2 chars long
    if (strlen(note) == 2)
    {
        letter = note[0];
        octave = note[1] - '0';
    }

    // Determine the locations of each charatcer in the string if the string is 3 chars long
    if (strlen(note) == 3)
    {
        letter = note[0];
        a = note[1];
        octave = note[2] - '0';
    }
    // Support notes A0 through A8
    if (letter == 'A' && strlen(note) == 2)
    {
        if (octave >= 4)  // From A4 to A8
        {
            f = 440 * pow(2, octave - 4);
            return f;
        }
        else if (octave < 4) // From A0 to A3
        {
            if (octave == 0)
            {
                freq = 440 / pow(2, 4);
                return round(freq);
            }
            if (octave == 1)
            {
                f = 440 / pow(2, 3);
                return f;
            }
            if (octave == 2)
            {
                f = 440 / pow(2, 2);
                return f;
            }
            if (octave == 3)
            {
                f = 440 / pow(2, 1);
                return f;
            }
        }
    }
    // Support notes A#0 through A#8, and Bb0 through Bb8
    // Determine if the string starts with 'A' or 'B'
    if ((letter == 'A' || letter == 'B') && strlen(note) == 3)
    {
        if ((letter == 'A' && a == 35) || (letter == 'B' && a == 98)) // Determine accidentals
        {
            if (octave >= 4)
            {
                freq = (440 * pow(2.0, 1.0/12.0)) * pow(2, octave - 4);
                return round(freq);
            }
            else if (octave < 4)
            {
                if (octave == 0)
                {
                    freq = (440 * pow(2, 0.0833333)) / pow(2, 4);
                }
                if (octave == 1)
                {
                    freq = (440 * pow(2, 0.0833333)) / pow(2, 3);
                }
                if (octave == 2)
                {
                    freq = (440 * pow(2, 0.0833333)) / pow(2, 2);
                }
                if (octave == 3)
                {
                    freq = (440 * pow(2, 0.0833333)) / pow(2, 1);
                }
                return round(freq);
            }
        }
    }
    // Support notes B0 through B8
    if (letter == 'B' && strlen(note) == 2)
    {
        if (octave >= 4) //From B4 to B8
        {
            freq = (440 * pow(2, 0.16666667)) * pow(2, octave - 4);
            return round(freq);
        }
        else if (octave < 4) // From B0 to B3
        {
            if (octave == 0)
            {
                freq = (440 * pow(2, 0.16666667)) / pow(2, 4);
            }
            if (octave == 1)
            {
                freq = (440 * pow(2, 0.16666667)) / pow(2, 3);
            }
            if (octave == 2)
            {
                freq = (440 * pow(2, 0.16666667)) / pow(2, 2);
            }
            if (octave == 3)
            {
                freq = (440 * pow(2, 0.16666667)) / pow(2, 1);
            }
            return round(freq);
        }
    }
    // Support C0 through C8
    if (letter == 'C' && strlen(note) == 2)
    {
        if (octave >= 4) // From C4 to C8
        {
            freq = (220 * pow(2, 0.25)) * pow(2, octave - 4);
            return round(freq);
        }
        else if (octave < 4) // C0 to C3
        {
            if (octave == 0)
            {
                freq = (220 * pow(2, 0.25)) / pow(2, 4);
            }
            if (octave == 1)
            {
                freq = (220 * pow(2, 0.25)) / pow(2, 3);
            }
            if (octave == 2)
            {
                freq = (220 * pow(2, 0.25)) / pow(2, 2);
            }
            if (octave == 3)
            {
                freq = (220 * pow(2, 0.25)) / pow(2, 1);
            }
            return round(freq);
        }
    }
    // Support notes C#0 through C#8, and Db0 through Db8
    // Determine if the string starts with 'C' or 'D'
    if ((letter == 'C' || letter == 'D') && strlen(note) == 3)
    {
        if ((letter == 'C' && a == 35) || (letter == 'D' && a == 98)) // Determine accidentals
        {
            if (octave >= 4)
            {
                freq = (220 * pow(2, 0.3333333)) * pow(2, octave - 4);
                return round(freq);
            }
            else if (octave < 4)
            {
                if (octave == 0)
                {
                    freq = (220 * pow(2, 0.3333333)) / pow(2, 4);
                }
                if (octave == 1)
                {
                    freq = (220 * pow(2, 0.3333333)) / pow(2, 3);
                }
                if (octave == 2)
                {
                    freq = (220 * pow(2, 0.3333333)) / pow(2, 2);
                }
                if (octave == 3)
                {
                    freq = (220 * pow(2, 0.3333333)) / pow(2, 1);
                }
                return round(freq);
            }
        }
    }
    // Support D0 through D8
    if (letter == 'D' && strlen(note) == 2)
    {
        if (octave >= 4) // From D4 to D8
        {
            freq = (220 * pow(2, 0.41666667)) * pow(2, octave - 4);
            return round(freq);
        }
        else if (octave < 4) // From D0 to D3
        {
            if (octave == 0)
            {
                freq = (220 * pow(2, 0.41666667)) / pow(2, 4);
            }
            if (octave == 1)
            {
                freq = (220 * pow(2, 0.41666667)) / pow(2, 3);
            }
            if (octave == 2)
            {
                freq = (220 * pow(2, 0.41666667)) / pow(2, 2);
            }
            if (octave == 3)
            {
                freq = (220 * pow(2, 0.41666667)) / pow(2, 1);
            }
            return round(freq);
        }
    }
    // Support notes D#0 through D#8, and Eb0 through Eb8
    // Determine if the string starts with 'D' or 'E'
    if ((letter == 'D' || letter == 'E') && strlen(note) == 3)
    {
        if ((letter == 'D' && a == 35) || (letter == 'E' && a == 98)) // Determine accidentals
        {
            if (octave >= 4)
            {
                freq = (220 * pow(2, 0.5)) * pow(2, octave - 4);
                return round(freq);
            }
            else if (octave < 4)
            {
                if (octave == 0)
                {
                    freq = (220 * pow(2, 0.5)) / pow(2, 4);
                }
                if (octave == 1)
                {
                    freq = (220 * pow(2, 0.5)) / pow(2, 3);
                }
                if (octave == 2)
                {
                    freq = (220 * pow(2, 0.5)) / pow(2, 2);
                }
                if (octave == 3)
                {
                    freq = (220 * pow(2, 0.5)) / pow(2, 1);
                }
                return round(freq);
            }
        }
    }
    // Support E0 through E8
    if (letter == 'E' && strlen(note) == 2)
    {
        if (octave >= 4) // From E4 to E8
        {
            freq = (220 * pow(2, 0.5833333)) * pow(2, octave - 4);
            return round(freq);
        }
        else if (octave < 4) // From E0 to E3
        {
            if (octave == 0)
            {
                freq = (220 * pow(2, 0.5833333)) / pow(2, 4);
            }
            if (octave == 1)
            {
                freq = (220 * pow(2, 0.5833333)) / pow(2, 3);
            }
            if (octave == 2)
            {
                freq = (220 * pow(2, 0.5833333)) / pow(2, 2);
            }
            if (octave == 3)
            {
                freq = (220 * pow(2, 0.5833333)) / pow(2, 1);
            }
            return round(freq);
        }
    }
    // Support F0 through F8
    if (letter == 'F' && strlen(note) == 2)
    {
        if (octave >= 4) // From F4 to F8
        {
            freq = (220 * pow(2, 0.6666667)) * pow(2, octave - 4);
            return round(freq);
        }
        else if (octave < 4) // From F0 to F3
        {
            if (octave == 0)
            {
                freq = (220 * pow(2, 0.6666667)) / pow(2, 4);
            }
            if (octave == 1)
            {
                freq = (220 * pow(2, 0.6666667)) / pow(2, 3);
            }
            if (octave == 2)
            {
                freq = (220 * pow(2, 0.6666667)) / pow(2, 2);
            }
            if (octave == 3)
            {
                freq = (220 * pow(2, 0.6666667)) / pow(2, 1);
            }
            return round(freq);
        }
    }
    // Support notes F#0 through F#8, and Gb0 through Gb8
    // Determine if the string starts with 'F' or 'G'
    if ((letter == 'F' || letter == 'G') && strlen(note) == 3)
    {
        if ((letter == 'F' && a == 35) || (letter == 'G' && a == 98)) // Determine accitentals
        {
            if (octave >= 4)
            {
                freq = (220 * pow(2, 0.75)) * pow(2, octave - 4);
                return round(freq);
            }
            else if (octave < 4)
            {
                if (octave == 0)
                {
                    freq = (220 * pow(2, 0.75)) / pow(2, 4);
                }
                if (octave == 1)
                {
                    freq = (220 * pow(2, 0.75)) / pow(2, 3);
                }
                if (octave == 2)
                {
                    freq = (220 * pow(2, 0.75)) / pow(2, 2);
                }
                if (octave == 3)
                {
                    freq = (220 * pow(2, 0.75)) / pow(2, 1);
                }
                return round(freq);
            }
        }
    }
    // Support G0 through G8
    if (letter == 'G' && strlen(note) == 2)
    {
        if (octave >= 4) // From G4 to G8
        {
            freq = (220 * pow(2, 0.833333)) * pow(2, octave - 4);
            return round(freq);
        }
        else if (octave < 4) // From G0 to G3
        {
            if (octave == 0)
            {
                freq = (220 * pow(2, 0.833333)) / pow(2, 4);
            }
            if (octave == 1)
            {
                freq = (220 * pow(2, 0.833333)) / pow(2, 3);
            }
            if (octave == 2)
            {
                freq = (220 * pow(2, 0.833333)) / pow(2, 2);
            }
            if (octave == 3)
            {
                freq = (220 * pow(2, 0.833333)) / pow(2, 1);
            }
            return round(freq);
        }
    }
    // Support notes G#0 through G#8, and Ab0 through Ab8
    // Determine if the string starts with 'G' or 'A'
    if ((letter == 'G' || letter == 'A') && strlen(note) == 3)
    {
        if ((letter == 'G' && a == 35) || (letter == 'A' && a == 98)) // Determine accidentals
        {
            if (octave >= 4)
            {
                freq = (220 * pow(2, 0.91666667)) * pow(2, octave - 4);
                return round(freq);
            }
            else if (octave < 4)
            {
                if (octave == 0)
                {
                    freq = (220 * pow(2, 0.91666667)) / pow(2, 4);
                }
                if (octave == 1)
                {
                    freq = (220 * pow(2, 0.91666667)) / pow(2, 3);
                }
                if (octave == 2)
                {
                    freq = (220 * pow(2, 0.91666667)) / pow(2, 2);
                }
                if (octave == 3)
                {
                    freq = (220 * pow(2, 0.91666667)) / pow(2, 1);
                }
                return round(freq);
            }
        }
    }
    return 0;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0' || s[0] == '\n')
    {
        return true;
    }
    else
    {
        return false;
    }
}
