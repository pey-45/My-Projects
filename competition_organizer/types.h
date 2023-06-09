#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define NAME_LENGTH_LIMIT 25

typedef char tJuryName[NAME_LENGTH_LIMIT];

typedef char tParticipantName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tEUParticipant;

#endif //TYPES_H
