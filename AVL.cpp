

// AVL.cpp : Defines the entry point for the console application.


#include<iostream>
#include<stdlib.h>  // For exit function
#include<queue>     // For level order traversal for printing
#include<stack>     // Used in deletion 
#include <sstream> 
#include <fstream>  // For File handling

using namespace std;

class AVL_Node
{
      private:
              int key;

              int bf; // balance factor bf = height(left subtree) – height(right subtree)

              AVL_Node *LChild, *RChild;

              friend class AVL_Tree;
};

class AVL_Tree
{
      private:
		      AVL_Node *root;
              
      public:
              AVL_Tree(); // Constructor for initilisation

              AVL_Tree(const AVL_Tree &T);

              AVL_Tree &operator=(const AVL_Tree &T);

              void AVL_Insert(int k);               // For Inserting element in AVL Tree

              void AVL_Delete(int k);               // For Deleting element in AVL Tree

              bool AVL_Search(int k);               // For Searching element in AVL Tree

              void AVL_Print(const char *filename); // Generate DOT file for Visualisation

			  void levelorder_newline();            // Utility Function to print Level-Order traversal
			  
			  AVL_Node* link(int a, AVL_Node *s);

              ~AVL_Tree();                          // Destructor for reclaiming memory

			  void DestroyRecursive(AVL_Node *node); // Utility function for Recursively destroying each node of AVL Tree
};


AVL_Tree::AVL_Tree() // Constructor for initilisation
{
	this->root = NULL;
}

void AVL_Tree::DestroyRecursive(AVL_Node *node)// Utility function for Recursively destroying each node of AVL Tree
{
    if (node)
    {
        DestroyRecursive(node->LChild);
        DestroyRecursive(node->RChild);
        delete node;
    }
}

AVL_Tree::~AVL_Tree() // Destructor for reclaiming memory
{
    DestroyRecursive(root);
}

void AVL_Tree:: AVL_Insert(int k)
{
	//If root doesn't exist, create it.
	if(this->root==NULL)
	{
           
		    AVL_Node *n;
            n = new AVL_Node();
            n->key = k;

			this->root=n;

			this->root->LChild = this->root->RChild = NULL;
			this->root->bf=0;

            return;             
     }

	//If root exist
	else
	{
		AVL_Node *t; // This pointer keep track of header node

		AVL_Node *p; // This pointer will move down the tree

		AVL_Node *s; // This pointer points to node where rebalancing might happen

		AVL_Node *q; // Pointer for insertion of new node

		AVL_Node *r; // Utility pointer

		AVL_Node *head=new AVL_Node(); // header node

		head->RChild=this->root;
		//head->LChild=height();

		t=head;
		p=s=head->RChild;

		
		
		//Searching for position to insert key
        while(1)
		{
		        if(p->key==k)//Key already present
		        {
			            cout<<"Duplicate node"<<endl;
			            return;
		        }

		        else if(p->key>k)// Search left subtree for position to insert
		        {
			
         	          q=p->LChild;

			          if(q==NULL)// Position found
			          {
						   q=new AVL_Node();
				           p->LChild=q;
				           break;
			          }

			           else if(q->bf != 0)// Position NOT found
			          {
				           t=p;
				           s=q;
				           
			           }
					  p=q;//Return to p->key check
		         }

		         else if(p->key<k)// Search right subtree for position to insert
		         {
			            q=p->RChild;

			            if(q==NULL)// Position found
			            {
							 q=new AVL_Node();
				             p->RChild=q;
				             break;
			            }

			           else if(q->bf != 0)// Position NOT found
			            {
				             t=p;
				             s=q;
				             
			            }

			           p=q;//Return to p->key check
		
		          }

		}
		
		//Assign suitable values to newly inserted node
		q->key=k;
		q->LChild=q->RChild=NULL;
		q->bf=0;
		


		//Now we balance and update balance factor

		int a;

		r=new AVL_Node();

		if(k<s->key)
		{
			     a=1; // Inserted node gone to Left subtree
		}
		else
		{
			     a=-1; // Inserted node gone to Right subtree
		}



	    if(a==1)
		{
				 r=p=s->LChild;
		}

		if(a==-1)
		{
			     r=p=s->RChild;
		}

		while(p != q)
		{
			if(k<p->key)
			{
				p->bf=1;
				p=p->LChild;
			}
			else if(k>p->key)
			{
				p->bf=-1;
				p=p->RChild;
			}

			else
				p=q;
		}

		int rotcount; // Variable to Identify type of rotation, Single or double

		if(s->bf==0) // Rotation NOT necessary
		{
			s->bf=a;

			//head->LChild+=1;

		    return;
		}

		else if(s->bf==-a)// Rotation NOT necessary as Tree is more balanced
		{
			s->bf=0;
			return;
		}

		else if(s->bf==a) // Rotation necessary
		{
			if(r->bf==a)
				rotcount=1; // Single rotation

			else if(r->bf==-a)
				rotcount=2; // Double rotation
		}


		if(rotcount==1) // Rotate LL or RR
		{
			p=r;

			// Rotation step
			if(a==1)
			{
				s->LChild=r->RChild;
			    r->RChild=s;
			}

			else if(a==-1)
			{
				s->RChild=r->LChild;
			    r->LChild=s;
			}

			// Reassign balance factor
			s->bf=r->bf=0;

		}

		else if(rotcount==2)// Rotate LR or RL
		{
			// Rotation step
			if(a==1)
			{
				p=r->RChild;
				r->RChild=p->LChild;
				p->LChild=r;
				s->LChild=p->RChild;
				p->RChild=s;
			}

			else if(a==-1)
			{
				p=r->LChild;
				r->LChild=p->RChild;
				p->RChild=r;
				s->RChild=p->LChild;
				p->LChild=s;
			}

			// Reassign balance factor after rotation
			if(p->bf==a)
			{
				s->bf=-a;
			    r->bf=0;
			}

			else if(p->bf==0)
			{
				s->bf=0;
			    r->bf=0;
			}

			else if(p->bf==-a)
			{
				s->bf=0;
				r->bf=a;
			}


			p->bf=0;
		
		}

		// IF rotation involves root then change RChild of root
		if(s==t->RChild)
			t->RChild=p;

		else
			t->LChild=p;

		// Reassign tree root
		this->root=head->RChild;
	}

	
	return;
}

