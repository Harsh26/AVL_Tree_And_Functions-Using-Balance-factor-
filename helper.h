
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
