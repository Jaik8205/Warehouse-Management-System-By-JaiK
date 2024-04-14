/***********************************************************************
 * Author: Jai Kumar (Jaik)
 * Date: April 15, 2024                                                     
 *                                                                  
 * Description:
 *   This program demonstrates a Warehouse Management System.
 *   You can add your warehouse Locations, Categories, and Products.
 *   You can filter them, Search your entries
 *   Manipulate many Things..!!
 * 
 * Go check out yourself..!!
 * 
 * Additional Things Needed to run this code:
 *  1. "warehouse.txt" file provided with this code.
 * 
 * You can also access all materials through:
 * https://github.com/Jaik8205/Warehouse-Management-System-By-JaiK 
 * 
 ***********************************************************************/

                                                                    /*
                                                                    All Header files are declared here
                                                                    */
#include <iostream>                                                 
#include <windows.h>
#include <cstdlib>
#include <fstream>                                                  
#include <string>
#include <set>
#include <iomanip>
#include <conio.h>


using namespace std;


const int MAX_PRODUCTS = 1000;                                      /*
                                                                    this constant is set for maximum 1000 products
                                                                    */


                                                                    /*
                                                                    Class animation has some ornamental functions
                                                                    */
class animation                                                        
    {
        public:

        void loading()
            {
                cout<<"\t\b\b\b\b\b\b\b\b\b\b | | | | | ";
                Sleep(150);
                cout<<"\b\b\b\b\b\b\b\b\b\b\b / / / / / ";
                Sleep(150);
                cout<<"\b\b\b\b\b\b\b\b\b\b\b - - - - - ";
                Sleep(150);
                cout<<"\b\b\b\b\b\b\b\b\b\b\b \\ \\ \\ \\ \\ ";
                Sleep(150);
                cout<<"\b\b\b\b\b\b\b\b\b\b\b";
            }

        void starload()
        {
            cout << "\n\n\t";

            for(int i=0;i<7;i++)
            {
                cout << " * ";
                Sleep(150);
            }
            cout<<"\n\n";
        }

        void blinkload()
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b | | | | | ";
                Sleep(100);
                
                cout<<"   RUNNING\b\b\b\b\b\b\b\b\b\b";
                Sleep(150);
                cout<<"          \b\b\b\b\b\b\b\b\b\b";
                
                cout<<"\b\b\b\b\b\b\b\b\b\b\b / / / / / ";
                Sleep(100);
                
                cout<<"   RUNNING\b\b\b\b\b\b\b\b\b\b";
                Sleep(150);
                cout<<"          \b\b\b\b\b\b\b\b\b\b";
                
                cout<<"\b\b\b\b\b\b\b\b\b\b\b - - - - - ";
                Sleep(100);
                
                cout<<"   RUNNING\b\b\b\b\b\b\b\b\b\b";
                Sleep(150);
                cout<<"          \b\b\b\b\b\b\b\b\b\b";
                    
                cout<<"\b\b\b\b\b\b\b\b\b\b\b \\ \\ \\ \\ \\ ";
                Sleep(100);
                
                cout<<"   RUNNING\b\b\b\b\b\b\b\b\b\b";
                Sleep(150);
                cout<<"          \b\b\b\b\b\b\b\b\b\b";

                cout<<"\b\b\b\b\b\b\b\b\b\b\b";

            }

        void consolecolor()
        {            
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO bufferInfo;                      // Define a structure to hold console screen buffer information
            GetConsoleScreenBufferInfo(hConsole, &bufferInfo);          // Set the background color for the entire console window
            WORD attributes = bufferInfo.wAttributes & 0xFFF0;          // Clear current background color
            SetConsoleTextAttribute(hConsole, 249);       
            system("cls");                                              // Clear the console screen
        }
    };


                                                                    /*
                                                                    here class animation is Inherited by Class WareHouse,
                                                                    
                                                                    This class contains:
                                                                        1. Add Product              :   (to add products to the warehouse)
                                                                        2. Listcities               :   (to list all the cities in which our warehouses are present)
                                                                        3. ListUniqueCategories     :   (to list all categories in which we categorize our stock)
                                                                        4. displayproductfromfile   :   (to list all the product from all the categories
                                                                                                         available in all cities)
                                                                        5. Searchproducts           :   (to search a particular product or category or city or both)
                                                                        {In Searchproducts Function Overloading is used}
                                                                    */
