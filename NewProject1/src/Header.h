#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

#define log(x) std::cout << x << std::endl

std::mt19937 mt(time(nullptr));


struct Player {
	std::string name;
	int total_Amount;
	int current_Bet;
	std::string currency;

	//Construtor de entidade
	Player()
	{
		name = "Tester";
		total_Amount = 5000;
		current_Bet = 100;
		currency = "Shitcoins";
	}
	//Desconstrutor de entidade
	~Player()
	{
	}
	// Aqui temos a 1a funcao da struct
	void betChanger()
	{
		static int bet = 0;
		PrintTotalAmmount();
		log("Choose a bet:");
		std::cin >> bet;

		if (!std::cin.fail())
		{ // Caso o input não falhe aka , caso seja numeros validos.
			if (bet > Player::total_Amount)
			{ //  Caso a aposta seja maior que o valor na carteira apresentamos a mensagem respetiva.
				Player::PrintBetTooBig(bet);
				Player::betChanger();
			}
			else
				//Caso passe tudo, siga para a struct.
				Player::current_Bet = bet;
		}
		else
		{
			// Caso falhe o primeiro IF, é pq o palhacinho da turma pôs uma letra ou um char em vez do número.
			// Limpamos o buffer cin e voltamos ao ínicio da função.
			Player::PrintBetNotValid();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			betChanger();
		}
	}
	// 4 funções que imprimem mensagens. much wow such uau
	static void PrintBetNotValid()
	{
		log("\n");
		log("Aposta inválida.");
		log("Faz uma aposta válida.");
		log("\n");

	}
	static void PrintBetTooBig(int x)
	{
		log("\n");
		log("Bet exceeds total amount.");
		log("\n");
	}
	void PrintCurrentBet()
	{
		log("Current bet: " << current_Bet << " " << currency);
	}

	void PrintTotalAmmount()
	{
		log("Wallet: " << total_Amount << " " << currency);
	}
};



struct SlotEntity
{

	// Criei aqui o vector dos resultados, mas nem testei noutros sítios.
	// Maybe later.
	std::vector<int> resultadoReturn;

	enum Reels : int
	{
		LeftReel = 0,
		CenterReel = 1,
		RightReel = 2
	};


	~SlotEntity()
	{
	}

	void Spin(Player& player)
	{
		if (player.current_Bet <= player.total_Amount)
		{
			const std::vector<int> L{ 1, 1, 3, 4, 5, 2, 2, 3, 4, 2, 2, 5, 3, 5, 3, 4, 2, 1, 2, 5, 4, 3, 2 };
			const std::vector<int> C{ 3, 1, 2, 2, 3, 5, 4, 4, 2, 2, 3, 2, 1, 5, 4, 3, 3, 2, 1, 5, 4, 1, 3, 5 };
			const std::vector<int> R{ 2, 3, 5, 4, 4, 3, 1, 1, 2, 2, 3, 5, 4, 3, 2, 1, 2, 1, 5, 1, 3, 4, 1, 5, 2 };
			// Limpamos os resultados anteriores.
			SlotEntity::resultadoReturn.clear();


			//Adicionar um nr random do tamanho do vector L, e depois seleciona esse index no vector REEL
			SlotEntity::resultadoReturn.push_back(L[mt() % L.size()]);


			//Adicionar um nr random do tamanho do vector L, e depois seleciona esse index no vector REEL
			SlotEntity::resultadoReturn.push_back(C[mt() % C.size()]);


			//Adicionar um nr random do tamanho do vector L, e depois seleciona esse index no vector REEL
			SlotEntity::resultadoReturn.push_back(R[mt() % R.size()]);


			//Imprimimos no resultado.
			SlotEntity::PrintResult();

			//Chamamos uma função para acabar a ronda.
			//A função basicamente confirma e efetua os pagamento da ronda
			SlotEntity::EndRound(player);
		}
		else
		{ // Caso o jogador n tenha dinheiro, volta ao menu e pode ajustar a aposta ou sair.
			log("Bet is bigger than total amount.");
			log("Modify your bet:\n");
		}
	}

