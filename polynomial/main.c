#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node       //定义结构体存储每个多项式中的单项式
{
    float a;    //系数
    int b;      //指数
    struct node *next;
} Polynode;
typedef Polynode *Polynomial;
Polynomial crete()       //构造多项式链表，并在构造时实现降幂排列
{
    Polynode *p, *q, *head = (Polynode *)malloc(sizeof(Polynode));
    head -> next = NULL;
    float m;
    int n;
    printf("输入每一项的系数，指数，每项一行，输入0 0时停止输入\n");
    while(scanf("%f%d", &m, &n) && m != 0)
    {
        if(head -> next)
        {
            p = head;
            while(p -> next && n < p -> next -> b)
                p = p -> next;
            if(p -> next)
            {
                if(n == p -> next -> b)     //合并同类项
                {
                    p -> next -> a += m;
                    if(p -> next -> a == 0)
                    {
                        q = p -> next;
                        p -> next = q;
                        free(q);
                    }
                }
                else
                {
                    q = (Polynode *)malloc(sizeof(Polynode));
                    q -> a = m;
                    q -> b = n;
                    q -> next = p -> next;
                    p -> next = q;
                 }
            }
            else
            {
                p -> next = (Polynode *)malloc(sizeof(Polynode));
                p -> next -> a = m;
                p -> next -> b = n;
                p -> next -> next = NULL;
            }

        }
        else
        {
            head -> next = (Polynode *)malloc(sizeof(Polynode));
            head -> next -> a = m;
            head -> next -> b = n;
            head -> next -> next = NULL;
        }
    }
    return head;
}
void free_poly(Polynomial poly) {   //释放内存，节省空间
    Polynode *p = poly->next;
    while(p)
    {
        free(p);
        p = p->next;
    }
}
Polynomial poly_add(Polynomial poly1, Polynomial poly2) {   //多项式加法函数
    Polynode *p, *q, *r;
    Polynomial poly = (Polynode *)malloc(sizeof(Polynode));
    p = poly1 -> next;
    q = poly2 -> next;
    r = poly;
    while(p && q)
    {
        if(p -> b > q -> b)
        {
            r -> next = (Polynode *)malloc(sizeof(Polynode));
            r = r -> next;
            r -> a = p -> a;
            r -> b = p -> b;
            p = p -> next;
        }
        else if(p -> b < q -> b)
        {
            r -> next = (Polynode *)malloc(sizeof(Polynode));
            r = r -> next;
            r -> a = q -> a;
            r -> b = q -> b;
            q = q -> next;
        }
        else
        {
            float m = p -> a + q -> a;
            if(m)
            {
                r -> next = (Polynode *)malloc(sizeof(Polynode));
                r = r -> next;
                r -> a = m;
                r -> b = p -> b;
            }
            q = q -> next;
            p = p -> next;
        }

    }
    while(p)  //如果一个多项式已经遍历结束，将剩下的多项式直接放到结果链表最后
        {
            r -> next = (Polynode *)malloc(sizeof(Polynode));
            r = r -> next;
            r -> a = p -> a;
            r -> b = p -> b;
            p = p -> next;
        }
    while(q)
        {
            r -> next = (Polynode *)malloc(sizeof(Polynode));
            r = r -> next;
            r -> a = q -> a;
            r -> b = q -> b;
            q = q -> next;
        }
     r -> next = NULL;
     return poly;
}
Polynomial poly_sub(Polynomial poly1, Polynomial poly2) {  //多项式减法
    Polynomial poly = (Polynode *)malloc(sizeof(Polynode));
    Polynode *p, *q;
    p = poly;
    q = poly2 -> next;
    while(q)   //减数多项式的每一项系数依次取反
    {
        p -> next = (Polynode *)malloc(sizeof(Polynode));
        p = p -> next;
        p -> a = -(q -> a);
        p -> b = q -> b;
        q = q -> next;
    }
    p -> next = NULL;
    return poly_add(poly1, poly);   //调用加法
}
Polynomial poly_mul(Polynomial poly1, Polynomial poly2) {   //多项式乘法
    Polynode *poly = (Polynode *)malloc(sizeof(Polynode));
    poly -> next = NULL;
    Polynode *p = poly2 -> next;
    Polynode *q = poly1 -> next;
    q = q -> next;
    Polynode *r;
    //r = poly;
    Polynode *part = (Polynode*)malloc(sizeof(Polynode));  //部分和链表
    r = part;

    while(p)   //建立一个和poly2长度相等的链表，来存储部分和，每次只需更新系数指数即可，不用释放空间，不仅节省空间，还可以减少节点的频繁申请
    {
        r -> next = (Polynode *)malloc(sizeof(Polynode));
        r = r -> next;
        p = p -> next;
    }
    r -> next =NULL;

    q = poly1 -> next;
    while(q)
    {
        p = poly2 -> next;
        r = part -> next;
        while(p)
        {
            r -> a = (p -> a) * (q -> a);
            r -> b = (p -> b) + (q -> b);
            p = p -> next;
            r = r -> next;
        }

        q = q -> next;
        poly = poly_add(poly, part);    //累加部分和

    }
    free_poly(part);      //释放部分和链表，节省内存
    return poly;
}

