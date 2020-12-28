//V5, 5/18/20: Tested in linux, include fstream.h doesnt work? Also need to make it so replaced inlist doesnt have "read_extra..." commands in there 
//V6, 5/18/20: Goal to make program rewrite orginal inlist instead of make new one. Seems easier to get to work?
    //Note: Now Works, still dumbs all LOGS directory into work directory. Also, make actual wait function?
        //Fixed this..logs_directory can take paths 
        // Moved this to controls up top (5/29/20)

# include <iostream>
# include <fstream>
# include <math.h>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <cstdlib>
//# include <fstream.h>
# include <string.h>
# include <string>
//# include <dos.h> //For Sleep() 


using namespace std;
int main() {
	ifstream inFile;
	
	///// Controls /////
	
	int NumOfModels = 15665;

    int NumOfSpaces = 3; //Changes number of spaces in output between each model
	
	char inputFileName[30] = "InputData.dat"; //File with the model parameters
	char inlist[40] = "inlist_rsp_Type_II_Cepheid_Templet"; //File with templet inlist
	char inlist_replaced[40] = "inlist_rsp_Type_II_Cepheid"; //File with inlist RSP will used (Replaced inlist)

    string log_directory_prefix = "SetD/LOGS_"; //Prefix to log_directory, suffix is model number.
	
	///Arrays:
	
	const int nArray = NumOfModels + 1;
	
	double Mod[nArray];
	double z[nArray];
	double x[nArray];
	double M[nArray];
	double L[nArray];
	double T[nArray];
	
	
	///////////////////
	
	//cout<<"Checking Directory.."<<endl;
    //system("dir");
	
	inFile.open(inputFileName,ios::in);
	
	// Warning if file cant be opened
	if(!inFile.is_open()){ 
		cout << "Error opening file. \n";
		cout << "Giving Retry... \n";
	}
	if(inFile.is_open()){
		cout<<"File was opened successfully"<<endl;
	}
	if(inFile.good()){
		cout<<"File is ready for reading"<<endl;
	}
	
	
	//reading file
	if(inFile.is_open()){
	
		// Putting cursor at start of file
		inFile.clear();
		
		//Reading first line - This is needed outside loop otherwise array won't fill.
		inFile >> Mod[0] >> z[0] >> x[0] >> M[0] >> L[0] >> T[0];
		cout<<"Model"<<setw(10)<<"z"<<setw(15)<<"x"<<setw(15)<<"M"<<setw(15)<<"L"<<setw(15)<<"T"<<endl;
		cout<<Mod[0]<<setw(15)<<z[0]<<setw(15)<<x[0]<<setw(15)<<M[0]<<setw(15)<<L[0]<<setw(15)<<T[0]<<endl;
		for (int a = 1; a < NumOfModels; a++){
			
			// Reading rest of file
			inFile >> Mod[a] >> z[a] >> x[a] >> M[a] >> L[a] >> T[a];
			cout<<Mod[a]<<setw(15)<<z[a]<<setw(15)<<x[a]<<setw(15)<<M[a]<<setw(15)<<L[a]<<setw(15)<<T[a]<<endl;
				
		}
			
		// Close the file.
		inFile.close();
	}
			
			
	if(!inFile.is_open()){
		cout<<"File closed successfully"<<endl;
	}
	
	/////////////////////////////////////////
	
	// The String that is 'viewing' each line in the file
	string readout;
	
	// Controls that are in inlist being read
	string RSP_mass_OG = "   RSP_mass = -1";
	string RSP_Teff_OG = "   RSP_Teff = -1";
	string RSP_L_OG = "   RSP_L = -1";
	string RSP_X_OG = "   RSP_X = -1";
	string RSP_Z_OG = "   RSP_Z = -1";
	string log_directory_OG = "   log_directory = 'LOGS'";
    string read_extra_star_job_inlist1_OG = "   !read_extra_star_job_inlist1 = .true.";
    string extra_star_job_inlist1_name_OG = "   !extra_star_job_inlist1_name = 'InputData'";
	
	// The Strings that are being changed in the inlist that is ran
	string RSP_mass;
	string RSP_Teff;
	string RSP_L;
	string RSP_X;
	string RSP_Z;
	string log_directory;
    string read_extra_star_job_inlist1;
    string extra_star_job_inlist1_name;
	
	// The numerical values used to transfer from array to inital variables ^^
	string Mass;
	string Temp;
	string Lum;
	string Xcomp;
	string Zcomp;
	string Model;
	
	// Loop to read inlist and replace parameters
	//int i = 0;
	for(int i = 0; i < NumOfModels; i++){
		
		//char inlist[30] = "inlist_rsp_Type_II_Cepheid_Templet";
		//char inlist_replaced[40] = "inlist_rsp_Type_II_Cepheid";
		
		inFile.open(inlist,ios::in);
		ofstream outFile(inlist_replaced);
		
		cout<<"Reading inlist and revising..."<<endl;
		while(getline(inFile,readout)){
			
			if(readout == RSP_mass_OG){
				stringstream stream;
				stream<<M[i];
				Mass = stream.str();
				
				//double MassNum = M[i];
				//Mass = to_string(MassNum);
				RSP_mass = "   RSP_mass = " + Mass + "d0";
				outFile<<RSP_mass<<endl;
			}
			else if(readout == RSP_Teff_OG){
				stringstream stream;
				stream<<T[i];
				Temp = stream.str();
				
				//Temp = to_string(T[i]);
				RSP_Teff = "   RSP_Teff = " + Temp + "d0";
				outFile<<RSP_Teff<<endl;
			}
			else if(readout == RSP_L_OG){
				stringstream stream;
				stream<<L[i];
				Lum = stream.str();
				
				//Lum = to_string(L[i]);
				RSP_L = "   RSP_L = " + Lum + "d0";
				outFile<<RSP_L<<endl;
			}
			else if(readout == RSP_X_OG){
				stringstream stream;
				stream<<x[i];
				Xcomp = stream.str();
				
				//Xcomp = to_string(x[i]);
				RSP_X = "   RSP_X = " + Xcomp + "d0";
				outFile<<RSP_X<<endl;
			}
			else if(readout == RSP_Z_OG){
				stringstream stream;
				stream<<z[i];
				Zcomp = stream.str();
				
				//Zcomp = to_string(z[i]);
				RSP_Z = "   RSP_Z = " + Zcomp + "d0";
				outFile<<RSP_Z<<endl;
			}
			else if(readout == log_directory_OG){
				stringstream stream;
				stream<<Mod[i];
				Model = stream.str();
				
				log_directory = "   log_directory = '" + log_directory_prefix + Model + "'";
				outFile<<log_directory<<endl;
			}
            //else if(readout == read_extra_star_job_inlist1_OG){
            //    outFile<<""<<endl;
            //}
            //else if(readout == extra_star_job_inlist1_name_OG){
            //    outFile<<""<<endl;
            //}
			
			
			else{
				outFile<<readout<<endl;
			}
			
		}
		
		// Closing inlist
		inFile.close();
		if(!inFile.is_open()){
			cout<<"Inlist closed successfully"<<endl;
		}
		
		// Run RSP
		cout<<"Running RSP with new inlist..."<<endl;
		system("./rn");
        
        cout<<"RSP done running...This is your time to ^c to end program early if you want"<<endl;
        cout<<"Waiting..."<<endl;
        
        //Waiting loop
        //for(int w = 0; w < wait_time; w++){
         //cout<<"...................."<<endl;   
        //}        

        //cout<<"Done waiting."<<endl;
        
        cout<<"Model "<<Mod[i]<<" is now completed."<<endl;
		
		//Space loop
        int s = 0;
        while(s < NumOfSpaces){
            cout<<""<<endl;
            s = s + 1;
        }
	}
	
	
	
	return 0;
}