AVL_Node* AVL_Tree :: link(int a, AVL_Node *s)
{
	return a == 1 ? s->LChild : s->RChild; 
}


void AVL_Tree :: AVL_Delete(int k)
{

	AVL_Node *head=new AVL_Node();
	head->RChild=this->root;

	AVL_Node *p = head->RChild; // pointer pointing to root of tree, eventually will point to k
	
	
	AVL_Node *s; // s -> AVL_Node to be balanced
	AVL_Node *t; // t -> parent of the AVL_Node to be balanced
	AVL_Node *r; // r -> left/right child of the AVL_Node to be balanced


	bool found = false;

	stack<AVL_Node*> path; // saves the path to the AVL_Node
	path.push(head); 

	if(p == NULL) throw "No element exists to be deleted";

	while(p)
	{
		if(k < p->key)
		{
			path.push(p);
			p = p->LChild;
		}
		else if(k > p->key)
		{
			path.push(p);
			p = p->RChild;
		}
		else
		{
			found = true;
			break;
		}

	}

	if(!found) throw "Element to be deleted does not exist";

	else
	{
		// If p has a single child or no child (leaf)
		if(!p->LChild || !p->RChild)
		{
			AVL_Node *temp = p->LChild ? p->LChild : p->RChild;
			AVL_Node *par = path.top();

			if(!temp)
			{
				temp = p;
				if(p == par->LChild)
					par->LChild = NULL;
				else par->RChild = NULL;
				p = NULL;
			}
			else
			{
				p->key = temp->key;
				p->bf = temp->bf;
				p->LChild = temp->LChild;
				p->RChild = temp->RChild;
			}
			delete temp;

		}

		// AVL_Node to be deleted has both the children
		else
		{
			path.push(p);
			AVL_Node *succ = p->RChild; //finding the successor of p
			while(succ->LChild)
			{
				path.push(succ);
			 	succ = succ->LChild;

			}

			p->key = succ->key;

			k = succ->key; // because the AVL_Node that is being deleted is the successor

			AVL_Node *temp = succ->LChild ? succ->LChild : succ->RChild;

			AVL_Node *par = path.top();

			if(!temp)
			{
				temp = succ;
				if(succ == par->LChild)
					par->LChild = NULL;
				else par->RChild = NULL;
				succ = NULL;
			}

			else
			{
				succ->key = temp->key;
				succ->bf = temp->bf;
				succ->LChild = temp->LChild;
				succ->RChild = temp->RChild;
			}

			delete temp;
		}
	}


	

	while(path.top() != head)
	{
		s = path.top();
		int a = k < s->key ? 1 : -1;
		path.pop();
		t = path.top();

		if(s->bf == a)
		{
			s->bf = 0;
			continue;
		}

		else if(s->bf == 0)
		{
			s->bf = -1*a;
			return;
		}

		else
		{
			r = link(s->bf, s);

			//single rotation
			if(r->bf == -1*a)
			{
				if(a == -1)
				{
					p = r;
					s->LChild = r->RChild;
					r->RChild = s;
					s->bf = 0;
					r->bf = 0; 
				}

				else if(a == 1)
				{
					p = r;
					s->RChild = r->LChild;
					r->LChild = s;
					s->bf = 0;
					r->bf = 0;
				}

			}

			//single rotation
			else if(r->bf == 0)
			{
				if(a == -1)
				{
					p = r;
					s->LChild = r->RChild;
					r->RChild = s;
					r->bf = a; 
				}
				else if(a == 1)
				{
					p = r;
					s->RChild = r->LChild;
					r->LChild = s;
					r->bf = a;
				}

			}

			//double rotation
			else if(r->bf == a)
			{
				if(a == -1)
				{
					p = r->RChild;
					r->RChild = p->LChild;
					p->LChild = r;
					s->LChild = p->RChild;
					p->RChild = s;
					s->bf = p->bf == 0 ? 0 : p->bf == 1 ? -1 : 0;
					r->bf = p->bf == 0 ? 0 : p->bf == 1 ? 0 : 1;
					p->bf = 0;
				}

				else if(a == 1)
				{
					p = r->LChild;
					r->LChild = p->RChild;
					p->RChild = r;
					s->RChild = p->LChild;
					p->LChild = s;
					s->bf = p->bf == 0 ? 0 : p->bf == 1 ? 0 : 1;
					r->bf = p->bf == 0 ? 0 : p->bf == 1 ? -1 : 0;
					p->bf = 0;
				}
			}
		}

		if(s == t->RChild) 
			t->RChild = p;

		else 
			t->LChild = p;		

		// Reassign tree root
		this->root=head->RChild;
	}

	
}




