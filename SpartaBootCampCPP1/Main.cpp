#include <iostream>
#include <Windows.h>
using namespace std;

void setTextColor(int color)	// 1 - Red, 2 - Green, 3 - Blue, else - 기본값
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (color)
	{
	case 1:		// 빨강
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	}
	break;
	case 2:		// 초록
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	}
	break;
	case 3:		// 파랑
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	break;
	case 4:		// 시안
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	break;
	case 5:		// 노랑
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	}
	break;
	default:	// 기본값
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	break;
	}
}

void printTextSlowly(string msg, int ms, int blankMs)
{
	for (int i = 0; i < msg.length(); i++)
	{
		cout << msg[i];

		if (msg[i] != ' ')
		{
			Sleep(ms);
		}
		else
		{
			Sleep(blankMs);
		}
	}
}

void printTextSlowlyWithColor(string msg, int ms, int blankMs, int color)
{
	setTextColor(color);
	printTextSlowly(msg, ms, blankMs);
	setTextColor(0);
}

void printColorStatus(int index)
{
	switch (index)
	{
	case 1:	// HP
	{
		setTextColor(1);
		cout << "HP";
	}
	break;
	case 2:	// MP
	{
		setTextColor(2);
		cout << "MP";
	}
	break;
	case 3:	// 공격력 ATK
	{
		setTextColor(3);
		cout << "공격력";
	}
	break;
	case 4:	// 방어력 DEF
	{
		setTextColor(4);
		cout << "방어력";
	}
	break;
	default:
	{
		cout << "Out of range.\n";
	}
	break;
	}
	setTextColor(0);
}

/*void printStatus(const int* const level, const int* const status, const int* const pHPPotionCnt, const int* const pMPPotionCnt)
{
	// level
	cout << "* ";
	setTextColor(5);
	cout << "Level ";
	setTextColor(0);
	cout << ": " << *(status + 4) << "\n";
	
	cout << "* ";
	// hp
	printColorStatus(1);
	cout << " : " << *status << " | ";

	// mp
	printColorStatus(2);
	cout<<" : " << *(status + 1) << " | ";
	
	// 공격력
	printColorStatus(3);
	cout << " : " << status[2] << " | ";

	// 방어력
	printColorStatus(4);
	cout << " : " << status[3] << endl;

	cout << "---------------------------------------\n"; // 구분선 출력
	// 소지 포션
	cout << "소지 중인 표션 수\n";
	printColorStatus(1);
	cout << " : " << *pHPPotionCnt << ", ";
	printColorStatus(2);
	cout << " : " << *pMPPotionCnt << "\n";
}*/

void printStatus(const int &level, const int(&status)[8], const int &hpPotionCnt, const int &mpPotionCnt)
{
	// level
	setTextColor(5);
	cout << "Level ";
	setTextColor(0);
	cout << ": " << level << "\n";


	printColorStatus(1);
	cout << " : " << status[0] << " | ";

	printColorStatus(2);
	cout<<": " << status[1] << " | ";

	printColorStatus(3);
	cout << " : " << status[2] << " | ";
	printColorStatus(4);
	cout << " : " << status[3] << endl;

	// STR
	cout << "힘 : " << status[4] << " | ";

	// AGI
	cout << "민첩 : " << status[5] << " | ";

	// END
	cout << "내구 : " << status[6] << " | ";

	// INT
	cout << "지눙 : " << status[7] << "\n";

	cout << "---------------------------------------\n"; // 구분선 출력
	// 소지 포션
	cout << "소지 중인 표션 수\n";
	printColorStatus(1);
	cout << " : " << hpPotionCnt << ", ";
	printColorStatus(2);
	cout << " : " << mpPotionCnt << "\n";
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
	*p_HPPotion = count;
	*p_MPPotion = count;
}

