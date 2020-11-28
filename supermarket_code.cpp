
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<windows.h>
using namespace std;


    // CLASS USED IN PROJECT

    class Item_abt
    {
        int pno;
        char pname[50];
        float price, qty, tax, disc;
        public:
            void item_create()
            {
                std::cout << "\nPlease Enter The Product No. of The Product ";
                std::cin >> pno;
                std::cout << "\n\nPlease Enter The Name of The Product ";
                std::cin>>pname;
                std::cout << "\nPlease Enter The Price of The Product ";
                std::cin >> price;
                std::cout << "\nPlease Enter The Discount (%) ";
                std::cin >> disc;
            }

        void disp_all()
        {
            std::cout << "\nThe Product No. of The Product : " << pno;
            std::cout << "\nThe Name of The Product : ";
            puts(pname);
            std::cout << "\nThe Price of The Product : " << price;
            std::cout << "\nDiscount : " << disc;
        }

        int retpno()
        {
            return pno;
        }

        float retprice()
        {
            return price;
        }

        char * retpname()
        {
            return pname;
        }

        int retdisc()
        {
            return disc;
        }

    };

//***************************************************************
// global declaration of object and file object..


fstream fp;
product pr;
//***************************************************************
// function to write in file
//****************************************************************

void prod_write()
{
    fp.open("Shop.dat", std::ios::out | std::ios::app);
    pr.item_create();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    std::cout << "\n\nThe Product Has Been Created ";
    getch();
}
//***************************************************************
// function to read all records from file
//****************************************************************
void menu_()
{
    system("cls");
    std::cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", std::ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        pr.disp_all();
        std::cout << "\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n)
{
    int flag = 0;
    fp.open("Shop.dat", std::ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() == n)
        {
            system("cls");
            pr.disp_all();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        std::cout << "\n\n record not exist";
    getch();
}
//***************************************************************
// modify record of file
//****************************************************************
void item_modify()
{
    int no, found = 0;
    system("cls");
    std::cout << "\n\n\tTo Modify ";
    std::cout << "\n\n\tPlease Enter The Product No. of The Product";
    std::cin >> no;
    fp.open("Shop.dat", std::ios:: in | std::ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0)
    {
        if (pr.retpno() == no)
        {
            pr.disp_all();
            std::cout << "\nPlease Enter The New Details of Product" << std::endl;
            pr.item_create();
            long long pos = -1 * sizeof(pr);
            fp.seekp(pos, std::ios::cur);
            fp.write((char * ) & pr, sizeof(product));
            std::cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        std::cout << "\n\n Record Not Found ";
    getch();
}
//***************************************************************
// delete record of file
//****************************************************************
void item_delete()
{
    int no;
    system("cls");
    std::cout << "\n\n\n\tDelete Record";
    std::cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    std::cin >> no;
    fp.open("Shop.dat", std::ios:: in | std::ios::out);
    fstream fp2;
    fp2.open("Temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    std::cout << "\n\n\tRecord Deleted ..";
    getch();
}
//***************************************************************
//  display all products price list
//****************************************************************

void menu()
{
    system("cls");
    fp.open("Shop.dat", std::ios:: in );
    if (!fp)
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        std::cout << "\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    std::cout << "\n\n\t\tProduct MENU\n\n";
    std::cout << "====================================================\n";
    std::cout << "P.NO.\t\tNAME \t\tPRICE\n";
    std::cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product)))
    {
        std::cout << pr.retpno() << "\t\t" << pr.retpname() << "\t\t" << pr.retprice() <<std::endl;
    }
    fp.close();
}

//***************************************************************
// function to place order and generating bill for Products
//****************************************************************

void order_place()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    std::cout << "\n=============================\n";
    std::cout << "\n PLACE YOUR ORDER";
    std::cout << "\n=============================\n";
    do
    {
        std::cout << "\n\nEnter The Product No. Of The Product : ";
        std::cin >> order_arr[c];
        std::cout << "\nQuantity in number : ";
        std::cin >> quan[c];
        c++;
        std::cout << "\nDo You Want To Order Another Product ? (y/n)";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    std::cout << "\n\nThank You For Placing The Order";
    getch();
    system("cls");
    std::cout << "\n\n******************************** INVOICE ************************\n";
    std::cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";
    for(int x = 0; x <= c; x++)
    {
        fp.open("Shop.dat", std::ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == order_arr[x])
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdisc() / 100);
                std::cout << "\n" << order_arr[x] << "\t" << pr.retpname() <<
                    "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    std::cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    getch();
}

//***************************************************************
// INTRO FUNCTION
//****************************************************************

void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}


void start()
{
    system("cls");
    gotoxy(35, 11);
    std::cout << "SUPER MARKET ";
    gotoxy(35, 14);
    std::cout << "BILLING";
    gotoxy(35, 17);
    std::cout << "PROJECT";
    std::cout << "\n\nMADE BY : ISHAAN JAGGI";
    std::cout << "\n\nCOLLEGE : DELHI TECHNOLOGICAL UNIVERSITY";
    getch();

}

//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void return_to_menu()
{
    system("cls");
    char ch2;
    std::cout << "\n\n\n\tADMIN MENU";
    std::cout << "\n\n\t1.CREATE PRODUCT";
   std::cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    std::cout << "\n\n\t3.QUERY ";
    std::cout << "\n\n\t4.MODIFY PRODUCT";
    std::cout << "\n\n\t5.DELETE PRODUCT";
    std::cout << "\n\n\t6.VIEW PRODUCT MENU";
    std::cout << "\n\n\t7.BACK TO MAIN MENU";
    std::cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    ch2 = getche();
    switch (ch2)
    {
    case '1':
        system("cls");
        prod_write();
        break;
    case '2':
        menu_();
        break;
    case '3':
        int num;
        system("cls");
        std::cout << "\n\n\tPlease Enter The Product No. ";
        std::cin >> num;
        display_sp(num);
        break;
    case '4':
        item_modify();
        break;
    case '5':
        item_delete();
        break;
    case '6':
        menu();
        getch();
    case '7':
        break;
    default:
        std::cout << "\a";
        return_to_menu();
    }
}
//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
    char ch;
    start();
    do
    {
        system("cls");
        std::cout << "\n\n\n\tMAIN MENU";
        std::cout << "\n\n\t01. CUSTOMER";
        std::cout << "\n\n\t02. ADMINISTRATOR";
        std::cout << "\n\n\t03. EXIT";
        std::cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch)
        {
        case '1':
            system("cls");
            order_place();
            getch();
            break;
        case '2':
            return_to_menu();
            break;
        case '3':
            exit(0);
        default:
            std::cout << "\a";
        }
    } while (ch != '3');
}

//***************************************************************
// END OF CODE..
//***************************************************************
