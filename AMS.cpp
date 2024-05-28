#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;
//start

class routesearch {
private:
    unordered_map<string, unordered_map<string, int>> graph;

public:
    routesearch() {
        // Define the distances between cities
        graph["dhaka"]["mymensingh"] = 150;
        graph["dhaka"]["gazipur"] = 50;
        graph["dhaka"]["netrokona"] = 190;
        graph["dhaka"]["sylhet"] = 200;
        graph["mymensingh"]["gazipur"] = 100;
        graph["mymensingh"]["netrokona"] = 30;
        graph["mymensingh"]["sylhet"] = 350;
        graph["gazipur"]["netrokona"] = 140;
        graph["gazipur"]["sylhet"] = 250;
        graph["netrokona"]["sylhet"] = 390;
    }

    void shortestPath(string startCity, string destinationCity) {
        // Implement Dijkstra's algorithm to find the shortest path
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        for (const auto& entry : graph) {
            dist[entry.first] = numeric_limits<int>::max();
            prev[entry.first] = "";
        }

        dist[startCity] = 0;
        pq.push({0, startCity});

        while (!pq.empty()) {
            string u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& neighbor : graph[u]) {
                string v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Output the shortest path
        cout << "Shortest path from " << startCity << " to " << destinationCity << ":" << endl;
        vector<string> path;
        for (string at = destinationCity; at != ""; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    void searchroutes()
    {
        cout << "Printing all possible routes:" << endl;
        for (const auto& entry : graph) {
            cout << entry.first << " can go to: ";
            for (const auto& neighbor : entry.second) {
                cout << neighbor.first << " ";
            }
            cout << endl;
        }
    }
};

//finish

class filehandlingmodule {
public:
    string username1, password1;

    bool log_in(string username, string password) {
        ifstream fileread("login.txt");
        //fileread.open;
        while (fileread >> username1 >> password1) {
            if ((username == username1) && (password == password1)) {
                cout << endl << "                 Account Login Successful..." << endl;
                return true;
            }
        }
        cout << endl << "                 Account Login Failed..." << endl;
        return false;
    }

    void createaccount(string username, string password) {
        ofstream filewrite("login.txt", ios::app);
        //filewrite.open;
        filewrite << username << " " << password << "\n";
        filewrite.close();
        cout << endl << "                 Account Created ..." << endl;
    }
};

class inputmodule {
public:
    string username, password;

    string login() {
        while (true) {
            cout << "\n\n   ****************************        Welcome to Airline Management System       **************************" << endl;
            cout << "\n\n\n\n";
            cout << "                 ENTER                     " << endl;
            cout << "                 *****************************************" << endl;
            cout << "                 ****   1. To Login                  *****" << endl;
            cout << "                 *****************************************" << endl;
            cout << "                 ****   2. To Create New Account     ****" << endl;
            cout << "                 *****************************************" << endl;
            cout << "\n                 Enter Your Choice:";
            int ch;
            bool res;
            filehandlingmodule fobj;
            cin >> ch;
            switch (ch) {
                case 1:
                    system("CLS");
                    cout << "\n\n   ****************************        Welcome to Airline Management System       **************************" << endl;
                    cout << endl;
                    cout << "                 *****************************************" << endl;
                    cout << "                 Enter Username:";
                    cin >> username;
                    cout << "                 *****************************************" << endl;
                    cout << "                 Enter Your Password:";
                    cin >> password;
                    cout << "                 *****************************************" << endl;
                    res = fobj.log_in(username, password);
                    break;
                case 2:
                    system("CLS");
                    cout << "\n\n   ****************************        Welcome to Airline Management System       **************************" << endl;
                    cout << endl;
                    cout << "                 *****************************************" << endl;
                    cout << "                 Enter Username:";
                    cin >> username;
                    cout << "                 *****************************************" << endl;
                    cout << "                 Enter Your Password:";
                    cin >> password;
                    cout << "                 *****************************************" << endl;
                    fobj.createaccount(username, password);
                    break;
            }
            if (res == true)
                return username;
        }
    }
};

//


//
string toLower(string str)
{
	string lowerStr = str;

	for (size_t i = 0; i < str.length(); ++i) {
		lowerStr[i] = tolower((unsigned char)str[i]);
	}
	return lowerStr;
}

time_t t = time(NULL);
tm* timePtr = localtime(&t);

const int MAX_VALID_YR = timePtr->tm_year + 1901;
const int MIN_VALID_YR = timePtr->tm_year + 1900;

const int MIN_VALID_MNTH = timePtr->tm_mon + 1;
const int MAX_VALID_MNTH = timePtr->tm_mon + 2;



bool isLeap(int year)
{

	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));


}




bool isValidDate(int d, int m, int y)
{

	if (y > MAX_VALID_YR ||y < MIN_VALID_YR)
		return false;
	if (m < MIN_VALID_MNTH || m > MAX_VALID_MNTH)
		return false;
	if (d < 1 || d > 31)
		return false;

	if (m == 2)
	{
		if (isLeap(y))
			return (d <= 29);
		else
			return (d <= 28);
	}



	if (m == 4 || m == 6 ||m == 9 || m == 11)
		return (d <= 30);

	return true;
}


class flightDetails
{

