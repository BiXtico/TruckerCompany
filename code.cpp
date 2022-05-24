#include <iostream>
#include<vector>
#include<String>
#include <algorithm> 
#include <fstream>
#include <cstdlib>

using namespace std;

struct Country {
	int ID, Stage;
	bool Manufacturer;
	string Name, Exporter;

	Country(int id, bool manifacturer, string name, int stage,string exporter) {
		this->ID = id; this->Manufacturer = manifacturer; this->Name = name;
		this->Stage = stage; this->Exporter = exporter;
	}
	Country(){}
	friend std::ostream& operator << (ostream& out, const Country& obj)
	{
		out << obj.ID << "\n" << obj.Manufacturer << "\n" << obj.Name << "\n" << obj.Stage << "\n" << obj.Exporter << std::endl;
		return out;
	}
	friend std::istream& operator >> (std::istream& in, Country& obj)
	{
		in >> obj.ID;
		in >> obj.Manufacturer;
		in >> obj.Name;
		in >> obj.Stage;
		in >> obj.Exporter;
		return in;
	}

};

struct Truck {
	int ID, Capacity,Count;

	Truck(int id, int capacity,int count) {
		this->ID = id; this->Capacity = capacity;  this->Count = count;
	}
	Truck(){}
	friend std::ostream& operator << (ostream& out, const Truck& obj)
	{
		out << obj.ID << "\n" << obj.Capacity << "\n" << obj.Count << std::endl;
		return out;
	}
	friend std::istream& operator >> (std::istream& in, Truck& obj)
	{
		in >> obj.ID;
		in >> obj.Capacity;
		in >> obj.Count;
		return in;
	}
};



struct Supply {
	int ID, Quantity;
	string Type;
	bool Stored;

	Supply(int id, string type, int quantity,bool stored) {
		this->ID = id; this->Type = type; this->Quantity = quantity;
		this->Stored = stored;
	}
	Supply(){}
	friend std::ostream& operator << (ostream& out, const Supply& obj)
	{
		out << obj.ID << "\n" << obj.Type << "\n" << obj.Quantity<< "\n" << obj.Stored<< std::endl;
		return out;
	}
	friend std::istream& operator >> (std::istream& in, Supply& obj)
	{
		in >> obj.ID;
		in >> obj.Type;
		in >> obj.Quantity;
		in >> obj.Stored;
		return in;
	}

};
struct Order
{
	int Start, Finish, Profit;
	Order(int start, int finish, int profit) {
		this->Start = start; this->Finish = finish; this->Profit = profit;
	}
};


  vector<Truck> Trucks;
  vector<Country> Countries;
  vector<Supply> Supplies;
  vector<Order> Orders;


  //save all data to the database of vectors
void SaveData() 
 {
	ofstream myTrucks("trucks.txt");
	if (!myTrucks.is_open())
		cout << "Trucks file is not open" << endl;
	else{
		for(Truck t:Trucks)
			myTrucks << t << endl;
	 }
	ofstream myCountries("Countries.txt");
	if (!myCountries.is_open())
		cout << "countries file is not open" << endl;
	else {
		for (Country c : Countries)
			myCountries << c << endl;
	}
	ofstream mySupplies("supplies.txt");
	if (!mySupplies.is_open())
		cout << "supplies file is not open" << endl;
	else {
		for (Supply s : Supplies)
			mySupplies << s << endl;
	}
	myTrucks.close();
	myCountries.close();
	mySupplies.close();
 }

//load all the data once we run the program
void LoadData()
{
	ifstream myTrucks("trucks.txt"); 
	if (!myTrucks.is_open())
		cout << "unable to open file new data not loaded" << std::endl;
	else {
		Truck t1;
		for (int i = 0; i < 8; i++) {
			myTrucks >> t1;
			Trucks.push_back(t1);
		}
	}
	ifstream myCountries("Countries.txt");
	if (!myCountries.is_open())
		cout << "countries file is not open" << endl;
	else {
		Country t1;
		for (int i = 0; i < 8; i++) {
			myCountries >> t1;
			Countries.push_back(t1);
		}
	}
	ifstream mySupplies("supplies.txt");
	if (!mySupplies.is_open())
		cout << "supplies file is not open" << endl;
	else {
		Supply t1;
		for (int i = 0; i < 7; i++) {
			mySupplies >> t1;
			Supplies.push_back(t1);
		}
	}
	myTrucks.close();
	myCountries.close();
	mySupplies.close();
}



