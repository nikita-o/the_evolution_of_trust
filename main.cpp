#include <memory>
#include "Players.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <time.h>

using namespace std;

void game(player& p1, player& p2)
{
	srand((unsigned)time(NULL));
	bool a = p1.decision();
	bool b = p2.decision();
	a = rand() % 100 < 5 ? !a : a;
	b = rand() % 100 < 5 ? !b : b;
	p1.go(a, b);
	p2.go(b, a);
}

constexpr size_t naive_N	  = 10;
constexpr size_t liar_N		  = 10;
constexpr size_t vindictive_N = 10;
constexpr size_t copycat_N	  = 10;
constexpr size_t detecive_N   = 10;
constexpr size_t copykitten_N = 10;
constexpr size_t simpleton_N  = 10;
constexpr size_t randommen_N  = 10;

constexpr size_t N_Player = naive_N + liar_N + vindictive_N + copycat_N + detecive_N  + copykitten_N + simpleton_N + randommen_N;
constexpr size_t N_Game = 100;
constexpr size_t N_Match = 10;

constexpr size_t Selection = 5;

shared_ptr<player> gen(size_t id)
{
    assert(id < 8);
	switch (id)
	{
	case 0: return make_shared<naive>();
	case 1: return make_shared<liar>();
	case 2: return make_shared<vindictive>();
	case 3: return make_shared<copycat>();
	case 4: return make_shared<detecive>();
	case 5: return make_shared<copykitten>();
	case 6: return make_shared<simpleton>();
	case 7: return make_shared<randommen>();
	}
}

int main()
{	
	setlocale(LC_ALL, "RUSSIAN");
	vector<shared_ptr<player>> players(N_Player);

	{
		size_t k = 0;
		for (size_t i = 0; i < naive_N; i++)
			players[k++] = gen(0);
		for (size_t i = 0; i < liar_N; i++)
			players[k++] = gen(1);
		for (size_t i = 0; i < vindictive_N; i++)
			players[k++] = gen(2);
		for (size_t i = 0; i < copycat_N; i++)
			players[k++] = gen(3);
		for (size_t i = 0; i < detecive_N; i++)
			players[k++] = gen(4);
		for (size_t i = 0; i < copykitten_N; i++)
			players[k++] = gen(5);
		for (size_t i = 0; i < simpleton_N; i++)
			players[k++] = gen(6);
		for (size_t i = 0; i < randommen_N; i++)
			players[k++] = gen(7);
	}
	
	for (size_t _game = 0; _game < N_Game; _game++)
	{
		for (size_t i = 0; i < N_Player - 1; i++)
		{
			for (size_t j = i + 1; j < N_Player; j++)
			{
				for (size_t match = 0; match < N_Match; match++)
				{
					game(*players[i], *players[j]);
				}
				players[i]->restart();
				players[j]->restart();
			}
		}
		// удаляем 5 слабых, добавляем 5 сильных
		for (size_t i = 0; i < Selection; i++)
		{
			int max = players[i]->score();
			int idMax = i;
			int min = players[i]->score();
			int idMin = i;
			for (size_t j = i; j < N_Player - i; j++)
			{
				if (max < players[j]->score())
				{
					max = players[j]->score();
					idMax = j;
				}
				if (min > players[j]->score())
				{
					min = players[j]->score();
					idMin = j;
				}
			}
			swap(players[i], players[idMin]);
			swap(players[N_Player - i - 1], players[idMax]);
		}
		players.erase(players.begin(), players.begin() + Selection);
		for (size_t i = 0; i < Selection; i++)
			players.push_back(gen(players[players.size() - i - 1]->who()));

		for (size_t i = 0; i < N_Player; i++)		
			players[i]->newGame();				
	}	
	vector<int> kul(8, 0);
	for (size_t i = 0; i < N_Player; i++)	
		kul[players[i]->who()]++;
	
	cout << "Наивный: " << kul[0] << endl;
	cout << "Лжец: " << kul[1] << endl;
	cout << "Злопамятный: " << kul[2] << endl;
	cout << "Имитатор: " << kul[3] << endl;
	cout << "Детектив: " << kul[4] << endl;
	cout << "Имитатор++: " << kul[5] << endl;
	cout << "Простак: " << kul[6] << endl;
	cout << "Клоун: " << kul[7] << endl;

	return 0;
}