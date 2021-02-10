#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>

//set colors:
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

struct ships {
	int x1, y1, x2, y2, len, damage;
	struct ships* next;
}__attribute__((packed));

struct player {
	char name[100];
	int score;
	struct ships* ships_head;
	char naghshe_nobat[10][10];
}__attribute__((packed));
struct acc {
	char name[100];
	int score;
}__attribute__((packed));

struct player_game_saver {
	char name[100];
	int score;
	int ships_count;
	int ships_x1[10], ships_x2[10], ships_y1[10], ships_y2[10] , ships_len[10] , ships_damage[10];
	char naghshe_nobat_[10][10];

}__attribute__((packed));

struct string_s{
	char str[200];
}__attribute__((packed));

struct point {
	int  x, y;
}__attribute__((packed));
//declaration:

int qadr(int);

int minn(int, int);

int maxx(int, int);

void put_ships(struct player*);

void menu(struct player* p1, struct player* p2, int* game_method_p);

struct ships* new_ship(int x1, int y1, int x2, int y2, int len);

struct ships * old_ship(int x1 , int y1 , int x2 , int y2 , int len , int damage);

void add_ship_end(struct player* p, struct ships* new_sh);

int is_ship_valid(struct player p1, int x1, int y1, int x2, int y2, int len , int print_error);// panic

int print_available_users_and_get_name_score(struct player* p);

int is_in_acc_list(char nam[100]);

void put_new_acc_on_acc_list(char nam[100]);

int find_score(char nam[100]);

void show_score_board(void);

void sort_acc_list(void);

void set_bot(struct player*);

void play_with_bot(struct player* p1 , struct player * p2);//p2 is the bot

void play_togather(struct player*, struct player*);

void set_maps_to_space(struct player* p);

void print_map(struct player*);

int is_point_valid_to_attack(struct player* p, int  x, int  y);

int ship_counter(struct player * p);

struct player_game_saver make_game_saver(struct player * p);

void save_game(struct player* p1, struct player* p2 , int game_method);

int is_in_saved_game_list(struct string_s game_name);

struct string_s show_saved_games_and_get_name(void);

void load_game(struct player * p1 , struct player * p2 , struct string_s game_name , int * game_method_p);

void set_player(struct player * p , struct player_game_saver p_s);

void attack(struct player* p, int x, int  y, int* jayze, int* score);

void delete_ship(struct player* p, struct ships* target);

void complete_explosion(struct player* p, struct ships* destroyed_ship);

void update_map(struct player* p);

int is_point_valid_to_check(int x, int y);

void update_scores(struct player* p1, struct player* p2 , int game_method);

struct point bot_choice (struct player * p );

int number_of_saved_users(void);

void hitlers_Nuke(struct player * p1, struct player * p2);

void random_ships(struct player * p);

void empty_army(struct player * p);

void print_ships(struct player * p);

//details:

int main() {
	struct player p1, p2, bot;
	//set_bot(&bot);//ino baadan benevis
	int i, j, game_method;
	srand(time(0));

	printf("!!!   WELCOME TO RAD'S BATTLE SHIP GAME !!!\n");

	while (1) {
		menu(&p1, &p2, &game_method);
		if (game_method == 1) {
			play_with_bot(&p1 , &p2);
		}
		else if (game_method == 2) {
			play_togather(&p1, &p2);//ino baadan benevis
		}
	}
}

int qadr(int a) {
	if (a >= 0) {
		return a;
	}
	return (-1 * a);
}

