/*
KeccakTools

The Keccak sponge function, designed by Guido Bertoni, Joan Daemen,
Michaël Peeters and Gilles Van Assche. For more information, feedback or
questions, please refer to our website: http://keccak.noekeon.org/

Implementation by the designers,
hereby denoted as "the implementer".

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#include <string.h>
#include "Keccak.h"
#include "KeccakCrunchyContest.h"

int verifyPreimageChallenge(int r, int c, int nr, const UINT8 image[], int start, const UINT8 preimage[], const int preimageLength)
{
    const int imageLength = 80;
    UINT8 output[10];
    ReducedRoundKeccak keccakRR(r, c, start, nr);
    keccakRR.absorb(preimage, preimageLength);
    keccakRR.squeeze(output, imageLength);
    cout << "Preimage challenge on " << keccakRR << ": ";
    if (memcmp(output, image, (imageLength+7)/8) == 0) {
        cout << "OK!" << endl;
        return 1;
    }
    else {
        cout << "failed." << endl;
        return 0;
    }
}

int verifyCollisionChallenge(int r, int c, int nr, int start, const UINT8 input1[], const int input1Length, const UINT8 input2[], const int input2Length)
{
    const int imageLength = 160;
    UINT8 output1[20], output2[20];
    {
        ReducedRoundKeccak keccakRR(r, c, start, nr);
        keccakRR.absorb(input1, input1Length);
        keccakRR.squeeze(output1, imageLength);
    }
    {
        ReducedRoundKeccak keccakRR(r, c, start, nr);
        keccakRR.absorb(input2, input2Length);
        keccakRR.squeeze(output2, imageLength);
        cout << "Collision challenge on " << keccakRR << ": ";
    }
    if (memcmp(output1, output2, (imageLength+7)/8) == 0) {
        cout << "OK!" << endl;
        return 1;
    }
    else {
        cout << "failed." << endl;
        return 0;
    }
}

void verifyPreimageChallenges()
{
    int counter = 0;
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=1]: preimage challenge
        40, 160, 1, (const UINT8*)"\xe9\xf5\x7f\x02\xa9\xb0\xeb\xd8\x44\x98",
        // Solution by Joan Boyar (University of Southern Denmark) and Rene Peralta (NIST)
        0, // starting from first round
        (const UINT8*)"\x01\x00\x00\x00\x00\x58\x59\x0e\x59\xbf\x41\x9e\x19\x81\xb6", 117
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=1]: preimage challenge
        240, 160, 1, (const UINT8*)"\xd9\xd6\xd3\xc8\x4d\x1a\xc1\xd7\x5f\x96",
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\xD9\xC4\xF4\xFA\xBE\x46\x02\x00\x00\x80\x69\xFA\xF4\xFA\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x06\x4A\x10\x00", 224
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=1]: preimage challenge
        240, 160, 1, (const UINT8*)"\xd9\xd6\xd3\xc8\x4d\x1a\xc1\xd7\x5f\x96",
        // Solution by Tim Rademacher (Lexmark International, Inc.)
        0, // starting from first round
        (const UINT8*)"\x1c\xbd\x24\x19\xa6\x9b\x83\xa9\x8e\xcb\x64\x57", 96
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=1]: preimage challenge
        640, 160, 1, (const UINT8*)"\x3f\x41\x9f\x88\x1c\x42\xcf\xfc\x5f\xd7",
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x0D\x97\x8F\x88\x38\x02\xD6\x21\x00\x00\x00\xEB\x00\x00\x08\x00\x00\x47\x00\x90\x0D\x97\x8F\x88\x00\x00\xD6\x21\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\xE8\xEB\x00\x00\x00\x00\x00\x00\x00\x00\xF4\xCC\x01\x00\x00\x00\x00\x00\x02\x00\xE0\x00\x00\x88\x08\x00\x00\x00\x00\x00", 636
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=1]: preimage challenge
        640, 160, 1, (const UINT8*)"\x3f\x41\x9f\x88\x1c\x42\xcf\xfc\x5f\xd7",
        // Solution by Tim Rademacher (Lexmark International, Inc.)
        0, // starting from first round
        (const UINT8*)"\xfd\xc8\x18\x7f\x70\x9e\x46\x5a\x06\x3c\xea\x7f\x2d\x55\xd4\x59\x62\xa8\x2a\xc2\xe6\xf9\x0b\xab", 192
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=1]: preimage challenge
        1440, 160, 1, (const UINT8*)"\x0f\x0a\xf7\x07\x4b\x6a\xbd\x48\x6f\x80",
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x90\x00\x00\x00\x00\xD6\x0B\x00\x00\x70\x7F\x03\xA4\x0E\x0A\x80\x00\x0B\x00\x00\x48\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 1436
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=1]: preimage challenge
        1440, 160, 1, (const UINT8*)"\x0f\x0a\xf7\x07\x4b\x6a\xbd\x48\x6f\x80",
        // Solution by Tim Rademacher (Lexmark International, Inc.)
        0, // starting from first round
        (const UINT8*)"\x26\xf4\xc2\xde\xfa\x25\x62\x7d\x4a\xbb\xfe\x87\x51\x78\xf5\x4d\x65\x2d\x65\xb0\x21\xc5\x75\xf0\x27\xed\x18\x92\xa9\x83\x18\x2b\xae\x9d\xe8\xf7\x1a\xb7\x3d\xfe\xd2\x16\xea\xb4\x78\x42\xf1\xb2", 384
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=2]: preimage challenge
        40, 160, 2, (const UINT8*)"\x02\x4a\x55\x18\xe1\xe9\x5d\xb5\x32\x19",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=2]: preimage challenge
        240, 160, 2, (const UINT8*)"\x7a\xb8\x98\x1a\xda\x8f\xdb\x60\xae\xfd",
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\xC5\x3F\x88\xD9\x2B\x9D\x19\x69\xB9\x39\xEC\x29\x22\x4A\xFF\x45\x05\x97\xC8\x4C\xD0\x6E\x46\x4B\xB6\x90\x54\x7B\x07\x0F", 236
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=2]: preimage challenge
        640, 160, 2, (const UINT8*)"\x82\x8d\x4d\x09\x05\x0e\x06\x35\x07\x5e",
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\xDA\x17\x06\xF1\x47\xDB\xF9\x3D\x10\x2B\xA4\xBB\x15\x7E\x89\xB7\x37\xD0\x95\x83\xEF\xAA\x6B\xAA\x6D\x88\xF9\xBE\xFC\x55\x08\x7D\xEE\xB3\x39\x57\x42\x21\xDE\xB7\x7A\x45\x1E\xAB\x59\xF6\xBD\x60\xB8\x86\x5C\x00\x39\x6F\xBF\x7A\x0E\x58\x22\x42\xC0\xDF\xD4\xC2\xA8\x33\x61\xB5\x90\x85\x0E\x22\x3F\x77\xD6\xC6\xB1\x27\x03\x0C", 636
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=2]: preimage challenge
        1440, 160, 2, (const UINT8*)"\x63\x90\x22\x0e\x7b\x5d\x32\x84\xd2\x3e",
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x11\xFE\x35\xC8\x5C\x41\x5B\x35\xF6\x11\xBC\x40\xD5\x5E\xCA\x16\xBA\x51\x98\xFA\x6C\x42\xC7\x08\x79\x3A\x86\xE9\xBC\x50\x48\x1F\xAD\x98\xB8\xCB\x1B\x7E\x87\xB6\xA3\x93\x59\x24\xDB\x03\xB0\xEB\x23\xB0\x97\xD0\x87\xA4\x7C\xF0\x14\x61\x3A\x43\xF4\x3B\x97\x43\xBA\x4B\x5D\x04\xAA\xBD\xC5\x22\xB5\x66\x59\x9B\x2C\x5E\xF8\x1A\xB3\xBC\x8C\x2F\x21\x89\xC0\xAC\x33\xE7\x38\xAB\x4B\x99\x18\xA4\x0B\x02\x4C\xF0\x69\xA3\xED\xD5\x17\xA1\xEB\x7F\x87\x61\xC9\x5C\x23\xC6\x6B\x08\x88\xE9\x86\x94\x67\x75\x0D\x0B\x4D\xD6\x13\xAC\xA1\x92\x6A\x89\xF5\xAD\x8B\x57\x87\xD8\x6E\x4F\xDC\xD0\x2B\x28\x2A\x93\x1E\xE8\x10\xB6\xAB\xF5\x36\x34\xB7\x11\x6D\xDF\xCA\x1A\x88\x83\xBA\x57\x61\xE3\xC9\x5E\x38\x63\xC0\x04\x6F\x43\x68\xCA\x0A\xA0\xAE\x0A", 1436
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=3]: preimage challenge
        40, 160, 3, (const UINT8*)"\xd8\xed\x85\x69\x2a\xfb\xee\x4c\x99\xce",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=3]: preimage challenge
        240, 160, 3, (const UINT8*)"\x5c\x9d\x5e\x4b\x38\x5e\x9c\x4f\x8e\x2e",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=3]: preimage challenge
        640, 160, 3, (const UINT8*)"\x00\x7b\xb5\xc5\x99\x80\x66\x0e\x02\x93",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=3]: preimage challenge
        1440, 160, 3, (const UINT8*)"\x06\x25\xa3\x46\x28\xc0\xcf\xe7\x6c\x75",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=4]: preimage challenge
        40, 160, 4, (const UINT8*)"\x74\x2c\x7e\x3c\xd9\x46\x1d\x0d\x03\x4e",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=4]: preimage challenge
        240, 160, 4, (const UINT8*)"\x0d\xd2\x5e\x6d\xe2\x9a\x42\xad\xb3\x58",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=4]: preimage challenge
        640, 160, 4, (const UINT8*)"\x75\x1a\x16\xe5\xe4\x95\xe1\xe2\xff\x22",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=4]: preimage challenge
        1440, 160, 4, (const UINT8*)"\x7d\xaa\xd8\x07\xf8\x50\x6c\x9c\x02\x76",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=5]: preimage challenge
        40, 160, 5, (const UINT8*)"\xe0\x53\xf9\x64\x4f\xaa\xb1\xda\x31\x1b",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=5]: preimage challenge
        240, 160, 5, (const UINT8*)"\x8d\xf4\x44\x09\xb4\x6f\xb8\xc6\x1b\xc4",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=5]: preimage challenge
        640, 160, 5, (const UINT8*)"\x6e\xf2\x61\x6f\xeb\xb9\x9b\x1f\x70\xed",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=5]: preimage challenge
        1440, 160, 5, (const UINT8*)"\x65\x3b\xc0\xf8\x7d\x26\x4f\x08\x57\xd0",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=6]: preimage challenge
        40, 160, 6, (const UINT8*)"\xe5\x1c\x00\xc4\x8e\xd5\xdb\x07\x02\xb3",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=6]: preimage challenge
        240, 160, 6, (const UINT8*)"\x57\x16\xe7\x01\xef\x67\xcc\x04\x48\xb0",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=6]: preimage challenge
        640, 160, 6, (const UINT8*)"\x5f\x9e\x63\x88\x4f\x2e\x94\xf1\xa1\x0e",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=6]: preimage challenge
        1440, 160, 6, (const UINT8*)"\xd6\x05\x33\x5e\xdc\xe7\xd2\xca\xf4\x10",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=7]: preimage challenge
        40, 160, 7, (const UINT8*)"\x95\x93\x25\xc5\x67\x73\xa7\x4a\x43\xc6",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=7]: preimage challenge
        240, 160, 7, (const UINT8*)"\x9c\xec\xce\x92\x93\x8a\xea\xba\x26\xaf",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=7]: preimage challenge
        640, 160, 7, (const UINT8*)"\xa4\xc1\x35\x21\x90\x12\xaa\xc8\x08\xed",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=7]: preimage challenge
        1440, 160, 7, (const UINT8*)"\x5e\x0d\x17\x9c\x50\xc2\x93\x0c\x0d\x76",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=8]: preimage challenge
        40, 160, 8, (const UINT8*)"\x05\x4d\xda\xf1\xb9\xb5\x9b\x9a\x60\xbf",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=8]: preimage challenge
        240, 160, 8, (const UINT8*)"\x19\xc2\xd8\xff\x69\xe5\x66\xa5\x07\xc9",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=8]: preimage challenge
        640, 160, 8, (const UINT8*)"\xf4\x83\x5d\x80\x2a\xab\xc5\xbe\x75\x8e",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=8]: preimage challenge
        1440, 160, 8, (const UINT8*)"\x34\xe1\x81\x23\x29\xd5\xe8\x9d\x67\x1a",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=9]: preimage challenge
        40, 160, 9, (const UINT8*)"\x5e\xd1\xa9\xc1\x84\xeb\x72\xb9\x45\x46",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=9]: preimage challenge
        240, 160, 9, (const UINT8*)"\x78\xd6\x58\xde\xc5\x01\xee\xd6\x3b\x1e",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=9]: preimage challenge
        640, 160, 9, (const UINT8*)"\x2e\xdd\x24\x58\x7f\x22\x5c\x69\x6e\x61",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=9]: preimage challenge
        1440, 160, 9, (const UINT8*)"\xca\x18\x6a\x0f\xe1\x26\xed\xbe\x2c\xa6",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=10]: preimage challenge
        40, 160, 10, (const UINT8*)"\xc3\x8f\x61\x8f\x53\xa9\x6e\x4f\xfd\x53",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=10]: preimage challenge
        240, 160, 10, (const UINT8*)"\x46\x68\x1a\x4a\x3a\x97\x5b\x16\x2a\xc4",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=10]: preimage challenge
        640, 160, 10, (const UINT8*)"\xb8\x6d\xb6\x0f\xf7\x23\x18\x76\x6e\xef",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=10]: preimage challenge
        1440, 160, 10, (const UINT8*)"\xdf\x7b\xf3\x01\x7c\xd3\x22\xa4\x6c\x31",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=11]: preimage challenge
        40, 160, 11, (const UINT8*)"\x19\xf8\xe6\xbc\x5d\x71\x41\x77\x65\x95",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=11]: preimage challenge
        240, 160, 11, (const UINT8*)"\x12\x9e\x94\x0f\x63\x43\x00\xf6\xb4\x14",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=11]: preimage challenge
        640, 160, 11, (const UINT8*)"\xa2\x49\x0a\x3e\x68\xd5\xd0\x2d\xd4\xaa",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=11]: preimage challenge
        1440, 160, 11, (const UINT8*)"\x69\xc9\x4f\x0a\xe8\x30\x40\x26\xb3\xda",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=40, c=160, rounds=12]: preimage challenge
        40, 160, 12, (const UINT8*)"\x20\x68\x65\xeb\x08\xb4\x2a\x66\x63\xe1",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=240, c=160, rounds=12]: preimage challenge
        240, 160, 12, (const UINT8*)"\x85\x5a\x86\x45\x96\xc5\x1c\xaf\x7d\x3d",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=640, c=160, rounds=12]: preimage challenge
        640, 160, 12, (const UINT8*)"\x68\xed\xde\x13\xa4\x79\xe1\x47\x71\xbd",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );
    counter += verifyPreimageChallenge(
        // Keccak[r=1440, c=160, rounds=12]: preimage challenge
        1440, 160, 12, (const UINT8*)"\xbf\x8c\x82\x63\xa9\x87\x59\x5b\x21\xc0",
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24 // fill in this line
     );

    cout << dec << counter << " correct preimage challenge(s)." << endl;
}

void verifyCollisionChallenges()
{
    int counter = 0;
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=1]: collision challenge
        40, 160, 1,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=1]: collision challenge
        240, 160, 1,
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x7F\x08\x38\x01\x00\x00\x00\x00\x03\x90\x36\x05\x38\x01\x00\x00\x10\x02\x02\x00\x41\x0C\x20\x04\x00\x00\x00\x00\x00\x00", 236,
        (const UINT8*)"\xED\x2B\x38\x01\x20\x23\x00\x00\x93\x81\x76\x43\x38\x01\x00\x00\x90\x8E\x02\x00\xD3\x2F\x21\x1D\x00\x00\x00\x00\x00\x00", 236
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=1]: collision challenge
        240, 160, 1,
        // Solution by Tim Rademacher (Lexmark International, Inc.)
        0, // starting from first round
        (const UINT8*)"\x02\x9d\x93\x79\xdb\x28\x8f\xd6\x5f\x8d\xfd\x9a\x84\x6d\x00\x00\x1d\xf6\x8a\x7f\x90\x72\x00\x00\x6b\xa4", 208,
        (const UINT8*)"\x5b\x15\x78\xe1\xc6\x5b\x8f\xd6\xd1\x34\xc7\x7c\x84\x6d\x00\x00\x68\x3a\x8a\x7f\xc9\xfa\x00\x00\x6b\xa4", 208
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=1]: collision challenge
        640, 160, 1,
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x87\x02\x00\x00\x43\x00\x00\x80\x42\x00\x00\x00\x08\x00\x80\x10\x00\x00\x20\x90\x87\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x80\x00\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x43\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x80\x00\x00\x00\x10\x00\x00\x00\x00", 636,
        (const UINT8*)"\x00\x02\x00\x80\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x10\x00\x00\x00\x90\x00\x02\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x10\x00\x00\x00\x00", 636
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=1]: collision challenge
        640, 160, 1,
        // Solution by Tim Rademacher (Lexmark International, Inc.)
        0, // starting from first round
        (const UINT8*)"\xae\x69\xbe\xb7\xed\x58\x74\x56\xd5\x64\x6c\xde\x63\x36\xcd\xdf\x0b\x84\xe9\x12\x12\xe9\xa1\x20", 192,
        (const UINT8*)"\x65\xb5\xa3\xeb\x6c\x04\x62\xf5\x45\xaf\x0e\xea\x23\x18\x46\x0e\xc3\xe1\xd8\x08\xf9\xa2\x79\x14", 192
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=1]: collision challenge
        1440, 160, 1,
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x01\x02\x00\x20\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x08\x00\x00\x00\x00\x08\x00\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x01\x02\x00\x20\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 1436,
        (const UINT8*)"\x00\x02\x00\x20\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x20\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x90\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x02\x00\x00\x00", 1436
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=1]: collision challenge
        1440, 160, 1,
        // Solution by Alexandre Duc (Ecole Polytechnique Federale de Lausanne, Switzerland), Jian Guo (Institute for Infocomm Research, Singapore), Thomas Peyrin and Lei Wei (Nanyang Technological University, Singapore)
        0, // starting from first round
        (const
UINT8*)"\xdd\xe5\x47\xb0\x7d\xc6\x48\xdd\x00\xdd\x58\xa2\x02\x64\x1f\x49\xce\x16\xb5\xb1\xe4\xd2\x12\x9d\xe3\x37\x14\xfc\x93\xd2\x79\x70\xb8\xc1\x20\x35\x87\x68\x12\x87\x45\x6a\x29\x47\xce\x48\x90\x9d\x5e\x45\x4e\x43\x18\x61\xe0\xfb\x98\xf5\xf7\x2b\xc7\x71\x9c\x7f\x32\xbc\xb4\xb9\x25\xc6\x40\x6a\x31\x69\xb2\xff\xb2\x42\x9c\x10\x88\xeb\x53\xa0\x4c\x34\x9b\xe4\x29\x93\x0f\xf0\x04\xab\x70\x36\x68\x24\xef\x8d\xeb\x2f\xf7\x1c\x98\xa9\x1b\x4a\xec\xb8\x5b\x74\xa3\xae\x14\xef\xe2\xaf\xd3\x0b\x42\xe2\xfc\x46\x8e\x6c\x7c\xf6\x90\x6b\x83\x7b\x9a\x7a\x97\x33\x24\xb3\x7d\x10\x6b\xd8\x84\x0e\x87\x98\xfd\x69\x47\xd0\x75\x8a\xb2\x71\xd0\x40\xdd\x4d\x36\x6d\xb8\xb9\xe9\x53\x34\x80\x86\x58\x33\x03\x68\x9e\xdc\xec\xac\x63\x84\xa9\xcc\xcb\x79\x41\x55\x2c\xb2\x26\x6c\x8f\x73\xa3\xfd\x2b\x5c\xe6\x7e\x90\x66\x04\xe8\x9a\x18\x50\x38\xe4\x3c\xe5\x47\xc0\x8e\x13\x8c\x08\x55\xe1\x34\x07\x07\xa0\x97\x7a\x43\x94\xa6\xa0\x7a\x24\x30\xe0\x29\x19\x7a\x31\x69\xb3\x15\xa6\x98\x5c\x66\x26\x6f\xf2\x2e\xc4\xd4\x62\xcc\xdb\x03\x63\x56\x46\xf7\xfc\xe6\x71\x20\x17\x51\x49\x30\xcc\x7a\x91\x7f\x8f\x3f\x17\xeb\xa6\x3d\x5b\x98\x6c\x1f\x6c\xce\xeb\x48\xd1\x4e\x9e\x18\x45\x9a\xff\xb6\xba\x15\x08\x04\x45\xd4\x7e\xdf\x53\x0e\x1e\x6a\xf9\xc4\xa7\x54\x55\x13\x74\xc9\xe2\x5f\x11\xb3\xae\xaf\xcb\xf3\x49\xca\xaa\x04\xdf\xa2\x08\x25\x86\x86\x05\xd9\x94\x22\x43\x8e\xe7\xea\xe2\x44\xfe\x56\x0d\xe0\xb6\x1f\x93\x64\xce\x5f\x57\x18\x29\x01\x1c\x08\xb3\x24\x2d\x39\xaa\x31\x12\x3f",
2872,
        (const
UINT8*)"\xdd\xe5\x47\xb0\x7d\xc6\x48\xdd\x00\xdd\x58\xa2\x02\x64\x1f\x49\xce\x16\xb5\xb1\xe4\xd2\x12\x9d\xe3\x37\x14\xfc\x93\xd2\x79\x70\xb8\xc1\x20\x35\x87\x68\x12\x87\x45\x6a\x29\x47\xce\x48\x90\x9d\x5e\x45\x4e\x43\x18\x61\xe0\xfb\x98\xf5\xf7\x2b\xc7\x71\x9c\x7f\x32\xbc\xb4\xb9\x25\xc6\x40\x6a\x31\x69\xb2\xff\xb2\x42\x9c\x10\x88\xeb\x53\xa0\x4c\x34\x9b\xe4\x29\x93\x0f\xf0\x04\xab\x70\x36\x68\x24\xef\x8d\xeb\x2f\xf7\x1c\x98\xa9\x1b\x4a\xec\xb8\x5b\x74\xa3\xae\x14\xef\xe2\xaf\xd3\x0b\x42\xe2\xfc\x46\x8e\x6c\x7c\xf6\x90\x6b\x83\x7b\x9a\x7a\x97\x33\x24\xb3\x7d\x10\x6b\xd8\x84\x0e\x87\x98\xfd\x69\x47\xd0\x75\x8a\xb2\x71\xd0\x40\xdd\x4d\x36\x6d\xb8\xb9\xe9\x53\x34\x80\x86\x58\x33\x03\x68\x9e\xdc\xec\xac\x63\x84\xa9\xcc\xcb\x79\x41\x55\x2c\xb2\x26\x6c\x8f\x73\xa3\xfd\x2b\x5c\xe6\x7e\x90\x66\x04\xe8\x9a\x08\x50\x38\xe4\x3c\xe5\x47\xc0\x8e\x13\x8c\x08\x55\xe1\x34\x07\x07\xa0\x97\x7a\x43\x94\xa6\xa0\x7a\x24\x30\xe0\x29\x19\x7a\x31\x69\xb3\x15\xa6\x98\x5c\x66\x26\x6f\xf2\x2e\xc4\xd4\x62\xcc\xdb\x03\x63\x56\x46\xf7\xfc\xe6\x71\x20\x17\x51\x49\x30\xcc\x7a\x99\x7f\x8f\x3f\x17\xeb\xa6\x3d\x5b\x98\x6c\x1f\x6c\xce\xeb\x48\xd1\x4e\x9e\x18\x45\x9a\xfe\xb6\xba\x15\x08\x04\x45\xd4\x7e\xdf\x53\x0e\x1e\x6a\xf9\xc4\xa7\x54\x5d\x13\x74\xc9\xe2\x5f\x11\xb3\xae\xaf\xcb\xf3\x49\xca\xaa\x04\xdf\xb2\x08\x25\x86\x86\x04\xd9\x94\x22\x43\x8e\xe7\xea\xe2\x44\xfe\x56\x0d\xe0\xb6\x1f\x93\x64\xce\x5f\x57\x18\x29\x01\x1c\x08\xb3\x24\x2d\x39\xaa\x31\x12\x3f",
2872
    );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=1]: collision challenge
        1440, 160, 1,
        // Solution by Tim Rademacher (Lexmark International, Inc.)
        0, // starting from first round
        (const UINT8*)"\x5e\x1e\x36\x0f\x4c\x02\xc5\x77\x35\x13\xc5\x9f\xff\xd6\x72\xb7\x6a\x58\x62\x73\xf4\x30\x25\x0f\x18\x39\x05\x9e\xfe\x54\x5b\xd6\x29\x27\x6b\x16\xf0\xcd\x95\x01\xb5\x16\x10\xe3\x65\x8e\xf7\x46", 384,
        (const UINT8*)"\xda\x49\x78\xd5\x6a\x02\x31\xed\xc8\x94\x90\xf1\x9f\x18\x0b\x17\x95\xe8\xa8\x7e\x38\x09\x2a\xbb\xe6\xfa\x2f\xa9\xce\xb3\x67\x06\x56\x7f\x8e\x10\x16\x51\x92\xdb\xce\x20\xcb\x22\xdb\xfd\x1d\xb4", 384
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=2]: collision challenge
        40, 160, 2,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=2]: collision challenge
        240, 160, 2,
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x54\xD6\x65\x95\x64\x59\x91\xA1\x09\x18\x32\xB8\x9D\xE5\xA1\x12\xAD\x05\xF2\x4C\x06\x12\xF9\xE1\xD3\x57\xEC\x5C\x3E\x02", 236,
        (const UINT8*)"\x0B\x1D\x96\xE4\x64\x6A\x46\x5F\xD9\x9D\x3E\xC1\xE6\x88\x37\x5F\xCD\x12\x55\x3C\x7C\xB4\x4D\x58\xA1\x8E\x79\xA2\x62\x96", 236
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=2]: collision challenge
        640, 160, 2,
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\xBB\x90\x9D\xE7\x45\x98\xF2\x2F\x87\x85\x00\x97\xCD\x81\xDC\x6F\x89\xB7\x5D\x9B\x5E\x08\x8F\x8F\x1B\x2A\xD6\xD0\xBE\x5C\x6B\x63\xDF\x40\x2D\x2B\x6A\x3C\x7D\x03\x77\x38\x30\x3D\x60\x20\x66\x4A\xCE\xAD\x49\x3A\x2B\x62\xB3\x07\x68\x02\xE6\x1F\x8B\x01\x52\x19\x36\x82\x79\xD0\xEF\x84\x0A\x41\x0B\x69\xDE\xD0\x80\xB8\x50\x06", 636,
        (const UINT8*)"\x44\xF9\x62\x8B\xC1\x91\xAC\x57\x0C\xAE\x73\x02\x6A\xE7\x7A\x54\x51\xE1\xBC\x73\xB2\xF1\x8D\x81\xCF\x53\x5B\xB4\x3C\xE1\x97\xCC\x10\xE0\x4C\x62\xD6\x0D\x4F\x27\xEA\xD9\xD9\xD8\xD1\x41\x58\x2C\x79\xAE\xC3\x82\x74\x72\x12\x8B\x72\xB5\x66\x0E\xC6\xAA\xF4\xAF\x76\xE0\xEB\x21\xC0\xFE\x7D\xB1\x86\xD9\xA4\x5A\xDD\x98\x83\x0F", 636
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=2]: collision challenge
        1440, 160, 2,
        // Solution by Paweł Morawiecki (Kielce Univeristy of Commerce, Section of Informatics, Poland)
        0, // starting from first round
        (const UINT8*)"\x43\x81\x85\xF9\xB1\x62\x25\xB9\x9B\x6A\x06\x32\xFE\xEE\x98\xB1\x60\x02\x34\xE5\xD5\xFF\xE7\x43\xA7\x55\xE6\x9F\xA1\xE0\x70\x4C\x71\x26\xF4\x29\x30\x0A\x6A\x81\x3E\x8E\x47\x29\xD8\x92\x20\xA8\x35\xAD\xB9\xC0\x80\x0A\xCB\x71\x56\xE6\xA5\x8D\xB2\x43\x38\x44\x4D\xC4\x88\xC4\xF3\x4B\x18\x15\x8B\x7A\x54\x80\x0C\x0F\x14\x14\xA3\x69\xB4\xF2\xC8\xB0\x70\xAC\x1C\x2A\x61\xBA\xF6\x35\x69\xBD\xE3\x6C\x80\x4F\xC8\x94\x8B\x8F\xB4\x77\x00\x81\xE1\xCA\x7E\xD7\xBB\x82\x8D\xF1\xA5\x34\xC8\x25\x9F\x43\x2E\x20\xF0\x94\x13\x8D\xD1\xEF\x45\x48\x21\x10\x13\x75\xD0\x98\x15\x01\x0F\x02\x1C\xC1\x7C\xE7\xCF\x95\xA3\xC9\x26\xCC\x1F\xDD\xAF\x44\x19\x00\x12\x96\xD4\xA7\x06\x25\x11\x90\x77\x13\xA3\x40\x59\x1C\x01\x91\x60\xCF\x03\x41\x80\x0A", 1436,
        (const UINT8*)"\xEC\xD6\x33\x74\x77\x7F\x80\xB5\x3E\x23\xF6\x04\x08\xAE\xFC\x00\xEC\x6B\x35\x93\x4B\x9B\xCB\x59\xFD\xE8\x0B\xE9\x3C\xB1\x81\xD5\xA0\x66\xA4\x66\x75\xFC\x55\x03\x47\x28\x64\x83\xFE\x8D\x5B\x79\x64\xB6\x7B\x80\x89\xB6\xE8\x72\x14\x1E\x85\x8F\x6A\xB7\x80\x63\x4F\x04\x62\x42\x8E\x83\xDC\x3E\x69\x21\xB4\xD7\xD0\x0C\xAE\x59\x9F\xF9\x86\xEF\xF4\xB5\x51\x3A\x08\x29\x6E\xBC\xB5\x57\x79\xC1\xAB\xB2\x5E\xAE\x0C\xBE\x77\xB3\x8B\xDE\x0F\x36\x85\x91\xA7\x12\xF2\x5C\xFF\x57\x62\x44\x4A\xB1\x87\x31\xB3\x98\xCA\x53\x02\x98\xBF\xFB\xE8\xBF\x4F\x96\x1E\x21\x3A\x5B\x7A\xB4\xCB\x46\x24\x63\xBC\x79\x34\xE9\xE9\xBB\x63\xC5\x19\x35\x68\xBE\x95\x55\x5D\x82\x7D\x52\xDA\xFE\xF8\x41\x7D\x60\xB2\xED\x9C\xCF\xA5\xBA\x1C\x45\xAE\x4C\x70\x01", 1436
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=2]: collision challenge
        1440, 160, 2,
        // Solution by Alexandre Duc (Ecole Polytechnique Federale de Lausanne, Switzerland), Jian Guo (Institute for Infocomm Research, Singapore), Thomas Peyrin and Lei Wei (Nanyang Technological University, Singapore)
        0, // starting from first round
        (const
UINT8*)"\x90\xa9\x68\x63\x30\xa2\x23\x1c\xa5\x04\xb4\x3e\x47\x7d\xc8\x35\xd9\x8d\xe1\xb5\x62\x99\xc8\x28\x0c\x37\xf0\xb5\x94\xba\xc6\x24\x63\x2f\x87\x93\xd1\xaa\xaf\x76\xae\x63\xb4\xf5\xe1\x7c\x2a\xba\x09\x0c\x70\x6c\xa5\x38\x94\xb1\x70\x85\x66\x04\x3f\x2c\x28\xa3\x5b\xaf\x36\x2c\x59\xe6\xa3\x08\x49\x57\xfd\x2a\xd4\x28\xe5\xdd\x34\x55\x49\xd9\x8d\xde\x8a\xfd\x63\xf0\x01\xa2\x1c\x29\x45\x78\xd8\x7c\xa4\x32\x62\x47\x3a\xab\x9f\x37\xd6\x73\x5f\xbb\x50\x93\x10\x9a\x6c\x9d\x78\xf6\x9b\xdb\xe6\x9c\x7d\x03\xc6\xc3\x7b\x9e\x3f\x1f\xd0\xa1\x67\x0a\x4c\x06\x42\x22\x79\xa1\xdd\xc9\x35\xed\x63\xa1\x8b\xdb\x98\x26\xb6\x7e\xc2\x34\x81\x88\xf7\xfc\x27\x36\x1c\xf7\xd7\x83\x02\x23\x89\x44\x46\x02\xe5\x23\xcb\x1a\x11\x2f\xbc\x9c\x0a\x54\xc2\xc1\xd2\x84\xf5\x54\x0d\xec\x50\x34\x22\x68\x2b\xf9\xef\x2d\x1c\x78\x71\x62\x7a\x57\x86\x46\x71\x97\x75\x2d\x33\x7f\x81\xf5\x41\x54\x79\x35\xa8\x86\x21\xf8\xba\x43\x65\xe6\x3c\x54\x13\x59\xcd\x85\xbb\x47\xdc\x41\x8d\x4d\xd8\x02\x7b\x0b\x82\xfc\x00\xc2\x50\x7a\xf8\xf8\x00\x19\xf1\xbb\x5d\x56\xa1\x99\xaa\xb4\xf2\x77\x39\xae\xbf\x15\xef\x4c\x63\xc8\x4f\xde\xd3\xd5\xda\xd4\x93\x2b\x4e\x8b\x23\x4e\xa5\x14\x09\x00\x6a\xaa\x9b\x15\x5f\x8e\x8c\x98\x3c\x4b\xae\x2b\x98\x11\xf3\xe7\xef\xc7\xb8\xc9\x9b\x4b\xf4\xe9\xd7\x18\x37\x7c\x2c\x41\x7e\x97\xeb\x19\xac\x4a\xa7\x38\xe3\xe1\x84\x91\x0f\x1c\xa2\x02\x03\x91\xc8\xbb\x5a\x64\x06\x4f\x4d\xdd\x67\x85\x59\x93\xc6\xd7\x2a\xb1\xf1\xd6\xfc\x98\x0f\xdf\x7c\x93\x70\x8b\xaf",
2*1440-8,
        (const
UINT8*)"\x90\xa9\x68\x63\x30\xa2\x23\x1c\xa5\x04\xb4\x3e\x47\x7d\xc8\x35\xd9\x8d\xe1\xb5\x62\x99\xc8\x28\x0c\x37\xf0\xb5\x94\xba\xc6\x24\x63\x2f\x87\x93\xd1\xaa\xaf\x76\xae\x63\xb4\xf5\xe1\x7c\x2a\xba\x09\x0c\x70\x6c\xa5\x38\x94\xb1\x70\x85\x66\x04\x3f\x2c\x28\xa3\x5b\xaf\x36\x2c\x59\xe6\xa3\x08\x49\x57\xfd\x2a\xd4\x28\xe5\xdd\x34\x55\x49\xd9\x8d\xde\x8a\xfd\x63\xf0\x01\xa2\x1c\x29\x45\x78\xd8\x7c\xa4\x32\x62\x47\x3a\xab\x9f\x37\xd6\x73\x5f\xbb\x50\x93\x10\x9a\x6c\x9d\x78\xf6\x9b\xdb\xe6\x9c\x7d\x03\xc6\xc3\x7b\x9e\x3f\x1f\xd0\xa1\x67\x0a\x4c\x06\x42\x22\x79\xa1\xdd\xc9\x35\xed\x63\xa1\x8b\xdb\x98\x26\xb6\x7e\xc2\x34\x81\x88\xf7\xfc\x27\x36\x1c\xf7\xd7\x83\x02\x23\x89\x44\x46\x02\xe5\x23\xcb\x1a\x11\x2f\xbc\x9c\x0a\x54\xc2\xc1\xd2\x84\xf5\x54\x0d\xec\x50\x34\x22\x6c\x2b\xf9\xef\x2d\x1c\x78\x71\x62\x7a\x57\x86\x46\x71\x97\x75\x2d\x33\x7f\x81\xf5\x40\x54\x79\x35\xa8\x86\x21\xf8\xba\x43\x65\xe6\x3c\x54\x13\x59\xcd\x85\xbb\x47\xdc\x41\x8d\x4d\xd8\x02\x7b\x0b\x82\xfc\x00\xc2\x50\x7a\xf8\xf8\x00\x19\xf1\xbb\x5d\x56\xa1\x99\xaa\xb4\xf2\x77\x39\xae\xbf\x15\xef\x4c\x63\xc8\x4f\xde\xd3\xd1\xda\xd4\x93\x2b\x4e\x8b\x23\x4e\xa5\x14\x09\x02\x6a\xaa\x9b\x15\x5f\x8e\x8c\x98\x3c\x4b\xae\x2b\x98\x11\xf3\xe7\xef\xc7\xb8\xc9\x9b\x4b\xf4\xe9\xd7\x18\x37\x7c\x2c\x41\x7e\x97\xeb\x19\xac\x4a\xa7\x38\xe3\xe3\x84\x91\x0f\x1c\xa2\x02\x03\x91\xc9\xbb\x5a\x64\x06\x4f\x4d\xdd\x67\x85\x59\x93\xc6\xd7\x2a\xb1\xf1\xd6\xfc\x98\x0f\xdf\x7c\x93\x70\x8b\xaf",
2*1440-8
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=3]: collision challenge
        40, 160, 3,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=3]: collision challenge
        240, 160, 3,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=3]: collision challenge
        640, 160, 3,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=3]: collision challenge
        1440, 160, 3,
        // Solution by Itai Dinur, Orr Dunkelman and Adi Shamir
        0, // starting from first round
        (const UINT8*)"\xff\x4a\x25\x26\xe9\xc6\x6d\x01\xf6\xb7\x4e\x69"
        "\x72\xc5\x63\x64\xc0\xc1\x0c\x8e\x4c\x71\x52\xb8\xe5\x28\x86"
        "\xe0\x90\x67\x79\xc9\xda\xdd\xe4\x55\x79\x9a\xe3\xca\x35\x13"
        "\xa0\x11\x50\xa7\x8f\x66\xfd\xb4\xc3\xe5\x77\x68\x22\x7e\x44"
        "\x44\x02\x47\x36\x10\x11\x05\x95\x8f\x3f\x32\x25\x53\x99\x24"
        "\xe1\xfd\xed\x81\xd2\x6a\x97\xda\x68\x73\x4c\x49\xfe\xf1\xe7"
        "\x7d\x41\x7a\x12\xab\xcf\xb6\x77\x23\x72\x2b\xcb\x15\x14\x11"
        "\xf5\x51\xe4\x03\x06\x6f\x69\xc0\x1c\x68\x47\x10\x05\x1d\x51"
        "\x6d\x77\x28\x89\x17\xa1\xdc\x19\xc8\x9c\x33\xc3\x5d\x7b\x7e"
        "\x95\x8b\xd6\x38\xd3\xd6\xaa\x86\xeb\x30\x4c\x11\x16\x10\x84"
        "\xc1\xac\xa9\xb0\xa2\x47\x5a\x0f\xbc\x92\x7f\x3e\x70\x37\xc8"
        "\x1f\xd9\x47\x4e\x5f\x51\x4d\xf8\x14\xbf\x67\x80\xc8\x47\x33"
        "\x2b\xaa", 1432,
        (const UINT8*)"\x6b\xf0\xe3\xac\x5b\x50\x17\x58\xd3\x5d\x5b\x8a"
        "\xd9\x6b\x11\xd1\x08\xbc\xe4\x4a\x8e\x3f\x06\x67\x3c\x5f\x05"
        "\x3e\x15\xf9\x87\xa8\xee\x21\x1f\xba\x2b\x7f\xad\x1d\x53\x70"
        "\x03\xbd\x62\xa6\x9f\xca\x08\x3d\x15\x7c\xa6\x95\x86\x80\xc0"
        "\x7d\xaf\x19\x23\x07\xaa\xbd\xe0\xaf\x75\x47\xf2\xad\x45\x5d"
        "\x77\x2e\x3c\x48\x87\x61\xd3\x4b\xed\x55\xc3\x12\xaf\xdc\x66"
        "\xfa\x01\xd0\xfc\xaf\xc8\x7d\x1c\x3b\x3d\x2a\x71\x2c\xc4\x34"
        "\xb2\xf8\x37\x5e\x7c\x26\x71\xf7\xb9\x84\xdf\x01\x39\xd0\xb4"
        "\x6c\x38\x97\x5c\x1a\x52\x05\x99\x45\x62\x2c\xc7\x93\x8d\x62"
        "\xa5\x5f\xb9\x2f\x7f\x1d\x79\xbb\xbf\x4d\xe3\x31\x36\x03\x6f"
        "\x66\xf9\x31\xe3\x30\x41\xf8\x46\x90\x31\xd5\xd7\x41\x31\x88"
        "\x4f\x60\x31\x18\x6b\xf6\x27\xbc\x32\xab\xdb\x74\x30\x65\x5c"
        "\xa9\xc3", 1432
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=4]: collision challenge
        40, 160, 4,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=4]: collision challenge
        240, 160, 4,
        // Solution by Stefan Kölbl, Florian Mendel, Martin Schläffer and Tomislav Nad
        0, // starting from first round
        (const UINT8*)"\xFD\xA3\x35\x10\x12\xB2\x7E\xBC\xE6\x14\xEA\xFA\x6A\xB6\xF8\x6F\xB0\x51\xE6\x1F\x76\x3C\x69\xE9\x20\x45\xE9\xC1\x60\xD5", 238,
        (const UINT8*)"\xBC\x45\x5E\x60\x53\xBE\x8E\x1F\x64\x35\xB5\x2B\x37\x42\x0E\x3E\x45\xA0\x3F\x3C\x68\xE2\xDA\xE2\x6E\x72\xAA\xED\x20\xDA", 238
    );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=4]: collision challenge
        640, 160, 4,
        // Solution by Stefan Kölbl, Florian Mendel, Martin Schläffer and Tomislav Nad
        0, // starting from first round
        (const UINT8*)"\x92\x81\x80\x4A\x71\x78\xB0\xC6\xF4\x3C\xE4\x72\x5D\xA5\xD8\x38\x5B\xB3\x80\x59\x24\x4D\x70\x41\xF4\xB7\xAE\x63\xFA\x6D\xDE\x07\x29\x58\x23\x5A\x59\x29\xCF\x29\x23\xA6\x2C\xAA\x89\xF4\xBD\xA1\xBC\x2C\xBA\xE7\x91\x43\x30\xE2\x19\x7F\xEF\x4F\x3C\xB5\xFF\x5E\xCF\x2F\x9B\x8D\x1C\x85\x3A\x71\x41\xD9\x27\x17\x50\xC0\xA8\xCA", 638,
        (const UINT8*)"\x5C\x8C\x47\x64\xF2\xBB\x20\x8A\x28\xC1\x1F\xC6\xA5\x09\x3E\xF3\x67\x5A\x08\x90\x6B\x0D\x19\xDE\x1A\x2A\xE6\x67\x30\x02\x52\x05\x21\x5C\x6F\x32\xF5\xF9\x3E\x16\x40\x4B\x41\xDC\x6B\x78\xDE\x61\xF4\xA3\x32\x66\x13\xE7\x1D\xB7\xD0\xD8\x2F\x84\xA6\x80\xA6\xCD\x35\xB6\x00\xD8\x0A\x91\xE0\x44\x6B\xB6\x55\x07\x78\x88\x28\xDB", 638
    );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=4]: collision challenge
        1440, 160, 4,
        // Solution by Itai Dinur, Orr Dunkelman and Adi Shamir
        0, // starting from first round
        (const UINT8*)"\xff\x4a\x25\x26\xe9\xc6\x6d\x01\xf6\xb7\x4e\x69"
        "\x72\xc5\x63\x64\xc0\xc1\x0c\x8e\x4c\x71\x52\xb8\xe5\x28\x86"
        "\xe0\x90\x67\x79\xc9\xda\xdd\xe4\x55\x79\x9a\xe3\xca\x35\x13"
        "\xa0\x11\x50\xa7\x8f\x66\xfd\xb4\xc3\xe5\x77\x68\x22\x7e\x44"
        "\x44\x02\x47\x36\x10\x11\x05\x95\x8f\x3f\x32\x25\x53\x99\x24"
        "\xe1\xfd\xed\x81\xd2\x6a\x97\xda\x68\x73\x4c\x49\xfe\xf1\xe7"
        "\x7d\x41\x7a\x12\xab\xcf\xb6\x77\x23\x72\x2b\xcb\x15\x14\x11"
        "\xf5\x51\xe4\x03\x06\x6f\x69\xc0\x1c\x68\x47\x10\x05\x1d\x51"
        "\x6d\x77\x28\x89\x17\xa1\xdc\x19\xc8\x9c\x33\xc3\x5d\x7b\x7e"
        "\x95\x8b\xd6\x38\xd3\xd6\xaa\x86\xeb\x30\x4c\x11\x16\x10\x84"
        "\xc1\xac\xa9\xb0\xa2\x47\x5a\x0f\xbc\x92\x7f\x3e\x70\x37\xc8"
        "\x1f\xd9\x47\x4e\x5f\x51\x4d\xf8\x14\xbf\x67\x80\xc8\x47\x33"
        "\x2b\xaa", 1432,
        (const UINT8*)"\x6b\xf0\xe3\xac\x5b\x50\x17\x58\xd3\x5d\x5b\x8a"
        "\xd9\x6b\x11\xd1\x08\xbc\xe4\x4a\x8e\x3f\x06\x67\x3c\x5f\x05"
        "\x3e\x15\xf9\x87\xa8\xee\x21\x1f\xba\x2b\x7f\xad\x1d\x53\x70"
        "\x03\xbd\x62\xa6\x9f\xca\x08\x3d\x15\x7c\xa6\x95\x86\x80\xc0"
        "\x7d\xaf\x19\x23\x07\xaa\xbd\xe0\xaf\x75\x47\xf2\xad\x45\x5d"
        "\x77\x2e\x3c\x48\x87\x61\xd3\x4b\xed\x55\xc3\x12\xaf\xdc\x66"
        "\xfa\x01\xd0\xfc\xaf\xc8\x7d\x1c\x3b\x3d\x2a\x71\x2c\xc4\x34"
        "\xb2\xf8\x37\x5e\x7c\x26\x71\xf7\xb9\x84\xdf\x01\x39\xd0\xb4"
        "\x6c\x38\x97\x5c\x1a\x52\x05\x99\x45\x62\x2c\xc7\x93\x8d\x62"
        "\xa5\x5f\xb9\x2f\x7f\x1d\x79\xbb\xbf\x4d\xe3\x31\x36\x03\x6f"
        "\x66\xf9\x31\xe3\x30\x41\xf8\x46\x90\x31\xd5\xd7\x41\x31\x88"
        "\x4f\x60\x31\x18\x6b\xf6\x27\xbc\x32\xab\xdb\x74\x30\x65\x5c"
        "\xa9\xc3", 1432
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=5]: collision challenge
        40, 160, 5,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=5]: collision challenge
        240, 160, 5,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=5]: collision challenge
        640, 160, 5,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=5]: collision challenge
        1440, 160, 5,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=6]: collision challenge
        40, 160, 6,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=6]: collision challenge
        240, 160, 6,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=6]: collision challenge
        640, 160, 6,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=6]: collision challenge
        1440, 160, 6,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=7]: collision challenge
        40, 160, 7,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=7]: collision challenge
        240, 160, 7,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=7]: collision challenge
        640, 160, 7,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=7]: collision challenge
        1440, 160, 7,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=8]: collision challenge
        40, 160, 8,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=8]: collision challenge
        240, 160, 8,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=8]: collision challenge
        640, 160, 8,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=8]: collision challenge
        1440, 160, 8,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=9]: collision challenge
        40, 160, 9,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=9]: collision challenge
        240, 160, 9,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=9]: collision challenge
        640, 160, 9,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=9]: collision challenge
        1440, 160, 9,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=10]: collision challenge
        40, 160, 10,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=10]: collision challenge
        240, 160, 10,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=10]: collision challenge
        640, 160, 10,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=10]: collision challenge
        1440, 160, 10,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=11]: collision challenge
        40, 160, 11,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=11]: collision challenge
        240, 160, 11,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=11]: collision challenge
        640, 160, 11,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=11]: collision challenge
        1440, 160, 11,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=40, c=160, rounds=12]: collision challenge
        40, 160, 12,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=240, c=160, rounds=12]: collision challenge
        240, 160, 12,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=640, c=160, rounds=12]: collision challenge
        640, 160, 12,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );
    counter += verifyCollisionChallenge(
        // Keccak[r=1440, c=160, rounds=12]: collision challenge
        1440, 160, 12,
        0, // fill in this line with the start round index (0=first)
        (const UINT8*)"???", 24, // fill in this line
        (const UINT8*)"!!!!", 32 // and this line with a different input
     );

    cout << dec << counter << " correct collision challenge(s)." << endl;
}

void verifyChallenges()
{
    verifyPreimageChallenges();
    verifyCollisionChallenges();
}
