#include "Admin_Menu_Drinks.h"

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

Admin_Menu_Drinks::Admin_Menu_Drinks()
{
    //ctor
}

void Admin_Menu_Drinks::run()
{
    bool cont = true;
    while (cont)
    {
        system("CLS");
        cout << "======================================" << endl;
        cout << "            Manage items" << endl;
        cout << "======================================" << endl << endl;


        vector<Drink> items = _service.view_items();
        if (!items.size())
        {
            cout << "You currently have no sides in the database! Add one!" << endl;
        }
        else
        {
            cout << "List of all items in the database" << endl;

            for (unsigned int i = 0 ; i < items.size(); i++)
            {
                cout << left << "\tDrink name: " << setw(22) << items[i].get_name()  << "Shortcut: " << setw(5)  <<
                     items[i].get_identity() << "Price: " << items[i].get_price() << "Kr." << endl;
            }
            cout << endl;
        }

        cout << "Commands:" << endl;
        cout << "\t1. Add new item" << endl;
        cout << "\t2. Delete an item" << endl;

        cout << "Type in your command or type 'back' to go back to previous menu" << endl;

        cont = get_command();
    }

}

bool Admin_Menu_Drinks::get_command()
{
START:
    string input;
    cin >> input;

    if (input == "1")
    {
        add_item();
    }
    else if (input == "2")
    {
        delete_item();
    }
    else if (input == "back")
    {
        return false;
    }
    else
    {
        cout << "Invalid input, please try again" << endl;
        goto START;
    }

    return true;
}

void Admin_Menu_Drinks::add_item()
{
    bool cont = true;
    while (cont)
    {
        string name;
        char identity;
        int price;

        cout << "Adding Bottom (Type '\\' any where to cancel)"  << endl;

        while(true)
        {
            cout << "Name of Drink: ";
            cin.ignore();
            getline(cin, name);
            if (check_for_cancel(name)) break;

            cout << "Shortcut: ";
            cin >> identity;
            if (check_for_cancel(identity)) break;

            cout << "Price: ";
            cin >> price;
            if (check_for_cancel(incase_fail(price))) break;

            try
            {
                _service.add_item(Drink(name, identity, price));
                cout << "Drink has been added!" << endl;
                break;
            }
            catch (InvalidItemIdExceptions e)
            {
                cout << e.get_error() << endl;
            }
            catch (InvalidItemNameException e)
            {
                cout << e.get_error() << endl;
            }
            catch (InvalidItemPriceException e)
            {
                cout << e.get_error() << endl;
            }
        }

        char input;
        cout << "Would you like to add another item? (type 'y' for yes)" << endl;
        cin >> input;
        if (input == 'y')
        {
            cont = true;
        }
        else
        {
            system("CLS");
            cont = false;
        }
    }
}

void Admin_Menu_Drinks::delete_item()
{
    bool cont = true;
    while (cont)
    {
        string item_to_delete;
        string confirm;
        cout << "Deleting a drink (type '\\' any where to cancel):" << endl;

        while(true)
        {
            cout << "Type in the item you would like to delete" << endl;
            cin.ignore();
            getline(cin, item_to_delete);
            if (check_for_cancel(item_to_delete)) break;

            cout << "Are you sure you would like to delete the item: " << item_to_delete << "?(type 'yes' to confirm)" << endl;
            cin >> confirm;

            if (confirm == "yes")
            {
                try
                {
                    _service.delete_item(item_to_delete);
                    cout << "Item deleted successfully" << endl;
                    break;
                }
                catch(InvalidItemNameException e)
                {
                    cout << e.get_error() << endl;
                }
            }
            else
            {
                cout << "Item has not been deleted" << endl;
                break;
            }
        }

        char input;
        while (true)
        {
            cout << "\nDelete another item? ('y'): ";
            cin >> input;
            if (input == 'y')
            {
                cont = true;
                break;
            }
            else
            {
                cont = false;
                break;
            }
        }
    }
}
