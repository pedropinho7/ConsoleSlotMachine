//
// Created by Pedro on 30/06/2022.
//

#include "Header.h"

int main()
{
		Player p1;
		SlotEntity slot1;
		bool isRunning = true;
		while (isRunning)
		{

			p1.PrintTotalAmmount();
			p1.PrintCurrentBet();
			log("\n");
			log("X - SPIN\t\t\tC - CHANGE BET\t\t\tQ - QUIT");
			static char ch;
			std::cin >> ch;
			switch (ch)
			{
			case 'X': case 'x':
				slot1.Spin(p1);
				break;
			case 'c': case'C':
				p1.betChanger();
				break;
			case 'Q': case 'q':
				isRunning = false;
				break;
			default:
				log("Invalid input.");
				break;
			}
		}
		log("Thanks for playing, " << p1.name);
		return 0;
}