void initializeStatus(int(&status)[8])
{
	cout << "초기 스텟을 입력해주세요.\n";
	// HP, MP 입력
	while (true)
	{
		printColorStatus(1);
		cout << "와 ";
		printColorStatus(2);
		cout<<"를 입력해주세요 : ";
		cin >> status[0] >> status[1];
		if (status[0] > 50 && status[1] > 50)
		{
			break;
		}

		printColorStatus(1);
		cout << "나 ";
		printColorStatus(2);
		cout << "값이 너무 작습니다. 다시 입력해주세요.";
	}

	// 공격력, 방어력 입력
	while (true)
	{
		printColorStatus(3);
		cout << "와 ";
		printColorStatus(4);
		cout << "를 입력해주세요 : ";
		cin >> status[2] >> status[3];
		if (status[2] > 0 && status[3] > 0)
		{
			break;
		}

		printColorStatus(3);
		cout << "나 ";
		printColorStatus(4);
		cout << "값이 너무 작습니다. 다시 입력해주세요.\n";
	}

	status[4] = 5;	// 힘
	status[5] = 5;	// 민첩
	status[6] = 5;	// 내구
	status[7] = 5;	// 지능
	cout << "====================================================\n";
}

void showInputExplain()
{
	cout << "<스텟 관리 시스템>\n";
	// status up 메세지 출력
	for (int i = 1; i <= 4; i++)
	{
		cout << i <<". ";
		printColorStatus(i);
		cout << " UP\n";
	}
	cout << "5. 현재 능력치\n";
	cout << "6. ";
	setTextColor(5);
	cout << "Level UP\n";
	setTextColor(0);
	cout << "\n";
	cout << "0. 상태창 닫기 \n";

	cout << "\n입력하기 : ";
}

void useHPPotion(int& hpPotionCnt, int& currentHP)
{
	if (hpPotionCnt == 0)
	{
		cout << "포션이 부족합니다.\n";
		return;
	}
	hpPotionCnt--;
	currentHP += 20;

	// 변화한 수치 출력
	cout << "* ";
	printColorStatus(1);
	cout << " : " << currentHP << "로 증가합니다.\n";
	cout << "남은 ";
	printColorStatus(1);
	cout << "포션 개수 : " << hpPotionCnt;
}

void useMPPotion(int& mpPotionCnt, int& currentMP)
{
	if (mpPotionCnt == 0)
	{
		cout << "포션이 부족합니다.\n";
		return;
	}
	mpPotionCnt--;
	currentMP += 20;

	// 변화한 수치 출력
	cout << "* ";
	printColorStatus(2);
	cout << " : " << currentMP << "로 증가합니다.\n";
	cout << "남은 ";
	printColorStatus(2);
	cout << "포션 개수 : " << mpPotionCnt;
}

void strUP(int& currentSTR, int upValue)	// 힘 증가
{
	int prevSTR = currentSTR;
	currentSTR += upValue;

	printTextSlowly("힘이 증가합니다.\n", 50, 100);

	if (prevSTR < 50 && currentSTR >= 50)
	{
		printTextSlowly("전신에서 강력한 힘이 느껴집니다. 태산을 밀어버릴 수 있을 것 같은 기분이 듭니다.\n\n", 50, 100);
	}
	else if (prevSTR < 30 && currentSTR >= 30)
	{
		printTextSlowly("온몸의 근육에서 미약한 진동이 느껴집니다. 당신의 주먹은 물체를 가볍게 분쇄할 것입니다.\n\n", 50, 100);
	}
	else if (prevSTR < 10 && currentSTR >= 10)
	{
		printTextSlowly("당신의 손아귀에 단단한 압력이 느껴집니다.\n\n", 50, 100);
	}
}

