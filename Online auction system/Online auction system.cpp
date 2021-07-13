#include <iostream>
#include <string>
using namespace std;
const int month_Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
struct Date
{
    int day;
    int month;
    int year;
};
struct list_item
{
    int item_no;
    string category;
    float starting_price;
    string starting_date_of_auction_process;
    string end_date;
    string status;
    float suggest;
    Date sold_date;
};
struct user_information
{
    double id;
    string email;
    string password;
    string delivery_address;
    int phone;
    int rating;//used in add point function
    string comment;//used in add point function
    int points;
    list_item list_of_items;
};
struct report//for report function
{
    string category;
    int sell_number;//include the number of sells for each category
};
struct max_sold
{
    int max_number = 0;
    string max_category;
};
//global
report sells_report[1000];//report
user_information user_info[1000] = { 0 }; //for sign up function include the user info
//for purchase function
int selected_item_number;
float suggested_price;
int accept_or_not;
//for purchase function
string email, pass; //for login function
list_item market_place[1000];// include the available items

void sign_up(); //function declaration
void login();  //function declaration
void search_items();//function declaration
void purchase();//function declaration
void suggestion();//function declaration
void add_points();//function declaration
int count_Leap_Years(Date d);//function declaration
int get_days_Difference(Date first_date, Date second_date);//function declaration
void report();//function declaration
void show_user_information();//function declaration

