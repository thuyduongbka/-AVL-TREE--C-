#include <bits/stdc++.h>

using namespace std;


struct Node{
    string key;
    string mean;
    int height;  // chieucao
    Node * left;
    Node * right;
    };
typedef Node*AVLtree;

int cal_height(AVLtree T)
{
    if (T == NULL) return 0;
    return T->height;
}
int getBalance(AVLtree T)
{
    return cal_height(T->left)-cal_height(T->right);
}
Node * rightRotate(AVLtree & k1)
{
    Node * k2 = k1->left;
    Node * B  = k2->right;

    k2->right = k1;
    k1->left  = B;

    k1->height= max(cal_height(k1->left),cal_height(k1->right))+1;
    k2->height= max(cal_height(k2->left),cal_height(k2->right))+1;

    return k2;
}
Node * leftRotate(AVLtree & k2)
{
    Node * k1 = k2->right;
    Node * B  = k1->left;

    k1->left = k2;
    k2->right= B;

    k1->height= max(cal_height(k1->left),cal_height(k1->right))+1;
    k2->height= max(cal_height(k2->left),cal_height(k2->right))+1;

    return k1;
}
Node * insertNode(AVLtree & T, string id, string s2)
{
    if (T == NULL )
    {
        T = new Node;
        T->key = id;
        T->mean = s2;
        T->height=1;
        T->left=T->right=NULL;
    }
    else
    {
        if ( id < T->key )
            T->left = insertNode(T->left,id,s2);
        else
            T->right= insertNode(T->right,id,s2);
    }
    int balance = getBalance(T);
    if (balance >  1 && id < T->left->key )
        return rightRotate(T);
    if (balance < -1 && id > T->right->key )
        return leftRotate(T);
    if (balance >  1 && id > T->left->key )
    {
        T->left = leftRotate(T->left);
        return rightRotate(T);
    }
    if (balance < -1 && id < T->right->key )
    {
        T->right = rightRotate(T->right);
        return leftRotate(T);
    }
    T->height= max(cal_height(T->left),cal_height(T->right))+1;
    return T;
}
string searchAVL(AVLtree T, string s)
{
    if (T == NULL) return "0";
    if (T->key == s) return T->mean;
    else
    {
        if (s < T->key ) return searchAVL(T->left,s);
        else return searchAVL(T->right,s);
    }
}
void NLR(AVLtree  T)
{
    if (T != NULL)
    {
        cout << T->key << "  height: " << T->height <<endl;
        NLR(T->left);
        NLR(T->right);
    }
}
int main()
{
    AVLtree T;
    T = NULL;
/*---------------------------------------------------------------------*/

        fstream f; f.open("input.txt", ios::in);
        string s,s1,s2;
        while (!f.eof()){
            getline(f, s);
            int found = s.find(":");
            s1= s.substr(0,found);
            s2= s.substr(found+1,s.size());
            T= insertNode(T,s1,s2);
        } f.close();

/*---------------------------------------------------------------------*/
    while (true) {
     cout << "  Nhap tu can tim : ";
     getline(cin,s);
     s2="";
     for (int i=0; i< s.size(); i++)
     {
         char c=s[i];
         c= tolower(c);
         s2=s2+c;
     }
     s=s2;
     s1= searchAVL(T,s);
     cout << endl << endl;
     if (s1 == "0") cout << "  Khong co trong tu dien ! " << endl<< endl;
     else {
     cout << "  Nghia cua tu la: " << s1;
     cout << endl << endl;
     break;}
    }

    return 0;
}

