#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
//macrio for shapes
#define CHAR_BIRD 'O'
#define CHAR_STONE '*'
#define CHAR_BLANK ' '
//nblocks linked list
typedef struct node{
	int x, y;
	struct node *next;
}node, *Node;

Node head, tail;
int bird_x, bird_y;
int ticker;
void init();
void init_bird();
void init_draw();
void init_wall();
void init_head();
void drop(int sig);
int set_ticker(int n);

int main()
{
	char ch;
    
    init();
    while(1) 
    {
    	ch = getch();  //keyboard interruput 
    	if(ch == ' ' || ch == 'w' || ch == 'W'){
    		 //clear orignial bird
    		move(bird_y, bird_x);//move cursor
    		addch(CHAR_BLANK);
    		refresh();
    		bird_y--;  //update new bird
    		move(bird_y, bird_x);
    		addch(CHAR_BIRD);
    		refresh();
    		if((char)inch() == CHAR_STONE){  //gameover
    			set_ticker(0);
    			sleep(1);
    			endwin();
    			exit(0);
    		}
    	}
    	else if(ch == 'z' || ch == 'Z'){ //pause
    		set_ticker(0);
    		do 
    		{
    			ch = getch();
    		} while(ch != 'z' && ch != 'Z');
    		set_ticker(ticker);
    	}else if(ch == 'q' || ch == 'Q') {//quit
    		sleep(1);
    		endwin();
    		exit(0);
    	}
    }
    return 0;
}
//setting alarm for the event refer to GNU API
int set_ticker(int n_msec)
{
	struct itimerval timeset;
	long n_sec, n_usec;

	n_sec = n_msec / 1000;
	n_usec = (n_msec % 1000) * 1000L;

	timeset.it_interval.tv_sec = n_sec;
	timeset.it_interval.tv_usec = n_usec;

	timeset.it_value.tv_sec = n_sec;
	timeset.it_value.tv_usec = n_usec;

	return setitimer(ITIMER_REAL, &timeset, NULL);
}
//receiving alarm information --> lets drop the bird
void drop(int sig){
	//basic update with bird
    int j; 
    Node tmp, p;
    move(bird_y, bird_x);
    addch(CHAR_BLANK);//refill with blank
    refresh();
    bird_y++;
    move(bird_y, bird_x);//drop bird
    addch(CHAR_BIRD);
    refresh();
    if((char)inch() == CHAR_STONE){//gameover
        set_ticker(0);
    	sleep(1);
    	endwin();
    	exit(0);
    }
    p = head->next;
    if(p->x < 0){  //rm the blocks out of site and fill new 
			head->next = p->next;//move the head block
			free(p);//rm the orginal head
			tmp = (node *)malloc(sizeof(node));//creating a new block element at right
			tmp->x = 99;
			do {
				tmp->y = rand() % 16;
			}while(tmp->y < 5);
			tail->next = tmp;//updating the tail
			tmp->next = NULL;
			tail = tmp;
			ticker -= 10; //acclerate
			set_ticker(ticker);
    }
    //update the game background ***
    for(p = head->next; p->next != NULL; p->x--, p = p->next) { //iterate through linked list and moving the blocks //note p-- only update the element
			for(j = 0; j < p->y; j++){ //rmblock at the right edge
				move(j, p->x);
				addch(CHAR_BLANK);
				refresh();
			}
			for(j = p->y+5; j <= 23; j++){
				move(j, p->x);
				addch(CHAR_BLANK);
				refresh();
			}
			if(p->x-10 >= 0 && p->x < 80) { //draw the blocks at the left edge if in window
				for(j = 0; j < p->y; j++) {
					move(j, p->x-10);
					addch(CHAR_STONE);
					refresh();
				}
				for(j = p->y + 5; j <= 23; j++) {
					move(j, p->x-10);
					addch(CHAR_STONE);
					refresh();
				}
			}
    }
    tail->x--;//updating tail axises
}

void init() //initalize window for ncruise
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	srand(time(0));
	signal(SIGALRM, drop);
	init_bird();
	init_head();
	init_wall();
	init_draw();
	sleep(1);
	ticker = 500;
	set_ticker(ticker);
}

void init_bird(){ //give birth to the bird{
	bird_x = 5;
	bird_y = 15;
	move(bird_y, bird_x);
	addch(CHAR_BIRD);
	refresh();
	sleep(1);
}

void init_head(){ //initalize block
	Node tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->next = NULL;
	head = tmp;
	tail = head; //head=tail before everything started
}

void init_wall() //intialize the wall
{
	int i;
	Node tmp, p;
	p = head;//leads to the head
	for(i = 19; i <= 99; i += 20)//19->39->59->79->99
	{
		tmp = (node *)malloc(sizeof(node));
		tmp->x = i;
		do{
			tmp->y = rand() % 16;
		}while(tmp->y < 5); //anynumber from 5-16
		p->next = tmp;
		tmp->next = NULL;//linking 5blocks together
		p = tmp;//moving the blocks
	}
	tail = p;//now settingh the tail
}

void init_draw() //setting window
{
	Node p;
	int i, j;

	for(p = head->next; p->next != NULL; p = p->next){//iterate through linked list
		for(i = p->x; i > p->x-10; i--){//drawing stones and leave the middle blank
			for(j = 0; j < p->y; j++){
				move(j, i);
				addch(CHAR_STONE);
				refresh();
			}
			for(j = p->y+5; j <= 23; j++){
				move(j, i);
				addch(CHAR_STONE);
				refresh();
			}
		}
		sleep(1);
	}
}