int minn(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

int maxx(int a, int b) {
	if (a < b) {
		return b;
	}
	return a;
}

void put_ships(struct player* p) {
	int ans , ans2;
	struct ships* curr;
	int x1, y1, x2, y2, len, i;
	p->ships_head = NULL;

	printf("Enter 1 to put ships manually or 2 to do it automatically(randomly) .\n");
	while(1){
		scanf("%d" , &ans);
		if((ans == 1)||(ans == 2)){
			break;
		}
	}
	if(ans == 2){
		random_ships(p);
	    print_ships(p);
	    printf("is your army ok? (1 for yes and 0 for no)\n");
	    scanf("%d" , &ans2);
	    if(ans2 == 1)
		{
	        return;
		}
		else
		{
		    empty_army(p);
		    put_ships(p);
		    return;

		}
	}

	printf("now you put your ships ; remember that you set two points for each ship and you enter the row then column of each point. (<the number of row> space <the number of column>)\n all inputs must be betwin 0 , 9 (including both) \n\n");
	len = 5;
	do {
		printf("Enter position of ship 1 * 5 :  \n");
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	} while (is_ship_valid(*p, x1, y1, x2, y2, len , 1) == 0);
	p->ships_head = new_ship(x1, y1, x2, y2, len);

	len = 3;
	do
	{
		printf("Enter position of first ship 1 * 3 :  \n");
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	} while (is_ship_valid(*p, x1, y1, x2, y2, len , 1) == 0);
	add_ship_end(p, new_ship(x1, y1, x2, y2, len));

	do
	{
		printf("Enter position of second ship 1 * 3 :  \n");
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	} while (is_ship_valid(*p, x1, y1, x2, y2, len , 1) == 0);
	add_ship_end(p, new_ship(x1, y1, x2, y2, len));

	len = 2;

	for (i = 1; i <= 3; i++) {


		do
		{
			printf("Enter position of %dth ship 1 * 2 :  \n", i);
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		} while (is_ship_valid(*p, x1, y1, x2, y2, len , 1) == 0);
		add_ship_end(p, new_ship(x1, y1, x2, y2, len));
	}

	len = 1;

	for (i = 1; i <= 4; i++) {
		do
		{
			printf("Enter position of %dth ship 1 * 1 (only one point for this kind of ship):   \n", i);
			scanf("%d%d", &x1, &y1);
		} while (is_ship_valid(*p, x1, y1, x1, y1, len , 1) == 0);
		add_ship_end(p, new_ship(x1, y1, x1, y1, len));
	}
	print_ships(p);
	Sleep(10000);
}

void menu(struct player* p1, struct player* p2, int* game_method_p) {
	int ans1, ans2, temp;
	char nam[100];
	printf("1. Play with a Friend\n2. Play with bot\n3. Load game\n4. Load last game\n5. Settings\n6. Score Board\n7. Developer information\n8. Exit\n");
	scanf("%d", &ans1);
	if (ans1 == 1)
	{
		set_maps_to_space(p1);
		set_maps_to_space(p2);
		*game_method_p = 2;//means 2 player game
		printf("for player 1 :\n1. Choose user\n1. choose from available users\n2. new user\n");
		scanf("%d", &ans2);
		if (ans2 == 1) {
			temp = print_available_users_and_get_name_score(p1);
			if (temp == -1 || number_of_saved_users() < 1) {
				ans2 = 2;
			}
		}
		if (ans2 == 2)
		{
			while (1) {
				printf("please enter the name : \n");
				//scanf("%s", nam);
				fflush(stdin);
				gets(nam);
				if (is_in_acc_list(nam) == 1) {
					printf("this name is in the account list . \n choose another name:\n");
				}
				else {
					strcpy(p1->name, nam);
					put_new_acc_on_acc_list(p1->name);
					p1->score = 0;
					break;
				}
			}
		}
		printf("now put your ships %s\n", p1->name);
		put_ships(p1);
		system("cls");

		printf("for player 2 :\n1. Choose user\n1. choose from available users\n2. new user\n");
		scanf("%d", &ans2);
		if (ans2 == 1) {

			if (temp == -1 || number_of_saved_users() < 2) {
				printf("no available users yet .\n");
				ans2 = 2;
			}
			else{
				do{
					 print_available_users_and_get_name_score(p2);
					 if(strcmp(p2->name , p1->name) == 0){
					 	printf("this account is already chosen\n pick another one .\n");
					 }
				} while(strcmp(p1->name , p2->name) == 0);
			}
		}
		if (ans2 == 2) {

			while (1)
			{
				printf("please enter the name :\n");
				//scanf("%s", nam);
				fflush(stdin);
				gets(nam);
				if (is_in_acc_list(nam) == 1) {
					printf("this name is in the account list . \n choose another name:\n");
				}
				else {
					strcpy(p2->name, nam);
					put_new_acc_on_acc_list(p2->name);
					p2->score = 0;
					break;
				}
			}

		}
		printf("now put your ships %s\n", p2->name);
		put_ships(p2);
	}
	else if (ans1 == 2)
	{
		set_maps_to_space(p1);
		set_maps_to_space(p2);
		*game_method_p = 1;// 1 player game
		printf("for player 1 :\n1. Choose user\n1. choose from available users\n2. new user\n");
		scanf("%d", &ans2);
		if (ans2 == 1)
		{

		 temp =print_available_users_and_get_name_score(p1);
			if((temp == -1) || number_of_saved_users() < 1){
				ans2 = 2;
			}
		}
		if (ans2 == 2)
		{
			while (1)
			{
				printf("please enter the name :\n");
				//scanf("%s", nam);
				fflush(stdin);
				gets(nam);
				if (is_in_acc_list(nam) == 1)
				{
					printf("this name is in the account list . \n choose another name:\n");
				}
				else {
					strcpy(p1->name, nam);
					put_new_acc_on_acc_list(p1->name);
					p1->score = 0;
					break;
				}
			}
		}
		printf("now put your ships %s\n",p1->name);
		put_ships(p1);

		set_bot(p2);
	}

	else if(ans1 == 3){
		struct string_s game_name;
		game_name = show_saved_games_and_get_name();
		if(strcmp(game_name.str , "none")==0){
			*game_method_p = 0;
			return; //bazgasht be menu;
		}
		load_game(p1,p2,game_name , game_method_p);
	}
	else if (ans1 == 4)
	{
		struct string_s last_game_name;
		strcpy(last_game_name.str , "last game");
		load_game(p1, p2,last_game_name ,game_method_p);
	}
	else if (ans1 == 5)
	{
		printf("no settings yet :))))\n");
		Sleep(2000);
		system("cls");
		menu(p1, p2, game_method_p);
	}
	else if (ans1 == 6)
	{
		sort_acc_list();
		show_score_board();
		//getch();
		menu(p1, p2, game_method_p);
	}
	else if(ans1 == 7)
	{
		printf("CREATED BY :\n MOHAMMAD HEYDARI RAD \n 1399\n UNIVERSITY : AUT \n ID : 9931017\n\n");
		menu(p1, p2 , game_method_p);
		return;
	}
	else if (ans1 == 8) {
		system("cls");
		printf("bye bye\n");
		Sleep(3000);
		exit(0);
	}
	else {
		printf("not valid input");
		Sleep(2000);
		system("cls");
		menu(p1, p2, game_method_p);
	}
	return;
}

struct ships* new_ship(int x1, int y1, int x2, int y2, int len) {
	struct ships* new_sh = (struct ships*)malloc(sizeof(struct ships));
	new_sh->x1 = x1;
	new_sh->x2 = x2;
	new_sh->y1 = y1;
	new_sh->y2 = y2;
	new_sh->len = len;
	new_sh->damage = 0;
	new_sh->next = NULL;

	return new_sh;
}

struct ships* old_ship(int x1 , int y1 , int x2 , int y2 , int len, int damage){
	struct ships* old_sh = new_ship(x1,y1,x2,y2,len);
	old_sh->damage = damage;
	return old_sh;
}

void add_ship_end(struct player* p, struct ships* new_sh) {
	struct ships* curr;
	if (p->ships_head == NULL) {
		p->ships_head = new_sh;
	}
	else {
		for (curr = p->ships_head; curr->next != NULL; curr = curr->next);
		curr->next = new_sh;
		new_sh->next = NULL;
	}
	return;
}

int is_ship_valid(struct player p, int x1, int y1, int x2, int y2, int len , int print_errors) {
	struct ships* curr;
	int i, j, max_x, max_y;
	int map_valid_test[10][10] = { 0 };

	if ((x1 != x2) && (y1 != y2))
	{
		if(print_errors)
		{
		    printf("invalid ship .\n");
		    printf("broken ship .\n");
		}

		return 0;
	}

	else if ((x1 > 9) || (x2 > 9) || (y1 > 9) || (y2 > 9) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0))
	{
		if(print_errors)
		{
			printf("invalid ship .\n");
		    printf("not correctly fixed in the map .\n");
		}

		return 0;
	}
	else if((qadr(x1-x2) != len-1) && (qadr(y1-y2) != len-1)){
		if(print_errors)
		{
			printf("invalid ship .\n");
	 	    printf("not correct ship length .\n");
		}

		return 0;
	}
	else if (p.ships_head == NULL)
	{
		return 1;
	}
	//else :
	for (curr = p.ships_head; curr != NULL; curr = curr->next) {


		if (curr->x1 == curr->x2) { //horizenal
			for (j = minn(curr->y1, curr->y2); j <= maxx(curr->y1, curr->y2); j++)
			{
				map_valid_test[curr->x1][j] += 100;
				if (curr->x1 < 9)
				{
					map_valid_test[curr->x1 + 1][j] += 1;
				}
				if (curr->x1 > 0)
				{
					map_valid_test[curr->x1 - 1][j] += 1;
				}
			}
			if (maxx(curr->y1, curr->y2) < 9)
			{
				map_valid_test[curr->x1][maxx(curr->y1, curr->y2) + 1] += 1;
				if (curr->x1 > 0)
				{
					map_valid_test[curr->x1 - 1][maxx(curr->y1, curr->y2) + 1] += 1;
				}
				if (curr->x1 < 9)
				{
					map_valid_test[curr->x1 + 1][maxx(curr->y1, curr->y2) + 1] += 1;
				}
			}
			if (minn(curr->y1, curr->y2) > 0)
			{
				map_valid_test[curr->x1][minn(curr->y1, curr->y2) - 1] += 1;
				if (curr->x1 > 0)
				{
					map_valid_test[curr->x1 - 1][minn(curr->y1, curr->y2) - 1] += 1;
				}
				if (curr->x1 < 9)
				{
					map_valid_test[curr->x1 + 1][minn(curr->y1, curr->y2) - 1] += 1;
				}
			}
		}

		else if (curr->y1 == curr->y2) //VERTICAL
		{
			for (j = minn(curr->x1, curr->x2); j <= maxx(curr->x1, curr->x2); j++)
			{
				map_valid_test[j][curr->y1] += 100;
				if (curr->y1 < 9)
				{
					map_valid_test[j][curr->y1 + 1] += 1;
				}
				if (curr->y1 > 0)
				{
					map_valid_test[j][curr->y1 - 1] += 1;
				}
			}
			if (maxx(curr->x1, curr->x2) < 9)
			{
				map_valid_test[maxx(curr->x1, curr->x2) + 1][curr->y1] += 1;
				if (curr->y1 > 0)
				{
					map_valid_test[maxx(curr->x1, curr->x2) + 1][curr->y1 - 1] += 1;
				}
				if (curr->y1 < 9)
				{
					map_valid_test[maxx(curr->x1, curr->x2) + 1][curr->y1 + 1] += 1;
				}
			}
			if (minn(curr->x1, curr->x2) > 0)
			{
				map_valid_test[minn(curr->x1, curr->x2) - 1][curr->y1] += 1;
				if (curr->y1 > 0)
				{
					map_valid_test[minn(curr->x1, curr->x2) - 1][curr->y1 - 1] += 1;
				}
				if (curr->y1 < 9)
				{
					map_valid_test[minn(curr->x1, curr->x2) - 1][curr->y1 + 1] += 1;
				}
			}
		}
	}
	if (x1 == x2)
	{ //horizenal
		if (qadr(y1 - y2) != len - 1)
		{
			return 0;
		}
		for (j = minn(y1, y2); j <= maxx(y1, y2); j++)
		{
			map_valid_test[x1][j] += 100;
			if (x1 < 9)
			{
				map_valid_test[x1 + 1][j] += 1;
			}
			if (x1 > 0)
			{
				map_valid_test[x1 - 1][j] += 1;
			}
		}
		if (maxx(y1, y2) < 9)
		{
			map_valid_test[x1][maxx(y1, y2) + 1] += 1;
			if (x1 > 0)
			{
				map_valid_test[x1 - 1][maxx(y1, y2) + 1] += 1;
			}
			if (x1 < 9)
			{
				map_valid_test[x1 + 1][maxx(y1, y2) + 1] += 1;
			}
		}
		if (minn(y1, y2) > 0)
		{
			map_valid_test[x1][minn(y1, y2) - 1] += 1;
			if (x1 > 0)
			{
				map_valid_test[x1 - 1][minn(y1, y2) - 1] += 1;
			}
			if (x1 < 9)
			{
				map_valid_test[x1 + 1][minn(y1, y2) - 1] += 1;
			}
		}
	}

	else if (y1 == y2)//vertical
	{
		if (qadr(x1 - x2) != len - 1)
		{
			return 0;
		}
		for (j = minn(x1, x1); j <= maxx(x1, x2); j++)
		{
			map_valid_test[j][y1] += 100;
			if (y1 < 9)
			{
				map_valid_test[j][y1 + 1] += 1;
			}
			if (y1 > 0)
			{
				map_valid_test[j][y1 - 1] += 1;
			}
		}
		if (maxx(x1, x2) < 9)
		{
			map_valid_test[maxx(x1, x2) + 1][y1] += 1;
			if (y1 > 0)
			{
				map_valid_test[maxx(x1, x2) + 1][y1 - 1] += 1;
			}
			if (y1 < 9)
			{
				map_valid_test[maxx(x1, x2) + 1][y1 + 1] += 1;
			}
		}
		if (minn(x1, x2) > 0)
		{
			map_valid_test[minn(x1, x2) - 1][y1] += 1;
			if (y1 > 0)
			{
				map_valid_test[minn(x1, x2) - 1][y1 - 1] += 1;
			}
			if (y1 < 9)
			{
				map_valid_test[minn(x1, x2) - 1][y1 + 1] += 1;
			}
		}
	}
	int test;
	/*for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%4d", map_valid_test[i][j]);
		}
		printf("\n");
	}*/
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			test = map_valid_test[i][j];
			if (test > 100)
			{
				if(print_errors)
				{
				    printf("invalid ship .\n");
				    printf("crashed ships .\n");
				}

				return 0;
			}
		}
	}

	return 1;
}

