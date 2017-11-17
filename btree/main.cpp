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
        freopen("test.txt", "r", stdin);                       // �������������������
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
    int i, j;                                                  //���Ա���������
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
void print_btree(btree root) {                          //��ӡ������
    if(root == NULL)
        return;
    queue<btree> nodes;
    nodes.push(root);
    int nextlevel = 0;   //��һ�нڵ���
    int need_print = 1;//����ӡ�Ľڵ���
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
        if(need_print == 0)     //��ǰ�нڵ��ӡ���
        {
            printf("\n");
            need_print = nextlevel;
            nextlevel = 0;
            i -= 5;
            k -= 1;
        }
    }
}
int total_num(btree root) {                                    //ͳ�������ܽڵ���
    if(root == NULL) return 0;
    else return 1 + total_num(root->lchild) + total_num(root->rchild);
}
void level_order(btree root) {                                 //�������
    if(root == NULL)
        return;
    queue<btree> nodes;
    nodes.push(root);
    int nextlevel = 0;   //��һ�нڵ���
    int need_print = 1;  //����ӡ�Ľڵ���
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
        if(need_print == 0)     //��ǰ�нڵ��ӡ���
        {
            //printf("\n");
            need_print = nextlevel;
            nextlevel = 0;
        }
    }
    printf("\n");
}
void preorder_recursive(btree root) {                        //�ݹ��������
    if(root != NULL)
    {
        printf("%c ", root->data);
        preorder_recursive(root->lchild);
        preorder_recursive(root->rchild);
    }
}
void inorder_recursive(btree root) {                         //�ݹ��������
    if(root != NULL)
    {
        inorder_recursive(root->lchild);
        printf("%c ", root->data);
        inorder_recursive(root->rchild);
    }
}
void postorder_recursive(btree root) {                         //�ݹ�������
    if(root != NULL)
    {
        postorder_recursive(root->lchild);
        postorder_recursive(root->rchild);
        printf("%c ", root->data);
    }
}
void preorder_not_recursive(btree root) {                        //�ǵݹ��������
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
void inorder_not_resurcive(btree root) {                           //�ǵݹ��������
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
void postorder_not_resurcive(btree root) {                             //�ǵݹ�������
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
void inorderth(btree root) {                                   //������������������
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
void set_head(btree root) {                                     //ʵ�ִ���ͷ�ڵ����������������
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
void  inorderth2(btree root) {                                   //���������������������������
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
btree PreNext(btree p) {                     //����һ���ڵ㣬���������������������������Ѱ�Һ�̽ڵ�
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
void preordth2(btree p) {                        //���������������������������
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
btree InNext(btree p) {                        //����һ���ڵ㣬���������������������������Ѱ�Һ�̽ڵ�
    btree q;
    q = p->rchild;
    if(p->rtag == true) {
        while(q->ltag == true)
            q = q->lchild;
    return q;
    }

}
btree find_father(btree q, btree head) {                  //Ѱ������ڵ�ĸ��ڵ�
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
btree PostNext(btree p) {                               //����һ���ڵ㣬�����������������ĺ��������Ѱ�Һ�̽ڵ�
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
void post_orderth2(btree p) {                       //�������������������к������
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
    printf("�����������\n");
    btree root_0 = create_0(0);
    printf("��һ�������������д�����\n");
    print_btree(root_0);
    btree root_1 = create_1();
    printf("�ڶ��������������д�����\n");
    print_btree(root_1);
    printf("���ڵڶ���������������������\n");
    level_order(root_1);
    printf("���ڵڶ���������������������\n");
    preorder_recursive(root_1);
    printf("\n");
    printf("���ڵڶ���������������������\n");
    inorder_recursive(root_1);
    printf("\n");
    printf("���ڵڶ���������������������\n");
    postorder_recursive(root_1);
    printf("\n");
    printf("���ڵڶ��������ǵݹ���������������\n");
    preorder_not_recursive(root_1);
    printf("\n");
    printf("���ڵڶ��������ǵݹ���������������\n");
    inorder_not_resurcive(root_1);
    printf("\n");
    //printf("%d",total_num(root_1));
    printf("���ڵڶ��������ǵݹ��������������\n");
    postorder_not_resurcive(root_1);
    printf("\n");
    //inorderth(root_1);
    printf("���������������ѹ����ɹ�\n");
    set_head(root_1);
    printf("���������������������������������£�\n");
    preordth2(head);
    printf("\n");
    printf("���������������������������������£�\n");
    inorderth2(head);
    printf("\n");
    printf("���������������������������������£�\n");
    post_orderth2(head);
    printf("\n");
    printf("���ڸ�������ӽڵ㣬��������ĺ�̽ڵ�Ϊ��\n");
    printf("%c\n", PreNext(head->lchild->lchild)->data);
    printf("���ڸ�������ӽڵ㣬��������ĺ�̽ڵ�Ϊ��\n");
    printf("%c\n", InNext(head->lchild->lchild)->data);
    //printf("%c",find_father(head->lchild->lchild, head)->data);
    printf("���ڸ�������ӽڵ㣬��������ĺ�̽ڵ�Ϊ��\n");
    printf("%c\n", PostNext(head->lchild->lchild)->data);
    printf("��������������������������Ĳ�������Ϊ%d����\n", step_0);
    printf("��������������������������Ĳ�������Ϊ%d����\n", step_1);
    printf("�����ԣ�������֮������٣���ʡʱ��~\n");
    return 0;
}