	int flightSerial[15] = { 101, 102, 103, 122, 123, 124, 131, 132, 133, 241, 242, 243, 501, 502, 503 };
	int price[16] = { 12000, 10000, 15000, 11000, 14000, 10000, 12000, 13500, 9000, 12500, 14000, 12000, 16000, 16500, 13500 };
	int selectFlight;
	int perPersonPrice;

public:
	void Dhaka()
	{
		cout << "\n\n Flights available for Dhaka:";
		cout << "\n  " << flightSerial[0] << "-Flight (time: 5:00pm) " << price[0] << "/- per person";
		cout << "\n  " << flightSerial[1] << "-Flight (time: 12:00am) " << price[1] << "/- per person";
		cout << "\n  " << flightSerial[2] << "-Flight (time: 8:00pm) " << price[2] << "/- per person";

		cout << "\nChoose your flight: ";
		cin >> selectFlight;

		for (int i = 0; i < 3; i++)
		{
			if (selectFlight == flightSerial[i])
			{
				setPerPersonPrice(price[i]);
				break;
			}
		}
	}

public:
	void Mymensingh()
	{
		cout << "\n You have chosen Mymensingh.";
		cout << "\n Flights available for Mymensingh:";
		cout << "\n  " << flightSerial[3] << "-Flight (time: 3:00pm) " << price[3] << "/- per person";
		cout << "\n  " << flightSerial[4] << "-Flight (time: 7:00pm) " << price[4] << "/- per person";
		cout << "\n  " << flightSerial[5] << "-Flight (time: 2:00am) " << price[5] << "/- per person";

		cout << "\n\nChoose your flight: ";
		cin >> selectFlight;

		for (int i = 3; i <= 5; i++)
		{
			if (selectFlight == flightSerial[i])
			{
				setPerPersonPrice(price[i]);
				break;
			}
		}
	}

public:
	void Netrokona()
	{
		cout << "\n You have chosen Netrokona.";
		cout << "\n Flights available for Netrokona:";
		cout << "\n  " << flightSerial[6] << "-Flight (time: 4:00pm) " << price[6] << "/- per person";
		cout << "\n  " << flightSerial[7] << "-Flight (time: 9:00pm) " << price[7] << "/- per person";
		cout << "\n  " << flightSerial[8] << "-Flight (time: 2:00am) " << price[8] << "/- per person";

		cout << "\n\nChoose your flight: ";
		cin >> selectFlight;

		for (int i = 6; i <= 8; i++)
		{
			if (selectFlight == flightSerial[i])
			{
				setPerPersonPrice(price[i]);
				break;
			}
		}
	}

public:
	void Gazipur()
	{
		cout << "\n You have chosen Gazipur.";
		cout << "\n Flights available for Gazipur:";
		cout << "\n  " << flightSerial[9] << "-Flight (time: 5:00pm) " << price[9] << "/- per person";
		cout << "\n  " << flightSerial[10] << "-Flight (time: 6:00pm) " << price[10] << "/- per person";
		cout << "\n  " << flightSerial[11] << "-Flight (time: 1:00am) " << price[11] << "/- per person";

		cout << "\n\nChoose your flight: ";
		cin >> selectFlight;

		for (int i = 9; i <= 11; i++)
		{
			if (selectFlight == flightSerial[i])
			{
				setPerPersonPrice(price[i]);
				break;
			}
		}
	}

public:
	void Sylhet()
	{
		cout << "\n Flights available for Sylhet:";
		cout << "\n  " << flightSerial[12] << "-Flight (time: 4:00am) " << price[12] << "/- per person";
		cout << "\n  " << flightSerial[13] << "-Flight (time: 3:00pm) " << price[13] << "/- per person";
		cout << "\n  " << flightSerial[14] << "-Flight (time: 6:00am) " << price[14] << "/- per person";

		cout << "\n\nChoose your flight: ";
		cin >> selectFlight;

		for (int i = 12; i <= 14; i++)
		{
			if (selectFlight == flightSerial[i])
			{
				setPerPersonPrice(price[i]);
				break;
			}
		}
	}