class WareHouse : public animation                                     
    {
        public:
            animation load;

            string FileName="warehouse";

            void addProduct(const string& city, const string& category, const string& productName, double price, int quantity, double weight) 
                {
                    string filename = FileName + ".txt";
                    ofstream file(filename, ios::app);
            
                    if (!file.is_open()) 
                        {
                            cerr << "\n\n" << "Error opening file: " << filename << endl;
                            return;
                        }
                    
                    file << city << " | " << category << " | " << productName << " | " << price << " | " << quantity << " | " << weight << endl;
                    file.close();
                }

            void countProducts(const string& filename) 
                {
                    ifstream inputFile(filename);
                
                    if (!inputFile.is_open()) 
                        {
                            cerr << "Error: Unable to open file " << filename << endl;
                            return; 
                        }

                    int ProductCount = 0;
                    string line;

                    while (getline(inputFile, line)) 
                        {
                            ProductCount++;
                        }

                    cout << ProductCount;

                    inputFile.close();
                }

            void listcities() 
                {
                    string filename = FileName + ".txt";
                    ifstream file(filename);

                    if (!file.is_open()) 
                        {
                            cerr << "\n\n" << "Error opening file: " << filename << endl;
                            return;
                        }

                    set<string> uniqueCategories;
                    string line;

                    while (getline(file, line)) 
                        {
                            stringstream ss(line);
                            string category;
                            getline(ss, category, '|');
                            uniqueCategories.insert(category);
                        }

                    file.close();

                    cout << "\n\n";
                    cout << "::TOTAL CITIES::" << endl;
                    for (const auto& category : uniqueCategories) 
                        {
                            cout << setfill('-') << setw(20) << "" << setfill(' ') << endl;
                            cout << category << endl;
                        }
                }

            void listUniqueCategories(const string& filename) 
                {
                    ifstream file(filename);

                    if (!file.is_open()) 
                        {
                            cerr << "Error opening file: " << filename << endl;
                            return;
                        }

                    set<string> uniqueCategories;
                    string line;

                    while (getline(file, line)) 
                        {
                            stringstream ss(line);
                            string city, category, productName;
                            double price;
                            int quantity;
                            double weight;
                            char delimiter;

                            if (ss >> city >> delimiter >> category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight) 
                                {
                                    uniqueCategories.insert(category);
                                }
                        }

                    file.close();

                    cout << "\n   All Categories" << endl;
                
                    for (const auto& category : uniqueCategories) 
                        {
                            cout << setfill('-') << setw(20) << "" << setfill(' ') << endl;
                            cout << setw(20) << left << category << endl;
                        }
                }

            void displayProductListFromFile(const string& filename) 
                {
                    ifstream file(filename);
                    
                    if (!file.is_open()) 
                        {
                            cerr << "\n\n" << "Error opening file: " << filename << endl;
                            return;
                        }

                    string line;
                    cout << left << setw(25) << "City" << setw(25) << "Category" << setw(30) << "Product Name" << setw(20) << "Price" << setw(15) << "Quantity" << setw(15) << "Weight" << endl;
                    
                    while (getline(file, line)) 
                        {
                            string city, category, productName;
                            double price, weight;
                            int quantity;
                            char delimiter;

                            istringstream lineStream(line);
                            lineStream >> city >> delimiter >>category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight;

                            cout << setfill('-') << setw(130) << "" << setfill(' ') << endl;
                            cout << left << setw(25) << city << setw(25) << category << setw(30) << productName << setw(20) << price << setw(15) << quantity << setw(15) << weight << endl;    
                        }

                    file.close();
                }

            void searchProducts(const string& FileName, const string& searchTerm)
                {
                    string filename = FileName + ".txt";
                    ifstream file(filename);

                    if (!file.is_open())
                        {
                            cerr << "Error opening file: " << filename << endl;
                            return;
                        }

                    bool found = false;
                    string line;

                    cout << left << setw(25) << "City" << setw(25) << "Category" << setw(30) << "Product Name" << setw(20) << "Price" << setw(15) << "Quantity" << setw(15) << "Weight" << endl;

                    while (getline(file, line)) 
                        {
                            if (line.find(searchTerm) != string::npos) 
                                {
                                    found = true;
                                    string city, category, productName;
                                    double price, weight;
                                    int quantity;
                                    char delimiter;

                                    istringstream lineStream(line);
                                    lineStream >> city >> delimiter >> category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight;

                                    cout << setfill('-') << setw(130) << "" << setfill(' ') << endl;
                                    cout << left << setw(25) << city << setw(25) << category << setw(30) << productName << setw(20) << price << setw(15) << quantity << setw(15) << weight << endl;    

                                }
                        }

                    file.close();

                    if (!found)
                        {
                            cout << "No products found matching the search term." << endl;
                        }
                }

            void searchProducts(const string& FileName, const string& searchCity, const string& searchCategory) 
                {
                    string filename = FileName + ".txt";
                    ifstream file(filename);

                    if (!file.is_open()) 
                        {
                            cerr << "Error opening file: " << filename << endl;
                            return;
                        }

                    bool found = false;
                    string line;

                    cout << left << setw(25) << "City" << setw(25) << "Category" << setw(30) << "Product Name" << setw(20) << "Price" << setw(15) << "Quantity" << setw(15) << "Weight" << endl;

                    while (getline(file, line)) 
                        {
                            string city, category, productName;
                            double price, weight;
                            int quantity;
                            char delimiter;

                            istringstream lineStream(line);
                            lineStream >> city >> delimiter >> category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight;

                            bool cityMatch = searchCity.empty() || city == searchCity;
                            bool categoryMatch = searchCategory.empty() || category == searchCategory;

                            if (cityMatch && categoryMatch) 
                                {
                                    found = true;
                                    cout << setfill('-') << setw(130) << "" << setfill(' ') << endl;
                                    cout << left << setw(25) << city << setw(25) << category << setw(30) << productName << setw(20) << price << setw(15) << quantity << setw(15) << weight << endl;
                                }
                        }

                    file.close();

                    if (!found) 
                        {
                            cout << "No products found matching the search criteria." << endl;
                        }
                }

    };


                                                                    /*
                                                                    this Class Revenue tells us about the money earned by storing the products and the 
                                                                    charging criteria is by charging products using their weight
                                                                    
                                                                    This Class contains:
                                                                        1.AllWeight             :   (to display total weight of all products (quantity * WeightPerProduct)
                                                                                                    and then adding them and multiplying them with a default WeightPerKg value 
                                                                                                    which can also be changed)
                                                                        2. WeightPerCategory    :   to display weight stored in each category
                                                                        3. WeightPerCity        :   to display weight stored in each city   
                                                                    */
