#pragma once
#include <cstddef>


/*
Раунд - это игра между двумя игроками A и B, решения происходят здесь и сейчас 
Партия - партия состоит из N раундов между играками A и B
Тур - состоит из N партий, между всеми игроками
*/

class player
{
public:
	player(int me) :_score(0), _who(me) {};

	virtual bool decision() = 0;	// Решение, каждый игрок сам решает
	virtual void restart() {};		// Сброс статистики после окончания партии (опционально)
	virtual void strategy(bool me, bool opponent) {};	// Стратегия игроков, их анализ прошедшей игры и последующие решения (опционально)

	void go(bool me, bool opponent);

	int score();

	void newGame();

	int who();

private:
	void game(bool me, bool apponent);
	int _score;
	int _who;
};

/*
Наивный - игрок всем доверяет
*/
class naive : public player 
{
public:
	naive() : player(0) {};
	virtual bool decision();
};

/*
Лжец - игрок всех предает
*/
class liar : public player
{
public:
	liar() : player(1) {};
	virtual bool decision();
};

/*
Злопамятный - игрок при предательстве начинает постоянно мстить (начинает мирно)
*/
class vindictive : public player 
{
public:
	vindictive() : player(2) { restart(); };
	virtual bool decision();
	void strategy(bool me, bool opponent);
	virtual void restart();
private:
	bool revenge;
};

/*
Имитатор - игрок повторяет решения своего оппонента (начинает мирно)
*/
class copycat : public player // Имитатор
{
public:
	copycat() : player(3) { restart(); };
	virtual bool decision();
	virtual void strategy(bool me, bool apponent);
	virtual void restart();
private:
	bool trust;
};

/*
Детектив - играет в порядке: доверился, предал, доверился, доверился. Далее, если аппонент всегда доверял, начинает играть как Лжец, иначе как Имитатор.
*/
class detecive : public player // Детектив
{
public:
	detecive() : player(4), count_game(0), choice(1) { restart(); };
	virtual bool decision();
	virtual void strategy(bool me, bool apponent);
	virtual void restart();

private:
	size_t count_game;
	bool choice;
	bool taktik;
};

/*
Имитатор++ - как Имитатор, но дает шанс аппоненту при предательстве
*/
class copykitten : public player 
{
public:
	copykitten() : player(5) { restart(); };
	virtual bool decision();
	virtual void strategy(bool me, bool apponent);
	virtual void restart();
private:
	bool Lost1;
	bool Lost2;
};

/*
Простак - игрок повторяет свои прошлые решения, даже если он случайно ошибся. Но при предательстве, инвертирует свое решение. (начинает мирно)
*/
class simpleton : public player // Простак
{
public:
	simpleton() : player(6) { restart(); };
	virtual bool decision();
	virtual void strategy(bool me, bool apponent);
	virtual void restart();
private:
	bool choice;
};

/*
Клоун - игрок постоянно принимает случайные решения 50/50
*/
class randommen : public player 
{
public:
	randommen() : player(7) {};
	virtual bool decision();
};