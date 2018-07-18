#include "redblacktree.h"
#include <iostream>

using namespace std;

int main()
{
    int choice, y = 0;
    RedBlackTree rbtree;
//    for (int i = 1; i < 16; ++i)
//    {
//        rbtree.Insert(i, i);
//    }

    rbtree.Insert(4,4);
    rbtree.Insert(10,10);
    rbtree.Insert(3,3);
    rbtree.Insert(5,5);
    rbtree.Insert(15,15);


//    rbtree.Delete(9);
//    rbtree.Delete(8);
    rbtree.Display();

//    do{
//        cout << "\n\t ---- RED BLACK TREE - MAIN MENU ---- ";
//        cout << "\n 1: Insert new node in the tree ";
//        cout << "\n 2: Delete a node";
//        cout << "\n 3: Search for an element";
//        cout << "\n 4: Print the tree ";
//        cout << "\n 5: Quit ";
//        cout << "\nEnter Your Choice: ";
//        cin >> choice;
//        switch (choice)
//        {
//            int val;
//            case 1: cout << "Type the number to insert: ";
//                cin >> choice;
//                rbtree.Insert(val, val);
//                //break;
//            case 2: cout << "Type the number to be deleted: ";
//                cin >> choice;
//                rbtree.Delete(choice);
//                //break;
//            case 3: cout << "Type the number to search for: ";
//                cin >> choice;
//                rbtree.Search(choice);
//                //break;
//            case 4: rbtree.Display();
//                //break;
//            case 5: y = 1;
//                break;
//            default: cout << "\nIncorrect Choice - Enter a Valid Choice.";
//        }
//        cout << endl;
//
//    } while (y != 1);

    return 1;
}