int print_available_users_and_get_name_score(struct player* p) {
	char nam[100];
	struct acc account;
	FILE* fp = fopen("accounts.bin", "rb");
	if (fp == NULL) {
		printf("no available users to choose\n please enter new one\n");
		return -1;
	}
	while (1) {
		fread(&account, sizeof(struct acc), 1, fp);
		if (feof(fp))
		{
			fclose(fp);
			break;
		}

		else
		{
			strcpy(nam, account.name);
			printf("%s\n", nam);

		}
	}
	do {
		printf("please enter the exact name :\n");
		//scanf("%s", nam);
		fflush(stdin);
		gets(nam);
	} while (is_in_acc_list(nam) == 0);

	strcpy((p->name), nam);
	//p->score = find_score(p->name);
     p->score = 0;
	return 1;

}

int is_in_acc_list(char nam[]) {

	struct acc account;
	FILE* fp = fopen("accounts.bin", "rb");
	if (fp == NULL) {
		return 0;
	}

	while (1) {
		fread(&account, sizeof(struct acc), 1, fp);
		if (feof(fp)) {
			return 0;
		}
		else if (strcmp(account.name, nam) == 0) {
			return 1;
		}
	}
}

void put_new_acc_on_acc_list(char nam[100]) {
	FILE* fp = fopen("accounts.bin", "rb+");
	if (fp == NULL) {
		fp = fopen("accounts.bin", "wb");
	}
	fseek(fp, 0, SEEK_END);
	struct acc new_acc;
	strcpy(new_acc.name, nam);
	new_acc.score = 0;
	fwrite(&new_acc, sizeof(struct acc), 1, fp);
	fclose(fp);
	printf("new account saved successfuly .\n");
	return;
}