class Revenue
{
    public:        
    double TotalWeight;
    double TotalWeightCategory;
    double TotalWeightCity;
    
        float AllWeight(const string& filename) 
            {
                ifstream file(filename);
                
                if (!file.is_open()) 
                    {
                        cerr << "\n\n" << "Error opening file: " << filename << endl;
                        return 0;
                    }

                string line;
                
                while (getline(file, line)) 
                    {
                        string city, category, productName;
                        double price, weight;
                        int quantity;
                        char delimiter;

                        istringstream lineStream(line);
                        lineStream >> city >> delimiter >>category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight;

                        TotalWeight+=weight*quantity;    
                    }

                return TotalWeight;

                file.close();

            }

        float WeightPerCategory(const string& FileName, const string& searchTerm)
            {
                TotalWeightCategory=0;
                string filename = FileName + ".txt";
                ifstream file(filename);

                if (!file.is_open())
                    {
                        cerr << "Error opening file: " << filename << endl;
                        return 0.0f;
                    }

                bool found = false;
                string line;


                while (getline(file, line)) 
                    {
                        if (line.find(searchTerm) != string::npos) 
                            {
                                found = true;
                                string city, category, productName;
                                double price, weight;
                                int quantity;
                                char delimiter;

                                istringstream lineStream(line);
                                lineStream >> city >> delimiter >> category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight;
    
                                TotalWeightCategory+=quantity*weight;

                            }
                    }

                    return TotalWeightCategory;
                file.close();

                if (!found)
                    {
                        cout << "Nothing found matching the search term." << endl;
                    }     
            }     

