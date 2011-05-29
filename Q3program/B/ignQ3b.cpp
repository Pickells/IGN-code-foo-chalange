//////////////////////////////////////////////////////////////////////////////////////////////////////
//// THIS PROGRAM IS MADE BY ABDULLAH ALHASAN FROM KUWAIT FOR QUESTION 3 OF IGN code-foo AD       ////
//// THIS PROGRAM PRINTS THE MINNIMUM PATH OF A KNIGHT IN A CHESS BOARD TO COVER ALL THE SPACES   ////
//// AND THE MINNIMUM POSSIBLE MOVES FOR THE KNIGHT IS 21 MOVES SINCE THE STARTING POINT DOES NOT ////
//// COUNT AS A MOVE AND FOR EACH MOVE THE KNIGHT MAKES IT WILL COVER 3 NEW SPACES SO IF THERE IS ////
//// A PATH FOR A KNOGHT WITH 21 MOVES TO COVER ALL THE CHESS BOARD THEN THAT PATH IS THE MINNIMUM////
//// PATH. THIS PROGRAM MAY TAKE A FEW SECONDS TO PRINT THE RESULT                                ////
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>		// for cout
#include <cstddef>		// for NULL

using namespace std;


int start[2];			//this is the starting point of the knight
int count = 0;			// counts each move to determin the minnimum possibility
int chess[8][8];        // to know which space is visited and which are still available
int steps = 21;


struct node				// the structure of the nodes in the liked list for the path
{
	node* prev ;		// points to the previos node
	int m ;				// the knight has 8 possible kinds of moves but each move has 2 paths. this determines what kind of path it will take
	int position[2];	// the posistion of the node
	node* next;			// points to the next node
};
typedef node* nodeptr;


bool path ( nodeptr p );// this function creats the path that the knight will take
void move( nodeptr p );	// moves the current node to its new place
bool check ( int x[2] , int m );// checks the new path if it isn't out of bound of the chess board or not yet visited
void unvisit ( int x[2] , int m );// returns the visited path to unvisited
bool full();			// checks if the all the spaces in the chess board are visited or not
void makepath( nodeptr p ); // prints each step of the knight

int main ()
{

	nodeptr currptr;
	start[0] = 0;		// initializing start
	start[1] = 0;

	for ( int i=0 ; i < 8 ; i++ )// initializing the chess board to set it all to 0 which means not visited
		for ( int j=0; j<8 ; j++ )
			chess[i][j] = 0;

	cout << "A chess board has 64 spaces,\nthe starting position for the knight is already covered without any moves,\n";
	cout << "so we have 63 spaces left to cover,\nif for every move the knight makes it will cover 3 new spaces,\n";
	cout << "then the minnimum posible moves for the knight to cover all the chess board is \n63/3 which is 21 moves.\n\n";


	cout << " please wait this may take a min !!!! \n\n";

	currptr = new node;	// creating the first node
	currptr->m = 0;		//setting the kind of move to the first one
	currptr->next = NULL;//this is the first node so there is no next nor prev
	currptr->prev = NULL;
	currptr->position[0] = 0;//the starting position is going to be 0,0
	currptr->position[1] = 0;

	chess[start[0]][start[1]] = 1;// setting the starting possition to 1 which means that this space is visited

	if ( path( currptr ) )//check if there is a path with 21 moves
	{
		cout << "the path for a knight to cover all the chess baord starts at \n";
		cout << currptr->position[0]+1 << "," << currptr->position[1]+1 << "->";// prints the moves that the program selected
		currptr = currptr->next;
		while ( currptr->next != NULL )
		{
			cout << currptr->position[0]+1 << "," << currptr->position[1]+1 << "->";
			currptr = currptr->next;
		}
		cout << currptr->position[0] << "," << currptr->position[1];
		cout << "\nsince the knight steps on each space once and there is no cross over";
		cout << "\nthen this is the minnimum possiblity with " << steps << " moves \n";
	}
	else 
		cout << " no path for " << steps << " step " ;// there was no path that covers the chess board with 63 moves

	for( i=0 ; i<8 ; i++)
		for( int j=0; j<8 ; j++)
			chess[i][j] = 0;

	while ( currptr->prev != NULL )
		currptr = currptr->prev;

	makepath( currptr );

	return 0;
}