void agiUP(int& currentAGI, int upValue)	// 민첩 증가
{
	int prevAGI = currentAGI;
	currentAGI += upValue;

	printTextSlowly("민첩이 증가합니다.\n", 50, 100);

	if (prevAGI < 50 && currentAGI >= 50)
	{
		printTextSlowly("당신의 발검음에 바람이 머뭅니다. 주변의 흐름의 거스르지 않고 나아갑니다.\n\n", 50, 100);
	}
	else if (prevAGI < 30 && currentAGI >= 30)
	{
		printTextSlowly("세상이 약간 느리게 느껴지는 듯합니다.\n\n", 50, 100);
	}
	else if (prevAGI < 10 && currentAGI >= 10)
	{
		printTextSlowly("이전보다 발걸음이 가볍게 느껴집니다.\n\n", 50, 100);
	}
}

void endUP(int& currentEND, int upValue)	// 내구 증가
{
	int prevEND = currentEND;
	currentEND += upValue;

	printTextSlowly("내구가 증가합니다.\n", 50, 100);

	if (prevEND < 50 && currentEND >= 50)
	{
		printTextSlowly("당신의 심장이 강인한 박동을 이어갑니다. 치명적인 상태에서도 쉽게 스러지지 않는 강철 같은 의지를 얻습니다.\n\n", 50, 100);
	}
	else if (prevEND < 30 && currentEND >= 30)
	{
		printTextSlowly("상처가 이전보다 빠르게 아물기 시작합니다. 당신의 몸은 고통에도 멈추지 않습니다.\n\n", 50, 100);
	}
	else if (prevEND < 10 && currentEND >= 10)
	{
		printTextSlowly("몸에 미지근한 온기가 감돕니다. 피로를 조금 더 견딜 수 있게 됩니다.\n\n", 50, 100);
	}
}

void intUP(int& currentINT, int upValue)	// 지능 증가
{
	int prevINT = currentINT;
	currentINT += upValue;

	printTextSlowly("지능이 증가합니다.\n", 50, 100);

	if (prevINT < 50 && currentINT >= 50)
	{
		printTextSlowly("당신의 사고가 고용한 호수처럼 깊어집니다. 주변의 흐름을 읽고 제어하는 듯한 느낌을 받습니다.\n\n", 50, 100);
	}
	else if (prevINT < 30 && currentINT >= 30)
	{
		printTextSlowly("복잡한 상황에서도 사고가 흐트러지지 않습니다. 정보 처리 속도가 눈에 띄게 빨라집니다.\n\n", 50, 100);
	}
	else if (prevINT < 10 && currentINT >= 10)
	{
		printTextSlowly("머리속이 약간 선명해지는 것을 느낍니다. 사물을 바라보는 초점이 더 뚜렷해집니다.\n\n", 50, 100);
	}
}

void atkUP(int& currentATK, int& currentSTR, int& currentAGI) // 공격력 증가
{
	int prevATK = currentATK;
	currentATK <<= 1;

	printTextSlowlyWithColor("* 공격력이 ", 50, 100, 3);
	cout << currentATK;
	printTextSlowlyWithColor("로 상승했습니다.\n", 50, 100, 3);
	
	if (prevATK < 200 && currentATK >= 200)
	{
		printTextSlowlyWithColor("* 당신의 공격에 본질적인 충격이 실립니다. 강력한 가호를 지닌 적에게도 결정적인 피해를 입힐 가능성을 획득합니다.\n", 50, 100, 3);
	}
	else if (prevATK < 100 && currentATK >= 100)
	{
		printTextSlowlyWithColor("* 전신에 폭발적인 힘이 응축됩니다. 이제 일반적인 방어는 당신의 일격 앞에 쉽게 무너집니다.\n", 50, 100, 3);
	}
	else if (prevATK < 50 && currentATK >= 50)
	{
		printTextSlowlyWithColor("* 당신의 무기에 날카로운 기운이 스며들어, 약한 방호를 쉽게 뚫을 수 있는 권한을 얻습니다.\n", 50, 100, 3);
	}

	strUP(currentSTR, 2);
	agiUP(currentAGI, 2);
}