int find_score(char nam[100]) {
	FILE* fp = fopen("accounts.bin", "rb");
	struct acc account;
	while (1)
	{
		fread(&account, sizeof(struct acc), 1, fp);
		if (feof(fp)) {
			fclose(fp);
			return 0;//hich vaqt etefaq nemiofte
		}
		else if (strcmp(account.name, nam) == 0) {
			fclose(fp);
			return account.score;
		}
	}
}

void show_score_board(void) {
	FILE* fp = fopen("accounts.bin", "rb");
	if (fp == NULL) {
		printf("No accounts yet\n");
		return;
	}
	struct acc account;
	while (1)
	{
		fread(&account, sizeof(struct acc), 1, fp);
		if (feof(fp)) {
			fclose(fp);
			return;
		}
		printf("account : %s  score : %d\n", account.name, account.score);
	}
}

void sort_acc_list(void) { // decreasing sort
	FILE* fp = fopen("accounts.bin", "rb");
	if(fp == NULL){
		return;
	}
	struct acc account[1000], tmp;
	int i = 0, j = 0, k = 0;
	while (1) {
		fread(&account[i], sizeof(struct acc), 1, fp);
		i++;
		if (feof(fp))
		{
			i--;
			fclose(fp);
			break;
		}
	}
	for (j = 0; j < i; j++) {
		for (k = j + 1; k < i; k++) {
			if (account[j].score < account[k].score) {
				tmp = account[j];
				account[j] = account[k];
				account[k] = tmp;
			}
		}
	}
	fp = fopen("accounts.bin", "wb");
	fwrite(account, sizeof(struct acc), i, fp);
	fclose(fp);
	return;
}

void set_bot(struct player * p){

	strcpy(p->name , "");//set name
	p->score = 0;//set score
	p->ships_head = NULL;
	set_maps_to_space(p);//set map

	//set ships:
	random_ships(p);
	/*
	add_ship_end(p , new_ship(0 , 0 , 0 , 4 , 5));
	add_ship_end(p , new_ship(2 , 0 , 2 , 2 , 3));
	add_ship_end(p , new_ship(4 , 0 , 4 , 2 , 3));
	add_ship_end(p , new_ship(6 , 0 , 6 , 1 , 2));
	add_ship_end(p , new_ship(8 , 0 , 8 , 1 , 2));
	add_ship_end(p , new_ship(0 , 9 , 1 , 9 , 2));
	add_ship_end(p , new_ship(3 , 8 , 3 , 8 , 1));
	add_ship_end(p , new_ship(5 , 8 , 5 , 8 , 1));
	add_ship_end(p , new_ship(7 , 8 , 7 , 8 , 1));
	add_ship_end(p , new_ship(9 , 8 , 9 , 8 , 1));
	*/
	return;
}

void play_with_bot(struct player * p1 , struct player * p2){//p2 is the bot
	system("cls");
	int x11 , y11 , x22 , y22 ,jayze1 = 0 , jayze2 = 0;
	struct point bot_action;
	int nuke = 0;
	while((p1->ships_head != NULL) && (p2-> ships_head != NULL)){//condition is useless but just in case
		do{
			if(jayze1 != 1)
			{
				print_map(p2);
			}
			jayze1 = 0;
			printf("%s attacks: \nscore : %d\n" , p1->name , p1->score);
			do{
			    printf(" enter the point to attack (enter the number of the row then space then the number of column)(or -1 to save game): \n");
			    scanf("%d" , &x11);
			    if(x11 == -1)
				{
				   save_game(p1 , p2 , 1);
				   empty_army(p1);
				   empty_army(p2);
				   return;
			    }
			    scanf("%d",&y11);
			    fflush(stdin);//to dont let to cheat and choose more than one point
			    if((x11 == 18198 && y11 == 1919))
				{
			    	break;
				}

				if(is_point_valid_to_attack(p2 , x11 , y11) == 0){
					printf("not valid point to attack .\n");
				}
		    }while((is_point_valid_to_attack(p2 , x11 , y11) == 0));
		    if(x11 == 18198 && y11 == 1919)// the important numbers for NAZIs
			{
			    	hitlers_Nuke(p2 , p1);// p1 attacks p2
			    	nuke = 1;
			}
			if(nuke == 0){
				attack(p2 , x11, y11 , &jayze1 , &(p1->score));
			}
		    update_map(p2);
		    print_map(p2);

		}while(jayze1 == 1 && (p1->ships_head != NULL) && (p2->ships_head != NULL));
			Sleep(8000);
		system("cls");

		if (p2->ships_head == NULL) {//end of the game
			printf("!!! player %s wins !!!\n", p1->name);
			p2->score /=2;
			update_scores(p1, p2 , 1);
			return;
		}
		do{
			jayze2=0;
			bot_action = bot_choice(p1);
			x22=bot_action.x;
			y22=bot_action.y;
			attack(p1, x22 , y22 , &jayze2, &(p2->score));
			update_map(p1);
			printf("bot attacked (%d , %d)\n and this is the result :\n",x22, y22);
			print_map(p1);
			Sleep(8000);

		}while(jayze2 == 1 && (p1->ships_head != NULL) && (p2->ships_head != NULL));
		system("cls");
		if(p1->ships_head == NULL){//end of the game
			printf("!!! bot wins !!!");
			p1->score /= 2;
			update_scores(p1, p2 , 1);
			return;
		}
	}
}

