/*
Connor Rouan
Facial Recognition
GE1111, Prof. Love
Final Integrated Project
*/
#include <string> //String Class
#include <iostream> //required for output
#include <fstream> //readin/output to file
#include <iomanip> //exit function, width functions
#include <sstream>  //allows header manipulation (conversion from string to int)
#include <cmath>  //needed for the pow function
using namespace std;

double tempvals[5]; //(GLOBAL VARIABLE) stores the converted data temporarily between the main function and conversion function
int num_suspects, counter(0); //(GLOBAL VARIABLE) create a variable for the number of suspects and a global counter

void stringconvert(string line)  //This function converts strings obtained by the getline command to ints to be stored in the 2D xy arrays
{
	int pos(0); //declare a counter to store the values in the temp array
	double v1; //declare a temp variable to hold the data
	stringstream stream(line); //parses string and prepares for deconstruction by while loop, double by double
	while(stream>>v1)
	{
		tempvals[pos] = v1; //store values in temporary global array
		pos++;
	}
}

double facelines(double x1, double x2, double y1, double y2) //calculates the distance between the points passed in
{
	return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}

int main()
{
	
	/* PART A */
	
	string total_suspects;
	ifstream readin;
	readin.open("facedata.txt");
	if (!readin)
	{
		cout<<"unable to open file";
		system("pause");
		exit(0);
	}
	else
	{
		getline(readin, total_suspects); //reads in the number of suspects, the first line of the data file
		stringstream convert(total_suspects);
		if(!(convert>>num_suspects))  //finally converts string to int and stores in num_suspects
			num_suspects=0;
		
		string names[num_suspects]; //declare array to store suspect names
		double x_vals[5][num_suspects], y_vals[5][num_suspects]; //Declare 2 2D arrays to store the x and y vector values. 5 rows for each value by num_suspects for number of columns for the number of suspect data to store
		string entire_line, etline; //strings to temporarily store entire lines of xy doubles before conversion
		
		while (counter<num_suspects)
		{
			getline(readin, names[counter]); //gets player name and stores it in the names array
			getline(readin, entire_line); //gets line of x values and stores it as a string entire_line
			getline(readin, etline); //gets line of y values and stores it as a string etline
			
			stringconvert(entire_line); //convert x values from single string line to 5 doubles
			for(int i=0; i<5; i++)
			{
				x_vals[i][counter] = tempvals[i]; //take converted doubles out of temp array and store them in the 2D array
			}
			
			stringconvert(etline);
			for(int i=0; i<5; i++)
			{
				y_vals[i][counter] = tempvals[i];
			}
			
			counter++;
		}
		
		/* PART B */
		
		cout<<"Enter the name of the text file you wish to test (eg, suspect_1.txt): ";
		string file_name;
		cin>>file_name; //stores the user defined file name to a string
		ifstream infile;
		infile.open(file_name.c_str()); //opens file; need to convert variable string to constant char to open a file (with .c_str() function)
		if (!infile)
		{
			cout<<"unable to open file";
			system("pause");
			exit(0);
		}
		else
		{
			string l1, l2; //declare temp strings to store vals
			getline(infile, l1); //gets line of x values and stores it as a string l1
			getline(infile, l2); //gets line of y values and stores it as a string l2
			
			stringconvert(l1);
			double x_testvals[5];
			for(int i=0; i<5; i++) //convert and store the x double values into an array
			{
				x_testvals[i] = tempvals[i];
			}
			cout<<endl;
			stringconvert(l2);
			double y_testvals[5];
			for(int i=0; i<5; i++)
			{
				y_testvals[i] = tempvals[i];
			}
			
			/* PART C */
		
			double distances[10][num_suspects]; //store suspect distances
			for(int perp=0; perp<num_suspects; perp++) //iterate suspect
			{
				counter=0; //count comparison test number for storage in 2D distance array
				for(int k=0; k<4; k++) //iterate facial features point, n-1 since the final comparison accunts for both points (5-1=4)
				{
					for(int j=(4-k); j>0; j--) //count backwards, decreasing each time, for each facial point compared according to outer loop location so as to not count a facial distance twice
					{
						distances[counter][perp] = facelines(x_vals[k][perp], x_vals[j][perp], y_vals[k][perp], y_vals[j][perp]); //use function to calculute distance; store distances in array
						counter++;
					}
				}
			}
			
			double suspect_distance[10];
			counter=0;
			for(int k=0; k<4; k++)
			{
				for(int j=(4-k); j>0; j--)
				{
					suspect_distance[counter] = facelines(x_testvals[k], x_testvals[j], y_testvals[k], y_testvals[j]);
					counter++;
				}
			}
			
			/* PART D */
			
			double sumsquares[num_suspects], sum(0); //sum counts the distance for a suspect before storing it in the sumsquares array; sumsquares stores the sum of the differences squared for the suspects
			for(int suspect=0; suspect<num_suspects; suspect++) //iterate through suspects
			{
				for(int m=0; m<10; m++) //iterate through distances
				{
					sum += pow((distances[m][suspect]-suspect_distance[m]),2); //calculate the differences and sum in single variable
				}
				sumsquares[suspect] = sum; //store the sum in sumsquares array by suspect
				sum=0;
			}
			
			int position; //holds the position of the value to change
			double hold, holdx[5], holdy[5]; //temp doubles to hold the values being replaced
			string holdname; //temp string to hold the name being swapped
			for (int n=0; n<=num_suspects-2; ++n) //sorts the sumsquares array and the names array simultaniously
			{
				position=n;
				for (int p=n+1; p<=num_suspects-1; ++p) //inner sorting loop
				{
					if (sumsquares[p]<sumsquares[position])
						position=p; //find the postion
				}
				hold=sumsquares[position]; //all holds store the new value temporarily; sorts scores
				holdname=names[position]; //sorts names
				sumsquares[position]=sumsquares[n]; //the old and new values are then swapped
				names[position]=names[n];
				sumsquares[n]=hold; //the new value is then replaced in the new spot
				names[n]=holdname;
				for(int sort=0; sort<5; sort++) //sort x and y value arrays according to new order with names/distances
				{
					holdx[sort] = x_vals[sort][position];
					holdy[sort] = y_vals[sort][position];
					x_vals[sort][position] = x_vals[sort][n];
					y_vals[sort][position] = y_vals[sort][n];
					x_vals[sort][n] = holdx[sort];
					y_vals[sort][n] = holdy[sort];
				}
			}
			
			/* PART E */
			/* Data analysis complete, send over the top 4 results w/ corresponding values to MATLAB by printing to an output file */
			
			//NAMES
			ofstream results_names;
			results_names.open("results_names.txt");
			for(int top_suspects=0; top_suspects<4; top_suspects++)
			{
				results_names<<names[top_suspects]<<endl; //output the names array to file
			}
			results_names.close();
			
			//SCORES
			ofstream results_scores;
			results_scores.open("results_scores.txt");
			for(int top_suspects=0; top_suspects<4; top_suspects++)
			{
				results_scores<<sumsquares[top_suspects]<<endl;  //output the scores array to file
			}
			results_scores.close();
			
			//x values
			ofstream results_xvals;
			results_xvals.open("results_xvals.txt");
			for(int top_suspects=0; top_suspects<4; top_suspects++)
			{
				for(int xprint=0; xprint<5; xprint++)
				{
					results_xvals<<x_vals[xprint][top_suspects]<<endl;  //output the x-values array to file
				}
			}
			results_xvals.close();
			
			//y values
			ofstream results_yvals;
			results_yvals.open("results_yvals.txt");
			for(int top_suspects=0; top_suspects<4; top_suspects++)
			{
				for(int yprint=0; yprint<5; yprint++)
				{
					results_yvals<<y_vals[yprint][top_suspects]<<endl; //output the x-values array to file
				}
			}
			results_yvals.close();
			
			/* PART H */
			/* EXTRA CREDIT: print out top 4 candidate names and scores to scoresuspect.txt */
			
			ofstream outfile;
			outfile.open("scoresuspect.txt");
			for(int top_sus=0; top_sus<4; top_sus++)
			{
				outfile<<"Suspect = "<<names[top_sus]<<setw(15)<<"Score = "<<sumsquares[top_sus]<<endl;
			}
			outfile.close();
		}
		infile.close();
	}
	readin.close();
	system("pause");
	return 0;
}
