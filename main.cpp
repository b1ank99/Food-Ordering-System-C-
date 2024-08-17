// STLs
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <unistd.h>
//Header files
#include "Food struct.h"
#include "Western.h"
#include "Japanese.h"
#include "Chinese.h"
#include "Malay.h"
#include "Arabic.h"
#include "user.h"
#include "Customer.h"
#include "Rider.h"
#include "Order.h"
#include "orderDetails.h"

using namespace std;

//Read and write Files
foodInfo readCSV_FOOD(const string& filename){
    ifstream file(filename);
    vector<vector<string>> details;
    vector<vector<string>> preList;

    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        foodInfo Details = {};
        return Details;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> values;
        vector<string> pre;
        int i = 1;
        while (getline(ss, value, ',')) {
            if(i<5)
                values.push_back(value);
            else
                pre.push_back(value);
            ++i;
        }

        details.push_back(values);
        preList.push_back(pre);
    }
    foodInfo Details = {details, preList};
    file.close();
    return Details;
}

vector<string> readUniqueId(const string& filename){
    ifstream file(filename);
    vector<string> values;
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return values;
    }
    string line;
    if(getline(file, line))
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            values.push_back(value);
        }
    }

    file.close();
    return values;
}

void writeUniqueId(const string& filename, vector<string> allId){
    ofstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << std::endl;
        return;
    }
    file << "unique ID";
    file << "\n";
    for(auto& id : allId){
        file << id;
        file << "\n";
    }
    file.close();
}

vector<vector<string>> readCSV(const string& filename) {
    ifstream file(filename);
    string value;
    vector<string> values;
    vector<vector<string>> info;

    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return info;
    }
    string line;
    if(getline(file, line))
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> values;
        while (getline(ss, value, ',')) {
            values.push_back(value);
        }

        info.push_back(values);
    }

    file.close();
    return info;
}

vector<Customer> rewriteCustomer(const string& filename, Customer c, vector<Customer> customerList, vector<Rider> riderList){
    for(auto& cus : customerList){
        if(c.getUserId() == cus.getUserId()){
            cus.setPoints(c.getPoints());
        }
    }
    ofstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << std::endl;
        return customerList;
    }
    file << "Users";
    file << "\n";
    for(auto& cus : customerList){
        file << cus.getUserName();
        file << ",";
        file << cus.getUserId();
        file << ",";
        file << cus.getUserStatus();
        file << ",";
        file << cus.getUserPassword();
        file << ",";
        file << cus.getAddress();
        file << ",";
        file << cus.getDistance();
        file << ",";
        file << cus.getPoints();
        file << "\n";
    }
    for(auto& rid : riderList){
        file << rid.getUserName();
        file << ",";
        file << rid.getUserId();
        file << ",";
        file << rid.getUserStatus();
        file << ",";
        file << rid.getTransport();
        file << ",";
        file << rid.getColor();
        file << ",";
        file << rid.getPlate();
        file << "\n";
    }


    file.close();
    return customerList;
}

//check input validation
void digitInputValidation(int n, int min, int max){
    // (Singh, 2016)
    // check if inputs are digit (Pai, 2015)
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        string msg = "Please enter digits.";
        throw msg;
    }
    if(n<min || n>max){
        string msg = "Out of range";
        throw msg;
    }
}

void cardNumberValidtion(string number){
    string msg = "Invalid card number";
    if(number.size()!=19)
        throw msg;
        // xxxx-xxxx-xxxx-xxxx
    for(int i = 0; i<19; i++){
        if(i == 4 || i == 9 || i == 14){
            if(number[i] != '-'){
                throw msg;
            }
        }
        else{
            if(!isdigit(number[i])){
                throw msg;
            }
        }
    }
}

void cardExpiryValidtion(string number){
    string msg = "Invalid Date";
    if(number.size()!=5)
        throw msg;
        // MM/YY
    for(int i = 0; i<5; i++){
        if(i == 2){
            if(number[i] != '/'){
                throw msg;
            }
        }
        else{
            if(!isdigit(number[i])){
                throw msg;
            }
        }
    }
    if(stoi(number.substr(0,2)) > 12 || stoi(number.substr(0,2))<1){
        throw msg;
    }
    if(stoi(number.substr(3,2))<24){
        throw msg;
    }
}

void securityCodeValidtion(string number){
    string msg = "Invalid code";
    if(number.size()!=3)
        throw msg;
        // xxx
    for(int i = 0; i<3; i++){
        if(!isdigit(number[i])){
            throw msg;
        }
    }
}

void walletNumberValidtion(string number){
    string msg = "Invalid wallet number";
    if(number.size()!=11)
        throw msg;
        // xxx-xxxxxxx
    for(int i = 0; i<11; i++){
        if(i == 3){
            if(number[i] != '-'){
                throw msg;
            }
        }
        else{
            if(!isdigit(number[i])){
                throw msg;
            }
        }
    }
}

void walletPinValidtion(string number){
    string msg = "Invalid pin";
    if(number.size()!=6)
        throw msg;
        // xxxxxx
    for(int i = 0; i<6; i++){
        if(!isdigit(number[i])){
            throw msg;
        }
    }
}

void ratingValidtion(string number){
    string msg = "Invalid input";
    for(int i = 0; i<number.size(); i++){
        if(!isdigit(number[i])){
            throw msg;
        }
    }
    if(stoi(number) < 1 || stoi(number) > 5)
        throw msg;
}

bool toRegister(char reg){
    if(reg == 'Y' || reg == 'y'){
        return true;
    }
    else if(reg == 'N' || reg == 'n'){
        return false;
    }
    else{
        string errormsg = "Invalid input";
        throw errormsg;
    }
}

void checkRegisterId(string id, vector<Customer> customerList){
    string msg = "Id used.";
    for(auto& ctm : customerList){
        if(id == ctm.getUserId()){
            throw msg;
        }
    }
}

void registrationNewCustomer(const string& filename, vector<string>& regInfo){
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < regInfo.size(); i++) {
        file << regInfo[i];
        file << ",";
    }

    file << "0";
    file << "\n";
    file.close();
    cout << endl;
    cout << "Register Successfully !" << endl;
}

bool checkValidCustomer(string id, string pw, vector<Customer> customerList){
    for(auto& customer : customerList){
        if(id == customer.getUserId() && pw == customer.getUserPassword()){
            return true;
        }
    }
    cout << endl;
    cout << "Invalid login details, please try again.";
    cout << endl << endl;
    return false;
}

Customer assignCurrentCustomer(string id,vector<Customer> customerList){
    for(auto& customer : customerList){
        if(id == customer.getUserId()){
            return customer;
        }
    }
}

vector<Restaurant> getRestaurantList(int choice, vector<Restaurant> restaurantList){
    vector<Restaurant> tempResList;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        string msg = "Invalid input";
        throw msg;
    }
    string term;
    switch(choice){
        case 1:
            term = "western";
            break;
        case 2:
            term = "japanese";
            break;
        case 3:
            term = "chinese";
            break;
        case 4:
            term = "malay";
            break;
        case 5:
            term = "arabic";
            break;
        default:
            string msg = "Out of Range";
            throw msg;
            break;
    }
    for(auto& res : restaurantList){
        if(term == res.getCuisine()){
            tempResList.push_back(res);
        }
    }
    return tempResList;
}