void defUP(int& currentDEF, int& currentEND, int& currentINT) // 방어력 증가
{
	int prevDEF = currentDEF;
	currentDEF <<= 1;

	printTextSlowlyWithColor("* 방어력이 ", 50, 100, 4);
	cout << currentDEF;
	printTextSlowlyWithColor("로 상승했습니다.\n", 50, 100, 4);

	if (prevDEF < 200 && currentDEF >= 200)
	{
		printTextSlowlyWithColor("* 당신의 몸 자체가 강력한 방패가 됩니다. 차원이 다른 위협에도 굳건히 버텨낼 의지력과 저항권을 얻었습니다.\n", 50, 100, 4);
	}
	else if (prevDEF < 100 && currentDEF >= 100)
	{
		printTextSlowlyWithColor("* 알 수 없는 기운이 전신을 감싸기 시작합니다. 일반적인 피해는 더 이상 당신에게 깊은 상처를 남기지 못합니다.\n", 50, 100, 4);
	}
	else if (prevDEF < 50 && currentDEF >= 50)
	{
		printTextSlowlyWithColor("* 피부와 뼈가 단단해지는 것을 느낍니다. 사소한 충격과 피해를 자력으로 경감시킬 수 있게 됩니다.\n", 50, 100, 4);
	}

	endUP(currentEND, 2);
	intUP(currentINT, 2);
}

void getLevelUpReward(int& hpPotionCnt, int& mpPotionCnt)
{
	hpPotionCnt++;
	mpPotionCnt++;
	cout << "각 포션을 1개씩 획득합니다.\n";
	printColorStatus(1);
	cout << " : " << hpPotionCnt << "개, ";
	printColorStatus(2);
	cout << " : " << mpPotionCnt << "개\n";
}

void levelUP(int& currentLevel, int& tryCnt, int& hpPotionCnt, int& mpPotionCnt, int(&status)[8])
{
	getLevelUpReward(hpPotionCnt, mpPotionCnt);
	if (++tryCnt == 6)
	{
		tryCnt = 0;
		currentLevel++;
		printTextSlowlyWithColor("* Level UP * \n\n", 50, 100, 5);
		strUP(status[4], 3);
		agiUP(status[5], 3);
		endUP(status[6], 3);
		intUP(status[7], 3);
	}
	else
	{
		// 다음 레벨업까지 남은 횟수 출력
		printTextSlowlyWithColor("다음 Level 상승까지 ", 50, 100, 5);
		cout << (6 - tryCnt);
		printTextSlowlyWithColor("회 남았습니다.\n", 50, 100, 5);
	}
}


int main()
{
	// HP, MP, ATK(공격력), DEF(방어력), 힘, 민첩, 내구, 지능
	int status[] = { 0,0,0,0,5,5,5,5 };
	int currentLevel = 1, levelUpTryCnt = 0;
	int hpPotionCnt = 0, mpPotionCnt = 0;
	int input = -1;

	initializeStatus(status);
	setPotion(5, &hpPotionCnt, &mpPotionCnt);
	while (true)
	{
		system("cls");

		showInputExplain();
		cin.ignore();

		cin >> input;
		cout << "\n\n";

		if (input != 0)
		{
			switch (input)
			{
			case 1:
			{
				useHPPotion(hpPotionCnt, status[0]);;
			}
			break;
			case 2:
			{
				useMPPotion(mpPotionCnt, status[1]);
			}
			break;
			case 3:
			{
				atkUP(status[2], status[4], status[5]);
			}
			break;
			case 4:
			{
				defUP(status[3], status[6], status[7]);
			}
			break;
			case 5:
			{
				printStatus(currentLevel, status, hpPotionCnt, mpPotionCnt);
				Sleep(1000);
			}
			break;
			case 6:
			{
				levelUP(currentLevel, levelUpTryCnt, hpPotionCnt, mpPotionCnt, status);
			}
			break;
			default:
			{
				cout << "존재하지 않는 선택지입니다.\n";
			}
			break;
			}
		}
		else
		{
			cout << "프로그램을 종료합니다.\n";
			break;
		}
		Sleep(1000);
	}
	return 0;
}