//////////////// function 1 /////////////////// divide and conquer


// binary search using recursion , using the ID of the supplies the function will return a pointer
// to the object containning the ID
int SearchSupplies(vector<int> s, int left, int right, int key)
{
	// if left of the vector is equal or smaller than the right side of the vector, we will make a variable of 
	//int and put inside it the left + ((right -left) /2) to break down the vector into two parts
	if (left <= right)
	{
		int middle = left + ((right - left) / 2);

		// if the middle of the vector will equal the key that the user entered, return the middle
		if (s[middle] == key)
			return middle;
		// if the middle of the vector is greater than the key, we will return the searchsupplies recursivley and it will take the vector,
		//the left side of the vector, the middle -1 to keep looping in the left, and the key.
		else if (s[middle] > key)
			return SearchSupplies(s, left, middle - 1, key);
		// if the two conditions above didn't pass,  we will return the searchsupplies recursivley and it will take the vector, the middle +1 to keep looping in the right, 
		//the right side of the vector, and the key which equals the supplyID in the SearchSuppliesbyID() function.
		else
			return SearchSupplies(s, middle + 1, right, key);
	}
	return -1;
}

void SearchSuppliesbyID() {
	int SupplyID;
	int	index = 0;
	vector<int> indexSupplies;
	for (Supply i : Supplies) 
		indexSupplies.push_back(i.ID);
		indexSupplies.push_back(i.ID);
	// this for sorting the vector from the its beginning to its end
	sort(indexSupplies.begin(), indexSupplies.end());

	cout << "Please enter the ID that you want to search : " << endl;
	cin >> SupplyID;
	index = SearchSupplies(indexSupplies, 0, Supplies.size() - 1, SupplyID);
	if (index != -1) // if the index of the supplies not equal -1, it will print the supply's quantity, type, and the ID is found suuccessfully
		cout << "The ID is found : " << Supplies[index].ID << ", and its quantity : " << Supplies[index].Quantity << " , and its type : " << Supplies[index].Type << endl;
	else
		cout << "The ID is not found" << endl;
}

///////////////////// function 2 ///////////////// Transform and conquer



// return list of objects that have "name" as an exporter
vector<Country> getoperatingcountries(vector<Country> s,string name) {
	vector<Country> Count;
	for (Country s : Countries) {
		if (s.Exporter == name) {
			Count.push_back(s);
		}
	}
	return Count;
}

// return list of stages from each country
vector<int> CalculateOperatingStages(string name) {
	vector<int> Count;
	for (Country s : Countries) {
		if (s.Exporter == name) {
			Count.push_back(s.Stage);
		}
	}
	return Count;
}


//calculate the total distance taken by in regard to each exporter
int CalculateOperatingPeriod(vector<int> v) {
	int S = v.size();
	sort(v.begin(), v.end());
	int dist = 0, TotalDist = 0;
	for (int i = 0; i <= S - 2; i++) {
		dist = v[i] - v[i + 1];
		TotalDist += dist;
	}
	return abs(TotalDist);
}


// display countries and the trip cost to in regard to petrol
void CalculateTripInfo(vector<Country> lr,string name, float price) {
	vector<Country> coun = getoperatingcountries(lr, name);
	cout << "The Trip costs : " << CalculateOperatingPeriod(CalculateOperatingStages(name)) * price << endl;
	cout << "Counties that the Exporter will export to : " << endl;
	for (Country c : coun) {
		cout << c.Name << endl;
	}
}


////////////////  for function 3 /////////////////////////// using greedy

void findleastTrucks(int s,vector<int> trucksize) {
	
	vector<int> ans;
	int sizekeeper = s;
	int n = trucksize.size();
	//go through all sizes to find the least ones to fill the objective
	for (int i = n - 1; i >= 0; i--) {
		while (s >= trucksize[i]) {
			//when size is found decrease trucksize by that amount
			s -= trucksize[i];
			ans.push_back(trucksize[i]);
		}
	}

	// Print result 
	cout << "For supplies of size " << sizekeeper << "the sizes for the trucks to minimize cost is : ";
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << "  ";
}

