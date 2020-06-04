#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */
#include "./quadtree/src/quadtree.h"

typedef struct Ship
{

  int type; //int ou string(char*) ?
  int ActiveCells;

} Ship;

typedef struct Cell
{
  int state; // 0 = empty, 1 = piece without being hitted,// 2 = piece hitted, 3 = missed shot
  int shotState;
  Ship bellongsTo; // if cell is empty bellongsTo is null
} Cell;
typedef struct Node
{
  Ship value;
  int amount;
  int index;
  int gravity_point_row;
  int gravity_point_col;
  int rotate;
} Node;

typedef struct Player
{
  int ID_P;
  int activeShips;
  char *name;
  Node *myShips;
  int total_pieces;
  Cell matriz[40][40];
  quadtree_t *tree ;

} Player;

typedef struct shipPlayer
{

  Ship ship;
  Player palyer;
} shipPlayer;

void chooseShips(Player *player, int random);
void updateCell(Cell *, int, Ship);
Cell *newCell();
int isFree(Cell *);
void shotCell(Cell *);
void decreaseActiveCell(Ship *);
Ship newShip(int type, int n);
void setUp(int size, Cell matriz[40][40], Player Player);
void putSingleShip(Player *Player, int index);
void initializeMatriz(Player *Player, int size);
void print(Player *player, int size);

void startGame(Player *p1, Player *p2, int shmt);

void updateCellShort(Cell *cell, int state);
int shipSank(Ship ship);
void print_table(Player *player, int flag, int SIZE);
void changePlayer();
int ScanAndShot(Player *source_player, Player *target_player);
int randomN(int min, int max);
void write_conf(char *name, Player *p,int quad);
void read_conf(char *name, Player *p,int quad);
int writeSharedMemory(Player p, int SHM_KEY);
Player *readSharedMemory(int SHM_KEY);
int closeSharedMemory(Player *p);
int closeWriteSharedMemory(int shmid);
void startGameNoShared(Player *p1, Player *p2, int semaphore_id);
void switchMatrizToQuad(Player *player);