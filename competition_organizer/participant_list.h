#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H

#include "types.h"

#define NULLP NULL
#define unused __attribute__((unused))

typedef struct tItemP {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemP;

typedef struct tNodoP * tPosP;
struct tNodoP {
    tItemP ItemP;
    tPosP sig;
};
typedef tPosP tListP;

bool CreateNodo(tPosP *pos)
{
    *pos = malloc(sizeof(struct tNodoP));
    return *pos!=NULLP;
}

tPosP findPosition (const tParticipantName name, tListP L)
{
    tPosP participant_pos;
    for (participant_pos = L; participant_pos->sig!=NULLP && strcmp(participant_pos->sig->ItemP.participantName, name)<0; participant_pos = participant_pos->sig);
    return participant_pos;
}

void createEmptyListP (tListP *L)
{
    *L = NULLP;
}

bool isEmptyListP (tListP L)
{
    return L==NULLP;
}

tPosP firstP (tListP L)
{
    return L;
}

tPosP lastP (tListP L)
{
    tPosP participant_pos;
    for (participant_pos = L; participant_pos->sig!=NULLP; participant_pos = participant_pos->sig);

    return participant_pos;
}

tPosP nextP (tPosP pos, unused tListP L)
{
    return pos->sig;
}

tPosP previousP (tPosP pos, tListP L)
{
    if (pos==L)
        return NULLP;

    tPosP participant_pos;
    for (participant_pos = L; participant_pos->sig!=pos; participant_pos = participant_pos->sig);

    return participant_pos;
}

bool insertItemP (tItemP item, tListP *L)
{
    tPosP q, aux;

    if (!CreateNodo(&q))
        return false;
    else
    {
        q->ItemP = item;
        q->sig = NULLP;
    }

    if (*L==NULLP)
        *L = q;
    else if (strcmp(item.participantName, (*L)->ItemP.participantName)<0)
    {
        q->sig = *L;
        *L = q;
    }
    else
    {
        aux = findPosition(item.participantName, *L);
        q->sig = aux->sig;
        aux->sig = q;
    }

    return true;
}

void deleteAtPositionP (tPosP pos, tListP *L)
{
    tPosP n;

    if (pos==*L)
        *L = (*L)->sig;
    else if (pos==lastP(*L))
        previousP(lastP(*L), *L)->sig = NULLP;
    else
    {
        n = pos->sig;
        pos->ItemP = n->ItemP;
        pos->sig = n->sig;
        pos = n;
    }

    free(pos);
}

tItemP getItemP (tPosP pos, unused tListP L)
{
    return pos->ItemP;
}

void updateItemP (tItemP item, tPosP pos, unused tListP *L)
{
    pos->ItemP = item;
}

tPosP findItemP (tParticipantName name, tListP L)
{
    if (isEmptyListP(L))
        return NULLP;

    tPosP participant_pos;
    for (participant_pos = L; participant_pos!=NULLP && strcmp(participant_pos->ItemP.participantName, name)!=0; participant_pos = participant_pos->sig);

    return participant_pos;
}

#endif //PARTICIPANT_LIST_H