void play_togather(struct player* p1, struct player* p2) {
	system("cls");
	int x11, y11, x22, y22, jayze1 = 0, jayze2 = 0;
	int nuke = 0;

	while ((p1->ships_head != NULL) && (p2->ships_head != NULL)) {// condition is useless ; but just in case
		do {
			if (jayze1 != 1) {
				print_map(p2);//nobat nafar 1
			}
			jayze1 = 0;
			printf("%s attacks : \nscore: %d\n", p1->name , p1->score);
			do {
				//printf(" enter the point to attack (or -1 to save game):\n");
				printf(" enter the point to attack (enter the number of the row then space then the number of column)(or -1 to save game): \n");
				scanf("%d", &x11);
				if (x11 == -1) {
					save_game(p1, p2 , 2);
					empty_army(p1);
					empty_army(p2);
					return;
				}
				scanf("%d", &y11);
				fflush(stdin);//to dont let to cheat and choose more than one point
				if(x11 == 18198 && y11 == 1919){
					break;
				}

				if(is_point_valid_to_attack(p2 , x11 , y11) == 0){
					printf("not valid point to attack.\n");
				}
			} while (is_point_valid_to_attack(p2, x11, y11) == 0);
			if(x11 == 18198 && y11 == 1919){
				hitlers_Nuke(p2 , p1);//p1 attacks p2
				nuke = 1;
			}
			if(nuke == 0){
				attack(p2, x11, y11, &jayze1, &(p1->score));
			}
			update_map(p2);
			print_map(p2);
		} while (jayze1 == 1 && (p1->ships_head != NULL) && (p2->ships_head != NULL));

		Sleep(8000);
		system("cls");

		if (p2->ships_head == NULL) {
			printf("!!! player %s wins !!!\n", p1->name);
			p2->score /=2;
			update_scores(p1, p2 ,2);
			return;
		}

		do {
			if (jayze2 != 1) {
				print_map(p1);//nobat nafar 2
			}
			jayze2 = 0;
			printf("%s attacks : \n score : %d\n", p2->name , p2->score);
			do {
				//printf(" enter the point to attack (or -1 to save game):\n");
				printf(" enter the point to attack (enter the number of the row then space then the number of column)(or -1 to save game): \n");
				scanf("%d", &x22);
				if (x22 == -1) {
					save_game(p2, p1 ,2);//nobat p2 hast pas dar reload bazi bayad oon p1 bashe
					empty_army(p1);
					empty_army(p2);
					return;

				}
				scanf("%d", &y22);
				fflush(stdin);//to dont let to cheat and choose more than one point
				if(x22 == 18198 && y22 == 1919)
				{
				    break;
				}
				if(is_point_valid_to_attack(p1 , x22 , y22) == 0){
					printf("not valid point to attack.\n");
				}
			} while (is_point_valid_to_attack(p1, x22, y22) == 0);
			if(x22 == 18198 && y22 == 1919){
				hitlers_Nuke(p1  , p2);//p2 attacks p1
				nuke = 1;
			}
			if(nuke == 0){
			attack(p1, x22, y22, &jayze2, &(p2->score));
			}
			update_map(p1);
			print_map(p1);
		} while (jayze2 == 1 && (p1->ships_head != NULL) && (p2->ships_head != NULL));
		Sleep(8000);
		system("cls");

		if (p1->ships_head == NULL) {
			printf("!!! player %s wins !!!\n", p2->name);
			p1->score /= 2;
			update_scores(p1, p2 , 2);//ino bayad taqir bedi
			return;
		}

	}

}

void set_maps_to_space(struct player* p) {
	int i, j;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			(*p).naghshe_nobat[i][j] = ' ';
		}
	}
	return;
}

void print_map(struct player* p) {
	int i, j;
	printf("//////");
	for(j=0; j<10; j++){
		printf("| %d |" , j);
	}
	printf("\n//////\n");
	//printf("\n-----------------------------------------------------\n");
	//printf("\n");
	for (i = 0; i < 10; i++) {
		printf("%d     " , i);
		for (j = 0; j < 10; j++) {
			if(p->naghshe_nobat[i][j]=='W'){
				printf(BLUE"| ");
				printf(CYAN"%c", p->naghshe_nobat[i][j]);
				printf(BLUE" |");
				printf(RESET);
			}
			else if(p->naghshe_nobat[i][j]=='E'){
				printf(BLUE"| ");
				printf(YELLOW"%c", p->naghshe_nobat[i][j]);
				printf(BLUE" |");
				printf(RESET);
			}
			else if(p->naghshe_nobat[i][j]=='C'){
				printf(BLUE"| ");
				printf(RED"%c", p->naghshe_nobat[i][j]);
				printf(BLUE" |");
				printf(RESET);
			}
			else{// it was space:
			printf(BLUE"| %c |",p->naghshe_nobat[i][j]);
			printf(RESET);
			}
		}
		printf(BLUE"\n--------------------------------------------------------\n");
		printf(RESET);
	}
	return;
}

int is_point_valid_to_attack(struct player* p, int x, int y) {


	if ((x > 9) || (y > 9) || (x < 0) || (y < 0)) {
		return 0;
	}
	else if (p->naghshe_nobat[x][y] != ' ') {
		return 0;
	}
	else {
		return 1;
	}
}

int ship_counter(struct player * p){
	struct ships * curr;
	int n;
	for(n=0 , curr = p->ships_head ; curr != NULL ; n++  , curr = curr->next);
	return n;

}

struct player_game_saver make_game_saver(struct player * p){

	struct player_game_saver  p_s;
	struct ships * curr;
	int i,j;
	strcpy(p_s.name , p->name );
	p_s.score = p->score;
	p_s.ships_count = ship_counter(p);
	for(i = 0 , curr = p->ships_head ; i< p_s.ships_count ; i++ , curr = curr->next){
		p_s.ships_x1[i]=curr->x1;
		p_s.ships_x2[i]=curr->x2;
		p_s.ships_y1[i]=curr->y1;
		p_s.ships_y2[i]=curr->y2;
		p_s.ships_len[i]=curr->len;
		p_s.ships_damage[i]=curr->damage;
	}
	for( i=0 ; i<10 ; i++){
		for( j=0 ;j<10 ;j++){
			p_s.naghshe_nobat_[i][j] = p->naghshe_nobat[i][j];
		}
	}

	return p_s;
}