void calculateTrucks() {
	vector<int> sizes;
	for (Truck t : Trucks)
		sizes.push_back(t.Capacity);

	sort(sizes.begin(), sizes.end());
	int n = sizes.size();
	int input;
	cout << "please enter the size of supplies you want to transport : " << endl;
	cin >> input;
	findleastTrucks(input, sizes);
}



///////////////   for function 4   //////////////////////// using dynamic programming



//function that's used to state a condition for the sorting of the objects
bool OrderCompare(Order s1, Order s2)
{
    return (s1.Finish < s2.Finish);
}

// a function that nearest job besfore i that doesn't conflict for the start and finish 
int findpreOrder(vector<Order> arr, int i)
{
	//Go through the list of orders to find the nearest one before i that doesn’t overlap with order[i].
    for (int j = i - 1; j >= 0; j--)
    {
		//checking the overlapping (if order j finish time does not over lap with i finish time) it return index of order in array
        if (arr[j].Finish <= arr[i - 1].Start)
            return j;
    }
    return -1;
}

int findMaxProfit(vector<Order> arr, int n)
{
	// Sort jobs according to finish time 
	sort(arr.begin(), arr.end(), OrderCompare);

	// create a table to store the profits
	int* table = new int[n];
	table[0] = arr[0].Profit;

	//overlapping the profit in i and comaring it with the profit before 
	//also we're keeping in mind orders don't overlap
	for (int i = 1; i < n; i++)
	{
		int inclProf = arr[i].Profit;
		int l = findpreOrder(arr, i);
		//adding the profit of latest job that doesn't overlap to the cuurent order
		if (l != -1)
			inclProf += table[l];
		// storing the a new profit in table[] by choosing between profit calculated before or new one
		table[i] = max(inclProf, table[i - 1]);
	}

	// Store result and free dynamic memory allocated for the table
	int result = table[n - 1];
	delete[] table;

	return result;
}
//drive function 
void findmaxprofitofOrders() {
	int n, start, finish, profit, maxprofit;
	cout << "please enter the amout of Oreders needed :";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "please enter the start time for job " << i + 1 << " :";
		cin >> start;
		cout << "please enter the finish time for job " << i + 1 << " :";
		cin >> finish;
		cout << "please enter the profit for job " << i + 1 << " :";
		cin >> profit;
		Orders.push_back(Order(start, finish, profit));
	}
	maxprofit = findMaxProfit(Orders, n);
	std::cout << "The max profit you can make from these jobs is : " << findMaxProfit(Orders, n) << endl;
	if (maxprofit >= 200) {
		cout << "These orders are worth concidering" << endl;
	}
	else {
		cout << "These orders not worth working" << endl;
	}
}



///////////// to open list for main  /////////////////////////// 


 // open the list to the options that the user might choose from
int OpenList() {
	int choise = 0;
	cout << "1. Search Supplies by ID" << endl;
	cout << "2. Display Trip Info" << endl;
	cout << "3. Calculate Trucks Needed for exportation" << endl;
	cout << "4. find max profit of orders" << endl;
	cout << "5. close" << endl;

	cin >> choise;
	if (choise == 0) {
		cout << "you did not choose any thing" << endl;
		return OpenList();
	}
	else if (choise == 1 || 2 || 3 || 4 || 5)
		return choise;
}

int Close() {
	SaveData();
	return 0;
}
////////////   Driver Function  ////////////


int main() {

	LoadData();
	// openning the list . and choosing one option
	int choise = OpenList();
	string s;
	float p;
	switch (choise){
	case 1:
		SearchSuppliesbyID();
		break;
	case 2:
		cout << "please Enter the Exporter Country Name : ";
		cin >> s;
		cout << "please Enter the petrol cost : ";
		cin >> p;
		CalculateTripInfo(Countries, s, p);
		break;
	case 3:
		calculateTrucks();
		break;
	case 4:
		findmaxprofitofOrders();
		break;
	case 5:
		return Close();
	}
}