        float WeightPerCity(const string& FileName, const string& searchTerm)
            {
                TotalWeightCity=0;
                string filename = FileName + ".txt";
                ifstream file(filename);

                if (!file.is_open())
                    {
                        cerr << "Error opening file: " << filename << endl;
                        return 0.0f;
                    }

                bool found = false;
                string line;


                while (getline(file, line)) 
                    {
                        if (line.find(searchTerm) != string::npos) 
                            {
                                found = true;
                                string city, category, productName;
                                double price, weight;
                                int quantity;
                                char delimiter;

                                istringstream lineStream(line);
                                lineStream >> city >> delimiter >> category >> delimiter >> productName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight;
    
                                TotalWeightCity+=quantity*weight;

                            }
                    }

                    return TotalWeightCity;
                file.close();

                if (!found)
                    {
                        cout << "Nothing found matching the search term." << endl;
                    }     
            }     


};


                                                                    /*
                                                                    here class WareHouse is Inherited by class Manageproduct,
                                                                    
                                                                    This class Contains:
                                                                        1. changeprice  :   (to change the price of a product)
                                                                        2. displayproducts  :   (to show details of a particular product)
                                                                        3. changequanity    :   (to change quantity of a product)

                                                                    This class depicts that warehouses are constantly Importing and Exporting products        
                                                                    */
