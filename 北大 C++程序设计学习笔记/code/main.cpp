#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef struct TNode* BinaryTree;

struct TNode
{
    int data;
    TNode* left;
    TNode* right;
};

//层序生成算法
int CreateBinaryTree(BinaryTree &BT)
{
    queue<TNode*> q;
    int data;
    TNode* tnode = NULL;
    cin >> data;
    if(data == 0) return 0;
    else {
        BT = tnode = new TNode();
        tnode->data = data;
        tnode->left = NULL;
        tnode->right = NULL;
        q.push(tnode);
    }

    while(!q.empty())
    {
        tnode = q.front();
        q.pop();

        cin >> data;
        if(data == 0)
        {
            tnode->left = NULL;
        }
        else {
            tnode->left = new TNode();
            tnode->left->data = data;
            tnode->left->left = tnode->left->right = NULL;
            q.push(tnode->left);
        }

        cin >> data;
        if(data == 0)
        {
            tnode->right = NULL;
        }
        else {
            tnode->right = new TNode();
            tnode->right->data = data;
            tnode->right->left = tnode->right->right = NULL;
            q.push(tnode->right);
        }
    }
    return 0;
}

//先序
int PreOder(BinaryTree BT)
{
    BinaryTree T = BT;
    if(T) {
        cout<<T->data<<endl;
        PreOder(T->left);
        PreOder(T->right);
    }
    return 0;
}

// 非递归方法中序（先序可简单修改实现；后序需要二次入栈，然后从该节点的右子树继续深入，与前面类同，
// 仍为进入一个节点入栈一个节点，深入不下去再返回，直到第二次从栈中弹出该节点，才访问之）
int InorderTravesal(BinaryTree BT)
{
    BinaryTree T = BT;
    stack<BinaryTree> st;
    while(T!=NULL || !st.empty()) //注意是或，不是与！！
    {
        while(T!=NULL) //一直向左并将沿途结点压入堆栈
        {
            st.push(T);
            T = T->left;
        }
        T = st.top(); //结点弹出堆栈
        cout << T->data << endl; //访问结点
        st.pop();
        T = T->right;
    }
    return 0;
}


//层序遍历
int LevelorderTraversal(BinaryTree BT)
{
    BinaryTree T;
    queue<BinaryTree> q;
    q.push(BT);
    while(!q.empty())
    {
        T = q.front();
        cout << T->data << endl;
        q.pop();
        if(T->left != NULL) q.push(T->left);
        if(T->right != NULL) q.push(T->right);
    }
    return 0;
}


int main()
{
    BinaryTree BT = NULL;
    CreateBinaryTree(BT);
    PreOder(BT);
    InorderTravesal(BT);
    LevelorderTraversal(BT);
    return 0;
}






//int main() {
//    vector<int> v;
//    for (int i = 0; i < 10; i++) {
//        v.push_back(i);
//    }
//    v.clear();
//    cout << "vector size: " << v.size() << endl;
//    cout << "vector capacity: " << v.capacity() << endl;
//
////    cout << "vector size: " << v.size() << endl;
////    vector<int>::iterator it = v.begin();
////    for (; it != v.end(); it++) {
////        v.erase(it);
////    }
//
//    vector <int>().swap(v);
//
//    cout << "vector size: " << v.size() << endl;
//    cout << "vector capacity: " << v.capacity() << endl;
//}
