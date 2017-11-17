#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node       //����ṹ��洢ÿ������ʽ�еĵ���ʽ
{
    float a;    //ϵ��
    int b;      //ָ��
    struct node *next;
} Polynode;
typedef Polynode *Polynomial;
Polynomial crete()       //�������ʽ�������ڹ���ʱʵ�ֽ�������
{
    Polynode *p, *q, *head = (Polynode *)malloc(sizeof(Polynode));
    head -> next = NULL;
    float m;
    int n;
    printf("����ÿһ���ϵ����ָ����ÿ��һ�У�����0 0ʱֹͣ����\n");
    while(scanf("%f%d", &m, &n) && m != 0)
    {
        if(head -> next)
        {
            p = head;
            while(p -> next && n < p -> next -> b)
                p = p -> next;
            if(p -> next)
            {
                if(n == p -> next -> b)     //�ϲ�ͬ����
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
void free_poly(Polynomial poly) {   //�ͷ��ڴ棬��ʡ�ռ�
    Polynode *p = poly->next;
    while(p)
    {
        free(p);
        p = p->next;
    }
}
Polynomial poly_add(Polynomial poly1, Polynomial poly2) {   //����ʽ�ӷ�����
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
    while(p)  //���һ������ʽ�Ѿ�������������ʣ�µĶ���ʽֱ�ӷŵ�����������
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
Polynomial poly_sub(Polynomial poly1, Polynomial poly2) {  //����ʽ����
    Polynomial poly = (Polynode *)malloc(sizeof(Polynode));
    Polynode *p, *q;
    p = poly;
    q = poly2 -> next;
    while(q)   //��������ʽ��ÿһ��ϵ������ȡ��
    {
        p -> next = (Polynode *)malloc(sizeof(Polynode));
        p = p -> next;
        p -> a = -(q -> a);
        p -> b = q -> b;
        q = q -> next;
    }
    p -> next = NULL;
    return poly_add(poly1, poly);   //���üӷ�
}
Polynomial poly_mul(Polynomial poly1, Polynomial poly2) {   //����ʽ�˷�
    Polynode *poly = (Polynode *)malloc(sizeof(Polynode));
    poly -> next = NULL;
    Polynode *p = poly2 -> next;
    Polynode *q = poly1 -> next;
    q = q -> next;
    Polynode *r;
    //r = poly;
    Polynode *part = (Polynode*)malloc(sizeof(Polynode));  //���ֺ�����
    r = part;

    while(p)   //����һ����poly2������ȵ��������洢���ֺͣ�ÿ��ֻ�����ϵ��ָ�����ɣ������ͷſռ䣬������ʡ�ռ䣬�����Լ��ٽڵ��Ƶ������
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
        poly = poly_add(poly, part);    //�ۼӲ��ֺ�

    }
    free_poly(part);      //�ͷŲ��ֺ�������ʡ�ڴ�
    return poly;
}

void poly_div(Polynomial poly1, Polynomial poly2) {   //�������
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
    printf("���ǣ�\n");
    print_poly(quo);
    printf("�����ǣ�\n");
    print_poly(rem);
    free_poly(quo);       //�ͷ��̺���������
    free_poly(rem);
}
void print_poly(Polynomial poly) {   //��ӡ����
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
            printf("%.2f", p -> a);    //���ָ����0��ֻ��ӡϵ��
        }
        else
        {
            printf("%.2fx^%d", p -> a, p -> b);
        }
        printf("\n");
    }
    else printf("%d\n", 0);
}
double poly_cal(Polynomial poly, float x) {   //����x = x0ʱ�Ķ���ʽ��ֵ
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
    //freopen("poly_in.txt", "r", stdin);          //������������
    //freopen("poly_in_1.txt", "r", stdin);
    freopen("poly_in_2.txt", "r", stdin);
    freopen("poly_out.txt", "w", stdout);
    Polynomial poly1, poly2, poly;
    printf("����ʽ����\n");
    printf("��������ʽһ\n");
    poly1 = crete();
    print_poly(poly1);
    printf("��������ʽ��\n");
    poly2 = crete();
    print_poly(poly2);
    printf("������x��ֵ��\n");
    scanf("%f", &x);
    printf("�����ʽһ�е�xֵΪ%f�������ʽһ��ֵΪ��\n", x);
    printf("%lf\n", poly_cal(poly1, x));
    printf("�����ʽ���е�xֵΪ%f�������ʽ����ֵΪ��\n", x);
    printf("%lf\n", poly_cal(poly2, x));
    printf("��������ʽ��ӣ�\n");
    print_poly(poly_add(poly1, poly2));
    free_poly(poly_add(poly1, poly2));
    printf("��������ʽ�����\n");
    print_poly(poly_sub(poly1, poly2));
    free_poly(poly_sub(poly1, poly2));
    printf("��������ʽ���:\n");
    poly = poly_mul(poly1, poly2);
    print_poly(poly);
    free_poly(poly);
    printf("��������ʽ�����\n");
    poly_div(poly1, poly2);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