class ManageProduct: public WareHouse
    {
        public:

            void changePrice(const string& filename, const string& productName, double newPrice) 
                {
                    ifstream inFile(filename);
                    if (!inFile.is_open()) 
                        {
                            cerr << "\nError opening file: " << filename << endl;
                            return;
                        }

                    ofstream tempFile("temp.txt");
                    
                    if (!tempFile.is_open()) 
                        {
                            cerr << "\nError creating temporary file.\n" << endl;
                            inFile.close();
                            return;
                        }

                    bool found = false;
                    string line;
                    
                    while (getline(inFile, line)) 
                        {
                            string entryCity, entryCategory, entryProductName;
                            double price;
                            int quantity;
                            double weight;
                            char delimiter;

                            stringstream ss(line);
                        
                            if (ss >> entryCity >> delimiter >> entryCategory >> delimiter >> entryProductName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight) 
                                {
                                    if (entryProductName == productName) 
                                        {
                                            found = true;
                                            
                                            cout << setfill('-') << setw(15) << "" << setfill(' ') << endl;
                                            cout << "\nProduct details before updating price:" << endl;
                                            cout << endl;
                                            cout << setw(15) << left << "City:" << setw(15) << left << entryCity << endl;
                                            cout << setw(15) << left << "Category:" << setw(15) << left << entryCategory << endl;
                                            cout << setw(15) << left << "Product Name:" << setw(15) << left << entryProductName << endl;
                                            cout << setw(15) << left << "Price:" << setw(15) << left << price << endl;
                                            cout << setw(15) << left << "Quantity:" << setw(15) << left << quantity << endl;
                                            cout << setw(15) << left << "Weight:" << setw(15) << left << weight << endl;
                                            cout << endl;

                                            double confirmedPrice;
                                            cout << "\nEnter the new price for the product: ";
                                            cin >> confirmedPrice;

                                            char confirm;
                                            cout << "\nAre you sure you want to change the price? (Y/N): ";
                                            confirm=_getch();

                                            if (confirm == 'Y' || confirm == 'y') 
                                                {
                                                    price = confirmedPrice;
                                                    system("cls");
                                                    cout << "\n-->Price updated successfully.<--\n" << endl;
                                                } 
                                            else 
                                                {
                                                    system("cls");
                                                    cout << "\n-->Price change canceled.<--\n" << endl;
                                                }
                                        }
                        
                                    tempFile << entryCity << " | " << entryCategory << " | " << entryProductName << " | " << price << " | " << quantity << " | " << weight << endl;
                                }

                        }

                    inFile.close();
                    tempFile.close();

                    if (!found) 
                        {
                            cerr << "\n\nProduct not found." << endl;
                            remove("temp.txt");
                            return;
                        }

                    if (remove(filename.c_str()) != 0) 
                        {
                            cerr << "\n\nError removing original file." << endl;
                            return;
                        }

                    if (rename("temp.txt", filename.c_str()) != 0) 
                        {
                            cerr << "\n\nError renaming temporary file." << endl;
                            return;
                        }
                }

            void displayProductDetails(const string& filename, const string& productName) 
                {
                    ifstream inFile(filename);
                    if (!inFile.is_open()) 
                        {
                            cerr << "\n\nError opening file: " << filename << endl;
                            return;
                        }

                    bool found = false;
                    string line;
                    
                    cout << "\nDetails for product '" << productName << "':" << endl;

                    while (getline(inFile, line)) 
                        {
                            string entryCity, entryCategory, entryProductName;
                            double price;
                            int quantity;
                            double weight;
                            char delimiter;

                            stringstream ss(line);
                        
                            if (ss >> entryCity >> delimiter >> entryCategory >> delimiter >> entryProductName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight) 
                                {
                                    if (entryProductName == productName) 
                                        {
                                            found = true;
                                            
                                            cout << "\n";
                                            
                                            cout << setfill('-') << setw(15) << "" << setfill(' ') << endl;

                                            cout << setw(15) << left << "City:" << setw(15) << left << entryCity << endl;
                                            cout << setw(15) << left << "Category:" << setw(15) << left << entryCategory << endl;
                                            cout << setw(15) << left << "Product Name:" << setw(15) << left << entryProductName << endl;
                                            cout << setw(15) << left << "Price:" << setw(15) << left << price << endl;
                                            cout << setw(15) << left << "Quantity:" << setw(15) << left << quantity << endl;
                                            cout << setw(15) << left << "Weight:" << setw(15) << left << weight << endl;
                                            cout << endl;

                                        }
                                }
                        }

                    inFile.close();

                    if (!found) 
                        {
                            cerr << "Product not found." << endl;
                        }
                }

            void changeQuantity(const string& filename, const string& productName, int newQuantity) 
                {
                    ifstream inFile(filename);
                    if (!inFile.is_open()) 
                        {
                            cerr << "\n\nError opening file: " << filename << endl;
                            return;
                        }

                    ofstream tempFile("temp.txt");
                    
                    if (!tempFile.is_open()) 
                        {
                            cerr << "\n\nError creating temporary file." << endl;
                            inFile.close();
                            return;
                        }

                    bool found = false;
                    string line;
                    
                    while (getline(inFile, line)) 
                        {
                            string entryCity, entryCategory, entryProductName;
                            double price;
                            int quantity;
                            double weight;
                            char delimiter;

                            stringstream ss(line);
                        
                            if (ss >> entryCity >> delimiter >> entryCategory >> delimiter >> entryProductName >> delimiter >> price >> delimiter >> quantity >> delimiter >> weight) 
                                {
                                    if (entryProductName == productName) 
                                        {
                                            found = true;
                                    
                                            cout << "\nProduct details before updating quantity:" << endl;
                                    
                                            cout << setfill('-') << setw(15) << "" << setfill(' ') << endl;

                                            cout << endl;
                                            cout << setw(15) << left << "City:" << setw(15) << left << entryCity << endl;
                                            cout << setw(15) << left << "Category:" << setw(15) << left << entryCategory << endl;
                                            cout << setw(15) << left << "Product Name:" << setw(15) << left << entryProductName << endl;
                                            cout << setw(15) << left << "Price:" << setw(15) << left << price << endl;
                                            cout << setw(15) << left << "Quantity:" << setw(15) << left << quantity << endl;
                                            cout << setw(15) << left << "Weight:" << setw(15) << left << weight << endl;
                                            cout << endl;

                                            
                                            int confirmedQuantity;
                                            cout << "\nEnter the new quantity for the product: ";
                                            cin >> confirmedQuantity;

                                            char confirm;
                                            cout << "\nAre you sure you want to change the quantity? (Y/N): ";
                                            confirm=_getch();

                                            if (confirm == 'Y' || confirm == 'y') 
                                                {
                                                    quantity = confirmedQuantity;
                                                    system("cls");
                                                    cout << "\nQuantity updated successfully.\n" << endl;
                                                } 
                                            else 
                                                {
                                                    system("cls");
                                                    cout << "\nQuantity change canceled.\n" << endl;
                                                }
                                        }
                            
                                    tempFile << entryCity << " | " << entryCategory << " | " << entryProductName << " | " << price << " | " << quantity << " | " << weight << endl;
                                }
                        }

                    inFile.close();
                    tempFile.close();

                    if (!found) 
                        {
                            cerr << "Product not found." << endl;
                            remove("temp.txt");
                            return;
                        }

                    if (remove(filename.c_str()) != 0) 
                        {
                            cerr << "\nError removing original file.\n" << endl;
                            return;
                        }

                    if (rename("temp.txt", filename.c_str()) != 0) 
                        {
                            cerr << "\nError renaming temporary file.\n" << endl;
                            return;
                        }
                }

    };


                                                                    /*
                                                                    This class consists of all menus used throughout the program

                                                                    This class contains:
                                                                        1. MainMenu
                                                                        2. ManageMenu
                                                                        3. FilterMenu
                                                                        4. RevenueMenu
                                                                    */