bool AVL_Tree::AVL_Search(int k)
{
	if(this->root == NULL) // tree empty
		return false;

	else
	{
		AVL_Node *ptr=new AVL_Node();

		ptr=this->root; // ptr points to root of tree

		while(ptr)
		{
			if(ptr->key==k)     // Key Found
				return true;

			else if(ptr->key>k) // Key check in left subtree
				ptr=ptr->LChild;

			else                // Key check in right subtree
				ptr=ptr->RChild;
		}

		return false;           // Key NOT Found
	}
}



void AVL_Tree :: AVL_Print(const char *filename)
{

	// Creating/Opening .gv file
	ofstream MyFile("myfile.gv");

	// Write to the file
    MyFile << "digraph G{\n";
	MyFile << "node [shape = record, height = .1];";


	queue <AVL_Node *> q; // Queue for level order traversal

        AVL_Node *cur;

        q.push(this->root); // Enqueue root
        q.push(NULL);

		
        while(!q.empty())
		{
			cur = q.front();
           
            q.pop();

            if(cur == NULL && q.size()!=0)
			{
                
                q.push(NULL);

                continue;
            }

            if(cur!=NULL)
			{
               
                if (cur->LChild!=NULL)
				{
					 MyFile << "node" << cur->key << " [label = \"<f0> | <f1> " << cur->key << " | <f2> " << cur->bf << " | <f3>\"];\n"; // Inserting link in gv file if Left Child present

					 MyFile << "node" << cur->LChild->key << " [label = \"<f0> | <f1> " << cur->LChild->key << " | <f2> " << cur->LChild->bf << " | <f3>\"];\n";
    	             MyFile << "\"node" << cur->key << "\":f0 -> \"node" << cur->LChild->key << "\":f1;\n";

                     q.push(cur->LChild);// Enqueue Left Child if present
                }

                if (cur->RChild!=NULL)
				{
					 MyFile << "node" << cur->key << " [label = \"<f0> | <f1> " << cur->key << " | <f2> " << cur->bf << " | <f3>\"];\n"; // Inserting link in gv file if Left Child present

					 MyFile << "node" << cur->RChild->key << " [label = \"<f0> | <f1> " << cur->RChild->key << " | <f2> " << cur->RChild->bf << " | <f3>\"];\n";
    	             MyFile << "\"node" << cur->key << "\":f3 -> \"node" << cur->RChild->key << "\":f1;\n";

                     q.push(cur->RChild);// Enqueue Right Child if present
                }
            }
            
            
        }

		cout<<endl;


	MyFile << "}";

	// Close the file
    MyFile.close();
}

void AVL_Tree :: levelorder_newline() // Utility function for level order traversal
{
      queue <AVL_Node *> q;

        AVL_Node *cur=new AVL_Node();

        q.push(this->root);
        q.push(NULL);
		
        while(!q.empty())
		{
			cur = q.front();

            q.pop();

            if(cur == NULL && q.size()!=0)
			{
                cout<<"\n";
                
                q.push(NULL);

                continue;
            }

            if(cur!=NULL)
			{
                cout<<" "<<cur->key;

                if (cur->LChild!=NULL)
				{
					 
                     q.push(cur->LChild);
                }

                if (cur->RChild!=NULL)
				{
			
                     q.push(cur->RChild);
                }
            }
            
            
        }

		cout<<endl;  

		
}


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


