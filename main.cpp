#include <iostream>
#include <iomanip> // Formatting
#include <fstream> // File operations
using namespace std;
class products {
public:
	string item;
	int sales[4];
	double total;
	double avg;
};

void printData (products instance);
void GreatestProfits (products [], int);
void ProfitLoss (products [], int);
string ProfitTrend (products instance);

int main()
{
	int size=0; // Initialize integer values
	int abctotal=0;

    ifstream datafile; // Declare input file
    datafile.open("Report.txt"); // Open input file

   string line;   // Count number of records in external file
    line.clear();
	  getline(datafile,line);
	while (datafile) {
		size++;
		getline(datafile,line); } // Determines number of records

    if(datafile.eof()) {  // upon reaching end of file
       datafile.clear();  // clear internal flags of the stream
       datafile.seekg(0,ios::beg); }  // go back to the start of the file

    // Now declare records array in class 'products' with size determined above
	products records[size];
	for (int i=0; i<size; i++){
		datafile >> records[i].item; // Read in product name
		datafile >> records[i].sales[0]; // Read in said product sales for each quarter...
		datafile >> records[i].sales[1];
		datafile >> records[i].sales[2];
		datafile >> records[i].sales[3];

		//Calculate product's total annual profit
        records[i].total =records[i].sales[0] + records[i].sales[1] +
        records[i].sales[2] + records[i].sales[3];

		records[i].avg = records[i].total/4; } //Calculate product's average quarterly profit

	// Print table headers:
	cout << "HW#7 Anton Teren" << endl << endl;
	cout << setw(8) << "ITEMS"<< setw(8) << "Q1" << setw(6) << "Q2" <<setw(6) << "Q3"
	<< setw(6) << "Q4"<< setw(9) << "GROSS" << setw(5) << "AVG" << endl
    << "--------------------------------------------------" << endl;

	for (int i=0; i<size; i++)
		printData (records[i]); // Print records
	for (int i=0; i<size; i++)
		abctotal = abctotal + records[i].total; // Calculate company's total annual profits
	cout << endl;
	cout << "Total annual profits: " << abctotal << endl;
	cout << endl;
	cout << endl;
	cout << "BIGGEST QUARTERLY PROFITS:" << endl;
	cout << "---------------------------" << endl;
	GreatestProfits (records, size); // Prints greatest profit and corresponding product for each quarter
	cout << endl;
	cout << endl;
	ProfitLoss (records, size); // Prints table of how many items profited and lost profit for each quarter
	cout << endl;
	cout << endl;

	cout << "PROFIT TRENDS:" << endl; // Determines and prints profit trend for each product over the year
	cout << "-------------------------" << endl;

	for (int i=0; i<size; i++) {
		cout << records[i].item << "\t";
		cout << ProfitTrend(records[i]);
		cout << endl; }

    datafile.close(); // Close input file
	return 0; // Close main program function
}
void printData (products instance) {

	cout << left
	<< setw(14) << instance.item
	<< setw(6) << instance.sales[0]
	<< setw(6) << instance.sales[1]
	<< setw(6) << instance.sales[2]
	<< setw(6) << instance.sales[3]
	<< setw(7) << setprecision(0) << fixed << instance.total
	<< setw(7) << setprecision(1) << fixed << instance.avg
	<< endl;
	return; }

void GreatestProfits (products a[], int n){

	string GreatestProfitProd[4]; // Holds name of product with greatest profit for the quarter
	int ProfitForProd[4]; // Holds profit for said product
	for (int q=0; q<4; q++) {

		GreatestProfitProd[q] = a[0].item; // Initialize values for quarter
		ProfitForProd[q] = a[0].sales[q];

		for (int r=0; r<n; r++)  // Iterate through product sales for each quarter
			if (a[r].sales[q] > ProfitForProd[q]) {
				ProfitForProd[q] = a[r].sales[q];
				GreatestProfitProd[q] = a[r].item; }

		cout << " " << "Q" << q+1 << "\t"  // Print results
            << GreatestProfitProd[q] << "\t" << ProfitForProd[q] << endl; }

	return; }

void ProfitLoss (products a[], int n){

	int Profits[4]; int Losses[4]; // Declare arrays to store profit/loss item counts for each quarter
	cout << setw(8) << "" << "QUARTERLY" << endl;
	cout << setw(5) << "" << setw(9) << "Profits" << setw(7) << "Losses" << endl;
	cout << "--------------------" << endl;
	for (int q=0; q<4; q++) { // loop through quarters
	    Profits[q]=0; Losses[q]=0; // Initialize values

		for (int r=0; r<n; r++) { // loop through products
            if (a[r].sales[q] > 0)
				Profits[q]++;
			else if (a[r].sales[q] < 0)
				Losses[q]++; }

		cout << "Q" << q+1 << ":\t"  // Print results:
				<< Profits[q] << "\t" << Losses[q] << endl; }
	return; }

string ProfitTrend (products instance) {
	// Check for an increasing trend
	for (int q=0; q<4; q++){
        if (instance.sales[q] > instance.sales[q+1])
			break;
		else if (q == 2) return "INCREASE"; } // i.e., has reached the end of the loop (i.e., unbroken)

	for (int q=0; q<3; q++) {  // Check for a decreasing trend
		if (instance.sales[q] < instance.sales[q+1])
			break;
		else if (q == 2)  return "DECREASE"; }

	return "VARY"; } // else

