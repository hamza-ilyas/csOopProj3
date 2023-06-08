/**********
 ** File: BusCompany.cpp
 ** Project: CMSC 202, Project 3, Spring 2019
 ** Author: Hamza Ilyas
 ** Date: 03/25/2019
 ** Section: Discussion - 07, Lecture - 25
 ** E-mail: hamza3@umbc.edu
 **
 ** This file is the implementation of the corresponding BusCompany.h file.
 **
 **
 ** Extra spacing used to maintain code readability.
 ** 
 **********/

#include "Route.h"
#include "BusCompany.h"


BusCompany::BusCompany(){
  
  MainMenu();
  
}
  

BusCompany::BusCompany(string fileName){

  //for readability purposes
  cout << "\n" << endl;
  
  ReadFile(fileName);
  
  cout << "\n***********************************" << endl;
  cout << "Welcome to the UMBC Transit Simulator\n" << endl;
  
  MainMenu();

}

BusCompany::~BusCompany(){

  int size = m_routes.size();
  
  for(int i = 0; i < size; i++){
    
    m_routes[i] -> Clear();
    delete m_routes[i];
    
  }
  
  m_routes.clear();
  
}

void BusCompany::ReadFile(string fileName){

  string stopName;
  int num1;
  int num2;
  int num3;
  
  ifstream file;
  
  int numStops = 0;
  int numRoutes = 1;
  //since at least one route will be loaded,
  //use numRoutes = 1;
  
  Route* m_newRoute = new Route;
  
  file.open(fileName);
  
  if(file.is_open()){
    
    cout << "FILE OPENED!" << endl;
    
  }else{
    
    cout << "FILE DID NOT OPEN! PLEASE ENTER A NEW FILENAME" << endl;
    cin >> fileName;
    
    do{
      
      file.open(fileName);
    
      if(file.is_open() != true){
      
	cout << "STILL NO FILE OPENED!" << endl;
	cin >> fileName;

      }

    }
    
    while(file.is_open() != true);
    cout << "\nVALID FILE LOCATED AND OPENED!\n" << endl;
    
  }
  
  while(file.peek() != -1){
    //use peek to check if more data in file. -1 signifies null.
    getline(file, stopName, ',');
    
    if(stopName != "\nEnd Route"){

      file >> num1;
      file >> num2;
      file >> num3;

      numStops += 1;
      m_newRoute -> InsertAt(stopName, num1, num2, num3);
    }

    else{
      
      m_routes.push_back(m_newRoute);
      
      m_newRoute = new Route;
      //dynamic allocation needed to pushback more routes.
      
      cout << "Route " << numRoutes << " loaded with " << numStops << " stops." << endl;
      
      numRoutes += 1;
      numStops = 0;
      
    }
    
  }
  
  file.close();
  delete m_newRoute;
  
}


void BusCompany::MainMenu(){

  cout << "\nWhat would you like to do?" << endl;
  cout << " 1. Display Routes" << endl;
  cout << " 2. Display Earnings vs Expenses By Route" << endl;
  cout << " 3. Optimize Route" << endl;
  cout << " 4. Exit\n" << endl;

  int choice;
  
  do{

    cout << "Please enter a menu option: ";
    cin >> choice;
    
  }
  while(choice != 1 && choice != 2 && choice !=3 && choice !=4);
  
  //simple implementation that brings back to menu after a specific call.
  if(choice == 1){
    
    DisplayRoutes();
    MainMenu();
    
  }
  
  if(choice == 2){
    
    DisplayRouteData();
    MainMenu();
    
  }
  
  if(choice == 3){
    
    OptimizeRoute();
    MainMenu();
    
  }
  
  if(choice == 4){
    cout << "Thank you for using the simulator!" << endl;
    //program ends
  }
  
}


void BusCompany::DisplayRoutes(){

  for(unsigned i = 0; i < m_routes.size(); i++) {
    
    cout << "\n*** Route " << i + 1 << " ***" << endl;
    //display that uses friend function.
    cout << *m_routes[i] << endl;
    
  } 

}

void BusCompany::DisplayRouteData(){

  for(unsigned i = 0; i < m_routes.size(); i++){
    
      cout << "\n*** Route " << i + 1 << " ***" << endl;
      cout << "Earnings for this stop: $" << m_routes[i] -> GetRouteEarnings(RIDER_FARE) << endl;
      cout << "Cost of operation: $" << m_routes[i] -> GetRouteExpenses() << endl;
      
      m_routes[i] -> DisplayStopData(RIDER_FARE);
      
  }
  
}

void BusCompany::OptimizeRoute(){

  int choice;
  int size = m_routes.size();

  if(size == 1){
    
    m_routes[0] -> OptimizeRoute(RIDER_FARE);
  
  }else{
    
    cout << "\nWhich route would you like to optimize?" << endl;
    
    for(int i = 0; i < size; i++){
      
      cout << "Route " << i + 1 << endl;

    }
    

    
  do{
    
    cout << "Enter " << "1 - " << size << " inclusive: ";    
    cin >> choice;
    
  }
  
  while(choice < 1 || choice > size);
  
  m_routes[choice-1] -> OptimizeRoute(RIDER_FARE);
  cout << "\nOPTIMIZATION FOR ROUTE " << choice << " COMPLETE." << endl;

  }

}

//endfile
