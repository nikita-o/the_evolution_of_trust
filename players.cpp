#include "players.h"
#include <random>

void player::go(bool me, bool opponent)
{
    game(me, opponent);	    // сама игра
    strategy(me, opponent);	// анализ прошедшей игры
}
int player::score()
{
    return _score;
}
void player::newGame()
{
    _score = 0;
}
int player::who()
{
    return _who;
}
void player::game(bool me, bool apponent)	
{
    if (me && apponent)
    {
        _score += 2;
        return;
    }
    if (me && !apponent)
    {
        _score -= 1;
        return;
    }
    if (!me && apponent)
    {
        _score += 3;
        return;
    }
    // возможна реакция на двойное предательство
}

/*
Наивный
*/

bool naive::decision()
{
    return 1;
}

/*
Лжец
*/
bool liar::decision()
{
    return 0;
}

/*
Злопамятный
*/
bool vindictive::decision()
{		
    return !revenge;
}
void vindictive::strategy(bool me, bool opponent)
{
    if (!opponent) revenge = 1;
}
void vindictive::restart()
{
    revenge = 0;
};

/*
Имитатор
*/
bool copycat::decision()
{
    return trust;
}
void copycat::strategy(bool me, bool apponent)
{
    trust = apponent;
}
void copycat::restart()
{
    trust = 1;
};

/*
Детектив
*/
bool detecive::decision()
{
    count_game++;
    return choice;
}
void detecive::strategy(bool me, bool apponent)
{		
    switch (count_game)
    {
    case 0:
    case 2:
    case 3:
        choice = 1;
        break;
    case 1:
        choice = 0;
        break;
    default:
        choice = taktik ? apponent : 0;
        return;
    }

    if (!apponent)
        taktik = 1;
}
void detecive::restart()
{
    this->count_game = 0;
    this->choice = 1;
};

/*
Имитатор++
*/
bool copykitten::decision()
{
    return !Lost2;
}
void copykitten::strategy(bool me, bool apponent)
{
    if (apponent)   Lost1 = 0;
    else if (Lost1) Lost2 = 1;
    else			Lost1 = 1;
}
void copykitten::restart()
{
    Lost1 = 0;
    Lost2 = 0;
};

/*
Простак
*/
bool simpleton::decision()
{
    return choice;
}
void simpleton::strategy(bool me, bool apponent)
{
    choice = apponent ? me : !me;		
}
void simpleton::restart()
{
    choice = 1;
};

/*
Клоун
*/
bool randommen::decision()
{
    return rand() % 2;
}