//initialize static attribute
int orderDetails :: totalOrder = 0;

int main()
{
    // for generate random unique Order Id
    srand(time(0));
    // initialize variables (customers, riders, restaurants)
    string registerId;
    vector<Customer> customerList;
    vector<Rider> riderList;
    vector<Restaurant> restaurantList;
    vector<Restaurant> tempResList;
    Customer currentCustomer;
    Restaurant res;

    Order order;

    string filename = "user.csv";
    vector<vector<string>> customerInfo;
    //read all previous orders
    order.readHistory("history.csv");
    bool validLogin = false;
    bool status;
    //load all used unique id
    vector<string> uniqID = readUniqueId("uniqueId.csv");

    //Initialize restaurants and the foods
    vector<vector<string>> RestaurantsInfo = readCSV("restaurant.csv");
    vector<string> foodFile = {"George & Dragon.csv", "HardRock Cafe.csv",
                                "Sushi King.csv", "Kuroma Sushi.csv",
                                "Din Tai Fung.csv", "Jade Restaurant.csv",
                                "Kafe Kiri Kanan.csv", "Restoran Fatimah.csv",
                                "Arabella Restaurant.csv", "Halab KL.csv"};

    for(auto& x : RestaurantsInfo){
        restaurantList.push_back(Restaurant(x[0], x[1]));
    }
    for(auto& name : foodFile){
        foodInfo foodItems = readCSV_FOOD(name);
        for(auto& restaurant : restaurantList){
            int i = 0;
            if(name.substr(0, name.size()-4) == restaurant.getRestaurantName()){
                for(auto& x : foodItems.info){
                    restaurant.existedFood(x, foodItems.prefer[i]);
                    i++;
                }
            }
        }

    }

    cout << "**** Welcome To Geetha Food ****" << endl << endl;
    string id;
    string password;
    char registration;
    bool running;
    int count;

    while(!validLogin){
            customerInfo.clear();
            customerInfo = readCSV(filename);
            customerList.clear();
            riderList.clear();
            //load all registered users and riders
            for(auto& x : customerInfo){
                if(x[2] == "Customer"){
                    customerList.push_back(Customer(x[0], x[1], x[2], x[3], x[4], stod(x[5]), stoi(x[6])));
                }
                else if(x[2] == "Rider"){
                    riderList.push_back(Rider(x[0], x[1], x[2], x[3], x[4], x[5]));
                }
            }
            bool validRegister = false;
            cout << "Please enter information to Login (-1 to exit)" << endl;
            cout << "Customer ID: ";
            getline(cin ,id);

            //Code exit when "-1" is entered during Login
            if (id == "-1"){
                string history = "history.csv";
                //save all order records
                order.writeHistory(history);
                cout << endl;
                cout << "*** Thank you for using Geetha Food ***" << endl;
                cout << "\t*** See you ***" << endl;
                cout << endl;
                return 0;
            }
            cout << "Password: ";
            getline(cin ,password);
            if (password == "-1"){
                string history = "history.csv";
                //save all order records
                order.writeHistory(history);
                cout << endl;
                cout << "*** Thank you for using Geetha Food ***" << endl;
                cout << "\t*** See you ***" << endl;
                cout << endl;
                return 0;
            }

            // check if login is valid
            validLogin = checkValidCustomer(id, password, customerList);

            //if login failed, ask customer to register
            if(!validLogin){
                cout << "Do you wish to register? (Y/N)" << endl;
                cout << "input: ";
                cin >> registration;
                // remove extra characters entered (Singh, 2016)
                while( !cin.eof() && cin.get() != '\n' );

                cout << endl;

                //input validation
                status = true;
                while(status){
                    try{
                        validRegister = toRegister(registration);
                        status = false;
                    }
                    catch(string errormsg){
                        cout << endl;
                        cout << errormsg << endl;
                        cout << "Please enter y for yes, or n for no" << endl;
                        cout << "input: ";
                        cin >> registration;
                        // remove extra characters entered (Singh, 2016)
                        while( !cin.eof() && cin.get() != '\n' );
                        cout << endl;
                    }
                }
            }
            else{
                // Login successful
                // Hold logged in customers' information
                currentCustomer = assignCurrentCustomer(id, customerList);
                running = true;
                cout << endl;
                cout << "*** Welcome, " << currentCustomer.getUserName() << " ***" << endl;
            }

            string name, id, addr, pw, dist;
            vector<string> regInfo;
            // Register new customer
            if(validRegister == true){
                cout << "Registration" << endl;
                cout << "Enter Name: ";
                getline(cin, name);
                regInfo.push_back(name);

                cout << "Enter ID: ";
                getline(cin, id);
                //input validation
                status = true;
                while(status){
                    try{
                        checkRegisterId(id, customerList);
                        status = false;
                    }
                    catch(string msg){
                        cout << msg << endl;
                        cout << "Please try another id." << endl;
                        cout << "input: ";
                        cin >> id;
                        cout << endl;
                    }
                }
                regInfo.push_back(id);

                regInfo.push_back("Customer");
                cout << "Enter Password: ";
                getline(cin, pw);
                regInfo.push_back(pw);
                cout << "Enter your Address: ";
                getline(cin, addr);
                replace(addr.begin(), addr.end(), ',', '.');
                regInfo.push_back(addr);

                dist = to_string(rand()%11);
                regInfo.push_back(dist);
                registrationNewCustomer(filename, regInfo);
            }

            while(running){
                // display menu
                //current customer for this while loop
                order.setCustomer(currentCustomer);
                int choice;
                int choice_r;
                cout << endl;
                cout << "**** Menu ****" << endl;
                cout << "1) Order Food" << endl;
                cout << "2) View Order History" << endl;
                cout << "3) View Points" << endl;
                cout << "4) Exit" << endl;
                cout << "input: ";
                cin >> choice;
                // input validation
                status = true;
                while(status){
                    try{
                        digitInputValidation(choice, 1, 4);
                        status = false;
                    }
                    catch(string errorMsg){
                        cout << endl;
                        cout << "Error: " << errorMsg << endl;
                        cout << endl;
                        cout << "**** Menu ****" << endl;
                        cout << endl;
                        cout << "1) Order" << endl;
                        cout << "2) View Order History" << endl;
                        cout << "3) View Points" << endl;
                        cout << "4) Exit" << endl;
                        cout << "input: ";
                        cin >> choice;
                    }
                }
                // switch case bring customer to different action
                switch(choice){
                    case 1:{
                        //Food Ordering
                        // cuisine selection
                        vector<Restaurant> restaurant;
                        cout << endl;
                        cout << "**** Choose cuisine ****" << endl;
                        cout << "1) Western Food" << endl;
                        cout << "2) Japanese Food" << endl;
                        cout << "3) Chinese Food" << endl;
                        cout << "4) Malay Food" << endl;
                        cout << "5) Arabic Food" << endl;
                        cout << "input: ";
                        cin >> choice;
                        // input validation
                        status = true;
                        while(status){
                            try{
                                // *** important
                                restaurant = getRestaurantList(choice, restaurantList);
                                status = false;
                            }
                            catch(string msg){
                                cout << endl;
                                cout << msg << endl;
                                cout << endl;
                                cout << "**** Menu ****" << endl;
                                cout << endl;
                                cout << "**** Choose cuisine ****" << endl;
                                cout << "1) Western Food" << endl;
                                cout << "2) Japanese Food" << endl;
                                cout << "3) Chinese Food" << endl;
                                cout << "4) Malay Food" << endl;
                                cout << "5) Arabic Food" << endl;
                                cout << "input: ";
                                cin >> choice;
                            }
                        }
                        // Restaurant display and selection
                        cout << endl;
                        cout << "**** List of Restaurants ****" << endl;
                        count = 1;
                        for(auto& res : restaurant){
                            cout << count << ") " << res.getRestaurantName() << endl;
                            count++;
                        }
                        cout << "input: ";
                        cin >> choice_r;
                        // input validation
                        status = true;
                        while(status){
                            try{
                                digitInputValidation(choice_r, 1, count -1);
                                status = false;
                            }
                            catch(string Msg){
                                cout << endl;
                                cout << Msg << endl;
                                cout << endl;
                                cout << "**** List of Restaurants ****" << endl;
                                count = 1;
                                for(auto& res : restaurant){
                                    cout << count << ") " << res.getRestaurantName() << endl;
                                    count++;
                                }
                                cout << "input: ";
                                cin >> choice_r;
                            }
                        }

                        string currentResName;

                        vector<Western> items;
                        vector<Japanese> items2;
                        vector<Chinese> items3;
                        vector<Malay> items4;
                        vector<Arabic> items5;
                        res = restaurant[choice_r-1];
                        // get food according to restaurant cuisine
                        if(res.getCuisine() == "western"){
                            items = res.getWesternFood();
                        }
                        else if(res.getCuisine() == "japanese"){
                            items2 = res.getJapaneseFood();
                        }
                        else if(res.getCuisine() == "chinese"){
                            items3 = res.getChineseFood();
                        }
                        else if(res.getCuisine() == "malay"){
                            items4 = res.getMalayFood();
                        }
                        else if(res.getCuisine() == "arabic"){
                            items5 = res.getArabicFood();
                        }

                        bool selecting = true;
                        // initialize order details to store purchase information
                        orderDetails ordDetails(currentCustomer, res.getCuisine(), res.getRestaurantName());
                        // keep show restaurant food items
                        // allow customer to continue choose until ready to checkout
                        while(selecting){
                            cout << endl;
                            cout << "**** " << res.getRestaurantName() << " ****" << endl;
                            count = 1;
                            cout << "----------------" << endl;
                            cout << count << ") Ratings & Reviews" << endl;
                            cout << "----------------" << endl;
                            count++;
                            if(res.getCuisine() == "western"){
                                for(auto& item : items){
                                    cout << count << ") " << item.getFoodName() << endl;
                                    cout << "   Price: RM" << item.getFoodPrice() << endl;
                                    cout << "----------------" << endl;
                                    count++;
                                }
                            }
                            else if(res.getCuisine() == "japanese"){
                                for(auto& item : items2){
                                    cout << count << ") " << item.getFoodName() << endl;
                                    cout << "   Price: RM" << item.getFoodPrice() << endl;
                                    cout << "----------------" << endl;
                                    count++;
                                }
                            }
                            else if(res.getCuisine() == "chinese"){
                                for(auto& item : items3){
                                    cout << count << ") " << item.getFoodName() << endl;
                                    cout << "   Price: RM" << item.getFoodPrice() << endl;
                                    cout << "----------------" << endl;
                                    count++;
                                }
                            }
                            else if(res.getCuisine() == "malay"){
                                for(auto& item : items4){
                                    cout << count << ") " << item.getFoodName() << endl;
                                    cout << "   Price: RM" << item.getFoodPrice() << endl;
                                    cout << "----------------" << endl;
                                    count++;
                                }
                            }
                            else if(res.getCuisine() == "arabic"){
                                for(auto& item : items5){
                                    cout << count << ") " << item.getFoodName() << endl;
                                    cout << "   Price: RM" << item.getFoodPrice() << endl;
                                    cout << "----------------" << endl;
                                    count++;
                                }
                            }

                            cout << count << ") Checkout" << endl;
                            cout << "input: ";
                            cin >> choice;
                            // input validation
                            status = true;
                            while(status){
                                try{
                                    digitInputValidation(choice, 1, count);
                                    status = false;
                                }
                                catch(string Msg){
                                    cout << endl;
                                    cout << Msg << endl;
                                    cout << endl;
                                    cout << "**** " << currentResName << " ****" << endl;
                                    count = 1;
                                    cout << "----------------" << endl;
                                    cout << count << ") Ratings & Reviews" << endl;
                                    cout << "----------------" << endl;
                                    count++;
                                    if(res.getCuisine() == "western"){
                                        for(auto& item : items){
                                            cout << count << ") " << item.getFoodName() << endl;
                                            cout << "   Price: RM" << item.getFoodPrice() << endl;
                                            cout << "----------------" << endl;
                                            count++;
                                        }
                                    }
                                    else if(res.getCuisine() == "japanese"){
                                        for(auto& item : items2){
                                            cout << count << ") " << item.getFoodName() << endl;
                                            cout << "   Price: RM" << item.getFoodPrice() << endl;
                                            cout << "----------------" << endl;
                                            count++;
                                        }
                                    }
                                    else if(res.getCuisine() == "chinese"){
                                        for(auto& item : items3){
                                            cout << count << ") " << item.getFoodName() << endl;
                                            cout << "   Price: RM" << item.getFoodPrice() << endl;
                                            cout << "----------------" << endl;
                                            count++;
                                        }
                                    }
                                    else if(res.getCuisine() == "malay"){
                                        for(auto& item : items4){
                                            cout << count << ") " << item.getFoodName() << endl;
                                            cout << "   Price: RM" << item.getFoodPrice() << endl;
                                            cout << "----------------" << endl;
                                            count++;
                                        }
                                    }
                                    else if(res.getCuisine() == "arabic"){
                                        for(auto& item : items5){
                                            cout << count << ") " << item.getFoodName() << endl;
                                            cout << "   Price: RM" << item.getFoodPrice() << endl;
                                            cout << "----------------" << endl;
                                            count++;
                                        }
                                    }

                                    cout << count << ") Checkout" << endl;
                                    cout << "----------------" << endl;
                                    cout << "input: ";
                                    cin >> choice;
                                }
                            }
                            // exit (customer log out)
                            if(choice == count){
                                selecting = false;
                            }
                            // select view ratings and reviews
                            else if(choice == 1){
                                // get ratings and reviews from the restaurant selected by customer
                                vector<string> ratings = res.getRating();
                                vector<string> reviews = res.getReview();
                                cout << endl;
                                cout << "*** Ratings & Reviews ***" << endl;
                                if(ratings.empty() && reviews.empty())
                                    cout << "\tNo ratings & reviews yet." << endl;
                                cout << "----------------" << endl;
                                for (int i = 0; i<ratings.size(); i++){
                                    cout << "Ratings: " << ratings[i] << endl;
                                    cout << "Reviews: " << reviews[i] << endl;
                                    cout << "----------------" << endl;
                                }
                            }
                            else{
                                // select food item
                                int amount;
                                int option;
                                string instructions;
                                vector<string> preferList;

                                // display selected item from the restaurant based on cuisine selected
                                // by customer
                                if(res.getCuisine() == "western"){
                                    cout << endl;
                                    cout << items[choice-2].getFoodName() << " - RM";
                                    cout << items[choice-2].getFoodPrice() << endl;
                                }
                                else if(res.getCuisine() == "japanese"){
                                    cout << endl;
                                    cout << items2[choice-2].getFoodName() << " - RM";
                                    cout << items2[choice-2].getFoodPrice() << endl;
                                }
                                else if(res.getCuisine() == "chinese"){
                                    cout << endl;
                                    cout << items3[choice-2].getFoodName() << " - RM";
                                    cout << items3[choice-2].getFoodPrice() << endl;
                                }
                                else if(res.getCuisine() == "malay"){
                                    cout << endl;
                                    cout << items4[choice-2].getFoodName() << " - RM";
                                    cout << items4[choice-2].getFoodPrice() << endl;
                                }
                                else if(res.getCuisine() == "arabic"){
                                    cout << endl;
                                    cout << items5[choice-2].getFoodName() << " - RM";
                                    cout << items5[choice-2].getFoodPrice() << endl;
                                }

                                // enter desired amount for selected item
                                cout << "Enter amount: ";
                                cin >> amount;
                                // input validation
                                status = true;
                                while(status){
                                    try{
                                        digitInputValidation(amount,1,99999999);
                                        status = false;
                                    }
                                    catch(string Msg){
                                        cout << endl;
                                        cout << Msg << endl;
                                        if(res.getCuisine() == "western"){
                                                cout << endl;
                                                cout << items[choice-2].getFoodName() << " - RM";
                                                cout << items[choice-2].getFoodPrice() << endl;
                                            }
                                            else if(res.getCuisine() == "japanese"){
                                                cout << endl;
                                                cout << items2[choice-2].getFoodName() << " - RM";
                                                cout << items2[choice-2].getFoodPrice() << endl;
                                            }
                                            else if(res.getCuisine() == "chinese"){
                                                cout << endl;
                                                cout << items3[choice-2].getFoodName() << " - RM";
                                                cout << items3[choice-2].getFoodPrice() << endl;
                                            }
                                            else if(res.getCuisine() == "malay"){
                                                cout << endl;
                                                cout << items4[choice-2].getFoodName() << " - RM";
                                                cout << items4[choice-2].getFoodPrice() << endl;
                                            }
                                            else if(res.getCuisine() == "arabic"){
                                                cout << endl;
                                                cout << items5[choice-2].getFoodName() << " - RM";
                                                cout << items5[choice-2].getFoodPrice() << endl;
                                            }
                                        cout << "Enter amount: ";
                                        cin >> amount;
                                    }
                                }

                                // ask customer preference of food if there is any
                                if(res.getCuisine() == "western"){
                                    // check if food has preference choice
                                    if(items[choice-2].hasPreference()){
                                        // get choice of preference available for the food
                                        preferList = items[choice-2].hasPrefrenceSelection();
                                        cout << "Choose your preference" << endl;
                                        count = 1;
                                        for(auto& x : preferList){
                                            cout << count << ") " << x << endl;
                                            count++;
                                        }
                                        cout << "input: ";
                                        cin >> option;
                                        // input validation
                                        status = true;
                                        while(status){
                                            try{
                                                digitInputValidation(option, 0, count);
                                                status = false;
                                                items[choice-2].setPreference(preferList[option-1]);
                                            }
                                            catch(string Msg){
                                                cout << endl;
                                                cout << Msg << endl;
                                                cout << endl;
                                                cout << "Choose your preference" << endl;
                                                count = 1;
                                                for(auto& x : preferList){
                                                    cout << count << ") " << x << endl;
                                                    count++;
                                                }
                                                cout << "input: ";
                                                cin >> option;
                                            }
                                        }
                                    }
                                }
                                else if(res.getCuisine() == "japanese"){
                                    if(items2[choice-2].hasPreference()){
                                        preferList = items2[choice-2].hasPrefrenceSelection();
                                        cout << "Choose your preference" << endl;
                                        count = 1;
                                        for(auto& x : preferList){
                                            cout << count << ") " << x << endl;
                                            count++;
                                        }
                                        cout << "input: ";
                                        cin >> option;
                                        status = true;
                                        while(status){
                                            try{
                                                digitInputValidation(option, 0, count);
                                                status = false;
                                                items2[choice-2].setPreference(preferList[option-1]);

                                            }
                                            catch(string Msg){
                                                cout << endl;
                                                cout << Msg << endl;
                                                cout << endl;
                                                cout << "Choose your preference" << endl;
                                                count = 1;
                                                for(auto& x : preferList){
                                                    cout << count << ") " << x << endl;
                                                    count++;
                                                }
                                                cout << "input: ";
                                                cin >> option;
                                            }
                                        }
                                    }
                                }
                                else if(res.getCuisine() == "chinese"){
                                    if(items3[choice-2].hasPreference()){
                                        preferList = items3[choice-2].hasPrefrenceSelection();
                                        cout << "Choose your preference" << endl;
                                        count = 1;
                                        for(auto& x : preferList){
                                            cout << count << ") " << x << endl;
                                            count++;
                                        }
                                        cout << "input: ";
                                        cin >> option;
                                        status = true;
                                        while(status){
                                            try{
                                                digitInputValidation(option, 0, count);
                                                status = false;
                                                items3[choice-2].setPreference(preferList[option-1]);

                                            }
                                            catch(string Msg){
                                                cout << endl;
                                                cout << Msg << endl;
                                                cout << endl;
                                                cout << "Choose your preference" << endl;
                                                count = 1;
                                                for(auto& x : preferList){
                                                    cout << count << ") " << x << endl;
                                                    count++;
                                                }
                                                cout << "input: ";
                                                cin >> option;
                                            }
                                        }
                                    }
                                }
                                else if(res.getCuisine() == "malay"){
                                    if(items4[choice-2].hasPreference()){
                                        preferList = items4[choice-2].hasPrefrenceSelection();
                                        cout << "Choose your preference" << endl;
                                        count = 1;
                                        for(auto& x : preferList){
                                            cout << count << ") " << x << endl;
                                            count++;
                                        }
                                        cout << "input: ";
                                        cin >> option;
                                        status = true;
                                        while(status){
                                            try{
                                                digitInputValidation(option, 0, count);
                                                status = false;
                                                items4[choice-2].setPreference(preferList[option-1]);

                                            }
                                            catch(string Msg){
                                                cout << endl;
                                                cout << Msg << endl;
                                                cout << endl;
                                                cout << "Choose your preference" << endl;
                                                count = 1;
                                                for(auto& x : preferList){
                                                    cout << count << ") " << x << endl;
                                                    count++;
                                                }
                                                cout << "input: ";
                                                cin >> option;
                                            }
                                        }
                                    }
                                }
                                else if(res.getCuisine() == "arabic"){
                                    if(items5[choice-2].hasPreference()){
                                        preferList = items5[choice-2].hasPrefrenceSelection();
                                        cout << "Choose your preference" << endl;
                                        count = 1;
                                        for(auto& x : preferList){
                                            cout << count << ") " << x << endl;
                                            count++;
                                        }
                                        cout << "input: ";
                                        cin >> option;
                                        status = true;
                                        while(status){
                                            try{
                                                digitInputValidation(option, 0, count);
                                                status = false;
                                                items5[choice-2].setPreference(preferList[option-1]);

                                            }
                                            catch(string Msg){
                                                cout << endl;
                                                cout << Msg << endl;
                                                cout << endl;
                                                cout << "Choose your preference" << endl;
                                                count = 1;
                                                for(auto& x : preferList){
                                                    cout << count << ") " << x << endl;
                                                    count++;
                                                }
                                                cout << "input: ";
                                                cin >> option;
                                            }
                                        }
                                    }
                                }

                                cin.ignore();

                                // prompt customer to enter instructions if any
                                cout << "Enter any special instructions: ";
                                getline(cin, instructions);
                                if(res.getCuisine() == "western")
                                    items[choice-2].setInstruction(instructions);
                                else if(res.getCuisine() == "japanese")
                                    items2[choice-2].setInstruction(instructions);
                                else if(res.getCuisine() == "chinese")
                                    items3[choice-2].setInstruction(instructions);
                                else if(res.getCuisine() == "malay")
                                    items4[choice-2].setInstruction(instructions);
                                else if(res.getCuisine() == "arabic")
                                    items5[choice-2].setInstruction(instructions);
                                // add ordered food into order detail based on cuisine
                                if(ordDetails.getCuisine()=="western"){
                                    // add western food and amount into order details
                                    ordDetails.addWesternOrder(items[choice-2]);
                                    ordDetails.updateAmount(amount);
                                }
                                else if(ordDetails.getCuisine()=="japanese"){
                                    ordDetails.addJapaneseOrder(items2[choice-2]);
                                    ordDetails.updateAmount(amount);
                                }
                                else if(ordDetails.getCuisine()=="chinese"){
                                    ordDetails.addChineseOrder(items3[choice-2]);
                                    ordDetails.updateAmount(amount);
                                }
                                else if(ordDetails.getCuisine()=="malay"){
                                    ordDetails.addMalayOrder(items4[choice-2]);
                                    ordDetails.updateAmount(amount);
                                }
                                else if(ordDetails.getCuisine()=="arabic"){
                                    ordDetails.addArabicOrder(items5[choice-2]);
                                    ordDetails.updateAmount(amount);
                                }
                            }
                        }
                        // check if customer order anything
                        // proceed to checkout and payment only if there is item purchased
                        if(!ordDetails.hasNoOrder()){
                            int opt;
                            cout << endl;
                            cout << "*** Delivery Option ***" << endl;
                            cout << "1) Direct - RM5 (<30 minutes)" << endl;
                            cout << "2) Standard - RM3 (45 minutes)" << endl;
                            cout << "3) Saver - RM1 (60 minutes)" << endl;
                            cout << "input: ";
                            cin >> opt;
                            // input validation
                            status = true;
                            while(status){
                                try{
                                    // set delivery method and calculate fee
                                    ordDetails.setDelivery(opt, currentCustomer.getDistance());
                                    status = false;
                                }
                                catch(orderDetails :: deliveryOption d){
                                    cout << endl;
                                    if(d.getOpt())
                                        cout << "Out of range" << endl;
                                    else
                                        cout << "Enter digit" << endl;
                                    cout << endl;
                                    cout << "*** Delivery Option ***" << endl;
                                    cout << "1) Direct (<30 minutes)" << endl;
                                    cout << "2) Standard (45 minutes)" << endl;
                                    cout << "3) Saver (60 minutes)" << endl;
                                    cout << "input: ";
                                    cin >> opt;
                                }
                            }
                            cout << endl;
                            // displau order subtotal and delivery fee
                            cout << "*** Order Summary ***" << endl;
                            ordDetails.displayDetails();
                            ordDetails.CalcTotal();
                            cout << "Subtotal: RM" << ordDetails.getSubtotal() << endl;
                            // free delivery for every 10th customer purchasing
                            if(ordDetails.free()){
                                cout << "Congrats, you are the " << ordDetails.getTotalOrder() << "th purchase." << endl;
                                cout << "Enjoy your free delivery." << endl;
                            }
                            cout << "Delivery fee: RM" << ordDetails.getDeliveryFee() << endl;
                            cout << "Total Payment: RM" << ordDetails.getTotal() << endl;
                            //prompt customers to exchange 50% discount using 300 points, if any
                            if(ordDetails.hasPoints()){
                                int c;
                                cout <<"You have " <<ordDetails.getPoint() << " points." << endl;
                                cout << "Do you wish to use 300 points for a 50% discount?" << endl;
                                cout << "1) Yes" << endl;
                                cout << "2) No" << endl;
                                cin >> c;

                                // input validation
                                status = true;
                                while(status){
                                    try{
                                        ordDetails.useLoyaltyPoints(c);
                                        status = false;
                                    }
                                    catch(orderDetails :: loyalPoint p){
                                        cout << endl;
                                        p.displayMsg();
                                        cout << endl;
                                        cout <<"You have " <<ordDetails.getPoint() << " points." << endl;
                                        cout << "Do you wish to use 300 points for a 50% discount?" << endl;
                                        cout << "1) Yes" << endl;
                                        cout << "2) No" << endl;
                                        cin >> c;
                                    }
                                }
                                // display subtotal again (after 50% discount)
                                cout << "*** Order Summary ***" << endl;
                                ordDetails.displayDetails();
                                cout << "Subtotal: RM" << ordDetails.getSubtotal() << endl;
                                if(ordDetails.free()){
                                    cout << "Free delivery for " << ordDetails.getTotalOrder() << "th purchase." << endl;
                                }
                                cout << "Delivery fee: RM" << ordDetails.getDeliveryFee() << endl;
                                cout << "Total Payment: RM" << ordDetails.getTotal();
                                if(c == 1)
                                    cout << " After Discount 50% using 300 points" << endl;
                                else
                                    cout << endl;
                            }
                            int idx = rand()%riderList.size();
                            ordDetails.getRide(riderList[idx]);
                            ordDetails.generateUniqueId();
                            status = true;
                            while(status){
                                status = false;
                                for(auto& id : uniqID){
                                    if(ordDetails.getUniqueId() == id){
                                        status = true;
                                    }
                                }
                                if(status){
                                    ordDetails.generateUniqueId();
                                }
                                else{
                                    uniqID.push_back(ordDetails.getUniqueId());
                                }
                            }
                            // record order id generated (Prevent any repeatition)
                            writeUniqueId("uniqueId.csv", uniqID);
                            // prompt user for payment and verification
                            cout << endl;
                            cout << "*** Payment ***" << endl;
                            cout << "1) Credit Card" << endl;
                            cout << "2) E-Wallet" << endl;
                            cout << "3) Cash on Delivery" << endl;
                            cout << "input: ";
                            cin >> opt;
                            status = true;
                            while(status){
                                try{
                                    digitInputValidation(opt, 1, 3);
                                    status = false;
                                }
                                catch(string msg){
                                    cout << endl;
                                    cout << msg << endl;
                                    cout << endl;
                                    cout << "*** Payment ***" << endl;
                                    cout << "1) Credit Card" << endl;
                                    cout << "2) E-Wallet" << endl;
                                    cout << "3) Cash on Delivery" << endl;
                                    cout << "input: ";
                                    cin >> opt;
                                }
                            }
                            cin.ignore();
                            // switch case the payment methods
                            switch(opt){
                                case 1:{
                                    string cardName;
                                    string securityCode;
                                    string expiryDate;
                                    string cardNumber;
                                    cout << endl;
                                    cout << "*** Card Details ***" << endl;
                                    cout << "Card Holder Name: ";
                                    getline(cin, cardName);

                                    cout << "Card Number (xxxx-xxxx-xxxx-xxxx): ";
                                    getline(cin, cardNumber);
                                    // Card number validation (check if is number & correct format)
                                    status = true;
                                    while(status){
                                        try{
                                            cardNumberValidtion(cardNumber);
                                            status = false;
                                        }
                                        catch(string msg){
                                            cout << endl;
                                            cout << msg << endl;
                                            cout << endl;
                                            cout << "Card Number (xxxx-xxxx-xxxx-xxxx): ";
                                            getline(cin, cardNumber);
                                        }

                                    }

                                    cout << "Expiry Date (MM/YY): ";
                                    getline(cin, expiryDate);
                                    // date validation
                                    status = true;
                                    while(status){
                                        try{
                                            cardExpiryValidtion(expiryDate);
                                            status = false;
                                        }
                                        catch(string msg){
                                            cout << endl;
                                            cout << msg << endl;
                                            cout << endl;
                                            cout << "Expiry Date (MM/YY): ";
                                            getline(cin, expiryDate);
                                        }

                                    }

                                    cout << "Security Code (xxx): ";
                                    // security code validation
                                    getline(cin, securityCode);
                                    status = true;
                                    while(status){
                                        try{
                                            securityCodeValidtion(securityCode);
                                            status = false;
                                        }
                                        catch(string msg){
                                            cout << endl;
                                            cout << msg << endl;
                                            cout << endl;
                                            cout << "Security Code (xxx): ";
                                            getline(cin, securityCode);
                                        }

                                    }
                                }
                                    break;
                                case 2:{
                                    string walletNumber;
                                    string walletPin;
                                    cout << endl;
                                    cout << "*** E-Wallet Detail ***" << endl;
                                    cout << "Wallet Number (xxx-xxxxxxx): ";
                                    getline(cin, walletNumber);
                                    // wallet number(phone number) validation
                                    status = true;
                                    while(status){
                                        try{
                                            walletNumberValidtion(walletNumber);
                                            status = false;
                                        }
                                        catch(string msg){
                                            cout << endl;
                                            cout << msg << endl;
                                            cout << endl;
                                            cout << "Wallet Number (xxx-xxxxxxx): ";
                                            getline(cin, walletNumber);
                                        }

                                    }

                                    cout << "Pin: ";
                                    getline(cin, walletPin);
                                    // input validation
                                    status = true;
                                    while(status){
                                        try{
                                            walletPinValidtion(walletPin);
                                            status = false;
                                        }
                                        catch(string msg){
                                            cout << endl;
                                            cout << msg << endl;
                                            cout << endl;
                                            cout << "Pin (xxxxxx): ";
                                            getline(cin, walletPin);
                                        }

                                    }


                                }
                                    break;
                                case 3:
                                    // cash on delivery
                                    break;
                            }
                            cout << endl;
                            // simulate processing time
                            cout << "Processing";
                            for(int i = 0; i<3; i++){
                                sleep(1);
                                cout << ".";
                            }
                            sleep(1);
                            cout << endl << endl;
                            string confirm;
                            cout << endl;
                            // let customer confirm the order
                            cout << "Type in \"CONFIRM\" to confirm your order: ";
                            getline(cin, confirm);
                            status = true;
                            while(status){
                                if(confirm == "CONFIRM"){
                                    status = false;
                                }
                                else{
                                    cout << "Type in \"CONFIRM\" to confirm your order: ";
                                    getline(cin, confirm);
                                }
                            }

                            // order confirmation
                            cout << endl;
                            cout << "*** Confirmation of Order ***" << endl;
                            cout << "Order ID: " << ordDetails.getUniqueId() << endl;
                            ordDetails.displayDetails();
                            cout << "Subtotal: RM" << ordDetails.getSubtotal() << endl;
                            if(ordDetails.free()){
                                    cout << "Free delivery for " << ordDetails.getTotalOrder() << "th purchase." << endl;
                                }
                            cout << "Delivery fee: RM" << ordDetails.getDeliveryFee() << endl;
                            cout << "Total Payment: RM" << ordDetails.getTotal() << endl;
                            cout << endl;
                            cout << "Rider Detail" << endl;
                            ordDetails.displayRider();
                            order.addAllorders(ordDetails);
                            cout << endl;
                            int c;
                            // let customer rate and review
                            cout << "Would you like to rate and review this restaurant?" << endl;
                            cout << "1) Rate and Review" << endl;
                            cout << "2) Back" << endl;

                            cout << "input: ";

                            cin >> c;
                            status = true;
                            while(status){
                                try{
                                    digitInputValidation(c, 1, 2);
                                    status = false;
                                }
                                catch(string msg){
                                    cout << endl;
                                    cout << msg << endl;
                                    cout << endl;
                                    cout << "Would you like to rate and review this restaurant?" << endl;
                                    cout << "1) Rate and Review" << endl;
                                    cout << "2) Back" << endl;
                                    cout << "input: ";
                                    cin >> c;
                                        }
                            }
                            if(c == 1){
                                cin.ignore();
                                string rates;
                                string reviews;
                                cout << "Rate and Review " << restaurant[choice_r-1].getRestaurantName() << endl;
                                cout << "Rating (1,2,3,4,5): ";
                                getline(cin, rates);
                                // input validation ( 1 to 5 only for stars rating)
                                status = true;
                                while(status){
                                    try{
                                        ratingValidtion(rates);
                                        status = false;
                                    }
                                    catch(string msg){
                                        cout << endl;
                                        cout << msg << endl;
                                        cout << endl;
                                        cout << "Rating (1,2,3,4,5): ";
                                        getline(cin, rates);
                                    }
                                }
                                cout << "Review: ";
                                getline(cin, reviews);
                                restaurant[choice_r-1].addRatingReview(rates, reviews);
                                cout << endl;
                                cout << "Thank you for Rating & Reviewing" << endl;
                                cout << endl;
                            }
                        }
                        else{
                            // display if customer checkout without selecting any items
                            cout << endl;
                            cout << "No order" << endl;
                            cout << endl;
                        }
                        //Update points
                        currentCustomer = ordDetails.getCustomer();
                        customerList = rewriteCustomer("user.csv", currentCustomer, customerList, riderList);
                        order.writeHistory("history.csv");
                        }
                        break;
                    case 2:{

                        int opt;
                        // get purchase history
                        vector<orderDetails> history = order.getHistory();

                        cout << endl;
                        cout << "*** Previous Orders ***" << endl;
                        // display no order if there is none
                        if(history.empty()){
                            cout << "No Order Yet" << endl;
                            cout << "----------------" << endl;
                        }
                        // display history purchase and allow customer to reoder
                        else{
                            cout << "----------------" << endl;
                            int i;
                            for(i = 0; i < history.size(); i++){
                                cout << i+1 << ")" << endl;
                                cout << "Order ID: " << history[i].getUniqueId() << endl;
                                cout << history[i].getRestaurant() << endl;
                                history[i].displayDetails();
                                cout << "Delivery Option: " << history[i].getDeliver() << endl;
                                cout << "Subtotal: RM" << history[i].getSubtotal() << endl;
                                if(history[i].getDeliveryFee() == 0){
                                            cout << "Free delivery (free for every 10th customer)" << endl;
                                        }
                                cout << "Delivery fee: RM" << history[i].getDeliveryFee() << endl;
                                cout << "Total Payment: RM" << history[i].getTotal();
                                if(history[i].getDiscount() == 0.5){
                                    cout << " - After 50% discount using 300 points";
                                }
                                cout << endl;
                                cout << "----------------" << endl;
                            }
                            i++;
                            cout << i << ") " << "Back" << endl;
                            cout << "input: ";
                            cin >> opt;
                            status = true;
                            while(status){
                                try{
                                    digitInputValidation(opt, 1, history.size()+1);
                                    status = false;
                                }
                                catch(string msg){
                                    cout << endl;
                                    cout << msg << endl;
                                    cout << endl;
                                    cout << "*** Previous Orders ***" << endl;
                                    cout << "----------------" << endl;
                                    int i;
                                    for(i = 0; i < history.size(); i++){
                                        cout << i+1 << ")" << endl;
                                        cout << "Order ID: " << history[i].getUniqueId() << endl;
                                        cout << history[i].getRestaurant() << endl;
                                        history[i].displayDetails();
                                        cout << "Delivery Option: " << history[i].getDeliver() << endl;
                                        cout << "Subtotal: RM" << history[i].getSubtotal() << endl;
                                        if(history[i].getDeliveryFee() == 0){
                                            cout << "Free delivery (free for every 10th customer)" << endl;
                                        }
                                        cout << "Delivery fee: RM" << history[i].getDeliveryFee() << endl;
                                        cout << "Total Payment: RM" << history[i].getTotal();
                                        if(history[i].getDiscount() == 0.5){
                                            cout << " - After 50% discount using 300 points";
                                        }
                                        cout << endl;
                                        cout << "----------------" << endl;
                                    }
                                    i++;
                                    cout << i << ") " << "Back" << endl;
                                    cout << "input: ";
                                    cin >> opt;
                                }
                            }
                            // no reorder
                            if(opt==i){
                                break;
                            }
                            // reoder (create new order)
                            orderDetails ord = history[opt-1];
                            ord.setCustomer(currentCustomer);
                            if(!ord.hasNoOrder()){
                                int opt;
                                cout << endl;
                                cout << "*** Delivery Option ***" << endl;
                                cout << "1) Direct (<30 minutes)" << endl;
                                cout << "2) Standard (45 minutes)" << endl;
                                cout << "3) Saver (60 minutes)" << endl;
                                cout << "input: ";
                                cin >> opt;
                                // input validation
                                status = true;
                                while(status){
                                    try{
                                        ord.setDelivery(opt, currentCustomer.getDistance());
                                        status = false;
                                    }
                                    catch(orderDetails :: deliveryOption d){
                                        cout << endl;
                                        if(d.getOpt())
                                            cout << "Out of range" << endl;
                                        else
                                            cout << "Enter digit" << endl;
                                        cout << endl;
                                        cout << "*** Delivery Option ***" << endl;
                                        cout << "1) Direct (<30 minutes)" << endl;
                                        cout << "2) Standard (45 minutes)" << endl;
                                        cout << "3) Saver (60 minutes)" << endl;
                                        cout << "input: ";
                                        cin >> opt;
                                    }
                                }
                                cout << endl;
                                // display subtotal
                                cout << "*** Order Summary ***" << endl;
                                ord.displayDetails();
                                cout << "Subtotal: RM" << ord.getSubtotal() << endl;
                                if(ord.free()){
                                    cout << "Congrats, you are the " << ord.getTotalOrder() << "th purchase." << endl;
                                    cout << "Enjoy your free delivery." << endl;
                                }
                                cout << "Delivery fee: RM" << ord.getDeliveryFee() << endl;
                                cout << "Total Payment: RM" << ord.getTotal() << endl;
                                // check if customer has more than 300 points
                                if(ord.hasPoints()){
                                    int c;
                                    cout <<"You have " <<ord.getPoint() << " points." << endl;
                                    cout << "Do you wish to use 300 points for a 50% discount?" << endl;
                                    cout << "1) Yes" << endl;
                                    cout << "2) No" << endl;
                                    cin >> c;
                                    // input validation
                                    status = true;
                                    while(status){
                                        try{
                                            ord.useLoyaltyPoints(c);
                                            status = false;
                                        }
                                        catch(orderDetails :: loyalPoint p){
                                            cout << endl;
                                            p.displayMsg();
                                            cout << endl;
                                            cout <<"You have " <<ord.getPoint() << " points." << endl;
                                            cout << "Do you wish to use 300 points for a 50% discount?" << endl;
                                            cout << "1) Yes" << endl;
                                            cout << "2) No" << endl;
                                            cin >> c;
                                        }
                                    }
                                    // display subtotal if discount applied
                                    cout << "*** Order Summary ***" << endl;
                                    ord.displayDetails();
                                    cout << "Subtotal: RM" << ord.getSubtotal() << endl;
                                    if(ord.free()){
                                        cout << "Free delivery for " << ord.getTotalOrder() << "th purchase." << endl;
                                    }
                                    cout << "Delivery fee: RM" << ord.getDeliveryFee() << endl;
                                    cout << "Total Payment: RM" << ord.getTotal();
                                    if(c == 1)
                                        cout << " After Discount 50% using 300 points" << endl;
                                    else
                                        cout << endl;
                                }
                                // randomly assign a rider for delivery
                                int idx = rand()%riderList.size();
                                ord.getRide(riderList[idx]);
                                ord.generateUniqueId();
                                status = true;
                                while(status){
                                    status = false;
                                    for(auto& id : uniqID){
                                        if(ord.getUniqueId() == id){
                                            status = true;
                                        }
                                    }
                                    if(status){
                                        ord.generateUniqueId();
                                    }
                                    else{
                                        uniqID.push_back(ord.getUniqueId());
                                    }
                                }
                                // record unique id
                                writeUniqueId("uniqueId.csv", uniqID);
                                cout << endl;
                                cout << "*** Payment ***" << endl;
                                cout << "1) Credit Card" << endl;
                                cout << "2) E-Wallet" << endl;
                                cout << "3) Cash on Delivery" << endl;
                                cout << "input: ";
                                cin >> opt;
                                // input validation
                                status = true;
                                while(status){
                                    try{
                                        digitInputValidation(opt, 1, 3);
                                        status = false;
                                    }
                                    catch(string msg){
                                        cout << endl;
                                        cout << msg << endl;
                                        cout << endl;
                                        cout << "*** Payment ***" << endl;
                                        cout << "1) Credit Card" << endl;
                                        cout << "2) E-Wallet" << endl;
                                        cout << "3) Cash on Delivery" << endl;
                                        cout << "input: ";
                                        cin >> opt;
                                    }
                                }
                                cin.ignore();
                                switch(opt){
                                    case 1:{
                                        string cardName;
                                        string securityCode;
                                        string expiryDate;
                                        string cardNumber;
                                        cout << endl;
                                        cout << "*** Card Details ***" << endl;
                                        cout << "Card Holder Name: ";
                                        getline(cin, cardName);

                                        cout << "Card Number (xxxx-xxxx-xxxx-xxxx): ";
                                        getline(cin, cardNumber);
                                        status = true;
                                        while(status){
                                            try{
                                                cardNumberValidtion(cardNumber);
                                                status = false;
                                            }
                                            catch(string msg){
                                                cout << endl;
                                                cout << msg << endl;
                                                cout << endl;
                                                cout << "Card Number (xxxx-xxxx-xxxx-xxxx): ";
                                                getline(cin, cardNumber);
                                            }

                                        }

                                        cout << "Expiry Date (MM/YY): ";
                                        getline(cin, expiryDate);
                                        status = true;
                                        while(status){
                                            try{
                                                cardExpiryValidtion(expiryDate);
                                                status = false;
                                            }
                                            catch(string msg){
                                                cout << endl;
                                                cout << msg << endl;
                                                cout << endl;
                                                cout << "Expiry Date (MM/YY): ";
                                                getline(cin, expiryDate);
                                            }

                                        }

                                        cout << "Security Code (xxx): ";
                                        getline(cin, securityCode);
                                        status = true;
                                        while(status){
                                            try{
                                                securityCodeValidtion(securityCode);
                                                status = false;
                                            }
                                            catch(string msg){
                                                cout << endl;
                                                cout << msg << endl;
                                                cout << endl;
                                                cout << "Security Code (xxx): ";
                                                getline(cin, securityCode);
                                            }

                                        }
                                    }
                                        break;
                                    case 2:{
                                        string walletNumber;
                                        string walletPin;
                                        cout << endl;
                                        cout << "*** E-Wallet Detail ***" << endl;
                                        cout << "Wallet Number (xxx-xxxxxxx): ";
                                        getline(cin, walletNumber);
                                        status = true;
                                        while(status){
                                            try{
                                                walletNumberValidtion(walletNumber);
                                                status = false;
                                            }
                                            catch(string msg){
                                                cout << endl;
                                                cout << msg << endl;
                                                cout << endl;
                                                cout << "Wallet Number (xxx-xxxxxxx): ";
                                                getline(cin, walletNumber);
                                            }

                                        }

                                        cout << "Pin: ";
                                        getline(cin, walletPin);
                                        status = true;
                                        while(status){
                                            try{
                                                walletPinValidtion(walletPin);
                                                status = false;
                                            }
                                            catch(string msg){
                                                cout << endl;
                                                cout << msg << endl;
                                                cout << endl;
                                                cout << "Pin (xxxxxx): ";
                                                getline(cin, walletPin);
                                            }

                                        }

                                    }
                                        break;
                                    case 3:
                                        // cash on delivery
                                        break;
                                }
                                cout << endl;
                                cout << "Processing";
                                for(int i = 0; i<3; i++){
                                    sleep(1);
                                    cout << ".";
                                }
                                sleep(1);
                                cout << endl << endl;
                                string confirm;
                                cout << endl;
                                cout << "Type in \"CONFIRM\" to confirm your order: ";
                                getline(cin, confirm);
                                status = true;
                                while(status){
                                    if(confirm == "CONFIRM"){
                                        status = false;
                                    }
                                    else{
                                        cout << "Type in \"CONFIRM\" to confirm your order: ";
                                        getline(cin, confirm);
                                    }
                                }

                                // order confirmation
                                cout << endl;
                                cout << "*** Confirmation of Order ***" << endl;
                                cout << "Order ID: " << ord.getUniqueId() << endl;
                                ord.displayDetails();
                                cout << "Subtotal: RM" << ord.getSubtotal() << endl;
                                if(ord.free()){
                                    cout << "Free delivery for " << ord.getTotalOrder() << "th purchase." << endl;
                                }
                                cout << "Delivery fee: RM" << ord.getDeliveryFee() << endl;
                                cout << "Total Payment: RM" << ord.getTotal() << endl;
                                cout << endl;
                                cout << "Rider Detail" << endl;
                                ord.displayRider();
                                order.addAllorders(ord);
                                cout << endl;
                                int c;
                                cout << "Would you like to rate and review this restaurant?" << endl;
                                cout << "1) Rate and Review" << endl;
                                cout << "2) Back" << endl;

                                cout << "input: ";

                                cin >> c;
                                // input validation
                                status = true;
                                while(status){
                                    try{
                                        digitInputValidation(c, 1, 2);
                                        status = false;
                                    }
                                    catch(string msg){
                                        cout << endl;
                                        cout << msg << endl;
                                        cout << endl;
                                        cout << "Would you like to rate and review this restaurant?" << endl;
                                        cout << "1) Rate and Review" << endl;
                                        cout << "2) Back" << endl;
                                        cout << "input: ";
                                        cin >> c;
                                            }
                                }
                                // if cuustomer choose to rate
                                if(c == 1){
                                    cin.ignore();
                                    string rates;
                                    string reviews;
                                    cout << "Rate and Review " << ord.getRestaurant() << endl;
                                    cout << "Rating (1,2,3,4,5): ";
                                    getline(cin, rates);
                                    status = true;
                                    while(status){
                                        try{
                                            ratingValidtion(rates);
                                            status = false;
                                        }
                                        catch(string msg){
                                            cout << endl;
                                            cout << msg << endl;
                                            cout << endl;
                                            cout << "Rating (1,2,3,4,5): ";
                                            getline(cin, rates);
                                        }
                                    }
                                    cout << "Review: ";
                                    getline(cin, reviews);
                                    for(auto& res : restaurantList){
                                        if(res.getRestaurantName() == ord.getRestaurant())
                                            res.addRatingReview(rates, reviews);
                                    }

                                    cout << endl;
                                    cout << "Thank you for Rating & Reviewing" << endl;
                                    cout << endl;
                                }

                            }
                            else{
                                cout << endl;
                                cout << "No order" << endl;
                                cout << "----------------" << endl;
                            }
                            // update current customer point
                            currentCustomer = ord.getCustomer();
                            // update the customer in the list
                            customerList = rewriteCustomer("user.csv", currentCustomer, customerList, riderList);
                            // save the order
                            order.writeHistory("history.csv");
                        }
                        }
                        break;
                    case 3:
                        // display customer's point
                        cout << endl;
                        cout << "*** Loyalty Points ***" << endl;
                        cout << "Purchase RM 1 = 1 point" << endl;
                        cout << "Currently you have " << currentCustomer.getPoints() << " points" << endl;
                        cout << endl;
                        break;
                    case 4:
                        // customer logout
                        running = false;
                        validLogin = false;
                        cout << endl;
                        cin.ignore();
                        cout << "Bye, " << currentCustomer.getUserName() << endl;
                        cout << endl;
                        break;
                    default:
                        cout << endl;
                        cout << "No such selection." << endl;
                        break;
                }
            }
        }
}
// source code (Reference)
//Singh, M. (2016, June 22). Clearing The Input Buffer In C/C++. GeeksforGeeks. https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
//Pai, A. (2015, February 11). Validating user input in C++ - Akshay Pai. HackerEarth. https://www.hackerearth.com/practice/notes/validating-user-input-in-c/