	void setPerPersonPrice(int price)
	{
		perPersonPrice = price;
	}


	int getperPersonPrice()
	{
		return perPersonPrice;
	}


	int getSelectFlight()
	{
		return selectFlight;
	}
};



class Node
{
public:
	string name = "", date = "", departureCity = "", destinationCity = "", gender = "";
	int age = 0, bookingCode = 0, ticketSerialNo = 0;
	float fare = 0;
	Node* next = NULL;
};





class bookingProcedureOfTicket{

private:
	Node* head = NULL;
	Node* current = NULL;//current->name=Emon
	Node* front = NULL;
	Node* rear = NULL;
	int Bcode = 0;
	int Bcode2 = 0;
	flightDetails call;

public:
	int Age = 0;
	int members = 0;
	int count = 0;
	float sum = 0;
	float fare = 0;
	float discount = 0;
	float discountFare = 0;
	float totalFare = 0;

	int numberOfBooking = 0;

public:


	bool isValidCity(string city)
	{
		if (toLower(city) == "dhaka" || toLower(city) == "netrokona" || toLower(city) == "gazipur"||toLower(city) == "mymensingh" || toLower(city) == "sylhet")
		{
			return true;
		}
		return false;
	}



	void inputPassengersInfo()
	{
		Bcode = rand();
		Bcode2 = 8971 + Bcode;

		string departureCity = "", destinationCity = "", date = "";
		int change = 1;

		do {
			if (change == 1 || change == 2)
			{
				do
				{
					cout << "DEPARTURE\n";
					cout << "    Our flights are only available from Mymensingh, Dhaka, Gazipur, Netrokona and Sylhet.\n";
					cout << "\nEnter your departure city: ";
					cin >> departureCity;
				} while (!isValidCity(departureCity));
			}

			if (change == 1 || change == 3)
			{
				do
				{
					cout << "DESTINATION\n";
					cout << "    Our flights are only available to Mymensingh, Dhaka, Gazipur, Netrokona and Sylhet.\n";
					cout << "\nEnter your destination city: ";
					cin >> destinationCity;
				} while (!isValidCity(destinationCity));

			}

			if (toLower(departureCity) == toLower(destinationCity))
			{
				cout << "\nDeparture and Destination cities cannot be same." << endl;
				cout << "\nTo change both Enter 1.\nTo change Deaprture Enter 2.\nTo Change Destnation Enter 3.\n" << endl;
				cout << "Select: ";
				cin >> change;
			}
		} while (toLower(departureCity) == toLower(destinationCity));


		int d = 0, m = 0, y = 0;
		bool validDate = false;
        try{
		do
		{
            cout << "\nEnter Day: ";
			cin >> d;
			cout << "Enter Month: ";
			cin >> m;
			cout << "Enter Year: ";
			cin >> y;

			validDate = isValidDate(d, m, y);

			if (!validDate)
			{
				cout << "\nPlease enter a valid date, month and year. You can book seats upto 30 days in advance.\n";
			}





		} while (!validDate);
		  }
		catch(exception e)
		     {
		         //cout<<e<<endl;
		     }

		date = to_string(d) + "/" + to_string(m) + "/" + to_string(y);

        while(true)
        {
        cout << "\nFor how many people you want to book tickets: ";
		cin >> members;
		if (members>2)
        {
            cout<<"You can't buy more than two tickets at a time "<<endl;

        }
        else
        {
            break;

        }
        }



		cout << endl;

		numberOfBooking = count + members;


		for (int i = 1; i <= members; i++)
		{
			Node* passenger_newnode = new Node();

			cout << "Enter passenger name: ";
			cin >> passenger_newnode->name;

			cout << "Enter your age: ";
			cin >> passenger_newnode->age;

			passenger_newnode->date = date;

			cout << "Enter gender: ";
			cin >> passenger_newnode->gender;



			cout << "Your ticket Serial No. is: S-" << i;
			passenger_newnode->ticketSerialNo = i;
			cout << "\n----------------------------------------------------\n" << endl;

			passenger_newnode->departureCity = departureCity;
			passenger_newnode->destinationCity = destinationCity;

			passenger_newnode->bookingCode = Bcode2;


			count++;

			if (numberOfBooking > 10)
			{
				if (front == NULL)
				{
					front = passenger_newnode;
					rear = passenger_newnode;
				}

				else
				{
					rear->next = passenger_newnode;
					rear = passenger_newnode;
				}
			}


			else
			{
				if (head == NULL)
				{
					head = passenger_newnode;
					passenger_newnode->next = NULL;
				}

				else
				{
					current = head;

					while (current->next != NULL)
					{
						current = current->next;
					}

					current->next = passenger_newnode;
				}
			}

		}



		if (destinationCity == "Dhaka" || destinationCity == "Dhaka")
		{
			call.Dhaka();
		}
		else if (destinationCity == "Netrokona" || destinationCity == "Netrokona")
		{
			call.Netrokona();
		}
		else if (destinationCity == "Mymensingh" || destinationCity == "Mymensingh")
		{
			call.Mymensingh();
		}
		else if (destinationCity == "Sylhet" || destinationCity == "Sylhet")
		{
			call.Sylhet();
		}
		else if (destinationCity == "Gazipur" || destinationCity == "Gazipur")
		{
			call.Gazipur();
		}
		else
		{
			cout << "Wrong destinationCity\n";
		}



		if (numberOfBooking > 10)
		{
			cout << "\nYour booking code is " << Bcode2;
			cout << "\nNo more seats are availbale, you are added in the waiting list" << endl;
		}
		else
		{
			cout << "\nYour booking code is " << Bcode2;
			cout << "\nTo proceed and view total price, Press 2.";
		}



	}