void save_game(struct player * p1 , struct player *p2 , int game_method ){
     struct string_s game_name;
	 char file_name[200];
	 struct player_game_saver  p1_saver ,  p2_saver;

	 printf("Enter the name of the game to save :\n");

	 fflush(stdin); // empty input buffer
	 gets(game_name.str);

	 strcpy(file_name , game_name.str);
	 strcat(file_name,".bin");

	 p1_saver = make_game_saver(p1);
     p2_saver = make_game_saver(p2);

     FILE * fp = fopen(file_name , "wb");
      fwrite(&game_method , sizeof(int) , 1 , fp);
      fwrite(&p1_saver , sizeof(struct player_game_saver) , 1 , fp);
      fwrite(&p2_saver , sizeof(struct player_game_saver) , 1 , fp);
      fclose(fp);

	 	 fp = fopen ("saved games list.bin" , "rb+");
	  if(fp == NULL){
	  	fp = fopen("saved games list.bin" , "wb");
	  }
	  if(is_in_saved_game_list(game_name) == 0 ){//agar tooye list nabood
	  fseek(fp , 0 , SEEK_END);
      fwrite(&game_name , sizeof(struct string_s) , 1 , fp );
      fclose(fp);
	  }
       fp = fopen ("last game.bin","wb");
      fwrite(&game_method , sizeof(int), 1 , fp);
      fwrite(&p1_saver , sizeof(struct player_game_saver) , 1 , fp);
      fwrite(&p2_saver , sizeof(struct player_game_saver) , 1 , fp);
      fclose(fp);

       system("cls");
       printf("game successfuly saved \n");
       Sleep(3000);

       //exit(0);
       return;
}

int is_in_saved_game_list(struct string_s game_name){
   FILE * fp = fopen("saved games list.bin" , "rb");
   struct string_s game_name_prime;
   if(fp == NULL){
   	return 0;
   }
   else{
   	do{
   		fread(&game_name_prime , sizeof(struct string_s) , 1 , fp);
   		if(feof(fp)){
   			fclose(fp);
   			return 0;
		   }
   		else if(strcmp(game_name_prime.str ,game_name.str ) == 0){
   			return 1;
		   }
	   }while(!feof(fp));
   }
}

struct string_s show_saved_games_and_get_name(void){
	struct string_s game_name;
	int n=0 , game_number;
	FILE* fp = fopen("saved games list.bin","rb");
	if(fp == NULL){
		printf("no saved games yet\n");
		strcpy(game_name.str , "none");
	}
	else{
		do{

			fread(&game_name , sizeof(struct string_s) , 1 , fp);
			n++;
			if(feof(fp))
			{
				fclose(fp);
				break;
			}

			else
			{
			  printf("%d _ %s\n", n, game_name.str);
			}
		}while(!feof(fp));

		printf("Enter the number of the game you want :\n");
		scanf("%d", &game_number);
		fseek(fp , (game_number -1) , SEEK_SET);
		fread(&game_name , sizeof(struct string_s) , 1, fp);

	}

	return game_name;
}

void load_game(struct player * p1 , struct player * p2 , struct string_s game_name , int * game_method_p){
	char game_file_name[200];
	struct player_game_saver p1_s , p2_s;

	strcpy(game_file_name , game_name.str);
	strcat(game_file_name,".bin");
	FILE* fp = fopen(game_file_name , "rb");
	if(fp == NULL){
		printf("No saved recent games\n");
		return;
	}

	fread(game_method_p ,sizeof(int ) , 1, fp);
	fread(&p1_s , sizeof(struct player_game_saver) , 1 , fp);
	fread(&p2_s , sizeof(struct player_game_saver) , 1 , fp);
	fclose(fp);

	set_player(p1 , p1_s);
	set_player(p2 , p2_s);
	return;
}

void set_player(struct player * p , struct player_game_saver p_s){
	int i , j;
	strcpy (p->name , p_s.name);//set name
	//p->score = 0;
	p->score = p_s.score;//set score


	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			p->naghshe_nobat[i][j] = p_s.naghshe_nobat_[i][j];//set maps
		}
	}

	p->ships_head = NULL;
	for(i=0;i<p_s.ships_count;i++){
		add_ship_end(p , old_ship(p_s.ships_x1[i] , p_s.ships_y1[i] , p_s.ships_x2[i] , p_s.ships_y2[i] , p_s.ships_len[i] , p_s.ships_damage[i]));
	}//set ships;

	return;
}

void attack(struct player* p, int x, int  y, int* jayze, int* score) {
	struct ships* curr;
	int found = 0;
	for (curr = p->ships_head; curr != NULL; curr = curr->next)
	{
		if (curr->x1 == curr->x2)//check horizenal ship
		{
			if ((x == curr->x1) && (minn(curr->y1, curr->y2) <= y) && (y <= maxx(curr->y2, curr->y1))) {
				curr->damage++;
				(*score)+=1;//afzayesh emtiaz baraye zadan ye khoone eshqal shode harif
				p->naghshe_nobat[x][y] = 'E';
				found = 1;
			}
		}
		else {//check vertical ship
			if ((y == curr->y1) && (minn(curr->x1, curr->x2) <= x) && (x <= maxx(curr->x1, curr->x2))) {
				curr->damage++;
				(*score)+=1;
				p->naghshe_nobat[x][y] = 'E';
				found = 1;
			}
		}

		if (curr->damage == curr->len)
		{
			if (curr->len == 5) {
				(*score )+= 5;
			}
			else if (curr->len == 3) {
				(*score) += 8;
			}
			else if (curr->len == 2) {
				(*score )+= 12;
			}
			else if (curr->len == 1) {
				(*score )+= 25;
			}
			complete_explosion(p, curr);
			delete_ship(p, curr);

		}
		if (found == 1) {
			*jayze = 1;
			return;
		}
	}
	// if in no ships:
	p->naghshe_nobat[x][y] = 'W';
	return;
}//hanooz kar dare

void delete_ship(struct player* p, struct ships* target) {
	struct ships* prev, * curr, * tmp;
	prev = p->ships_head;
	curr = prev->next;
	if (p->ships_head == target)
	{
		if (p->ships_head->next == NULL)
		{
			free(p->ships_head);
			p->ships_head = NULL;
		}
		else
		{
			tmp = p->ships_head->next;
			free(p->ships_head);
			p->ships_head = tmp;
		}
	}
	else
	{
		while (curr != target) {
			prev = curr;
			curr = curr->next;
		}
		tmp = curr->next;
		free(curr);
		prev->next = tmp;
	}

	return;
}