	//Imprimos o resultado com a caixinha toda catita dos resultados.
	void PrintResult()
	{
		log("\t\t\t\t  _\t  _\t  _");
		log("\t\t\t\t" << "| " << SlotEntity::resultadoReturn[LeftReel] << " |" << '\t' << "| " << SlotEntity::resultadoReturn[CenterReel] << " |" << '\t' << "| " << SlotEntity::resultadoReturn[RightReel] << " | ");
		log("\t\t\t\t  -\t  -\t  -");
	}


	void EndRound(Player& player)
	{ //A tal função do pagamento da ronda.
	  //A função Payment() verifica se os resultados e devolve o bonus_amplifier (se perder é 0)

		int roundPayment = (Payment(player));
		//Aqui usamos a tal do ronaldinho aos IFs . Se for 0 é falso, se for >0 é true;
		if (roundPayment)
		{

			// Se houver prémio.
			player.total_Amount += (roundPayment * player.current_Bet);
			log("\a");
			log("\t\t\t\t\t+ " << (roundPayment * player.current_Bet) << " " << player.currency);

		}
		else
		{
			// Se não houver prémio.
			player.total_Amount -= player.current_Bet;
			log("\t\t\t\t\t- " << player.current_Bet << " " << player.currency);
		}
	}


	int Payment(Player& player)
	{
		//Aqui são as regras de vitória e o pagamento de cada uma.
		static int bonus_amplifier;
		if ((SlotEntity::resultadoReturn[LeftReel] == 1) && (SlotEntity::resultadoReturn[CenterReel] == 1) && (SlotEntity::resultadoReturn[RightReel] == 1))
			bonus_amplifier = 2;
		else if ((SlotEntity::resultadoReturn[LeftReel] == 2) && (SlotEntity::resultadoReturn[CenterReel] == 2) && (SlotEntity::resultadoReturn[RightReel] == 2))
			bonus_amplifier = 7;
		else if ((SlotEntity::resultadoReturn[LeftReel] == 3) && (SlotEntity::resultadoReturn[CenterReel] == 3) && (SlotEntity::resultadoReturn[RightReel] == 3))
			bonus_amplifier = 10;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 3) && (SlotEntity::resultadoReturn[CenterReel] == 3) && (SlotEntity::resultadoReturn[RightReel] == 1))
			bonus_amplifier = 2;
		else if ((SlotEntity::resultadoReturn[LeftReel] == 3) && (SlotEntity::resultadoReturn[CenterReel] == 3) && (SlotEntity::resultadoReturn[RightReel] == 2))
			bonus_amplifier = 2;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 3) && (SlotEntity::resultadoReturn[CenterReel] == 3) && (SlotEntity::resultadoReturn[RightReel] == 4))
			bonus_amplifier = 3;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 3) && (SlotEntity::resultadoReturn[CenterReel] == 3) && (SlotEntity::resultadoReturn[RightReel] == 5))
			bonus_amplifier = 4;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 4) && (SlotEntity::resultadoReturn[CenterReel] == 4) && (SlotEntity::resultadoReturn[RightReel] == 4))
			bonus_amplifier = 15;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 4) && (SlotEntity::resultadoReturn[CenterReel] == 4) && (SlotEntity::resultadoReturn[RightReel] == 1))
			bonus_amplifier = 5;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 4) && (SlotEntity::resultadoReturn[CenterReel] == 4) && (SlotEntity::resultadoReturn[RightReel] == 2))
			bonus_amplifier = 5;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 4) && (SlotEntity::resultadoReturn[CenterReel] == 4) && (SlotEntity::resultadoReturn[RightReel] == 3))
			bonus_amplifier = 2;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 4) && (SlotEntity::resultadoReturn[CenterReel] == 4) && (SlotEntity::resultadoReturn[RightReel] == 5))
			bonus_amplifier = 6;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 1) && (SlotEntity::resultadoReturn[CenterReel] == 2) && (SlotEntity::resultadoReturn[RightReel] == 3))
			bonus_amplifier = 2;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 5) && (SlotEntity::resultadoReturn[CenterReel] == 5) && (SlotEntity::resultadoReturn[RightReel] == 1))
			bonus_amplifier = 2;

		else if ((SlotEntity::resultadoReturn[LeftReel] == 5) && (SlotEntity::resultadoReturn[CenterReel] == 5) && (SlotEntity::resultadoReturn[RightReel] == 5))
			bonus_amplifier = 70;
		else
			bonus_amplifier = 0;


		return bonus_amplifier;
	}
};