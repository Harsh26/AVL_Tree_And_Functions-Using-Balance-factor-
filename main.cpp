#include<iostream>
#include<stdlib.h>  // For exit function
#include<queue>     // For level order traversal for printing
#include<stack>     // Used in deletion 
#include "helper.h"
#include <sstream> 
#include <fstream>  // For File handling

using namespace std;

int main()
{
    AVL_Tree tree;

	int choice, X;


	while(1)
	 {
		 cout<<"\n\n\n******MENU DRIVEN MODE******\n\n\n";
		 cout<<"1. Insertion\n\n2. Deletion\n\n3. Search\n\n4. Printing in File\n\n5. Level order traversal(Extra function to verify result)\n\n6. Exit";
		 cout<<"\n\n\n";

		 cout<<"Input Your Choice of Operation:";
		 cin>>choice;

		 switch(choice)
		 {
             case 1:
				    {
						cout<<"Enter Element to insert:";
					    cin>>X;

					    tree.AVL_Insert(X); // Insert element with data X in AVL tree
					}
                    break;

			 case 2:
				    {
						cout<<"Enter Element to delete:";
					    cin>>X;

					    tree.AVL_Delete(X); // Deletes element with data X in AVL tree
					}
                    break;

			 case 3:
				    {
						cout<<"Enter Element to search:";
					    cin>>X;

				        bool res=tree.AVL_Search(X); // Search for element with data X in AVL tree

	                     if(res==true)
		                     cout<<"Element Found!!!"<<endl;

	                     else
		                     cout<<"Element NOT Found"<<endl;
					}
				    
					break;

			 case 4:
				    {
						char filename[20]="myfile";
	                    tree.AVL_Print(filename); // Print tree in DOT File

						cout<<"SUCCESS in creating file Check your directory..."<<endl;

					}

	 			    break;

			 

			 case 5: // Extra function to verify result
				   {
					   cout<<"Level-Order Traversal of tree=\n";
				       tree.levelorder_newline(); // Prints Level order traversal of tree
					   cout<<endl;
					   break;
				   }
             
    
			 case 6:
				   exit(0); // exits Menu Driven Mode
    

			 default:
				  cout<<"Invalid Choice....\n\n";
				  break;

	      }
	}

	return 0;
}