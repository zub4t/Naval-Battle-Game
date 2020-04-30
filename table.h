
// typedef struct Player
// {
//  //vai ter de ser criada
// } Player;

typedef struct Ship
{

  int type; //int ou string(char*) ?
  int ActiveCells;

} Ship;

typedef struct Cell
{
  int state; // 0 = empty, 1 = piece without being hitted,
             // 2 = piece hitted, 3 = missed shot
  int shotState;
  Ship *bellongsTo; // if cell is empty bellongsTo is null
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
  Cell matriz[10][10];
} Player;

void chooseShips(Player *player);

void updateCell(Cell *, int, Ship *);
Cell *newCell();
int isFree(Cell *);
void shotCell(Cell *);
void decreaseActiveCell(Ship *);
Ship *newShip(int);
void setUp(int size, Cell matriz[10][10], Player Player);
void putSingleShip(Player *Player,int index);
void initializeMatriz(Player *Player, int size);
void print(Player *player);

void startGame(Player *p1, Player *p2);

void updateCellShort(Cell *cell, int state);
int shipSank(Ship *ship);
void print_table(Player *player, int flag);
void changePlayer();
int  ScanAndShot(Player *source_player,Player *target_player);
