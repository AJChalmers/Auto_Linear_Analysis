//V1, 5/17/20: laid out program. Ran into problem with to_string function not working with root. 
	//NOTE: Found work around, program now copies inlist and replaces M,L,T,X,Z controls with model parameters from file
//V2, 5/17/20: Program now can create new inlist to run correctly, and do so for each new i (i here is next model)
	//NOTE: Still not running rsp - should be able to use system("./rn"). Will need to set rsp to stop right after lin calc. Also will need to save the LINA data so it doesnt get overwritten next turn
//V3, 5/17/20: Goal to change LOGs directory each interation and actually run RSP each time too. RSP controls should handle itself?


# include <iostream>
# include <fstream>
# include <math.h>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <cstdlib>
# include <fstream.h>
# include <string.h>
# include <string>


using namespace std;
int main() {
	ifstream inFile;
	
	///// Controls /////
	
	int NumOfModels = 11;
	
	//char inputFileName[30] = "ShellTestData.dat";
	
	
	///Arrays:
	
	const int nArray = NumOfModels + 1;
	
	double Mod[nArray];
	double z[nArray];
	double x[nArray];
	double M[nArray];
	double L[nArray];
	double T[nArray];
	
	
	///////////////////
	
	cout<<"Checking Directory.."<<endl;
    system("dir");
	
	inFile.open("ShellTestData.dat",ios::in);
	
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
	string log_directroy_OG = "   log_directroy = 'LOGS'";
	
	// The Strings that are being changed in the inlist that is ran
	string RSP_mass;
	string RSP_Teff;
	string RSP_L;
	string RSP_X;
	string RSP_Z;
	string log_directroy;
	
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
		
		char inlist[30] = "inlist_rsp_Type_II_Cepheid";
		char inlist_replaced[40] = "inlist_rsp_Type_II_Cepheid_Replaced";
		
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
			else if(readout == log_directroy_OG){
				stringstream stream;
				stream<<Mod[i];
				Model = stream.str();
				
				log_directroy = "   log_directroy = 'LOGS_" + Model + "'";
				outFile<<log_directroy<<endl;
			}
			
			
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
		
		
	}
	
	
	
	return 0;
}