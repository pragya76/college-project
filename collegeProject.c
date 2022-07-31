#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

FILE *fs, *ft; // file declaration fs for student ft for teacher

struct dateStructure // for date(month and day
{
    int day, month; // d=day,m=month
};
struct studentStructure
{
    char name[50];
    char semester[20];
    char program[50];
    int roll;
    int fee;
    float fine, total, advance, due, paidAmount;
    struct dateStructure date;

} student;
struct staffStructure
{
    char name[50];
    char address[20];
    char degree[50];
    int contactNo;
    float salary, advance, total;
    struct dateStructure date;

} staff;
void start();

int chkdat(int mnt, int dnt)
{
    int mon, day;
    if (mnt > 12 || mnt < 1 || dnt < 1 || dnt > 32)
    {
        MessageBox(0, "Invalid Date!\nEnter Again", "Error!", 0);
        fflush(stdin);
        scanf("%d%d", &mon, &day);
        mon = chkdat(mon, day);
    }
    else
        return (mnt);
}
void login()
{
    int a = 0, i = 0;
    char userName[10], c = ' ';
    char password[10], code[10];
    char user[10] = "user";
    char pass[10] = "pass";
    do
    {
        system("cls");
        printf("\n\t>>>>>>>>>>>>>>>>>>>>>>>>>> |LOGIN|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        printf(" \n\t\tUSERNAME:-");
        scanf("%s", &userName);
        printf(" \n\t\tPASSWORD:-");
        while (i < 10)
        {
            password[i] = getch();
            c = password[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        password[i] = '\0';
        // char code=password;
        i = 0;
        if (strcmp(userName, "user") == 0 && strcmp(password, "pass") == 0)
        {
            system("cls");
            printf("\n\t**********************************************************************************");
            printf("\n\t*           WELCOME TO CILLEGE BILLING SYSTEM !!!! LOGIN IS SUCCESSFUL           *");
            printf("\n\t**********************************************************************************");
            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch(); // holds the screen
            break;
        }
        else
        {
            system("cls");
            printf("\n          LOGIN IS UNSUCESSFUL");
            printf("\n        Invalid userName and Password");
            a++;
            getch(); // holds the screen
        }
    } while (a <= 2);
    if (a > 2)
    {
        printf("\nSorry you have entered the wrong username and password for four times!!!");
        getch();
    }
    system("cls");
};
//-------------------------------------------------exit----------------------------------------------------------
void exitNow()
{
    int i;
    printf("\n\n\t\t Thanks for using our School's Billing System. .\n\n");
    system("pause");
    system("cls");
    printf("\n\n\t\t\t Exiting In A Moment\n\n");
    for (i = 1; i <= 60; i++)
    {
        Sleep(50);
        printf("->");
    }
    exit(0);
};

//###################################################| STUDENT |#####################################################################//---------------------------add record--------------------------------------------------------------------------------------
//------------------------------------------------------add student------------------------------------------------------------
void addStudent()
{

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char c = 'y';
    system("cls");
    printf("\n\t   ******************************************************************");
    printf("\n\t  >>>>>>>>>>>>>>>>>>       ADD RECORDS         <<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\t   ******************************************************************");

    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        fflush(stdin);
        printf("\nEnter Name of the student(string): ");
        scanf("%s", student.name);
        fflush(stdin);
        printf("\nEnter the program(string): ");
        scanf("%s", student.program);
        fflush(stdin);
        printf("\nEnter your semester(string): ");
        scanf("%s", student.semester);
        fflush(stdin);
        printf("\nEnter Roll No.(int):");
        scanf("%d", &student.roll);
        printf("\nEnter fee(int):");
        scanf("%d", &student.fee);
        printf("\nEnter month  till which Fee is paid:");
        fflush(stdin);
        printf("\nMonth:");
        scanf("%2d", &student.date.month);
        printf("\nDay:");
        scanf("%2d", &student.date.day);

        student.total = ((tm.tm_mon + 1) * student.fee) + (tm.tm_mday * (student.fee / 30));
        float feePaidUpTo = ((student.date.month) * student.fee) + (student.date.day * (student.fee / 30));
        if ((feePaidUpTo > student.total))
        {
            student.advance = feePaidUpTo - student.total;
            student.due = 0;
            student.fine = 0;
            student.paidAmount = feePaidUpTo;
        }
        else
        {
            student.advance = 0;
            student.due = student.total - feePaidUpTo;
            student.fine = (student.total - feePaidUpTo) * 0.1;
            student.paidAmount = feePaidUpTo;
        }

        // for calculation of total fee
        fs = fopen("student.txt", "ab+"); // opening a binary file in apend mode
        fwrite(&student, sizeof(struct studentStructure), 1, fs);
        fclose(fs);
        printf("\nRecorded Successfully !! ");

        printf("\n\nPress Esc To Exit or Do you want to continue adding records(press enter");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    printf("\n\n");
    system("pause");
}

//---------------------------------------------------------student fee---------------------------------------------

void fee(int mm)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int choice;
    system("cls");
    printf("\n\t******************************************************************");
    printf("\n\t<<<<<<<<<<<<<<<<<<<<<<       FEE     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("\n\t******************************************************************");

    FILE *f;
    int a = 0;
    char name[50], c = 'y';
    int roll, month, day;
    float adv, due, fine;

    while (c == 'y' || c == 'Y')
    {

        printf("\n\n\t\tPLEASE CHOOSE CALCULATE TYPE::");
        printf("\n\n\t\t1::with paid::");
        printf("\n\n\t\t2::without paid::");
        printf("\n\n\t\t3::Exit");
        printf("\n\n\t\t::Enter your choice:: ");
        fflush(stdin);
        scanf("%d", &choice);
        if (choice == 1)
        {
            int a = 1, day = 0;
            fflush(stdin);
            printf("\n\nEnter name:: ");
            scanf("%[^\n]", name);
            printf("\n\nEnter roll:: ");
            fflush(stdin);
            scanf("%d", &roll);
            f = fopen("student.txt", "rb+");
            while (fread(&student, sizeof(student), 1, f) == 1)
            {
                if (strcmp(student.name, name) == 0 && roll == student.roll)
                {
                    a = 0;
                    printf("\n\nEnter the month & day till which fee to be Calculated:: ");
                    fflush(stdin);
                    printf("\nMonth:");
                    scanf("%2d", &month);
                    printf("\nDay:");
                    scanf("%2d", &day);
                    if ((student.date.month + (student.date.day / 30)) > (month + (day / 30)))
                    {
                        system("cls");
                        printf("Date must be greater than previous paid date\n");
                        printf("Previous paid date is month:%d,day:%d", student.date.month, student.date.day);
                    }
                    else
                    {
                        system("cls");
                        float calculatedFee = ((month)*student.fee) + (day * (student.fee / 30));
                        float finalFee = calculatedFee - student.paidAmount + student.fine;
                        if (student.advance > 0)
                        {
                            printf("\nAdvance amount :: %.2f", student.advance);
                            printf("\nPrevious paid amount including advance :: %.2f", student.paidAmount);
                        }
                        else if (
                            student.due > 0)
                        {
                            printf("\nDue amount :: %.2f", student.due);
                            printf("\nfine amount :: %.2f", student.fine);
                            printf("\nPrevious paid amount including due and fine :: %.2f", student.paidAmount);
                        }
                        printf("\nStudent monthly fee :: %d", student.fee);
                        printf("\nfee upto calculated date :: %.2f", calculatedFee);
                        printf("\nfinal fee :: %.2f", finalFee);
                    }

                    // fwrite(&student, sizeof(student), 1, t);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nFEE CALCULATED  SUCCESSFULLY");
            printf("\n\n");
            system("pause");
        }

        else if (choice == 2)
        {
            int a = 1, day = 0;
            fflush(stdin);
            printf("\n\nEnter name:: ");
            scanf("%[^\n]", name);
            printf("\n\nEnter roll:: ");
            fflush(stdin);
            scanf("%d", &roll);
            f = fopen("student.txt", "rb+");
            while (fread(&student, sizeof(student), 1, f) == 1)
            {
                if (strcmp(student.name, name) == 0 && roll == student.roll)
                {
                    a = 0;
                    printf("\n\nEnter the month & day till which fee to be Calculated:: ");
                    fflush(stdin);
                    printf("\nMonth:");
                    scanf("%2d", &month);
                    printf("\nDay:");
                    scanf("%2d", &day);

                    system("cls");
                    float calculatedFee = ((month)*student.fee) + (day * (student.fee / 30));
                    float totalFeeUpToToday = ((tm.tm_mon + 1) * student.fee) + (tm.tm_mday * (student.fee / 30));

                    if ((calculatedFee > totalFeeUpToToday))
                    {
                        adv = calculatedFee - totalFeeUpToToday;
                        due = 0;
                        fine = 0;
                        printf("\nAdvance amount :: %.2f", adv);
                        printf("\nDue amount :: %.2f", due);
                        printf("\nfine amount :: %.2f", fine);
                    }
                    else
                    {
                        adv = 0;
                        due = totalFeeUpToToday - calculatedFee;
                        fine = (totalFeeUpToToday - calculatedFee) * 0.1;
                        printf("\nAdvance amount :: %.2f", 0.0);
                        printf("\nDue amount :: %.2f", due);
                        printf("\nfine amount :: %.2f", fine);
                    }

                    printf("\nStudent monthly fee :: %d", student.fee);
                    printf("\nfee upto today date :: %.2f", totalFeeUpToToday);
                    printf("\nfee upto calculated date :: %.2f", calculatedFee);

                    // fwrite(&student, sizeof(student), 1, t);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nFEE SUCCESSFULLY  CALCULATED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 3)
            // ext();
            start();
        else
        {
            printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
            system("pause");
            fee(1);
        }

        printf("\n\n Press Esc To Exit or Do you want to continue calculate fee(press y or Y)");
        fflush(stdin);
        c = getch();
        system("cls");
        if (c == 27)
            start();
    }
    fflush(stdin);
    printf("\n\n");
    system("pause");
}
//------------------------------------------------------serarc student------------------------------------------------------------
void searchStudent()
{
    char namet[50];
    int searchNumber;
    int a = 1, choice;
    char c = 'y';

    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        system("cls");
        printf("\n\t******************************************************************");
        printf("\n\t<<<<<<<<<<<<<<<<<<<<   SEARCH RECORDS    >>>>>>>>>>>>>>>>>>>>>>>>>");
        printf("\n\t******************************************************************");
        printf("\n\n\t\t CHOOSE SEARCH TYPE::");
        printf("\n\n\t\t1>>Search by name::");
        printf("\n\n\t\t2>>Search by rollNo::");
        printf("\n\n\t\t3>>Search by program::");
        printf("\n\n\t\t4>>Go Back");
        printf("\n\n\t\t>>Enter Your Type:: ");
        fflush(stdin);
        scanf("%d", &choice);
        system("cls");
        if (choice == 1)
        {
            char name[50];
            a = 1;
            printf("\n\nEnter name of student to search(string): ");
            fflush(stdin);
            scanf("%s", name);
            fs = fopen("student.txt", "rb");
            printf("--------------Student Information------------------\n");
            while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
            {
                if (strcmpi(name, student.name) == 0)
                {
                    a = 0;

                    printf("\nName = %s", student.name);
                    printf("\nProgram = %s", student.program);
                    printf("\nRollNo = %d", student.roll);
                    printf("\nMonthy Fee =%d", student.fee);
                    printf("\nSemester =%s", student.semester);
                    printf("\nTotal Fee  =%f", student.total);
                    printf("\nDue =%f", student.due);
                    printf("\nAdvance  =%f", student.advance);
                    printf("\nFine  =%f", student.fine);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(fs);
        }
        else if (choice == 2)
        {
            int rollNo;
            a = 1;
            printf("\n\nEnter roll no of student(int): ");
            scanf("%d", &rollNo);
            fs = fopen("student.txt", "rb");
            printf("--------------Student Information------------------\n");

            while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
            {
                if (student.roll == rollNo)
                {
                    a = 0;
                    printf("\nName = %s", student.name);
                    printf("\nProgram = %s", student.program);
                    printf("\nRollNo = %d", student.roll);
                    printf("\nMonthy Fee =%d", student.fee);
                    printf("\nSemester =%s", student.semester);
                    printf("\nTotal Fee  =%f", student.total);
                    printf("\nDue =%f", student.due);
                    printf("\nAdvance  =%f", student.advance);
                    printf("\nFine  =%f", student.fine);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(fs);
        }
        else if (choice == 3)
        {
            char program[50];
            a = 1;
            printf("\n\nEnter program of student to search(string): ");
            scanf("%s", &program);
            fflush(stdin);
            fs = fopen("student.txt", "rb");
            printf("--------------Student Information------------------\n");

            while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
            {
                if (strcmpi(program, student.program) == 0)
                {
                    a = 0;
                    printf("\nName = %s", student.name);
                    printf("\nProgram = %s", student.program);
                    printf("\nRollNo = %d", student.roll);
                    printf("\nMonthy Fee =%d", student.fee);
                    printf("\nSemester =%s", student.semester);
                    printf("\nTotal Fee  =%f", student.total);
                    printf("\nDue =%f", student.due);
                    printf("\nAdvance  =%f", student.advance);
                    printf("\nFine  =%f", student.fine);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(fs);
        }
        else if (choice == 4)
        {
            // ext();
            start();
        }
        else
        {
            printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
            system("pause");
            searchStudent(1);
        }
        printf("\n\n Press Esc To Exit or Do you want to continue searching(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//--------------------------------------------------modify student---------------------------------------------------
void modifyStudent()
{
    char name[50];
    int a = 1, choice, cl, rolno;
    int month = 0, day = 0; // cdat=month till which fee is cleared
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char c = 'y';

    while (c == 'y' || c == 'Y')
    {
        system("cls");
        printf("\n\t******************************************************************");
        printf("\n\t<<<<<<<<<<<<<<<<<<<   MODIFY RECORDS     >>>>>>>>>>>>>>>>>>>>>>>>>>");
        printf("\n\t******************************************************************");
        printf("\n\n\t\tPLEASE CHOOSE MODIFY TYPE::");
        printf("\n\n\t\t1::Modify by name::");
        printf("\n\n\t\t2::Modify by name &class::");
        printf("\n\n\t\t3::Modify by name,class & rollno::");
        printf("\n\n\t\t4::Exit");
        printf("\n\n\t\t::Enter your choice:: ");
        fflush(stdin);
        scanf("%d", &choice);
        if (choice == 1)
        {
            int a = 0;
            printf("\n\nenter name of student to modify(string): ");
            fflush(stdin);
            scanf("%s", name);
            fs = fopen("student.txt", "rb+");
            while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
            {
                a = 1;
                if (strcmpi(name, student.name) == 0)
                {
                    a = 0;
                    fflush(stdin);
                    printf("\nEnter Name of the student(string): ");
                    scanf("%s", student.name);
                    fflush(stdin);
                    printf("\nEnter the program(string): ");
                    scanf("%s", student.program);
                    fflush(stdin);
                    printf("\nEnter your semester(string): ");
                    scanf("%s", student.semester);
                    fflush(stdin);
                    printf("\nEnter Roll No.(int):");
                    scanf("%d", &student.roll);
                    printf("\nEnter fee(int):");
                    scanf("%d", &student.fee);
                    printf("\nEnter month  till which Fee is paid:");
                    fflush(stdin);
                    printf("\nMonth:");
                    scanf("%2d", &month);
                    printf("\nDay:");
                    scanf("%2d", &day);
                    student.total = ((tm.tm_mon + 1) * student.fee) + (tm.tm_mday * (student.fee / 30));
                    float feePaidUpTo = ((month)*student.fee) + (day * (student.fee / 30));
                    if ((feePaidUpTo > student.total))
                    {
                        student.advance = feePaidUpTo - student.total;
                        student.due = 0;
                        student.fine = 0;
                    }
                    else
                    {
                        student.advance = 0;
                        student.due = student.total - feePaidUpTo;
                        student.fine = (student.total - feePaidUpTo) * 0.1;
                    }
                    fseek(fs, -sizeof(student), SEEK_CUR);
                    fwrite(&student, sizeof(struct studentStructure), 1, fs);
                    fclose(fs);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 2)
        {
            int rollNo;
            int a = 0;
            printf("\n\nEnter name of student to modify(string): ");
            fflush(stdin);
            scanf("%s", name);
            printf("\n\nEnter roll no of student(int) : ");
            scanf("%d", &rollNo);
            fs = fopen("student.txt", "rb+");
            while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
            {
                a = 1;
                if (strcmpi(name, student.name) == 0 && rollNo == student.roll)
                {
                    a = 0;
                    fflush(stdin);
                    printf("\nEnter Name of the student(string): ");
                    scanf("%s", student.name);
                    fflush(stdin);
                    printf("\nEnter the program(string): ");
                    scanf("%s", student.program);
                    fflush(stdin);
                    printf("\nEnter your semester(string): ");
                    scanf("%s", student.semester);
                    fflush(stdin);
                    printf("\nEnter Roll No.(int):");
                    scanf("%d", &student.roll);
                    printf("\nEnter fee(int):");
                    scanf("%d", &student.fee);
                    printf("\nEnter month  till which Fee is paid:");
                    fflush(stdin);
                    printf("\nMonth:");
                    scanf("%2d", &month);
                    printf("\nDay:");
                    scanf("%2d", &day);
                    fflush(stdin);
                    fseek(fs, -sizeof(student), SEEK_CUR);
                    fwrite(&student, sizeof(struct studentStructure), 1, fs);
                    fclose(fs);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 3)
        {
            char program[50];
            int rollNo;
            int a = 0;
            fflush(stdin);
            printf("\nEnter New  name of the student(string): ");
            scanf("%s", student.name);
            fflush(stdin);
            printf("\n Enter new the program(string): ");
            scanf("%s", program);
            fflush(stdin);
            printf("\nEnter new Roll No.(int):");
            scanf("%d", &rollNo);

            fs = fopen("student.txt", "rb+");
            while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
            {
                a = 1;
                if (strcmpi(name, student.name) == 0 && rollNo == student.roll && strcmpi(program, student.program) == 0)
                {
                    a = 0;
                    fflush(stdin);
                    printf("\nEnter Name of the student(string): ");
                    scanf("%s", student.name);
                    fflush(stdin);
                    printf("\nEnter the program(string): ");
                    scanf("%s", student.program);
                    fflush(stdin);
                    printf("\nEnter your semester(string): ");
                    scanf("%s", student.semester);
                    fflush(stdin);
                    printf("\nEnter Roll No.(int):");
                    scanf("%d", &student.roll);
                    printf("\nEnter fee(int):");
                    scanf("%d", &student.fee);
                    printf("\nEnter month  till which Fee is paid:");
                    fflush(stdin);
                    printf("\nMonth:");
                    scanf("%2d", &month);
                    printf("\nDay:");
                    scanf("%2d", &day);
                    fflush(stdin);
                    fseek(fs, -sizeof(student), SEEK_CUR);
                    fwrite(&student, sizeof(struct studentStructure), 1, fs);
                    fclose(fs);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 4)
            // ext();
            start();
        else
        {
            printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
            system("pause");
            modifyStudent(1);
        }

        printf("\n\n Press Esc To Exit or Do you want to continue modifying records(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//--------------------------------------------------delete student---------------------------------------------
void deleteStudent()
{
    system("cls");
    printf("\n\t******************************************************************");
    printf("\n\t<<<<<<<<<<<<<<<<<<       DELETE RECORDS     >>>>>>>>>>>>>>>>>>>>>>");
    printf("\n\t******************************************************************");
    FILE *temp, *t1;
    int a = 1;
    char name[50], c = 'y';

    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        printf("\n\nEnter name of student to delete(string): ");
        fflush(stdin);
        scanf("%s", name);
        fs = fopen("student.txt", "rb");
        temp = fopen("delete.tmp", "wb"); // opening of temporary file for deleting process
        while (fread(&student, sizeof(struct studentStructure), 1, fs) == 1)
        {
            if (strcmp(student.name, name) == 0)
            {
                a = 0;
                continue;
            }
            else
            {

                fwrite(&student, sizeof(struct studentStructure), 1, temp);
            }
        }

        if (a == 1)
            printf("\n\nRECORD NOT FOUND");
        else
            printf("\n\nRECORD SUCCESSFULLY  DELETED");
        printf("\n\n");
        system("pause");
        fflush(stdin);
        fclose(fs);
        fclose(temp);
        remove("student.txt");               // remove student
        rename("delete.tmp", "student.txt"); // make tmt file as student.txt
        printf("\n\n Press Esc To Exit or Do you wish to continue deleting other records(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//###################################################| STAFF |#####################################################################
//---------------------------------------------------add staff------------------------------------------------------------------
void addStaff()
{
    float ff;
    time_t t;
    char c = 'y';
    system("cls");
    printf("\n\t   ******************************************************************");
    printf("\n\t  >>>>>>>>>>>>>>>>>>       ADD RECORDS         <<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\t   ******************************************************************");

    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        fflush(stdin);
        printf("\nEnter  Name of the staff(string): ");
        scanf("%s", staff.name);
        fflush(stdin);
        printf("\nEnter the Address(string): ");
        scanf("%s", staff.address);
        fflush(stdin);
        printf("\nEnter your Degree(string): ");
        scanf("%s", staff.degree);
        fflush(stdin);
        printf("\nEnter contact No.(int):");
        scanf("%d", &staff.contactNo);
        printf("\nEnter salary(int):");
        scanf("%d", &staff.salary);

        ft = fopen("staff.txt", "ab+"); // opening a binary file in apend mode
        fwrite(&staff, sizeof(struct staffStructure), 1, ft);
        fclose(ft);
        printf("\nRecorded Successfully !! ");

        printf("\n\nPress Esc To Exit or Do you want to continue adding records(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }

    fflush(stdin);
    printf("\n\n");
    system("pause");
}
//------------------------------------------------search staff-----------------------------------------------------------------------
void searchStaff()
{
    int a = 1, choice;
    char c = 'y';

    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        system("cls");
        printf("\n\t******************************************************************");
        printf("\n\t<<<<<<<<<<<<<<<<<<<<   SEARCH RECORDS    >>>>>>>>>>>>>>>>>>>>>>>>>");
        printf("\n\t******************************************************************");
        printf("\n\n\t\t CHOOSE SEARCH TYPE::");
        printf("\n\n\t\t1>>Search by name::");
        printf("\n\n\t\t2>>Search by address::");
        printf("\n\n\t\t3>>Search by degree::");
        printf("\n\n\t\t4>>Search by contact::");
        printf("\n\n\t\t5>>Go Back");
        printf("\n\n\t\t>>Enter Your Type:: ");
        fflush(stdin);
        scanf("%d", &choice);
        system("cls");
        if (choice == 1)
        {
            char name[50];
            a = 1;
            printf("\n\nEnter name of staff to search(string): ");
            fflush(stdin);
            scanf("%s", name);
            ft = fopen("staff.txt", "rb");
            printf("--------------staff Information------------------\n");
            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                if (strcmpi(name, staff.name) == 0)
                {
                    a = 0;
                    printf("\nName = %s", staff.name);
                    printf("\nDegree = %s", staff.degree);
                    printf("\nSubject = %s", staff.address);
                    printf("\nSalary =%d", staff.salary);
                    printf("\nContact =%d", staff.contactNo);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(ft);
        }
        else if (choice == 2)
        {
            char address[50];
            a = 1;
            printf("\n\nEnter address of staff(string): ");
            scanf("%s", address);
            ft = fopen("staff.txt", "rb");
            printf("--------------staff Information------------------\n");

            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                if (strcmpi(address, staff.address) == 0)
                {
                    a = 0;
                    printf("\nName = %s", staff.name);
                    printf("\nDegree = %s", staff.degree);
                    printf("\nSubject = %s", staff.address);
                    printf("\nSalary =%d", staff.salary);
                    printf("\nContact =%d", staff.contactNo);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(ft);
        }
        else if (choice == 3)
        {
            char degree[50];
            a = 1;
            printf("\n\nEnter degree of staff to search(string): ");
            scanf("%s", &degree);
            fflush(stdin);
            ft = fopen("staff.txt", "rb");
            printf("--------------staff Information------------------\n");

            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                if (strcmpi(degree, staff.degree) == 0)
                {
                    a = 0;
                    printf("\nName = %s", staff.name);
                    printf("\nDegree = %s", staff.degree);
                    printf("\nSubject = %s", staff.address);
                    printf("\nSalary =%d", staff.salary);
                    printf("\nContact =%d", staff.contactNo);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(ft);
        }
        else if (choice == 4)
        {
            int contact;
            a = 1;
            printf("\n\nEnter contact of staff to search(int): ");
            scanf("%d", &contact);
            fflush(stdin);
            ft = fopen("staff.txt", "rb");
            printf("--------------staff Information------------------\n");

            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                if (contact == staff.contactNo)
                {
                    a = 0;
                    printf("\nName = %s", staff.name);
                    printf("\nDegree = %s", staff.degree);
                    printf("\nSubject = %s", staff.address);
                    printf("\nSalary =%d", staff.salary);
                    printf("\nContact =%d", staff.contactNo);
                    printf("\n");
                }
            }
            if (a == 1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(ft);
        }
        else if (choice == 5)
        {
            // ext();
            start();
        }
        else
        {
            printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
            system("pause");
            searchStudent(1);
        }
        printf("\n\n Press Esc To Exit or Do you want to continue searching(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//------------------------------------------------modifiy staff----------------------------------------------------------------------
void modifyStaff()
{
    char name[50];
    int a = 1, choice;
    char c = 'y';

    while (c == 'y' || c == 'Y')
    {
        system("cls");
        printf("\n\t******************************************************************");
        printf("\n\t<<<<<<<<<<<<<<<<<<<   MODIFY RECORDS     >>>>>>>>>>>>>>>>>>>>>>>>>>");
        printf("\n\t******************************************************************");
        printf("\n\n\t\tPLEASE CHOOSE MODIFY TYPE::");
        printf("\n\n\t\t1::Modify by name::");
        printf("\n\n\t\t2::Modify by name & address::");
        printf("\n\n\t\t3::Modify by name,address & contactNo::");
        printf("\n\n\t\t4::Exit");
        printf("\n\n\t\t::Enter your choice:: ");
        fflush(stdin);
        scanf("%d", &choice);
        if (choice == 1)
        {
            int a = 0;
            printf("\n\nEnter name of staff to modify(string): ");
            fflush(stdin);
            scanf("%s", name);
            ft = fopen("staff.txt", "rb+");
            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                a = 1;
                if (strcmpi(name, staff.name) == 0)
                {
                    a = 0;
                    fflush(stdin);
                    printf("\nEnter  Name of the staff(string): ");
                    scanf("%s", staff.name);
                    fflush(stdin);
                    printf("\nEnter the Address(string): ");
                    scanf("%s", staff.address);
                    fflush(stdin);
                    printf("\nEnter your Degree(string): ");
                    scanf("%s", staff.degree);
                    fflush(stdin);
                    printf("\nEnter contact No.(int):");
                    scanf("%d", &staff.contactNo);
                    printf("\nEnter salary(int):");
                    scanf("%d", &staff.salary);
                    fflush(stdin);

                    fseek(ft, -sizeof(staff), SEEK_CUR);
                    fwrite(&staff, sizeof(struct staffStructure), 1, ft);
                    fclose(ft);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 2)
        {
            char address[50];
            int a = 0;
            printf("\n\nEnter name of staff to modify(string): ");
            fflush(stdin);
            scanf("%s", name);
            printf("\n\nEnter address no of staff (string): ");
            scanf("%s", address);

            ft = fopen("staff.txt", "rb+");
            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                a = 1;
                if (strcmpi(name, staff.name) == 0 && strcmpi(address, staff.address))
                {
                    a = 0;
                    fflush(stdin);
                    printf("\nEnter  Name of the staff(string): ");
                    scanf("%s", staff.name);
                    fflush(stdin);
                    printf("\nEnter the Address(string): ");
                    scanf("%s", staff.address);
                    fflush(stdin);
                    printf("\nEnter your Degree(string): ");
                    scanf("%s", staff.degree);
                    fflush(stdin);
                    printf("\nEnter contact No.(int):");
                    scanf("%d", &staff.contactNo);
                    printf("\nEnter salary(int):");
                    scanf("%d", &staff.salary);
                    fflush(stdin);
                    fseek(ft, -sizeof(staff), SEEK_CUR);
                    fwrite(&staff, sizeof(struct staffStructure), 1, ft);
                    fclose(ft);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 3)
        {
            char address[50];
            int contact;
            int a = 0;
            fflush(stdin);
            printf("\nEnter New  name of the student(string): ");
            scanf("%s", name);
            fflush(stdin);
            printf("\n Enter new the program(string): ");
            scanf("%s", address);
            fflush(stdin);
            printf("\nEnter new contact No.(int):");
            scanf("%d", &contact);

            ft = fopen("staff.txt", "rb+");
            while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
            {
                a = 1;
                if (strcmpi(name, staff.name) == 0 && contact == staff.contactNo && strcmpi(address, staff.address) == 0)
                {
                    a = 0;
                    fflush(stdin);
                    printf("\nEnter  Name of the staff(string): ");
                    scanf("%s", staff.name);
                    fflush(stdin);
                    printf("\nEnter the Address(string): ");
                    scanf("%s", staff.address);
                    fflush(stdin);
                    printf("\nEnter your Degree(string): ");
                    scanf("%s", staff.degree);
                    fflush(stdin);
                    printf("\nEnter contact No.(int):");
                    scanf("%d", &staff.contactNo);
                    printf("\nEnter salary(int):");
                    scanf("%d", &staff.salary);
                    fflush(stdin);
                    fseek(ft, -sizeof(staff), SEEK_CUR);
                    fwrite(&staff, sizeof(struct staffStructure), 1, ft);
                    fclose(ft);
                }
            }
            if (a == 1)
                printf("\n\nRECORDS NOT FOUND");
            else
                printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
        }
        else if (choice == 4)
            // ext();
            start();
        else
        {
            printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
            system("pause");
            modifyStudent(1);
        }

        printf("\n\n Press Esc To Exit or Do you want to continue modifying records(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//-------------------------------------------------deleteStaff-----------------------------------------------------------------------
void deleteStaff()
{
    system("cls");
    printf("\n\t******************************************************************");
    printf("\n\t<<<<<<<<<<<<<<<<<<       DELETE RECORDS     >>>>>>>>>>>>>>>>>>>>>>");
    printf("\n\t******************************************************************");
    FILE *temp1, *t2;
    int a = 1;
    char name[50], c = 'y';

    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        printf("\n\nEnter name of staff to delete(string): ");
        fflush(stdin);
        scanf("%s", name);
        ft = fopen("staff.txt", "rb");
        temp1 = fopen("deleteStaff.tmp", "wb"); // opening of temporary file for deleting process
        while (fread(&staff, sizeof(struct staffStructure), 1, ft) == 1)
        {
            if (strcmp(staff.name, name) == 0)
            {
                a = 0;
                continue;
            }
            else
            {

                fwrite(&staff, sizeof(struct staffStructure), 1, temp1);
            }
        }

        if (a == 1)
            printf("\n\nRECORD NOT FOUND");
        else
            printf("\n\nRECORD SUCCESSFULLY  DELETED");
        printf("\n\n");
        system("pause");
        fflush(stdin);
        fclose(ft);
        fclose(temp1);
        remove("staff.txt");                    // remove student
        rename("deleteStaff.tmp", "staff.txt"); // make tmt file as student.txt
        printf("\n\n Press Esc To Exit or Do you wish to continue deleting other records(press y or Y)");
        fflush(stdin);
        c = getch();
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//-------------------------------------------------salary------------------------------------------------------------------
void salary(int mm)
{
    system("cls");
    printf("\n\t******************************************************************");

    printf("\n\t<<<<<<<<<<<<<<<<<<        SALARY     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

    printf("\n\t******************************************************************");
    FILE *f, *t;
    int a = 1, day;
    char name[50], c = 'y';
    int month, dif, id;
    while (c == 'y' || c == 'Y')
    {
        int a = 1;
        fflush(stdin);
        printf("\n\nEnter name:: ");
        scanf("%[^\n]", name);
        printf("\n\nEnter ID:: ");
        scanf("%d", &id);
        f = fopen("teacher", "rb+");
        t = fopen("te", "wb+");
        while (fread(&staff, sizeof(staff), 1, f) == 1) // file opened
        {
            if (strcmp(staff.name, name) == 0) // name entered is compared to the existing name in file
            {
                float lastSalary;
                a = 0;
                printf("\n\nEnter the month & day till which salary is to be paid:: ");
                fflush(stdin);
                scanf("%d", &month);
                month = chkdat(month, day);
                staff.advance = (month - mm - 1) * staff.salary;
                if (staff.advance < 0)
                    staff.advance = 0;
                lastSalary = mm - staff.date.month; // months of salary left to be paid
                if (lastSalary < 0)
                    lastSalary = 0;
                staff.total = staff.advance + staff.salary * (1 + lastSalary);
                if (month == staff.date.month)
                    staff.total = 0;
                printf("\nmonthy salary left to be paid:: %.2f", lastSalary);
                printf("\ntotal :: %.2f", staff.total);
                printf("\nadvance :: %.2f", staff.advance);
                staff.date.month = month;
                fwrite(&staff, sizeof(staff), 1, t);
                fclose(f);
                fclose(t);

                if (a == 1)
                    printf("\n\nRECORD NOT FOUND");
                printf("\n\n");
                system("pause");
                fflush(stdin);
                system("del teacher");
                system("ren te, teacher");
            }
        }
        printf("\n\n Press Esc To Exit or Do you want to continue(press y or Y)");
        fflush(stdin);
        c = getch();
        if (c == 27)
            start();
    }
    getch();
}
//--------------------------------------------------start function-------------------------------------------------
void start()
{
    int i, j; // j is for selection of account type
    system("cls");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  |SELECT YOUR ACCOUNT|  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
    printf("\n");
    printf("\n\t\t1->> Student");
    printf("\n\t\t2->> Teacher & Staffs");
    printf("\n\t\t3->> Exit");
    printf("\n");
    printf("\n\t\t Enter Your Account Type :- ");
    fflush(stdin);
    scanf("%d", &j);
    switch (j)
    {
    case 3:
        exitNow();
        break;
    case 1:
    {
        system("cls");
        printf("\n");
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  |STUDENT ACC. MENU|  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
        printf("\n");
        printf("\n\t\t SELECT YOUR CHOICE  :");
        printf("\n\t\t1>> Add Student's Record");
        printf("\n\t\t2>> Search Student's Record");
        printf("\n\t\t3>> Modify Student's Record");
        printf("\n\t\t4>> Delete Student's Record");
        printf("\n\t\t5>> Calculate Student's Fee");
        printf("\n\t\t6>> Go Back");
        printf("\n");
        printf("\n");
        // time_t t;   //for current date and time//
        // time(&t);
        // printf("\nCurrent date and time : %s", ctime(&t)); // to display current date and time//
        printf("\n\n Enter Your Choice:-  ");
        fflush(stdin);
        scanf("%d", &i);
        system("cls");
        switch (i)
        {
        case 1:
            addStudent(); // function call
            start();
            break;
        case 2:
            searchStudent();
            start();
            break;
        case 3:
            modifyStudent();
            start();
        case 4:
            deleteStudent();
            start();
            break;
        case 5:
            fee(1);
            break;
        case 6:
            start();
            break;
        default:
        {
            printf("\n\n\tInvalid entry!!");
            printf("\n\nTo Account Type\n\n\t");
            system("pause");
            start();
        }
        }
    }
    break;
    case 2:
    {
        system("cls");
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  |STAFF ACC. MENU|  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        printf("\n\t\t SELECT YOUR CHOICE");
        printf("\n\t\t1-> Add Staff's Records");
        printf("\n\t\t2-> Search Staff's Records");
        printf("\n\t\t3-> Modify Staff's Records");
        printf("\n\t\t4-> Delete Staff's Records");
        printf("\n\t\t5-> Calculate Staff's Salary");
        printf("\n\t\t6->  Go Back");
        printf("\n");
        printf("\n");
        // time_t t;   //for current date and time//
        // time(&t);
        for (i = 0; i < 80; i++)
            printf("-");
        // printf("\nCurrent date and time : %s", ctime(&t)); // to displau current date and time//
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\n\n Enter Your Choice  ");
        fflush(stdin);
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            addStaff();
            start();
            break;
        case 2:
            searchStaff();
            start();
            break;
        case 3:
            modifyStaff();
            start();
            break;
        case 4:
            deleteStaff();
            start();
            break;
        case 5:
        // salary(mm);
        // start();
        case 6:
            start();
            break;
        default:
        {
            printf("\n\n\tInvalid Entry!!");
            printf("\n\nTo Account Type\n\n\t");
            system("pause");
            start();
        }
        }
        break;
    }
    default:
    {
        printf("\n\n\tInvalid Entry!!");
        printf("\n\nTo Account Type\n\n\t");
        system("pause");
        start();
    }
    }
}
//--------------------------------------------------main function------------------------------------------------
void main()
{
    int i, j, k;

    system("color 0");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                    \t**********************************************************\n");
    printf("                    \t*                                                        *\n");
    printf("                    \t***                WELCOME TO KCC COLLEGE              ***\n");
    printf("                    \t*                >>College Billing System<<              *\n");
    printf("                    \t*                    Putalisadak KTM                     *\n");
    printf("                    \t*                    Prepared by Group                   *\n");
    printf("                    \t*                    Tel.065478933201                    *\n");
    printf("                    \t*                                                        *\n");
    printf("                    \t**********************************************************\n");
    printf("\n");
    printf("                     \n   \t \t \t \t  ENTER ANY KEY TO CONTINUE . . ");
    printf("\n");
    getch();
    system("cls"); // clears the screen
    printf("\n");
    printf("                    \n\t\t\t ***************************************************************");
    printf("                    \n\t\t\t *                                                             *");
    printf("                    \n\t\t\t *              WELCOME TO COLLEGE BILLING SYSTEM              *");
    printf("                    \n\t\t\t *                                                             *");
    printf("                    \n\t\t\t ***************************************************************");
    printf("                               \n\t\t\t\t\t LOADING PLEASE WAIT ");
    for (i = 0; i < 3; i++)
    {

        printf(".");
        Sleep(500);
    }
    printf("\n");
    printf("\n\t\t\t\t\tENTER ANY KEY TO CONTINUE ... ");
    getch();
    system("cls");
    login();
    start();
}