bool path ( nodeptr p )
{
	bool b = false;		// if this flag is false then there is no path yet 
	nodeptr temp;		// a temporary pointer


	// read the next comments from the last loop to the first to uinderstand it 

	while ( start[1] < 3 && b == false )// if the node is the first node then move it to a new starting point
	{
		while ( start[0] < 3 && b == false )// if the node is the first node then move it to a new starting point
		{
			do			// if all the possible move are checked and no one is acceptable then return to the previos node
			{
				for ( ;p->m < 16 && b == false; p->m++) // if the the program didn't check all this positions possible moves and the path has not been found yet do this 
				{
					while ( check ( p->position , p->m ) && b == false ) // if the next move is good and the path has not been found yet do this 
					{
						count ++; // increas the move count by 1
				
						p->next = new node ; // creat a new node and move it to its new position
						p->next->m = 0;
						p->next->next = NULL;
						p->next->prev = p;
						p = p->next;
						move ( p );			// move the new node to its new possition
		
						if ( count == steps)  // if we have 21 moves then we have a full path for the knight
							b = true;		// we found a path
	
					}
				
		
				}

				if ( b == false && p->prev != NULL )	// if we haven't found a path yet do this 
				{
					chess[p->position[0]][p->position[1]] = 0;	// make this position not visited again
					temp = p;		// move to the previos node and delete the node the we just left 
					p = p->prev;
					delete temp;
					p->next = NULL;
					unvisit( p->position, p->m ); // make the path that was visited not visited again
					p->m++;			// increas m by 1 to not check the same place again
					count--;		// because we returnd we need to decreas the move counter by 1
				
				}
			} while ( p->prev != NULL && b == false );	// (this is for the do()while) this checks that this is not the first node so we dont delete it


			if ( b == false )
			{
				unvisit ( p->position, p->m );
				chess[start[0]][start[1]] = 0;	// return to not visited
				start[0] = start[0]+1;			// change the starting possition
				chess[start[0]][start[1]] = 1;	// make the new starting possition visited
				p->position[0] = start[0];		
				p->position[1] = start[1];
				p->m = 0;		//set the move to the first mave again because it comes with the last one
			}
		}
		if ( b == false )
		{
			unvisit ( p->position, p->m );
			chess[start[0]][start[1]] = 0;	// same as the previos one 
			start[1] = start[1]+1;
			start[0] = start[1];
			chess[start[0]][start[1]] = 1;
			p->position[0] = start[0];
			p->position[1] = start[1];
			p->m = 0;
		}
	}
	

	return b; 
}



void move( nodeptr p )
{
	switch(p->prev->m)		// move the new position to its chosen place
	{
	case 0:
	case 1: p->position[0] = p->prev->position[0]+1;	// there are 8 possible moves for a knight
			  p->position[1] = p->prev->position[1]+2;
			  break;
	case 2:
	case 3: p->position[0] = p->prev->position[0]+2;
			  p->position[1] = p->prev->position[1]+1;
			  break;
	case 4:
	case 5:p->position[0] = p->prev->position[0]+2;
			  p->position[1] = p->prev->position[1]-1;
			  break;
	case 6:
	case 7: p->position[0] = p->prev->position[0]+1;
			  p->position[1] = p->prev->position[1]-2;
			  break;
	case 8:
	case 9: p->position[0] = p->prev->position[0]-1;
			  p->position[1] = p->prev->position[1]-2;
			  break;
	case 10:
	case 11: p->position[0] = p->prev->position[0]-2;
			  p->position[1] = p->prev->position[1]-1;
			  break;
	case 12:
	case 13: p->position[0] = p->prev->position[0]-2;
			  p->position[1] = p->prev->position[1]+1;
			  break;
	case 14:
	case 15:p->position[0] = p->prev->position[0]-1;
			  p->position[1] = p->prev->position[1]+2;
			  break;
	default : break;
	}
}