class Menu
    {
        public:
            
            void MainMenu()
                {
                    cout << "\n\n";
                    cout << "1. Add Product\n";
                    cout << "2. List All Cities\n";
                    cout << "3. List All Categories\n";
                    cout << "4. List All Products\n";
                    cout << "5. Filter Products\n";
                    cout << "6. Manage Product\n";
                    cout << "7. Revenue Management\n";
                    cout << "8. Total Products\n";
                    cout << "0. Exit Program\n";
                }

            void ManageMenu()
                {
                    cout << "1. Change Price\n";
                    cout << "2. Change Quantity\n";
                    cout << "3. Display Each Product Details\n";
                    cout << "0. Return to Main Menu\n";
                }

            void FilterMenu()
                {
                    cout << "\n\n";
                    cout << "1. Filter By Name\n";
                    cout << "2. Filter By Category\n";
                    cout << "3. Filter By City\n";    
                    cout << "4. Filter By City and Category\n";    
                    cout << "0. Return To Main Menu\n";
                }
            
            void RevenueMenu()
                {
                    cout << "\n\n";
                    cout << "1. Total Revenue Generated\n";
                    cout << "2. Revenue per Category\n";
                    cout << "3. Revenue per City\n";
                    cout << "0. Return To Main Menu\n";
                }
    };


                                                                    /*
                                                                    This is the main function in which whole code will run

                                                                    Main function contains:
                                                                        All the switches and nested switches to run the menus inside a do while loop 
                                                                        to mimic a forever runnig program
                                                                    */