void complete_explosion(struct player* p, struct ships* destroyed_ship) {
	int i;
	if (destroyed_ship->x1 == destroyed_ship->x2)//horizenal ship
	{
		for (i = minn(destroyed_ship->y1, destroyed_ship->y2); i <= maxx(destroyed_ship->y1, destroyed_ship->y2); i++)
		{
			p->naghshe_nobat[destroyed_ship->x1][i] = 'C';
		}
	}
	else // vertical ship
	{
		for (i = minn(destroyed_ship->x1, destroyed_ship->x2); i <= maxx(destroyed_ship->x1, destroyed_ship->x2); i++)
		{
			p->naghshe_nobat[i][destroyed_ship->y1] = 'C';
		}
	}
	return;
}

void update_map(struct player* p) {
	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (p->naghshe_nobat[i][j] == 'C')
			{
				//barressi dor o atraf:
				if (is_point_valid_to_check(i, j + 1))
				{
					if (p->naghshe_nobat[i][j + 1] == ' ')
					{
						p->naghshe_nobat[i][j + 1] = 'W';
					}
				}

				if (is_point_valid_to_check(i, j - 1))
				{
					if (p->naghshe_nobat[i][j - 1] == ' ')
					{
						p->naghshe_nobat[i][j - 1] = 'W';
					}
				}

				if (is_point_valid_to_check(i + 1, j))
				{
					if (p->naghshe_nobat[i + 1][j] == ' ')
					{
						p->naghshe_nobat[i + 1][j] = 'W';
					}
				}

				if (is_point_valid_to_check(i + 1, j + 1))
				{
					if (p->naghshe_nobat[i + 1][j + 1] == ' ')
					{
						p->naghshe_nobat[i + 1][j + 1] = 'W';
					}
				}
				if (is_point_valid_to_check(i + 1, j - 1))
				{
					if (p->naghshe_nobat[i + 1][j - 1] == ' ')
					{
						p->naghshe_nobat[i + 1][j - 1] = 'W';
					}
				}

				if (is_point_valid_to_check(i - 1, j))
				{
					if (p->naghshe_nobat[i - 1][j] == ' ')
					{
						p->naghshe_nobat[i - 1][j] = 'W';
					}
				}

				if (is_point_valid_to_check(i - 1, j + 1))
				{
					if (p->naghshe_nobat[i - 1][j + 1] == ' ')
					{
						p->naghshe_nobat[i - 1][j + 1] = 'W';
					}
				}

				if (is_point_valid_to_check(i - 1, j - 1))
				{
					if (p->naghshe_nobat[i - 1][j - 1] == ' ')
					{
						p->naghshe_nobat[i - 1][j - 1] = 'W';
					}
				}
			}
		}
	}
}

int is_point_valid_to_check(int x, int y) {
	if ((x <= 9) && (x >= 0) && (y <= 9) && (y >= 0))
	{
		return 1;
	}
	else {
		return 0;
	}
}

void update_scores(struct player* p1, struct player* p2 , int game_method) {
	//printf("player %s with score %d \nplayer %s with score %d\n",p1->name , p1->score ,p2->name , p2->score);
	printf("player %s with score %d \n",p1->name , p1->score);
	if(strcmp(p2->name , "") != 0)//if p2 was not the bot
	{
		printf("player %s with score %d\n",p2->name , p2->score);
	}
	Sleep(6000);
	system("cls");
	FILE* fp = fopen("accounts.bin", "rb+");
	struct acc account;
	int j = 0;
	if(game_method == 1){
		do {
		    fread(&account, sizeof(struct acc), 1, fp);
		    j++;
		     if (feof(fp)) {
			    fclose(fp);
			    printf("Scores updated\n");
			    Sleep(3000);
			    system("cls");
			    return;
		    }
		     if (strcmp(account.name, p1->name) == 0) {
			    account.score += p1->score;
			    fseek(fp, (j - 1) * (sizeof(struct acc)), SEEK_SET);
			    fwrite(&account, sizeof(struct acc), 1, fp);
			    fseek(fp  , j * sizeof(struct acc) , SEEK_SET);
		     }

	    } while (!feof(fp));
	}//the scores of bot dont matter and do not save
    else if(game_method == 2){

	    do {
		    fread(&account, sizeof(struct acc), 1, fp);
		    j++;
		     if (feof(fp)) {
			    fclose(fp);
			    printf("Scores updated\n");
			    Sleep(3000);
			    system("cls");
			    return;
		    }
		     if (strcmp(account.name, p1->name) == 0) {
			    account.score += p1->score;
			    fseek(fp, (j - 1) * (sizeof(struct acc)), SEEK_SET);
			    fwrite(&account, sizeof(struct acc), 1, fp);
			    fseek(fp  , j * sizeof(struct acc) , SEEK_SET);
		     }
		    if (strcmp(account.name, p2->name) == 0) {
			    account.score += p2->score;
			    fseek(fp, (j - 1) * (sizeof(struct acc)), SEEK_SET);
			    fwrite(&account, sizeof(struct acc), 1, fp);
			    fseek(fp, j* sizeof(struct acc),SEEK_SET);
		    }
	    } while (!feof(fp));
	}
    printf("Scores updated\n");
	Sleep(3000);
	system("cls");

	fclose(fp);
	return;
}

struct point bot_choice(struct player * p ){
    int i , j;
	struct point choice;
	int rand_num , attack_valid_points_count =0;
	//the number of valid points to attack
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(is_point_valid_to_attack(p , i , j)){
				attack_valid_points_count++;
			}
		}
	}
	//smart choice:
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(p->naghshe_nobat[i][j] == 'E')
			{

				if(p->naghshe_nobat[i-1][j] == 'E')
				{

					if(is_point_valid_to_attack(p , i-2 , j))
					{
						choice.x = i-2;
						choice.y = j;

						return choice;
					}
				}

				if(p->naghshe_nobat[i+1][j] == 'E')
				{

					if(is_point_valid_to_attack(p , i+2 , j))
					{
						choice.x = i+2;
						choice.y = j;

						return choice;
					}
				}

				if(p->naghshe_nobat[i][j-1] == 'E')
				{

					if(is_point_valid_to_attack(p , i, j-2))
					{
						choice.x = i;
						choice.y = j-2;

						return choice;
					}
			    }

			    if(p->naghshe_nobat[i][j+1] == 'E')
				{

					if(is_point_valid_to_attack(p , i , j+2))
					{
						choice.x = i;
						choice.y = j+2;

						return choice;
					}
				}

			}
		}
	}

	//if there was no neghbor exploded points , look for one :
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{

		     if(p->naghshe_nobat[i][j] == 'E'){
		     	if(is_point_valid_to_attack(p , i-1, j)){
		     		choice.x = i-1;
		     		choice.y = j;

		     		return choice;
				 }
				 else if(is_point_valid_to_attack(p , i+1, j)){
				 	choice.x = i+1;
				 	choice.y = j;

				 	return choice;
				 }
				 else if(is_point_valid_to_attack(p , i, j-1)){
				 	choice.x = i;
				 	choice.y = j-1;

				 	return choice;
				 }
				 else if(is_point_valid_to_attack(p , i, j+1)){
				 	choice.x = i;
				 	choice.y = j+1;

				 	return choice;
				 }
			 }
		}
	}
	//if there was no choice :
	//random choice:
	rand_num = (rand())%attack_valid_points_count;
	choice.x=0;
	choice.y=0;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){

			   if(is_point_valid_to_attack(p , i, j) && rand_num>0){
			   	    rand_num--;
				    choice.x = i;
			     	choice.y = j;
			   }
		}
	}
	return choice;
}