	void showWaitingList()
	{
		current = front;

		if (current == NULL)
			cout << "Waiting list is empty" << endl;

		else
		{
			while (current != NULL)
			{
				cout << "_____________________________________________________________________ " << endl << endl;
				cout << "| Serial No.:     \t" << "S-" << current->ticketSerialNo << " \t\t\t|" << endl;
				cout << "| Passenger Name: \t" << current->name << " \t\t\t|" << endl;
				cout << "| Age:            \t" << current->age << " \t\t\t|" << endl;
				cout << "| Booking Date:   \t" << current->date << " \t\t|" << endl;
				cout << "| From:           \t" << current->departureCity << " \t\t|" << endl;
				cout << "| To:             \t" << current->destinationCity << " \t\t|" << endl;
				cout << "_____________________________________________________________________ " << endl << endl;

				current = current->next;
			}
		}

	}



	void calculatePrice()
	{
		current = head;
		bool found = false;
		fare = call.getperPersonPrice();
		totalFare = sum = 0;

		int bcode;

		cout << "Enter your booking code: ";
		cin >> bcode;

		if (current == NULL)
			cout << "\nNo price to display";

		while (current != NULL)
		{
			if (bcode == current->bookingCode)
			{
				if (current->age > 0 && current->age <= 6)
				{
					discount = call.getperPersonPrice() * 0.5;
					discountFare = call.getperPersonPrice() - discount;
					current->fare = discountFare;
					sum += discountFare;
				}
				else if (current->age > 6 && current->age <= 12)
				{
					discount = call.getperPersonPrice() * 0.3;
					discountFare = call.getperPersonPrice() - discount;
					current->fare = discountFare;
					sum += discountFare;
				}
				else if (current->age >= 60)
				{
					discount = call.getperPersonPrice() * 0.2;
					discountFare = call.getperPersonPrice() - discount;
					current->fare = discountFare;
					sum += discountFare;
				}
				else
				{
					fare = call.getperPersonPrice();
					current->fare = fare;
					sum += fare;
				}

				found = true;
			}
			current = current->next;
		}


		if (found = false)
		{
			cout << "Enter correct booking code" << endl;
		}
		else
		{
			totalFare = sum;
			cout << "Your Total Fare is: " << totalFare;
		}
	}