bool check ( int x[2] , int m )	// check the new possition's path if available
{
	int test[2];
	test[0] = x[0];
	test[1] = x[1];
	switch(m)					// there are 16 possible paths that a knight can take , if the path for the new possition is clear then return true
	{
	case 0: if ( chess[test[0]+1][test[1]] == 0 && chess[test[0]+1][test[1]+1] == 0 && chess[test[0]+1][test[1]+2] == 0 && test[0]+1 < 8 && test[1]+2 < 8 )
			{
				chess[test[0]+1][test[1]] = 1;
				chess[test[0]+1][test[1]+1] = 1;
				chess[test[0]+1][test[1]+2] = 1;
				return true;
			}
			break;

	case 1:	if ( chess[test[0]][test[1]+1] == 0 && chess[test[0]][test[1]+2] == 0 && chess[test[0]+1][test[1]+2] == 0 && test[0]+1 < 8 && test[1]+2 < 8)
			{
				chess[test[0]][test[1]+1] = 1;
				chess[test[0]][test[1]+2] = 1;
				chess[test[0]+1][test[1]+2] = 1;
				return true;
			}
			break;

	case 2: if ( chess[test[0]+1][test[1]] == 0 && chess[test[0]+2][test[1]] == 0 && chess[test[0]+2][test[1]+1] == 0 && test[0]+2 < 8 && test[1]+1 < 8)
			{
				chess[test[0]+1][test[1]] = 1;
				chess[test[0]+2][test[1]] = 1;
				chess[test[0]+2][test[1]+1] = 1;
				return true;
			}
			break;

	case 3: if ( chess[test[0]][test[1]+1] == 0 && chess[test[0]+1][test[1]+1] == 0 && chess[test[0]+2][test[1]+1] == 0 && test[0]+2 < 8 && test[1]+1 < 8)
			{
				chess[test[0]][test[1]+1] = 1;
				chess[test[0]+1][test[1]+1] = 1;
				chess[test[0]+2][test[1]+1] = 1;
				return true;
			}
			break;

	case 4: if ( chess[test[0]+1][test[1]] == 0 && chess[test[0]+2][test[1]] == 0 && chess[test[0]+2][test[1]-1] == 0 && test[0]+2 < 8 && test[1]-1 >= 0 )
			{
				chess[test[0]+1][test[1]] = 1;
				chess[test[0]+2][test[1]] = 1;
				chess[test[0]+2][test[1]-1] = 1;
				return true;
			}
			break;

	case 5: if ( chess[test[0]][test[1]-1] == 0 && chess[test[0]+1][test[1]-1] == 0 && chess[test[0]+2][test[1]-1] == 0 && test[0]+2 < 8 && test[1]-1 >= 0 )
			{
				chess[test[0]][test[1]-1] = 1;
				chess[test[0]+1][test[1]-1] = 1;
				chess[test[0]+2][test[1]-1] = 1;
				return true;
			}
			break;

	case 6: if ( chess[test[0]][test[1]-1] == 0 && chess[test[0]][test[1]-2] == 0 && chess[test[0]+1][test[1]-2] == 0 && test[0]+1 < 8 && test[1]-2 >= 0)
			{
				chess[test[0]][test[1]-1] = 1;
				chess[test[0]][test[1]-2] = 1;
				chess[test[0]+1][test[1]-2] = 1;
				return true;
			}
			break;

	case 7: if ( chess[test[0]+1][test[1]] == 0 && chess[test[0]+1][test[1]-1] == 0 && chess[test[0]+1][test[1]-2] == 0 && test[0]+1 < 8 && test[1]-2 >= 0)
			{
				chess[test[0]+1][test[1]] = 1;
				chess[test[0]+1][test[1]-1] = 1;
				chess[test[0]+1][test[1]-2] = 1;
				return true;
			}
			break;

	case 8: if ( chess[test[0]-1][test[1]] == 0 && chess[test[0]-1][test[1]-1] == 0 && chess[test[0]-1][test[1]-2] == 0 && test[0]-1 >= 0 && test[1]-2 >= 0)
			{
				chess[test[0]-1][test[1]] = 1;
				chess[test[0]-1][test[1]-1] = 1;
				chess[test[0]-1][test[1]-2] = 1;
				return true;
			}
			break;

	case 9: if ( chess[test[0]][test[1]-1] == 0 && chess[test[0]][test[1]-2] == 0 && chess[test[0]-1][test[1]-2] == 0 && test[0]-1 >= 0 && test[1]-2 >= 0)
			{
				chess[test[0]][test[1]-1] = 1;
				chess[test[0]][test[1]-2] = 1;
				chess[test[0]-1][test[1]-2] = 1;
				return true;
			}
			break;

	case 10: if ( chess[test[0]][test[1]-1] == 0 && chess[test[0]-1][test[1]-1] == 0 && chess[test[0]-2][test[1]-1] == 0 && test[0]-2 >= 0 && test[1]-1 >= 0)
			{
				chess[test[0]][test[1]-1] = 1;
				chess[test[0]-1][test[1]-1] = 1;
				chess[test[0]-2][test[1]-1] = 1;
				return true;
			}
			break;

	case 11: if ( chess[test[0]-1][test[1]] == 0 && chess[test[0]-2][test[1]] == 0 && chess[test[0]-2][test[1]-1] == 0 && test[0]-2 >= 0 && test[1]-1 >= 0)
			{
				chess[test[0]-1][test[1]] = 1;
				chess[test[0]-2][test[1]] = 1;
				chess[test[0]-2][test[1]-1] = 1;
				return true;
			}
			break;

	case 12: if ( chess[test[0]-1][test[1]] == 0 && chess[test[0]-2][test[1]] == 0 && chess[test[0]-2][test[1]+1] == 0 && test[0]-2 >= 0 && test[1]+1 < 8)
			{
				chess[test[0]-1][test[1]] = 1;
				chess[test[0]-2][test[1]] = 1;
				chess[test[0]-2][test[1]+1] = 1;
				return true;
			}
			break;

	case 13: if ( chess[test[0]][test[1]+1] == 0 && chess[test[0]-1][test[1]+1] == 0 && chess[test[0]-2][test[1]+1] == 0 && test[0]-2 >= 0 && test[1]+1 < 8)
			{
				chess[test[0]][test[1]+1] = 1;
				chess[test[0]-1][test[1]+1] = 1;
				chess[test[0]-2][test[1]+1] = 1;
				return true;
			}
			break;

	case 14: if ( chess[test[0]][test[1]+1] == 0 && chess[test[0]][test[1]+2] == 0 && chess[test[0]-1][test[1]+2] == 0 && test[0]-1 >= 0 && test[1]+2 < 8)
			{
				chess[test[0]][test[1]+1] = 1;
				chess[test[0]][test[1]+2] = 1;
				chess[test[0]-1][test[1]+2] = 1;
				return true;
			}
			break;

	case 15: if ( chess[test[0]-1][test[1]] == 0 && chess[test[0]-1][test[1]+1] == 0 && chess[test[0]-1][test[1]+2] == 0 && test[0]-1 >= 0 && test[1]+2 < 8)
			{
				chess[test[0]-1][test[1]] = 1;
				chess[test[0]-1][test[1]+1] = 1;
				chess[test[0]-1][test[1]+2] = 1;
				return true;
			}
			break;

	default: break;
	}

	return false;			// if at least 1 space of the path for the new posistion is already visited the return false
}