int number_of_saved_users(void){

	FILE * fp = fopen("accounts.bin" , "rb");
	struct acc account;
	int j=0;
	if(fp == NULL){
		return 0;
	}
	while (1){
		fread(&account , sizeof(struct acc) , 1, fp);
		if(feof(fp)){
			return j;
		}
		j++;
	}
}

void hitlers_Nuke(struct player * p1 , struct player * p2){
	int i , j;
	int jayze;//does not matter any more
	for(i=0;i<30000;i++){
		j=rand();
		printf("%c" , j);
	}
	system("cls");
	Sleep(600);

	for(i=0;i<30000;i++){
		j=rand();
		printf("%c" , j);
	}
	Sleep(600);
	system("cls");


	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(is_point_valid_to_attack(p1 , i , j )){
				attack(p1 , i , j , &jayze , &(p2->score));
			}
		}
	}
	printf("THAT WAS THE HITLER'S SECRET NUKE PASSWORD\n");
	printf("YOU DESTROYED ALL OF THE ENEMY'S ARMY\n");
	Sleep(3500);

	return ;
}
//cheat code
void random_ships(struct player * p){
	int horizenal , n , len;
	int x111,y111,x222,y222;

	len = 5;
	while(1)
	{
	    horizenal = (rand())%2;
	    if(horizenal)
		{
	    	x222 = x111 = (rand()) %10 ;
	    	y111 = (rand()) % (11-len);
	    	y222 = y111 + len -1;
		}
		else // vertical
		{
			y222 = y111 =( rand())%10;
			x111 = (rand()) %(11 - len);
			x222 = x111 + len -1 ;
		}
		if(is_ship_valid(*p , x111 , y111 , x222 , y222 , len , 0)){
			add_ship_end(p , new_ship(x111, y111 , x222 , y222 , len));
			break;
		}

	}

	len = 3;
	for(n=0 ; n<2; n++)
	{

	     while(1)
    	{
	         horizenal = (rand())%2;
	         if(horizenal)
		     {
	    	     x222 = x111 = (rand())%10 ;
	    	     y111 = (rand()) % (11-len);
	    	     y222 = y111 + len -1;
	 	     }
		     else // vertical
		     {
		 	     y222 = y111 = (rand()) %10;
			     x111 = (rand()) %(11 - len);
			     x222 = x111 + len -1 ;
		     }
		     if(is_ship_valid(*p , x111 , y111 , x222 , y222 , len , 0)){
			     add_ship_end(p , new_ship(x111, y111 , x222 , y222 , len));
			     break;
		     }

	     }
	}

	for(n=0 ; n<3 ; n++){
		len = 2;
	     while(1)
	     {
	         horizenal = (rand())%2;
	         if(horizenal)
		     {
	    	     x222 = x111 = (rand()) %10 ;
	    	     y111 = (rand()) % (11-len);
	    	     y222 = y111 + len -1;
		     }
		     else // vertical
		     {
			     y222 = y111 = (rand()) %10;
			     x111 = (rand()) %(11 - len);
			     x222 = x111 + len -1 ;
	 	     }
		     if(is_ship_valid(*p , x111 , y111 , x222 , y222 , len , 0)){
			     add_ship_end(p , new_ship(x111, y111 , x222 , y222 , len));
			     break;
		     }

	     }
	}
	for(n = 0 ; n<4;n++)
	{

	     len = 1;
	     while(1)
	     {
	         horizenal = (rand())%2;
	         if(horizenal)
		     {
	    	     x222 = x111 = (rand()) %10 ;
	    	     y111 = (rand()) % (11-len);
	    	     y222 = y111 + len -1;
		     }
		     else // vertical
		     {
			     y222 = y111 = (rand()) %10;
		  	     x111 = (rand()) %(11 - len);
		 	     x222 = x111 + len -1 ;
		     }
		     if(is_ship_valid(*p , x111 , y111 , x222 , y222 , len , 0)){
			      add_ship_end(p , new_ship(x111, y111 , x222 , y222 , len));
			      break;
		     }

	     }
     }

     return;
}

void empty_army(struct player * p){
	while(p->ships_head != NULL){
		delete_ship(p , p->ships_head);
	}
	return;
}

void print_ships(struct player * p){
	int army_map[10][10] = {0};
	int min_x , max_x , min_y , max_y , i, j;
	struct ships * curr;
	for(curr=p->ships_head ; curr != NULL ; curr = curr->next){
		min_x = minn(curr->x1 , curr->x2);
		min_y = minn(curr->y1 , curr -> y2);
		max_x = maxx(curr->x1, curr->x2);
		max_y = maxx(curr->y1, curr->y2);
		for( i=0 ; i<10 ; i++ ){
			for( j=0 ; j<10 ; j++){
				if((i<=max_x)&&(i>=min_x)&&(j<=max_y)&&(j>=min_y)){
					army_map[i][j] = curr->len;
				}
			}
		}
	}
	printf("the ships (each ship is fixed on the map by its length and ziro means empty point):\n");
	printf("//////");
	for(j=0; j<10; j++){
		printf("| %d |" , j);
	}
	printf("\n//////\n");

	//printf("\n");
	for (i = 0; i < 10; i++) {
		printf("%d     " , i);
		for (j = 0; j < 10; j++) {
			printf("| %d |", army_map[i][j]);
		}
		printf("\n--------------------------------------------------------\n");
	}
	return;
}