	void viewInfo()
{
    ofstream outFile("info.txt", ios::app); // Open file for appending

    cout << endl;

    current = head;
    int bookCode;
    bool found = false;

    cout << "Enter ticket code: ";
    cin >> bookCode;

    if (current == NULL)
    {
        cout << "There is no booking to display." << endl;
    }

    while (current != NULL)
    {
        if (bookCode == current->bookingCode)
        {
            outFile << current->ticketSerialNo << " "
                    << current->name << " "
                    << current->age << " "
                    << current->date << " "
                    << current->departureCity << " "
                    << current->destinationCity << " "
                    << current->fare << " "
                    << call.getSelectFlight() << endl;

            cout << "Booking information written to file." << endl;

            cout << "_____________________________________________________________________" << endl << endl;
            cout << "| Serial No.:     \t" << "S-" << current->ticketSerialNo << " \t\t\t|" << endl;
            cout << "| Passenger Name: \t" << current->name << " \t\t\t|" << endl;
            cout << "| Age:            \t" << current->age << " \t\t\t|" << endl;
            cout << "| Booking Date:   \t" << current->date << " \t\t|" << endl;
            cout << "| From:           \t" << current->departureCity << " \t\t|" << endl;
            cout << "| To:             \t" << current->destinationCity << " \t\t|" << endl;
            cout << "| Flight No.:     \tABS-" << call.getSelectFlight() << " \t\t|" << endl;
            cout << "| Fare:           \t" << current->fare << " \t\t\t|" << endl;
            cout << "_____________________________________________________________________" << endl;
            cout << endl;

            found = true;
        }
        current = current->next;
    }
    outFile.close();

    if (found != true)
    {
        cout << "Booking not found" << endl;
    }
}





	void modifyTicket()
{
    int bcode;
    int serial;
    int found = -1;

    cout << "Enter your booking code: ";
    cin >> bcode;

    cout << "\nEnter serial number to edit: S-";
    cin >> serial;

    current = head;
    while (current != NULL)
    {
        if (bcode == current->bookingCode && serial == current->ticketSerialNo)
        {
            cout << "Enter passenger name: ";
            cin >> current->name;

            cout << "Enter your age: ";
            cin >> current->age;

            cout << "Enter date: ";
            cin >> current->date;

            cout << "Enter gender: ";
            cin >> current->gender;

            // Now, let's update the information in the file as well
            ifstream inFile("info.txt");
            ofstream tempFile("temp.txt");

            int ticketSerialNo;
            string name, date, departureCity, destinationCity;
            float fare;
            int flightNo;
            while (inFile >> ticketSerialNo >> name >> date >> departureCity >> destinationCity >> fare >> flightNo)
            {
                if (ticketSerialNo == current->ticketSerialNo)
                {
                    tempFile << current->ticketSerialNo << " "
                             << current->name << " "
                             << current->age << " "
                             << current->date << " "
                             << current->departureCity << " "
                             << current->destinationCity << " "
                             << current->fare << " "
                             << call.getSelectFlight() << endl;
                }
                else
                {
                    tempFile << ticketSerialNo << " "
                             << name << " "
                             //<< age << " "
                             << date << " "
                             << departureCity << " "
                             << destinationCity << " "
                             << fare << " "
                             << flightNo << endl;
                }
            }
            inFile.close();
            tempFile.close();

            remove("info.txt");          // Remove the old file
            rename("temp.txt", "info.txt"); // Rename temp file to the original name

            found = 0;
            cout << endl;
            break;
        }
        current = current->next;
    }

    if (found == -1)
    {
        cout << "Record not Found" << endl;
    }
}