void unvisit ( int x[2] , int m )	// returns the visited path to unvisited
{
	int test[2];
	test[0] = x[0];
	test[1] = x[1];
	switch(m)
	{
	case 0: chess[test[0]+1][test[1]] = 0;
			chess[test[0]+1][test[1]+1] = 0;
			chess[test[0]+1][test[1]+2] = 0;
			break;

	case 1:	chess[test[0]][test[1]+1] = 0;
			chess[test[0]][test[1]+2] = 0;
			chess[test[0]+1][test[1]+2] = 0;
			break;

	case 2:	chess[test[0]+1][test[1]] = 0;
			chess[test[0]+2][test[1]] = 0;
			chess[test[0]+2][test[1]+1] = 0;
			break;

	case 3:	chess[test[0]][test[1]+1] = 0;
			chess[test[0]+1][test[1]+1] = 0;
			chess[test[0]+2][test[1]+1] = 0;
			break;

	case 4: chess[test[0]+1][test[1]] = 0;
			chess[test[0]+2][test[1]] = 0;
			chess[test[0]+2][test[1]-1] = 0;
			break;

	case 5:	chess[test[0]][test[1]-1] = 0;
			chess[test[0]+1][test[1]-1] = 0;
			chess[test[0]+2][test[1]-1] = 0;
			break;

	case 6:	chess[test[0]][test[1]-1] = 0;
			chess[test[0]][test[1]-2] = 0;
			chess[test[0]+1][test[1]-2] = 0;
			break;

	case 7: chess[test[0]+1][test[1]] = 0;
			chess[test[0]+1][test[1]-1] = 0;
			chess[test[0]+1][test[1]-2] = 0;
			break;

	case 8: chess[test[0]-1][test[1]] = 0;
			chess[test[0]-1][test[1]-1] = 0;
			chess[test[0]-1][test[1]-2] = 0;
			break;

	case 9: chess[test[0]][test[1]-1] = 0;
			chess[test[0]][test[1]-2] = 0;
			chess[test[0]-1][test[1]-2] = 0;
			break;

	case 10: chess[test[0]][test[1]-1] = 0;
			 chess[test[0]-1][test[1]-1] = 0;
			 chess[test[0]-2][test[1]-1] = 0;
			break;

	case 11: chess[test[0]-1][test[1]] = 0;
			 chess[test[0]-2][test[1]] = 0;
			 chess[test[0]-2][test[1]-1] = 0;
			break;

	case 12: chess[test[0]-1][test[1]] = 0;
			 chess[test[0]-2][test[1]] = 0;
			 chess[test[0]-2][test[1]+1] = 0;
			break;

	case 13: chess[test[0]][test[1]+1] = 0;
			 chess[test[0]-1][test[1]+1] = 0;
			 chess[test[0]-2][test[1]+1] = 0;
			break;

	case 14: chess[test[0]][test[1]+1] = 0;
			 chess[test[0]][test[1]+2] = 0;
			 chess[test[0]-1][test[1]+2] = 0;
			break;

	case 15: chess[test[0]-1][test[1]] = 0;
			 chess[test[0]-1][test[1]+1] = 0;
			 chess[test[0]-1][test[1]+2] = 0;
			break;

	default: break;
	}

}

bool full()				// checks if the all the spaces on the chess board is visited or not
{
	for( int i =0 ; i < 8 ; i++ )
		for ( int j = 0 ; j < 8 ; j++ )
			if ( chess[i][j] == 0 )
				return false;

	return true;
}


void makepath( nodeptr p )		// prints each move of the knight and the spaces it covers while moving 
{
	int counter = 0;

	chess[p->position[0]][p->position[1]] = 1;

	cout << "the program takes the top left as the 1,1 position.\n'0' means not yet covered and '1' means already covered\n\n";

	while ( !full() )
	{
		cout << "Move number " << counter << ":  \n\n";

		for ( int i = 0 ; i < 8 ; i++ )
		{
			for ( int j = 0 ; j < 8 ; j++ )
			{
				cout << chess[i][j] << "    ";
			}
			cout << "\n";
		}
		check( p->position , p->m );
		p = p->next;
		counter++;
		cout << "\n \n";
	}

	cout << "Move numer " << counter << ":\n\n";
	for ( int i = 0 ; i < 8 ; i++ )
	{
		for ( int j = 0 ; j < 8 ; j++ )
		{
			cout << chess[i][j] << "    ";
		}
		cout << "\n";
	}

}