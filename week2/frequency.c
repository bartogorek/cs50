#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string note = get_string("Your note : ");
    int note_length = strlen(note);
    char all_notes[13] = {'C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g', 'A', 'a', 'B', '\0'};
    int note_index = 100;       // index number from the corresponding note in 'all_notes' including accidentals,
                                // represented as lowercase
    int octave;         // second or third character of input string
    int accidental;     // values : flat -1 / none 0 / sharp 1
    float frequency;      // return value

    //printf("%lu\n", strlen(allnotes));

    // identify note index (match character from all_notes)
    for (int i = 0; i < strlen(all_notes); i++)
    {
        if (note[0] == all_notes[i])
        {
            note_index = i;
            break;
        }
    }
    printf("Note index : %i\n", note_index);

    // identify octave
    octave = note[note_length - 1] - '0';
    printf("Octave : %i\n", octave);

    // identify accidental if it exists
    if (note_length == 3)
    {
        switch(note[1])
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
        accidental = 0;
    printf("Accidental : %i\n", accidental);

    // check octave and change frequency for 'A' accordingly
    if (octave - 4 == 0)
        frequency = 440;
    else if (octave - 4 > 0)
        frequency = 440 * pow(2, (octave - 4));
    else
        frequency = 440 / pow(2, (4 - octave));
    printf("Frequency : %f\n", frequency);

    // check 'distance' between note_index and 'A' and change frequency accordingly
    // index for 'A' = 9
    if (note_index - 9 > 0)
        frequency = frequency * pow(2, (note_index - 9) * 0.08333);
    else if (note_index - 9 < 0)
        frequency = frequency / pow(2, (9 - note_index) * 0.08333);
    printf("Frequency 2 : %f\n", frequency);

    // check accidental and change frequency accordingly
    if (accidental == 1)
        frequency = frequency * pow(2, 0.08333);
    else if (accidental == -1)
        frequency = frequency / pow(2, 0.08333);
    printf("Frequency 3 : %f\n", frequency);

}