	void confirmPayment()
	{
		current = head;

		int bcode, userInput;
		string cnic;
		bool found = false;

		cout << "Enter your booking code: ";
		cin >> bcode;



		if (current == NULL)
		{
			cout << "\nThere is no booking aganist entered booking code" << endl;
		}

		while (current != NULL)
		{
			if (bcode == current->bookingCode )
			{
				found = true;
				break;
			}
			current = current->next;
		}

		if (found)
		{

			cout << "\nYour Total Fare is: " << totalFare << endl;

			cout << "\nPay fare amount to confirm ticket: ";
			cin >> userInput;

			if (userInput == totalFare)
			{
				cout << "\nYour booking is confirmed, enjoy your trip!!!";
			}
			else
			{
				cout << "\nPlease pay the required amount" << endl;

				cout << "\nPay fare amount to confirm ticket: ";
				cin >> userInput;

				if (userInput == totalFare)
				{
					cout << "\nYour booking is confirmed, enjoy your trip!!!";
				}

				else
				{
					cout << "\nYour Booking is cancelled, book again." << endl;
				}
			}
		}
		else
		{
			cout << "\nBookings not found, book your ticket first" << endl;
		}
	}

void  shortestPath()
       {
           // write here the shortest path code
           // for Dhaka , Mymensingh , Gazipur, Netrokona , Sylhet
           // destence Dhaka to Mymensingh=150km, Dhaka to Gazipur = 50km,Dhaka to Netrokona =190km, Dhaka to Sylhet=200km
           // Mymensingh to Gazipur =100km, Mymensingh to Netrokona =40km, Mymensingh to Sylhet=350km
           // Gazipur to Netrokona =140km, Gazipur to Sylhet=250km, Netrokona to Sylhet =390km

             routesearch rs;

    // Search for a route
           rs.searchroutes();

    // Find the shortest path
          string startCity, destinationCity;
         cout << "Enter the start city for shortest path search: ";
         cin >> startCity;
          cout << "Enter the destination city for shortest path search: ";
       cin >> destinationCity;
             startCity = toLower(startCity);
           destinationCity = toLower(destinationCity);
         rs.shortestPath(startCity, destinationCity);


       }

	void DeletingPassengerInfo()
	{
		current = head;
		int Bcode;

		bool found = false;

		cout << "Enter your booking code to cancel booking: ";
		cin >> Bcode;

		if (head == NULL)
		{
			cout << "No booking to cancel" << endl;
		}
		else
		{
			if (current->next == NULL)
			{
				if (Bcode == current->bookingCode)
				{
					head = NULL;
					delete(current);
					found = true;
				}
			}
			else
			{

				if (current == head && Bcode == current->bookingCode)
				{
					Node* temp = current;
					current = current->next;
					delete(temp);
					found = true;
				}
				else
				{
					Node* previous = current;
					while (current != NULL)
					{
						if (Bcode == current->bookingCode)
						{
							previous->next = current->next;
							delete (current);
							found = true;
						}

						current = current->next;
					}


				}
			}

			if (found == false)
			{
				cout << "\nBooking not found" << endl;
			}
			else {
				cout << "\nBooking is cancelled, successfully" << endl;
			}
		}
	}
};



class Menu
{
	int choice = 0;
	bookingProcedureOfTicket call;

public:
	void showMenu()
	{

		do
		{
			cout << endl;
			cout << "\n----------------------------------" << endl;
			cout << "  ABS EMON International Airline ";
			cout << "\n";
			cout << "----------------------------------";

			cout << "\n 11 Services for the Cities";
			cout << "\n 1 Booking";
			cout << "\n 2 Price";
			cout << "\n 3 View Ticket details";
			cout << "\n 4 Modify Ticket details";
			cout << "\n 5 Payment confirmation ";
			cout << "\n 6 Cancel your booking";
			cout << "\n 7 Show waiting List";
			cout << "\n 8 Show Shortest Path";
			cout << "\n 0 Exit \n";
			cout << "\nEnter your Choice:  ";
			cin >> choice;

			switch (choice)
			{
			case 11:
				cout << endl;
				cout << "...............Services for the Cities............. \n";
				cout << "\n    Dhaka \n";
				cout << "\n    Mymensingh \n";
				cout << "\n    Netrokona \n";
				cout << "\n    Gazipur \n";
				cout << "\n    Sylhet \n" << endl;

				break;
			case 1:
				cout << endl;
				cout << "\n    Book ABS EMON Flight Tickets \n"<< endl;
				call.inputPassengersInfo();
				break;
			case 2:
				cout << endl;
				call.calculatePrice();
				break;
			case 3:
				cout << endl;
				call.viewInfo();
				break;
			case 4:
				cout << endl;
				call.modifyTicket();
				break;
			case 5:
				cout << endl;
				call.confirmPayment();
				break;
			case 6:
				cout << endl;
				call.DeletingPassengerInfo();
				break;
			case 7:
				cout << endl;
				call.showWaitingList();
				break;

            case 8:
				cout << endl;

				call.shortestPath();
			}

		} while (choice != 0);
	}
};

int main()
{
    inputmodule obj1;
    string username;
    username = obj1.login();



	Menu call;

	call.showMenu();

	return 0;
}