int main()
{
    int choice = 0;
    cout << "\t\t\t Welcome to the Online Auction System \n\n";
    cout << "choose from main menu.. if you are new to the system sign up first \n\n";
    cout << "For Sign up press 1 \n";
    cout << "For Login press 2 \n";
    cout << "For Search press 3 \n";
    cout << "For price suggestion press 4 \n";
    cout << "For showing user information and points press 5 \n";
    cout << "For showing Report about sold items and top category sold during Month press 6 \n";
    cin >> choice;
    switch (choice)
    {
    case 1: sign_up();
    case 2: login();
    case 3: search_items();
    case 4: suggestion();
    case 5: show_user_information();
    case 6: report();
    default: main();
    }
    return 0;
}
void sign_up()//function definition
{
    bool reportt = false;   //for report function
    char sign_up_again, buyer_or_seller;
    list_item list_of_items;
    for (int i = 0; i < 1000; i++)
    {
        do
        {
            cout << "welcome to sign up page \n\n";
            cout << "please enter ID \n";
            cin >> user_info[i].id;
            cout << "please enter email \n";
            cin >> user_info[i].email;
            cout << "please enter password \n";
            cin >> user_info[i].password;
            cout << "please enter delivery address \n";
            cin >> user_info[i].delivery_address;
            cout << "please enter phone number \n";
            cin >> user_info[i].phone;
            user_info[i].points = 0;

            cout << "do you have items to sell or you are a buyer \n";
            cout << "please press b if you are a buyer or s if you are a seller \n";
            cin >> buyer_or_seller;
            if (buyer_or_seller == 's' || buyer_or_seller == 'S')
            {
                cout << "please enter list of items to sell \n";
                user_info[i].list_of_items.item_no = i;
                market_place[i].item_no = user_info[i].list_of_items.item_no;
                cout << "enter category \n";
                cin >> user_info[i].list_of_items.category;
                market_place[i].category = user_info[i].list_of_items.category;

                //report
                for (int j = 0; j < 1000; j++)
                {
                    if (market_place[i].category == sells_report[j].category)
                    {
                        reportt = true;
                    }
                }
                if (reportt == false)
                {
                    sells_report[i].category = market_place[i].category;
                }
                reportt = false;
                //report

                cout << "enter starting price of the product \n";
                cin >> user_info[i].list_of_items.starting_price;
                market_place[i].starting_price = user_info[i].list_of_items.starting_price;
                cout << "enter starting date of auction process\n";
                cin >> user_info[i].list_of_items.starting_date_of_auction_process;
                market_place[i].starting_date_of_auction_process = user_info[i].list_of_items.starting_date_of_auction_process;
                cout << "enter end date of auction process \n";
                cin >> user_info[i].list_of_items.end_date;
                market_place[i].end_date = user_info[i].list_of_items.end_date;
                cout << "enter product status (available / not available)\n";
                cin >> user_info[i].list_of_items.status;
                market_place[i].status = user_info[i].list_of_items.status;
            }
            cout << "sign up again? (press 'y' to sign up again 'N' to go to login page) \n";
            cin >> sign_up_again;
            if (sign_up_again == 'y' || sign_up_again == 'Y')
                i++;
        } while (sign_up_again == 'y' || sign_up_again == 'Y');
        break;
    }
    main();
} //end of sign up function
void login() //function definition
{
    int try_again = 0;
    bool success = false;
    do
    {
        cout << "please enter email\n";
        cin >> email;
        cout << "Enter password\n";
        cin >> pass;
        for (int i = 0; i < 1000; i++)
        {
            if (email == user_info[i].email && pass == user_info[i].password)
            {
                success = true;
                cout << "successfully login \n";
            }
        }
        if (success == false)
        {
            cout << "\n wrong email or password .. please try again \n\n";
            cout << "to go to main menu press 1 , to try login again press 2\n";
            cin >> try_again;
            if (try_again == 1)
                break;
        }
    } while (success == false);
    main();
}//end login function
void search_items()//function definition
{
    char search_method; //category or price and category
    string category; //this variable is for category of category search only
    string category2;  float price1, price2; //they are for second method search with price and category
    //the price search include two prices and it will display items between the two prices
    cout << "\nif you want to search with category press 'c'\n";
    cout << "if you want to search with category and price press 'p'\n";
    cin >> search_method;

    if (search_method == 'c' || search_method == 'C')
    {
        cout << "enter category to search \n";
        cin >> category;
        for (int i = 0; i < 1000; i++)
        {
            if (category == market_place[i].category)
            {
                cout << "item number is: " << market_place[i].item_no << "\n";
                cout << "item category is: " << market_place[i].category << "\n";
                cout << "starting date of auction: " << market_place[i].starting_date_of_auction_process << "\n";
                cout << "end date of auction: " << market_place[i].end_date << "\n";
                cout << "item status is: " << market_place[i].status << "\n";
                cout << "item starting price is: " << market_place[i].starting_price << "\n";
                cout << "the id of the seller is: " << user_info[i].id << "\n";
            }//end sub if
        }//end for loop
        purchase();//here it will go to execute purchase function
    }//end if
    else if (search_method == 'p' || search_method == 'P')
    {
        cout << "enter items category\n";
        cin >> category2;
        cout << "please write your budget to start search\n";
        cout << "from: ";
        cin >> price1;
        cout << "to: ";
        cin >> price2;
        for (int i = 0; i < 1000; i++)
        {
            if (category2 == market_place[i].category && (price1 <= market_place[i].starting_price && market_place[i].starting_price <= price2))
            {
                cout << "item number is: " << market_place[i].item_no << "\n";
                cout << "item category is: " << market_place[i].category << "\n";
                cout << "starting date of auction: " << market_place[i].starting_date_of_auction_process << "\n";
                cout << "end date of auction: " << market_place[i].end_date << "\n";
                cout << "item status is: " << market_place[i].status << "\n";
                cout << "item starting price is: " << market_place[i].starting_price << "\n";
                cout << "the id of the seller is: " << user_info[i].id << "\n";
            }//end if
        }//end for
        purchase();//here it will go to execute purchase function
    }//end else if
}//end search items function
void purchase()//function definition
{
    int x;//choice
    cout << "if you agree with item price write item number\n";
    cout << "if you want to suggest another press 4444\n";
    cin >> x;
    for (int i = 0; i < 1000; i++)//as market place
    {
        if (market_place[i].item_no == x)
        {
            cout << "congratulations!\n item purchased successfully \n\n";

            //report
            for (int j = 0; j < 1000; j++)
            {
                if (sells_report[j].category == market_place[i].category)
                {
                    sells_report[j].sell_number++;
                    break;
                }
            }//end of sub for loop
            //report

            market_place[i] = { 0 };
            cout << "please enter the date of the day in (day month year)";
            cout << "with a space between them\n";
            cin >> market_place[i].sold_date.day >> market_place[i].sold_date.month >> market_place[i].sold_date.year;
            add_points();
            break;
        }//end if
        else if (x == 4444)
        {
            cout << "enter item number to suggest a price\n";
            cin >> selected_item_number;
            cout << "enter a suggested price\n";
            cin >> suggested_price;
            cout << "suggestion send successfully..waiting for owner approval\n";
            //now we have to login as seller to approve
            cout << "seller have to login now to accept or reject the suggested price \n";
            main();
        }//end else if
    }//end main for loop
    login();
}//end of purchase function
void suggestion()//function definition
{
    cout << "someone suggest a price: " << suggested_price << "\n";
    cout << "for item number: " << selected_item_number << "\n";
    cout << "if you accept this price press 1 \n";
    cout << "if you reject this price press 2 \n";
    cin >> accept_or_not;
    if (accept_or_not == 1)
    {
        for (int i = 0; i < 1000; i++)
        {
            if (market_place[i].item_no == selected_item_number)
            {

                //report
                for (int j = 0; j < 1000; j++)
                {
                    if (sells_report[j].category == market_place[i].category)
                    {
                        sells_report[j].sell_number++;
                        break;
                    }
                }//end of sub for loop
                //report
                market_place[i] = { 0 };
                cout << "please enter the date of the day in (day month year)";
                cout << "with a space between them\n";
                cin >> market_place[i].sold_date.day >> market_place[i].sold_date.month >> market_place[i].sold_date.year;
                add_points();
                break;
            }//end sub if
        }//end for
    }//end if
    main();
}//end suggestion function
void add_points()//(feedback function). function definition
{
    double id;
    cout << "please enter feedback\n";
    cout << "please enter his id\n";
    cin >> id;
    for (int i = 0; i < 1000; i++)
    {
        if (id == user_info[i].id)
        {
            cout << "enter your rating\n";
            cin >> user_info[i].rating;
            if (user_info[i].rating >= 3)
                user_info[i].points++;
            cout << "enter a comment\n";
            cin >> user_info[i].comment;
            cout << "\n\n";
            break;
        }//end if
    }//end for loop
}//end of function
void show_user_information()//function definition
{
    bool success = false;
    double id;
    string password;
    do
    {
        cout << "to show user information and points ";
        cout << "please enter user id \n";
        cin >> id;
        cout << "enter user password\n";
        cin >> password;
        for (int i = 0; i < 1000; i++)
        {
            if (id == user_info[i].id && password == user_info[i].password)
            {
                success = true;
                cout << "email: " << user_info[i].email << "\n";
                cout << "delivery address: " << user_info[i].delivery_address << "\n";
                cout << "id: " << user_info[i].id << "\n";
                cout << "password: " << user_info[i].password << "\n";
                cout << "phone number: " << user_info[i].phone << "\n";
                cout << "points: " << user_info[i].points << "\n";
                cout << "comment: " << user_info[i].comment << "\n";
            }
        }
        if (success == false)
            cout << "please try again \n";
    } while (success == false);
    main();
}
void report()//function definition
{
    max_sold maximum;
    Date report_date;
    cout << "to make a monthly report about the sold items and maximum category sold during\nthis month ";
    cout << "please enter the date of the day of this report in the form of (day month year)\n";
    cout << "with a space between them \n";
    cin >> report_date.day >> report_date.month >> report_date.year;
    for (int i = 0; i < 1000; i++)
    {
        get_days_Difference(market_place[i].sold_date, report_date);
        if (get_days_Difference(market_place[i].sold_date, report_date) <= 30)
        {
            if (sells_report[i].sell_number != 0)
            {
                cout << "for category: " << sells_report[i].category << "\n";
                cout << "number of sold items of this category is: ";
                cout << sells_report[i].sell_number;
                cout << "\n\n";
            }
        }
    }
    for (int j = 0; j < 1000; j++)
    {
        get_days_Difference(market_place[j].sold_date, report_date);
        if (get_days_Difference(market_place[j].sold_date, report_date) <= 30)
        {
            if (sells_report[j].sell_number > maximum.max_number)
            {
                maximum.max_number = sells_report[j].sell_number;
                maximum.max_category = sells_report[j].category;
            }
        }
    }
    cout << "max category sold is: " << maximum.max_category << "\n";
    cout << "and there was.. " << maximum.max_number << " ..item sold of this category\n\n";
    main();
}//end of report function
int count_Leap_Years(Date d) //function definition
{
    int years = d.year;
    if (d.month <= 2)
    {
        years = years - 1;
    }
    return years / 4 - years / 100 + years / 400;
}//end of count_Leap_Years function
int get_days_Difference(Date first_date, Date second_date) //function definition
{
    long int No1 = first_date.year * 365 + first_date.day;
    for (int i = 0; i < first_date.month - 1; i++)
    {
        No1 += month_Days[i];
    }
    No1 += count_Leap_Years(first_date);
    long int No2 = second_date.year * 365 + second_date.day;
    for (int i = 0; i < second_date.month - 1; i++)
        No2 += month_Days[i];
    No2 += count_Leap_Years(second_date);
    return (No2 - No1);
}//end of get_days_Difference function
