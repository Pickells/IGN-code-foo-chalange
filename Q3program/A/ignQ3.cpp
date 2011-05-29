//////////////////////////////////////////////////////////////////////////////////////////////////////
//// THIS PROGRAM IS MADE BY ABDULLAH ALHASAN FROM KUWAIT FOR QUESTION 3 OF IGN JOB AD            ////
//// THIS PROGRAM PRINTS THE MINNIMUM PATH OF A KNIGHT IN A CHESS BOARD TO COVER ALL THE SPACES   ////
//// AND THE MINNIMUM POSSIBLE MOVES FOR ANY PIECE IS 63 MOVES SINCE THE STARTING POINT DOES NOT  ////
//// COUNT AS A MOVE SO IF THERE IS A PATH FOR A KNOGHT WITH 63 MOVES TO COVER ALL THE CHESS BOARD////
//// THEN THAT PATH IS THE MINNIMUM PATH. THIS PROGRAM MAY TAKE A FEW SECONDS TO PRINT THE RESULT ////
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>		// for cout
#include <cstddef>		// for NULL

using namespace std;


int start[2];			//this is the starting point of the knight
int count = 0;			// couts each move to determin the minnimum possibility
int chess[8][8];        // to know which space is visited and which are still available


struct node				// the structure of the nodes in the liked list for the path
{
	node* prev ;		// points to the previos node
	int m ;				// the knight has 8 possible kinds of moves. this determines what kind of move it will take
	int position[2];	// the posistion of the node
	node* next;			// points to the next node
};
typedef node* nodeptr;


bool path ( nodeptr p );// this function creats the path that the knight will take
void move( nodeptr p );	// moves the current node to its new place
bool check ( int x[2] , int m );// checks the new place if it isn't out of bound of the chess board or not yet visited

int main ()
{
	int counter = 0;

	nodeptr currptr;
	start[0] = 0;		// initializing start
	start[1] = 0;

	for ( int i=0 ; i < 8 ; i++ )// initializing the chess board to set it all to 0 which means not visited
		for ( int j=0; j<8 ; j++ )
			chess[i][j] = 0;

	cout << "There are 64 sapces on a chess board, if the knight start on one then he needs to cover 63 spaces.\n";
	cout << "if for every move the knight makes he will step on a new space then the minnimum moves are 63.\n\n";

	currptr = new node;	// creating the first node
	currptr->m = 0;		//setting the kind of move to the first one
	currptr->next = NULL;//this is the first node so there is no next nor prev
	currptr->prev = NULL;
	currptr->position[0] = 0;//the starting position is going to be 0,0
	currptr->position[1] = 0;

	chess[start[0]][start[1]] = 1;// setting the starting possition to 1 which means that this space is visited

	if ( path( currptr ) )//check if there is a path with 63 moves
	{
		cout << "the path for a knight to cover all the chess board starts at \n";
		cout << currptr->position[0] << "," << currptr->position[1] << "->";// prints the moves that the program selected
		currptr = currptr->next;
		while ( currptr->next != NULL )
		{
			cout << currptr->position[0] << "," << currptr->position[1] << "->";
			currptr = currptr->next;
		}
		cout << currptr->position[0] << "," << currptr->position[1];
		cout << "\nsince the knight steps on each space once ";
		cout << "\nthen this is the minnimum possiblity with 63 moves \n\n";
	}
	else 
		cout << " no path for 63 step " ;// there was no path that covers the chess board with 63 moves


	while( currptr->prev != NULL )
		currptr = currptr->prev;

	for( i=0; i<8 ; i++)
		for ( int j =0; j < 8 ; j++ )
			chess[i][j] = 0;

	cout << "Starts at 0 and ends at 63: \n\n";

	while ( currptr->next != NULL )
	{
		counter++;
		currptr = currptr->next;
		chess[currptr->position[0]][currptr->position[1]] = counter;
	}

	

	for ( i = 0 ; i < 8 ; i++ )
	{
		for ( int j = 0 ; j < 8 ; j++ )
		{
			cout << chess[i][j] << "   ";
		}
		cout << "\n\n";
	}



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
				for ( ;p->m < 8 && b == false; p->m++) // if the the program didn't check all this positions possible moves and the path has not been found yet do this 
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
		
						if ( count == 63 )  // if we have 63 moves then we have a full path for the knight
							b = true;		// we found a path
	
					}
				
		
				}

				if ( b == false )	// if we haven't found a path yet do this 
				{
					chess[p->position[0]][p->position[1]] = 0;	// make this position not visited again
					temp = p;		// move to the previos node and delete the node the we just left 
					p = p->prev;
					delete temp;
					p->next = NULL;
					p->m++;			// increas m by 1 to not check the same place again
					count--;		// because we returnd we need to decreas the move counter by 1
				}
			} while ( p->prev != NULL && b == false );	// (this is for the do()while) this checks that this is not the first node so we dont delete it


			if ( b == false )
			{
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
	case 0: p->position[0] = p->prev->position[0]+1;	// from 0 to 7 are the possible moves for a knight
			  p->position[1] = p->prev->position[1]+2;
			  break;
	case 1: p->position[0] = p->prev->position[0]+2;
			  p->position[1] = p->prev->position[1]+1;
			  break;
	case 2: p->position[0] = p->prev->position[0]+2;
			  p->position[1] = p->prev->position[1]-1;
			  break;
	case 3: p->position[0] = p->prev->position[0]+1;
			  p->position[1] = p->prev->position[1]-2;
			  break;
	case 4: p->position[0] = p->prev->position[0]-1;
			  p->position[1] = p->prev->position[1]-2;
			  break;
	case 5: p->position[0] = p->prev->position[0]-2;
			  p->position[1] = p->prev->position[1]-1;
			  break;
	case 6: p->position[0] = p->prev->position[0]-2;
			  p->position[1] = p->prev->position[1]+1;
			  break;
	case 7: p->position[0] = p->prev->position[0]-1;
			  p->position[1] = p->prev->position[1]+2;
			  break;
	default : break;
	}
}

bool check ( int x[2] , int m )	// check the new possition if available
{
	int test[2];
	test[0] = x[0];
	test[1] = x[1];
	switch(m)
	{
	case 0: test[0] = test[0]+1;
			  test[1] = test[1]+2;
			  break;
	case 1: test[0] = test[0]+2;
			  test[1] = test[1]+1;
			  break;
	case 2: test[0] = test[0]+2;
			  test[1] = test[1]-1;
			  break;
	case 3: test[0] = test[0]+1;
			  test[1] = test[1]-2;
			  break;
	case 4: test[0] = test[0]-1;
			  test[1] = test[1]-2;
			  break;
	case 5: test[0] = test[0]-2;
			  test[1] = test[1]-1;
			  break;
	case 6: test[0] = test[0]-2;
			  test[1] = test[1]+1;
			  break;
	case 7: test[0] = test[0]-1;
			  test[1] = test[1]+2;
			  break;
	default: break;
	}

	if ( chess[test[0]][test[1]] == 1 || test[0] < 0 || test[1] < 0 || test[0] > 7 || test[1] > 7 )	// if the new place is visited or out of bound of the chess baord then
		return false; // don't move to this place
	chess[test[0]][test[1]] = 1;	// if not then put this place as visited and move to this place
	return true;
}