void poly_div(Polynomial poly1, Polynomial poly2) {   //计算除法
    Polynode *quo, *rem, *p, *q, *r, *t;
    quo = (Polynode *)malloc(sizeof(Polynode));
    rem = (Polynode *)malloc(sizeof(Polynode));
    p = quo;
    q = poly1 -> next;
    t = poly2 -> next;
    r = (Polynode *)malloc(sizeof(Polynode));
    r -> next = (Polynode *)malloc(sizeof(Polynode));
    r = r -> next;
    r -> next = NULL;
    while(q && q -> b >= t -> b)
    {
        poly1 = poly_sub(poly1, poly_mul(poly2, r));
        p -> next = (Polynode *)malloc(sizeof(Polynode));
        p = p -> next;
        p -> a = q -> a / t -> a;
        p -> b = q -> b - t -> b;
        q = q -> next;
    }
    p -> next = NULL;
    rem = poly_sub(poly1,poly_mul(poly2, quo));
    printf("商是：\n");
    print_poly(quo);
    printf("余数是：\n");
    print_poly(rem);
    free_poly(quo);       //释放商和余数链表
    free_poly(rem);
}
void print_poly(Polynomial poly) {   //打印链表
    if(poly && poly -> next)
    {
        Polynode *p = poly -> next;
        while(p -> next)
        {
            printf("%.2fx^%d", p -> a, p -> b);
            p = p -> next;
            if(p && (p -> a) > 0)
                printf("+");
        }
        if(p -> b == 0)
        {
            printf("%.2f", p -> a);    //如果指数是0，只打印系数
        }
        else
        {
            printf("%.2fx^%d", p -> a, p -> b);
        }
        printf("\n");
    }
    else printf("%d\n", 0);
}
double poly_cal(Polynomial poly, float x) {   //计算x = x0时的多项式的值
    Polynode *p = poly -> next;
    double sum = 0;
    while(p)
    {
        sum += (p -> a) * pow(x, (p -> b));
        p = p -> next;
    }
    return sum;
}
int main()
{
    float x;
    //freopen("poly_in.txt", "r", stdin);          //三个输入样本
    //freopen("poly_in_1.txt", "r", stdin);
    freopen("poly_in_2.txt", "r", stdin);
    freopen("poly_out.txt", "w", stdout);
    Polynomial poly1, poly2, poly;
    printf("多项式操作\n");
    printf("创建多项式一\n");
    poly1 = crete();
    print_poly(poly1);
    printf("创建多项式二\n");
    poly2 = crete();
    print_poly(poly2);
    printf("请输入x的值：\n");
    scanf("%f", &x);
    printf("令多项式一中的x值为%f，则多项式一的值为：\n", x);
    printf("%lf\n", poly_cal(poly1, x));
    printf("令多项式二中的x值为%f，则多项式二的值为：\n", x);
    printf("%lf\n", poly_cal(poly2, x));
    printf("两个多项式相加：\n");
    print_poly(poly_add(poly1, poly2));
    free_poly(poly_add(poly1, poly2));
    printf("两个多项式相减：\n");
    print_poly(poly_sub(poly1, poly2));
    free_poly(poly_sub(poly1, poly2));
    printf("两个多项式相乘:\n");
    poly = poly_mul(poly1, poly2);
    print_poly(poly);
    free_poly(poly);
    printf("两个多项式相除：\n");
    poly_div(poly1, poly2);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
