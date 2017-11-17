#include <iostream>
#include <queue>
#include <stack>
using namespace std;
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
    bool ltag;
    bool rtag;
}btreenode;
typedef btreenode * btree;
struct node1
{
    btree p;
    int flag;
};
btree pre = NULL;
btree head = new btreenode;
int num, step_0 = 0, step_1 = 0;
btree create_0(bool level) {
    if(!level)
        freopen("test.txt", "r", stdin);                       // 以先序遍历创立二叉树
    btree t;
    char c;
    scanf("%c",&c);
    if (c == '#') t = NULL;
    else {
        t = (btreenode *) malloc(sizeof(btreenode));
        t->data = c;
        t->lchild = create_0(1);
        t->rchild = create_0(1);
    }
    if(!level)
        fclose(stdin);
    return t;
}
btree create_1() {
    freopen("test1.txt", "r", stdin);                          //ab#d##c#e##
    int i, j;                                                  //线性表创建二叉树
    char ch;
    btree s[50], root, p;

    cin >> i >> ch;
    while(i != 0)
    {
        p = new btreenode;
        p->data = ch;
        p->lchild = NULL;
        p->rchild = NULL;

        s[i] = p;
        if (i == 1) root = p;
        else
        {
            j = i / 2;
            if(i % 2 == 0) s[j]->lchild = p;
            else s[j]->rchild = p;
        }
        cin >> i >> ch;
    }
    fclose(stdin);
    return root;
}
void print_btree(btree root) {                          //打印二叉树
    if(root == NULL)
        return;
    queue<btree> nodes;
    nodes.push(root);
    int nextlevel = 0;   //下一行节点数
    int need_print = 1;//待打印的节点数
    int i = 13, j, k = 6;
    while (!nodes.empty())
    {
        btree node = nodes.front();
        if(node->lchild)
        {
            nodes.push(node->lchild);
            nextlevel++;
        }
        if(node->rchild)
        {
            nodes.push(node->rchild);
            nextlevel++;
        }
        for(j = 0; j<= i; j++)
            printf(" ");
        printf("%c", nodes.front()->data);
        for(j = 0; j <= k; j++)
            printf(" ");
        nodes.pop();
        --need_print;
        if(need_print == 0)     //当前行节点打印完毕
        {
            printf("\n");
            need_print = nextlevel;
            nextlevel = 0;
            i -= 5;
            k -= 1;
        }
    }
}
int total_num(btree root) {                                    //统计树的总节点数
    if(root == NULL) return 0;
    else return 1 + total_num(root->lchild) + total_num(root->rchild);
}
void level_order(btree root) {                                 //层序遍历
    if(root == NULL)
        return;
    queue<btree> nodes;
    nodes.push(root);
    int nextlevel = 0;   //下一行节点数
    int need_print = 1;  //待打印的节点数
    while (!nodes.empty())
    {
        btree node = nodes.front();
        if(node->lchild)
        {
            nodes.push(node->lchild);
            nextlevel++;
        }
        if(node->rchild)
        {
            nodes.push(node->rchild);
            nextlevel++;
        }
        printf("%c ", nodes.front()->data);
        nodes.pop();
        --need_print;
        if(need_print == 0)     //当前行节点打印完毕
        {
            //printf("\n");
            need_print = nextlevel;
            nextlevel = 0;
        }
    }
    printf("\n");
}
void preorder_recursive(btree root) {                        //递归先序遍历
    if(root != NULL)
    {
        printf("%c ", root->data);
        preorder_recursive(root->lchild);
        preorder_recursive(root->rchild);
    }
}
void inorder_recursive(btree root) {                         //递归中序遍历
    if(root != NULL)
    {
        inorder_recursive(root->lchild);
        printf("%c ", root->data);
        inorder_recursive(root->rchild);
    }
}
void postorder_recursive(btree root) {                         //递归后序遍历
    if(root != NULL)
    {
        postorder_recursive(root->lchild);
        postorder_recursive(root->rchild);
        printf("%c ", root->data);
    }
}
void preorder_not_recursive(btree root) {                        //非递归先序遍历
    stack<btree>s;
    while (root != NULL || (!s.empty()))
    {
        while (root != NULL)
        {
            printf("%c ", root->data);
            s.push(root);
            root = root->lchild;
        }
        if(!s.empty())
        {
            root = s.top();
            s.pop();
            root = root->rchild;
        }
    }
}
void inorder_not_resurcive(btree root) {                           //非递归中序遍历
    stack<btree>s;
    while(root != NULL || !s.empty())
    {
        while (root != NULL)
        {
            s.push(root);
            root = root->lchild;
            step_0++;
        }
        if(!s.empty())
        {
            root = s.top();
            s.pop();
            printf("%c ", root->data);
            root = root -> rchild;
        }
        step_0++;
    }
}
void postorder_not_resurcive(btree root) {                             //非递归后序遍历
    stack<node1>s;
    node1 a;
    char c= root->data;
    int cnt = 0;
    num = total_num(root);
    while(root != NULL || !s.empty())
    {
        while(root != NULL)
        {
            a.p = root;
            a.flag = 1;
            s.push(a);
            root = root->lchild;
        }
        while(!s.empty() && s.top().flag == 2)
        {
            root = s.top().p;
            printf("%c ", root->data);
            s.pop();
            cnt++;
            if(cnt == num) return;
        }
        if(!s.empty())
        {
            s.top().flag = 2;
            root = s.top().p->rchild;
        }
    }
}
void inorderth(btree root) {                                   //构造中序线索二叉树
    if(root)
    {
        inorderth(root->lchild);
        if(root->lchild) root->ltag = true;
        else root->ltag = false;
        if(root->rchild) root->rtag = true;
        else root->rtag = false;
        if(pre)
        {
            if(pre->rtag == false) pre->rchild = root;
            if(root->ltag == false) root->lchild = pre;
        }
        pre = root;
        inorderth(root->rchild);
    }
}
void set_head(btree root) {                                     //实现带有头节点的中序线索二叉树
    btree t = root;
    //btree head = new btreenode;
    head->rtag = true;
    head->rchild = head;
    if(!t) {
        head->ltag = false;
        head->lchild = head;
    }
    else {
        pre = head;
        head->ltag = true;
        head->lchild = root;
        inorderth(t);
        pre->rchild = head;
        pre->rtag = false;
        head->rtag = pre;
    }
}
void  inorderth2(btree root) {                                   //对中序线索二叉树进行中序遍历
    btree p = head->lchild;
    while (p != head) {
        while (p->ltag == true) {
            p = p->lchild;
            step_1++;
        }
        printf("%c ", p->data);
        while (p->rtag == false && p->rchild != head) {
            p = p->rchild;
            printf("%c ", p->data);
            step_1++;
        }
        p = p->rchild;
        step_1++;
    }

}
btree PreNext(btree p) {                     //给定一个节点，在中序线索二叉树的先序遍历中寻找后继节点
    btree q;
    if(p->ltag == true)
        q = p->lchild;
    else {
        q = p;
        while (q->rtag == false)
            q = q->rchild;
        q = q->rchild;
    }
    return q;
}
void preordth2(btree p) {                        //对中序线索二叉树进行先序遍历
    btree q;
    p = p->lchild;
    printf("%c ", p->data);
    while (p != head) {
        q = PreNext(p);
        if(q != head)
          printf("%c ", q->data);
        else return;
        p = q;
    }
}
btree InNext(btree p) {                        //给定一个节点，在中序线索二叉树的中序遍历中寻找后继节点
    btree q;
    q = p->rchild;
    if(p->rtag == true) {
        while(q->ltag == true)
            q = q->lchild;
    return q;
    }

}
btree find_father(btree q, btree head) {                  //寻找任意节点的父节点
    btree p = head->lchild;
    while (p != head) {
        while (p->ltag == true)
            p = p->lchild;
        //printf("%c ", p->data);
        if((p->lchild == q && p->ltag == true) || (p->rchild == q && p->rtag == true))
            return p;
        while (p->rtag == false && p->rchild != head) {
            p = p->rchild;
            //printf("%c ", p->data);
            if((p->lchild == q && p->ltag == true) || (p->rchild == q && p->rtag == true))
                return p;
        }
        p = p->rchild;
    }
}
btree PostNext(btree p) {                               //给定一个节点，在中序线索二叉树的后序遍历中寻找后继节点
    btree q = find_father(p, head);
    //printf("%c\n",q->data);
    if(q && q->rtag == true && q->rchild == p)
        return q;
    if(q && q->ltag == true && q->lchild == p) {
        if(q->rtag == false)
            return q;
        if(q->rtag == true) {
            q = q->rchild;
            while (q->ltag) {
                q = q->lchild;
            }
            return q;
        }
    }
}
void post_orderth2(btree p) {                       //对中序线索二叉树进行后序遍历
    btree q;
    btree root = p->lchild;
    int cnt = 0;
    while(p->ltag)
        p = p->lchild;
    printf("%c ", p->data);
    while(p != root && cnt <= num) {
        q = PostNext(p);
        printf("%c ", q->data);
        cnt++;
        p = q;
    }
}
int main() {
    printf("输入二叉树：\n");
    btree root_0 = create_0(0);
    printf("第一棵树（先序序列创建）\n");
    print_btree(root_0);
    btree root_1 = create_1();
    printf("第二棵树（线性序列创建）\n");
    print_btree(root_1);
    printf("对于第二棵树，层序遍历结果如下\n");
    level_order(root_1);
    printf("对于第二棵树，先序遍历结果如下\n");
    preorder_recursive(root_1);
    printf("\n");
    printf("对于第二棵树，中序遍历结果如下\n");
    inorder_recursive(root_1);
    printf("\n");
    printf("对于第二棵树，后序遍历结果如下\n");
    postorder_recursive(root_1);
    printf("\n");
    printf("对于第二棵树，非递归先序遍历结果如下\n");
    preorder_not_recursive(root_1);
    printf("\n");
    printf("对于第二棵树，非递归中序遍历结果如下\n");
    inorder_not_resurcive(root_1);
    printf("\n");
    //printf("%d",total_num(root_1));
    printf("对于第二棵树，非递归后序遍历结果如下\n");
    postorder_not_resurcive(root_1);
    printf("\n");
    //inorderth(root_1);
    printf("中序线索二叉树已构建成功\n");
    set_head(root_1);
    printf("对于中序线索二叉树，先序遍历结果如下：\n");
    preordth2(head);
    printf("\n");
    printf("对于中序线索二叉树，中序遍历结果如下：\n");
    inorderth2(head);
    printf("\n");
    printf("对于中序线索二叉树，后序遍历结果如下：\n");
    post_orderth2(head);
    printf("\n");
    printf("对于根的左儿子节点，先序遍历的后继节点为：\n");
    printf("%c\n", PreNext(head->lchild->lchild)->data);
    printf("对于根的左儿子节点，中序遍历的后继节点为：\n");
    printf("%c\n", InNext(head->lchild->lchild)->data);
    //printf("%c",find_father(head->lchild->lchild, head)->data);
    printf("对于根的左儿子节点，后序遍历的后继节点为：\n");
    printf("%c\n", PostNext(head->lchild->lchild)->data);
    printf("不采用线索二叉树，中序遍历的操作步骤为%d步，\n", step_0);
    printf("而采用线索二叉树，中序遍历的操作步骤为%d步。\n", step_1);
    printf("很明显，线索化之后步骤更少，更省时间~\n");
    return 0;
}