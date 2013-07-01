//DESCRIPTION
//HW 2
//Author: Jason Larkin
//Date: 2/10/10
//Purpose: This code is for MD Class HW3.
//*********************************************************************************

//*********************************************************************************
//HEADER
//*********************************************************************************
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <math.h>
#include <time.h>
using namespace std;
//*********************************************************************************


//*********************************************************************************
//FUNCTIONS
//*********************************************************************************

double Osc_Energy(double x);
//*********************************************************************************


//*********************************************************************************
//GLOBAL VARIABLES
//*********************************************************************************                                                                    //simulation cell size.
double pi = atan(1)*4;
				                                       // (J/K)

//*********************************************************************************


//*********************************************************************************
//IO STREM
//*********************************************************************************
ifstream input1("liquid256.txt");			// input data
ifstream input2("input.txt");          
ofstream props_out;							// energy, temperature, pressure and momentum output (vs. time)
ofstream output;			 				// extra output stream
ofstream chime_out;                         //chime output
//ofstream chime_out;							// chime
//ofstream atomeye_out;						// atomeye
//ofstream gr_out;							// rdf
//*********************************************************************************


//*********************************************************************************
//MAIN
//*********************************************************************************
int main() {	
   //Main variables    
   int i,k;  
   char hold;              //character to pause the program.
   char filename[255];	   //text string used to open/close files

   //cout<<P<<"\t"<<Pset<<endl;
   cin.get(hold);

//Input/Output Initialization
//*********************************************************************************	
//Open output streams                                                                                  
		sprintf(filename, "props.txt");
		props_out.open(filename);
		sprintf(filename, "positions.xyz");
		chime_out.open(filename);
		sprintf(filename, "PE_output.txt");
		output.open(filename);
		
//Program Initialization
//*********************************************************************************	

cout <<"Simulation"<<endl;

//Simulation Loop
//*********************************************************************************	

   //MC Simulation parameters
   int t_total = 100000000;
   int t=0; int t_stats=10000;    double frac; double frac2;

   double beta = 0.01;
   double delta = 3.0;
   double epsilon = 0.01;
   
   double x; double x_trial; double U; double U_trial;
    srand(time(NULL));
    int pos_rand;
    double delta_rand; double randnum; int numacc=0; int numreject=0; int numbin=0; int numoutside=0;
    double xi=-1.0; double xstar=0.0; int Num=0; double kcalc; double deltafn;
    
    x=xi; 
    U = Osc_Energy(x);    


for(t=0;t<=t_total;t++){
                 
                 delta_rand = ((2.0*( rand() % 10000+1)) - 10000.0)/10000.0;  
                 x_trial = x + delta*delta_rand; 
                 U_trial = Osc_Energy(x_trial);
                 //cout<<x_trial<<endl;
                //cin.get(hold);
        if (x_trial>(xstar + (epsilon/2.0))){
                        numoutside=numoutside+1;
                        numreject=numreject+1;
        }
        else {
             props_out<<x_trial<<endl;
             Num=Num+1;
                 randnum = ( rand() % 10000+1)/10000.0;  
                 //cout<<randnum<<endl;
                //cin.get(hold);          
             if (U_trial<U){
                x = x_trial; U=U_trial; numacc=numacc+1;
                if ((xstar - (epsilon/2.0))<=x_trial && x_trial<=(xstar+(epsilon/2.0))){
                numbin=numbin+1;
                }
                }
             else if (randnum <= exp(-beta*(U_trial-U))){ 
                x = x_trial; U=U_trial; numacc=numacc+1; 
                if ((xstar - (epsilon/2.0))<=x_trial && x_trial<=(xstar+(epsilon/2.0))){
                numbin=numbin+1;
                }
                }
             else {    
                 numreject=numreject+1;
                 }
  }
                 
        
            
            // output to screen (to monitor simulation)
    
    			if (t%(t_stats*100) == 0) {   
                                       deltafn = (1/((double) Num))*(1.0/epsilon)*((double) numbin);
                                       kcalc = 0.5*sqrt(2/(pi*beta))*deltafn;   
                                       frac=(double)numacc/(double)(numacc+ numreject); 
                                       frac2=(double)numoutside/(double)(t_total);      
                  cout << kcalc<<"\t"<< frac<<"\t"<< numbin <<"\t"<< frac2 <<endl;
      	        //output data
		        //       props_out<< t<<"\t"<< T*(epsilon_Ar/kb)<<"\t"<< P << "\t"<< P_ideal << "\t"<< P_virial << "\t" << L[0]<<"\t" <<"\t"<<KE<<"\t"<<PE<<"\t"<< TE <<"\t"<<numacc<<"\t"<<numreject<<endl;		

                }
    				    
    }
cin.get(hold);
    
}
//*********************************************************************************
//END MAIN
//*********************************************************************************



//*********************************************************************************
//FUNCTIONS
//*********************************************************************************


double Osc_Energy(double x){
double U=0.0;     
       U = x*x*x*x - 2.0*(x*x) +1.0;
return U;     
       }
