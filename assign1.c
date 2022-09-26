#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student
{
        char name[30];
        int roll;
        char tel[15];
        char addr[50];
};

struct SReg
{
        struct Student a[20];
        int length;
};

int add(struct SReg *sr, struct Student s)
{
        for(int i=0;i<sr->length;i++)
                if(sr->a[i].roll == s.roll)
                        return 0;
        sr->a[sr->length] = s;
        sr->length++;
        return 1;
}
void display(struct SReg sr)
{
        for(int i=0;i<sr.length;i++)
        {
                printf("Student info: ");
                printf("%s %d %s %s\n", sr.a[i].name, sr.a[i].roll, sr.a[i].tel, sr.a[i].addr);
        }
}

void dispst(struct Student s)
{
        printf("Student info:%s %d %s %s\n", s.name, s.roll, s.tel, s.addr);
}

struct Student get(struct SReg sr, int r)
{
        struct Student s0={"",0,"",""};
        for(int i=0;i<sr.length;i++)
                if(sr.a[i].roll == r) return sr.a[i];
        return s0;
}
int delete(struct SReg *sr, int r)
{
        int i;
        for(i=0;i<sr->length;i++)
                if(sr->a[i].roll == r) break;
        if(i==sr->length) return 0;
        for(int j=i;j<sr->length-1;j++)
                sr->a[j]=sr->a[j+1];
        sr->length--;
        return 1;
}

int modify(struct SReg *sr, struct Student s)
{
        for(int i=0;i<sr->length;i++)
                if(sr->a[i].roll == s.roll)
                {
                        sr->a[i] = s;
                        return 1;
                }
        return 0;

}
int getCount(struct SReg sr)
{
        return sr.length;
}

void swap(struct Student *p, struct Student *q)
{
        struct Student t = *p;
        *p = *q;
        *q = t;
}

void arr(char n[], char t[], char name[])
{
        int i, j;
        for(i=0;name[i]!=',';i++)
                t[i] = name[i];
        t[i] = '\0';
        i+=2;
        for(j=0;name[i];i++, j++)
                n[j] = name[i];
        n[j] ='\0';
}

void sort(struct SReg *sr)
{
        char ni[20], ti[20], nj[20], tj[20];
        int i, j, k, l;
        for(i=0;i<sr->length;i++)
        {
                for(j=i+1;j<sr->length;j++)
                {
                        arr(ni, ti, sr->a[i].name);
                        arr(nj, tj, sr->a[j].name);
                        k = strcmp(nj, ni);
                        l = strcmp(tj, ti);
                        if(k<0)
                                swap(&sr->a[i], &sr->a[j]);
                        else if(k == 0 && l<0)
                                swap(&sr->a[i], &sr->a[j]);
                }
        }
}
void export(struct SReg sr, char fname[])
{
        FILE *fp=NULL;
        fp = fopen(fname, "w");
        for(int i=0;i<sr.length;i++)
                fprintf(fp,"%s %d %s %s\n",sr.a[i].name, sr.a[i].roll, sr.a[i].tel, sr.a[i].addr);
        fclose(fp);
}

void merge(char name[], char n[], char t[])
{
        int i, j;
        for(i=0;t[i];i++)
                name[i]=t[i];
        name[i++]=' ';
        for(j=0;n[j];i++, j++)
                name[i]=n[j];
        name[i]='\0';
}
void load(struct SReg *sr, char fname[])
{
        int i=0, j;
        FILE *fp = NULL;
        fp = fopen(fname, "r");
        for(char c = getc(fp);c != EOF;c = getc(fp))
                if(c == '\n') i++;
        fclose(fp);
        fopen(fname, "r");
        for(j=0;j<i;j++)
        {
                char n[20], t[20];
                fscanf(fp, "%s %s %d %s %s", t, n, &sr->a[j].roll, sr->a[j].tel, sr->a[j].addr);
                merge(sr->a[j].name, n, t);
                sr->length++;
        }
        fclose(fp);
}
int main()
{
        struct SReg sr;
        sr.length = 0;
        printf("This is Student Registry.\n");
        int k;
        while(1)
        {
                printf("press 0 to print all operations.\n");
                printf("Enter a number: ");
                scanf("%d", &k);
                switch(k)
                {
                        case 0:
                                printf("press 1 for adding students.\n");
                                printf("press 2 for getting a student info from using roll no.\n");
                                printf("press 3 for deleting a student info using roll no.\n");
                                printf("press 4 to modify a student info.\n");
                                printf("press 5 to sort students alphabetically.\n");
                                printf("press 6 to show number of students.\n");
                                printf("press 7 to export student registry to file.\n");
                                printf("press 8 to load student registry from file.\n");
                                printf("press 9 to display the student registry\n");
                                printf("press 10 to exit from the program.\n");
                                break;
                        case 1:
                                printf("Give student name, roll, telephone no, address in this format: ");
                                printf("title,name roll telephone no address\n");
                                printf("How many students you want to add: ");
                                int l;
                                struct Student s;
                                scanf("%d", &l);
                                for(int i=0;i<l;i++)
                                {
                                        printf("Give %dth student info.\n", i+1);
                                        printf("Enter student name:");
                                        getchar();
                                        scanf("%[^\n]s", s.name);
                                        printf("Enter roll no: ");
                                        scanf("%d", &s.roll);
                                        printf("Enter telephone no:");
                                        scanf("%s", s.tel);
                                        printf("Enter address:");
                                        scanf("%s", s.addr);
                                        add(&sr, s);
                                }
                                break;
                        case 2:
                                printf("Enter the roll number of the student whose info you want to get: ");
                                int r1;
                                scanf("%d", &r1);
                                struct Student s1=get(sr, r1);
                                if(s1.roll == 0) printf("No student present in this student registry\n");
                                else dispst(s1);
                                break;
                        case 3:
                                printf("Enter the roll no of the student whose info you want to delete: ");
                                int r2;
                                scanf("%d", &r2);
                                int d = delete(&sr, r2);
                                if(d) printf("deleting was successful.\n");
                                else printf("There is no student with that roll no.\n");
                                break;
                        case 4:
                                struct Student s2;
                                printf("Give student info: \n");
                                printf("Enter student name:");
                                getchar();
                                scanf("%[^\n]s", s2.name);
                                printf("Enter roll no: ");
                                scanf("%d", &s2.roll);
                                printf("Enter telephone no:");
                                scanf("%s", s2.tel);
                                printf("Enter address:");
                                scanf("%s", s2.addr);
                                int f1 = modify(&sr, s2);
                                if(f1) printf("Modification is successful.\n");
                                else printf("Modification is not successful.\n");
                                break;
                        case 5:
                                printf("This will arrange the student registry alphabatically.\n");
                                sort(&sr);
                                break;
                        case 6:
                                printf("Numbers of students in the registry: %d\n", getCount(sr));
                                break;
                        case 7:
                                printf("Enter the filename in which you want to save the student registry:");
                                char fname[20];
                                scanf("%s", fname);
                                export(sr, fname);
                                break;
                        case 8:
                                printf("Enter the filename from where you want to save the student registry:");
                                char f1name[20];
                                scanf("%s", fname);
                                load(&sr, fname);
                                break;
                        case 9:
                                printf("*************************This is the student registry*******************************\n");
                                display(sr);
                                break;
                        case 10:
                                printf("******************************Thank you for using this student registry.************************************");
                                return 0;
                        default:
                                printf("Invalid input\n");
                                continue;

                }
        }
}





