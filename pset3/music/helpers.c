// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = fraction[0] - '0';              // numerator
    int y = fraction[2] - '0';              // denominator
    int result = x * (((y * 8) / y) / y);   // calculating number of eights
    return result;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int note_length = strlen(note);     // contains length of the string 'note'
    char all_notes[13] = {'C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g', 'A', 'a', 'B', '\0'}; // includes lowercase to represent #/b
    // index number from the corresponding note in 'all_notes' including accidentals,
    // represented as lowercase
    int note_index = 100;
    int octave;         // second or third character of input  (depending if flat/sharp exists)
    int accidental;     // values : flat -1 / none 0 / sharp 1
    float frequency;    // return value
    int result;         // contains result as 'int'

    // identify note index (match character from all_notes)
    for (int i = 0; i < strlen(all_notes); i++)
    {
        if (note[0] == all_notes[i])
        {
            note_index = i;
            break;
        }
    }

    // identify octave
    octave = note[note_length - 1] - '0';

    // identify accidental if it exists
    if (note_length == 3)
    {
        switch (note[1])
        {
            case '#':
                accidental = 1;
                break;
            case 'b':
                accidental = -1;
                break;
            default:
                accidental = 0;
                break;
        }
    }
    else
    {
        accidental = 0;
    }

    // check octave and change frequency for 'A' accordingly
    if (octave - 4 == 0)
    {
        frequency = 440;
    }
    else if (octave - 4 > 0)
    {
        frequency = 440 * pow(2, (octave - 4));
    }
    else
    {
        frequency = 440 / pow(2, (4 - octave));
    }

    // check 'distance' between note_index and 'A' and change frequency accordingly
    // index for 'A' = 9
    if (note_index - 9 > 0)
    {
        frequency = frequency * pow(2, (note_index - 9) * 0.08333);
    }
    else if (note_index - 9 < 0)
    {
        frequency = frequency / pow(2, (9 - note_index) * 0.08333);
    }

    // check accidental and change frequency accordingly
    if (accidental == 1)
    {
        frequency = frequency * pow(2, 0.08333);
    }
    else if (accidental == -1)
    {
        frequency = frequency / pow(2, 0.08333);
    }

    result = round(frequency);
    return result;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
