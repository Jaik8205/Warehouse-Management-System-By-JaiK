#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

const int MAX_PRODUCTS = 1000; 

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
            attributes |= BACKGROUND_INTENSITY;                         // Set new background color
            SetConsoleTextAttribute(hConsole, attributes);                 
            system("cls");                                              // Clear the console screen
        }
    };


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
                    cout << "Unique categories in the warehouse\n::CATEGORIES::" << endl;
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

    };


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
                                            cin >> confirm;

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
                                            cin >> confirm;

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


int main()
    {
        animation load;
        Menu menu;
        Revenue money;

        load.consolecolor();
        
        int option;   

        do 
            {
                menu.MainMenu();

                
                cout << "\n->Enter Your Choice: ";
                cin >> option;

                cout << "\n\n";
                cin.ignore(); 

                WareHouse warehouse;               

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
                                        cin >> option2; 

                                        switch(option2)
                                            {
                                                case 1:
                                                    {              
                                                        cout<<"\n\nFilter The Product By Name: ";
                                                        cin>>searchItem;        
                                                        warehouse.searchProducts(warehouse.FileName, searchItem);
                                                        break;
                                                    }

                                                case 2:
                                                    {              
                                                        cout<<"\n\nFilter The Product By Category: ";
                                                        cin>>searchItem;        
                                                        warehouse.searchProducts(warehouse.FileName, searchItem);
                                                        break;
                                                    }
                                                
                                                case 3:
                                                    {              
                                                        cout<<"\n\nFilter The Product By City: ";
                                                        cin>>searchItem;        
                                                        warehouse.searchProducts(warehouse.FileName, searchItem);
                                                        break;
                                                    }

                                                case 0:
                                                    {
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
                                        cin >> option2;     

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
                                    menu.RevenueMenu();

                                    cout << "Enter Your Choice: ";
                                    cin >> choice;

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

                                                        cout << "Total Weight: ";
                                                        cout << PrintTotalWeight << endl;
                                                        cout << "Price Per Kg: ";
                                                        cout << WeightPerKg << "Kg" << endl;

                                                        for(int i=0;i<2;i++)
                                                            {
                                                                load.blinkload();
                                                            }

                                                        cout << "Total Revenue: ";
                                                        cout << PrintTotalWeight*WeightPerKg << endl;

                                                        cout << "Do you want to Change Default Price(y/n)\n";
                                                        cin >> WeightOption;
                                                        
                                                        if(WeightOption=='y')
                                                            {
                                                                cout << "Enter New Price Per (KG): ";
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
                                                
                                                cout << "Enter Category Name: ";
                                                cin >> searchItem;        
                                                string filename = warehouse.FileName;
                                                
                                                PrintTotalWeightCategory=money.WeightPerCategory(filename,searchItem);

                                                do
                                                    {

                                                        cout << "Total Weight: ";
                                                        cout << PrintTotalWeightCategory << endl;
                                                        cout << "Price Per Kg: ";
                                                        cout << WeightPerKg << " Kg" << endl;

                                                        for(int i=0;i<2;i++)
                                                            {
                                                                load.blinkload();
                                                            }
                                                        
                                                        cout << "Total Revenue: ";
                                                        cout << PrintTotalWeightCategory*WeightPerKg << endl;

                                                        cout << "Do you want to Change Default Price(y/n)\n";
                                                        cin >> WeightOption;
                                                        
                                                        if(WeightOption=='y')
                                                            {
                                                                cout << "Enter New Price Per (KG): ";
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

                                                cout << "Enter City Name: ";
                                                cin >> searchItem;        
                                                string filename = warehouse.FileName;

                                                PrintTotalWeightCity=money.WeightPerCity(filename,searchItem);
                                                
                                                do
                                                    {

                                                        cout << "Total Weight: ";
                                                        cout << PrintTotalWeightCity << endl;
                                                        cout << "Price Per Kg: ";
                                                        cout << WeightPerKg << "Kg" << endl << endl;

                                                        for(int i=0;i<2;i++)
                                                            {
                                                                load.blinkload();
                                                            }
                                                            
                                                        cout << "Total Revenue: ";
                                                        cout << long (PrintTotalWeightCity*WeightPerKg) << endl << endl;

                                                        cout << "Do you want to Change Default Price(y/n)\n";
                                                        cin >> WeightOption;
                                                        
                                                        if(WeightOption=='y')
                                                            {
                                                                cout << "Enter New Weight: ";
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