int main()
    {
        animation load;
        Menu menu;
        Revenue money;
        WareHouse warehouse;               

        load.consolecolor();
        
        int option;   

        do 
            {
                menu.MainMenu();

                
                cout << "\n->Enter Your Choice: ";
                option=_getch()-'0';

                cout << "\n\n";


                switch (option) 
                    {

                        case 1:
                            {
                                int numProducts;
                                
                                system("cls");

                                cout << "Enter the number of products to add to the warehouse: ";
                                cin >> numProducts;
                                cin.ignore(); 

                                for (int i = 0; i < numProducts; ++i) 
                                    {
                                        string city, category, productName;
                                        double price, weight;
                                        int quantity;

                                        cout << "\n\nProduct " << i + 1 << ": ";
                                        cout << "\nCity: ";
                                        getline(cin, city);
                                        cout << "\nCategory: ";
                                        getline(cin, category);
                                        cout << "\nProduct Name: ";
                                        getline(cin, productName);
                                        cout << "\nPrice: ";
                                        cin >> price;
                                        cout << "\nQuantity: ";
                                        cin >> quantity;
                                        cout << "\nWeight (in kg): ";
                                        cin >> weight;
                                        cin.ignore(); 
                                        warehouse.addProduct(city, category, productName, price, quantity, weight);

                                        system("cls");
                                        cout << "\n\n-->Product added Successfully<--\n\n";
                                    }
                            
                                break;
                            }

                        case 2:
                            {
                                system("cls");  
                                warehouse.listcities();
                                break;
                            }
                        
                        case 3:
                            {
                                system("cls");
                                string filename = warehouse.FileName+".txt";
                                warehouse.listUniqueCategories(filename);
                                break;
                            }

                        case 4:
                            {
                                system("cls");
                                string filename = warehouse.FileName+".txt";
                                warehouse.displayProductListFromFile(filename);
                                break;
                            }

                        case 5:
                            {
                                system("cls");
                                int option2;
                                string searchItem; 

                                do
                                    {

                                        menu.FilterMenu();

                                        cout << "\n->Enter Your Choice: ";
                                        option2= _getch()-'0';                          

                                        switch(option2)
                                            {
                                                case 1:
                                                    {              
                                                        
                                                        system("cls");
                                                        cout<<"\n\nFilter The Product By Name: ";
                                                        cin>>searchItem;        
                                                        warehouse.searchProducts(warehouse.FileName, searchItem);
                                                        break;
                                                    }

                                                case 2:
                                                    {   
                                                        
                                                        system("cls");           
                                                        cout<<"\n\nFilter The Product By Category: ";
                                                        cin>>searchItem;        
                                                        warehouse.searchProducts(warehouse.FileName, searchItem);
                                                        break;
                                                    }
                                                
                                                case 3:
                                                    {   
                                                        
                                                        system("cls");           
                                                        cout<<"\n\nFilter The Product By City: ";
                                                        cin>>searchItem;        
                                                        warehouse.searchProducts(warehouse.FileName, searchItem);
                                                        break;
                                                    }

                                                case 4:
                                                    {
                                                        system("cls");
                                                        string searchCity;
                                                        string searchCategory;

                                                        cout<<"\n\nEnter City Name: ";
                                                        cin>>searchCity;
                                                        cout<<"\n\nEnter Category Name: ";
                                                        cin>>searchCategory;
                                                        
                                                        warehouse.searchProducts(warehouse.FileName, searchCity, searchCategory);  
                                                        break;
                                                    }

                                                case 0:
                                                    {
                                                        system("cls");
                                                        load.starload();                                             
                                                        system("cls");
                                                        break;
                                                    }
                                                
                                            }

                                    }
                                while(option2!=0);
                                break;
                            }

                        case 6:
                            {
                                system("cls");
                                ManageProduct manage;
                                string productName;
                                int option2;
                            
                                do 
                                    {
                                        string productName;
                                        string File = manage.FileName + ".txt";
                                        
                                        menu.ManageMenu();

                                        cout << "\n->Enter Your Choice: ";
                                        option2=_getch()-'0';
                                        system("cls");

                                        switch(option2)
                                            {
                                                                           
                                                case 1:
                                                    {
                                                        double newPrice;

                                                        cout << "\nName of Product to be Modified: ";
                                                        cin >> productName;

                                                        manage.changePrice(File, productName, newPrice);
                                                        break;
                                                    }

                                                case 2:
                                                    {
                                                        double newQuantity;

                                                        cout << "\nName of Product to be Modified: ";
                                                        cin >> productName;

                                                        manage.changeQuantity(File, productName, newQuantity);
                                                        break;                                                                                                     
                                                    }

                                                case 3:

                                                    {
                                                        cout << "\nName of Product to be Modified: ";
                                                        cin >> productName;
                                                     
                                                        manage.displayProductDetails(File, productName);
                                                        break;
                                                    }
                                                
                                                case 0:
                                                    {
                                                        load.starload();
                                                        system("cls");
                                                    }
                                                
                                            }                                        
                                    }
                                while(option2!=0);
                                break;
                            }

                        case 7:
                            {
                                double PrintTotalWeight;
                                double PrintTotalWeightCategory;
                                double PrintTotalWeightCity;
                                int choice;
                                
                                do
                                {
                                    system("cls");
                                    menu.RevenueMenu();

                                    cout << "\nEnter Your Choice: ";
                                    choice=_getch()-'0';

                                    system("cls");

                                    switch(choice)
                                    {
                                        
                                        case 1:
                                            {      
                                                int WeightPerKg=386;
                                                char WeightOption;

                                                string filename = warehouse.FileName+".txt";
                                                
                                                PrintTotalWeight=money.AllWeight(filename);
                                                
                                                do
                                                    {

                                                        cout << "\nTotal Weight: ";
                                                        cout << PrintTotalWeight << " Kg" << endl;
                                                        cout << "\nPrice Per Kg: ";
                                                        cout << "Rs." << fixed << setprecision(0) << WeightPerKg << endl;

                                                        for(int i=0;i<2;i++)
                                                            {
                                                                load.blinkload();
                                                            }

                                                        cout << "\nTotal Revenue: Rs.";
                                                        cout << PrintTotalWeight*WeightPerKg << endl;

                                                        cout << "\nDo you want to Change Default Price(y/n)\n";
                                                        WeightOption=_getch();
                                                        
                                                        if(WeightOption=='y')
                                                            {
                                                                cout << "\nEnter New Price Per (KG): ";
                                                                cin >> WeightPerKg;
                                                                
                                                                system("cls");
                                                            }
                                                        system("cls");

                                                    } 
                                                while (WeightOption!='n');
                                                break;
                                            }

                                        case 2:
                                            {
                                                int WeightPerKg=386;
                                                char WeightOption;

                                                string searchItem;
                                                
                                                cout << "\nEnter Category Name: ";
                                                cin >> searchItem;        
                                                string filename = warehouse.FileName;
                                                
                                                PrintTotalWeightCategory=money.WeightPerCategory(filename,searchItem);

                                                do
                                                    {

                                                        cout << "\nTotal Weight: ";
                                                        cout << PrintTotalWeightCategory << " Kg" << endl;
                                                        cout << "\nPrice Per Kg: ";
                                                        cout << "Rs." << fixed << setprecision(0) << WeightPerKg << endl;

                                                        for(int i=0;i<2;i++)
                                                            {
                                                                load.blinkload();
                                                            }
                                                        
                                                        cout << "\nTotal Revenue: Rs.";
                                                        cout << PrintTotalWeightCategory*WeightPerKg << endl;

                                                        cout << "\nDo you want to Change Default Price(y/n)\n";
                                                        WeightOption=_getch();
                                                        
                                                        if(WeightOption=='y')
                                                            {
                                                                cout << "\nEnter New Price Per (KG): ";
                                                                cin >> WeightPerKg;
                                                                
                                                                system("cls");
                                                            }
                                                        system("cls");

                                                    } 
                                                while (WeightOption!='n');
                                                break;
                            
                                            }

                                        case 3:
                                            {      
                                                int WeightPerKg=386;
                                                char WeightOption;

                                                string searchItem;

                                                cout << "\nEnter City Name: ";
                                                cin >> searchItem;        
                                                string filename = warehouse.FileName;

                                                PrintTotalWeightCity=money.WeightPerCity(filename,searchItem);
                                                
                                                do
                                                    {

                                                        cout << "\nTotal Weight: ";
                                                        cout << PrintTotalWeightCity << " Kg" << endl;
                                                        cout << "\nPrice Per Kg: Rs.";
                                                        cout << "Rs." << fixed << setprecision(0) << WeightPerKg << endl;

                                                        for(int i=0;i<2;i++)
                                                            {
                                                                load.blinkload();
                                                            }
                                                            
                                                        cout << "\nTotal Revenue: ";
                                                        cout << long (PrintTotalWeightCity*WeightPerKg) << endl << endl;

                                                        cout << "\nDo you want to Change Default Price(y/n)\n";
                                                        WeightOption=_getch();
                                                        
                                                        if(WeightOption=='y')
                                                            {
                                                                cout << "\nEnter New Price Per (Kg): ";
                                                                cin >> WeightPerKg;
                                                                
                                                                system("cls");
                                                            }
                                                        system("cls");

                                                    } 
                                                while (WeightOption!='n');
                                                break;
                                            }
                                        
                                        case 0:
                                            {
                                                load.starload();
                                                system("cls");
                                            }
                                    }
                                } 
                                while (choice!=0);
                                break;
                                
                            }

                        case 8:
                            {
                                system("cls");
                                string filename=warehouse.FileName+".txt";
                                cout << endl << setfill('-') << setw(45) << "" << setfill(' ') << endl;
                                cout << "Total Products In Our All WareHouses: ";
                                warehouse.countProducts(filename);  
                                cout << endl << setfill('-') << setw(45) << "" << setfill(' ') << endl;
                                cout << "\n";
                                break;
                            }
                        
                        case 0:
                            {
                                system("cls");
                                cout << "/|||||||||||\\\n";
                                cout << "|| Exiting ||\n";
                                cout << "\\|||||||||||/\n\n";

                                for(int i=0;i<2;i++)
                                    {
                                        load.loading();
                                    }
                                
                                system("cls");

                                return 0;
                            }
                        
                        default:
                            cout << "Invalid choice\n";
                    }
                            
            }
        while(option!=0);

        return 0;
    }
