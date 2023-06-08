/**********
 **File: Route.cpp
 ** Project: CMSC 202, Project 3, Spring 2019
 ** Author: Hamza Ilyas
 ** Date: 03/25/2019
 ** Section: Discussion - 07, Lecture - 25
 ** E-mail: hamza3@umbc.edu
 **
 **
 ** This file is the implementation of the corresponding Route.h file.
 **
 **
 ** Extra spacing used for code readability.
 **
 **********/


#include "Route.h"
using namespace std;



Route::Route(){

  //initialize linked list to null
  m_start = NULL;
  m_size = 0;
  
}


Route::~Route(){

  //remove dynamically allocated stops
  Stop *temp;
  
  while(m_start != NULL){
    
    temp = m_start -> m_next;
    delete m_start;
    m_start = temp;
    
  }
}



void Route::InsertAt(string name, int location, int riders, double cost){

  //insert parameters into a new dynamic stop
  Stop *temp = new Stop();
  temp -> m_name = name;
  temp -> m_location = location;
  temp -> m_riders = riders;
  temp -> m_cost = cost;

  //special case: empty list
  if(m_start == NULL){
    
    m_start = temp;
    m_start -> m_next = NULL;
    m_size += 1;
    return;
    
  }
  
  //special case: insertion before first stop
  if(location < (m_start -> m_location)){
    
    Stop *tempA = m_start;
    m_start = temp;
    temp -> m_next = tempA;
    m_size += 1;
    return;
    
  }

  //special case: insertion at the end
  Stop *tempD = m_start;
  for(int i = 0; i < m_size; i++){
    
    if(location > m_start -> m_location){
      
      if(tempD -> m_next != NULL){
	tempD = tempD -> m_next;
      }
    }
  }
  
  if(location > tempD -> m_location){
  
    tempD -> m_next = temp;
    m_size += 1;
    return;
    
  }
  //should be at the end of linked list after this loop  
  //assign the end pointer to be the pointer mentioned here

  
  //special case: insertion in the middle
  Stop *previous = m_start;
  Stop *next = m_start -> m_next;
 
    for(int i = 0; i < m_size; i++){
      
      if(location > previous -> m_location && location < next -> m_location){

	temp -> m_next = next;
	previous -> m_next = temp;
	m_size += 1;
	return;

      }else{

	if(previous -> m_next != NULL && next -> m_next != NULL){
	  
	  previous = previous -> m_next;	
	  next = next -> m_next;
	  
	}
      }
    }
    
}


void Route::DisplayRoute(){
  
  if(m_start == NULL){
    
    cout << "Linked list is empty." << endl;

  }
  
  else{
    
    //display by traversion
    Stop *temp = m_start;
    
    for(int i = 0; i < m_size; i++){
      
      cout << m_size << endl;
      cout << "Stop " << i+1 << " - "
	   << temp -> m_name << "(" << temp -> m_location << ")" << endl;
      
      temp = temp -> m_next;
      
    }
    
    cout << "END ROUTE" << endl;
    
  }

}


bool Route::IsEmpty(){

  if(m_size == 0){
    
    cout << "Route is empty." << endl;
    return 1;
    
  }else{
    
    cout<< "Route is NOT empty." << endl;
    return 0;
    
  }
  
}

double Route::GetRouteEarnings(double riderFare){

  Stop *temp = m_start;
  double total;
  int totalRiders;
  
  for(int i = 0; i < m_size; i++){
    
    totalRiders += (temp -> m_riders);
    temp = temp -> m_next;
    
  }
  
  //getting earnings by calculations
  total = riderFare * totalRiders;
  return total;
  
}


double Route::GetRouteExpenses(){

  Stop *temp = m_start;
  double expenses;
  //expenses given by simple accumulated addition
  
  for(int i = 0; i < m_size; i++){
    
    expenses += (temp -> m_cost);
    temp = temp -> m_next;
    
  }
  
  return expenses;
  
}



void Route::Clear(){

  Stop *temp = m_start;
  
  while(m_start != NULL){
    
    temp = m_start -> m_next;
    delete m_start;
    //clearing routes of stops
    m_start = temp;
    
  }
  
  m_start = NULL;
  m_size = 0;
  
}


void Route::OptimizeRoute(double riderFare){

  Stop *temp = m_start;
  Stop *tempNext = m_start;
  double cost;
  double earnings;

  while(temp != NULL){
    
    earnings = riderFare * (temp -> m_riders);
    cost = temp -> m_cost;
    tempNext = tempNext -> m_next;

    if(cost > earnings){
      //if cost is greater than earnings, deemed to be removed.
      RemoveStop(temp -> m_location);

    }
    
    temp = tempNext;
   
  }
  
}


void Route::RemoveStop(int stopLocation){



  //removal from start
  Stop *tempEnd = m_start;

  if(m_start -> m_location == stopLocation){
    tempEnd = m_start -> m_next;
    delete m_start;

    m_start = tempEnd;
    m_size -= 1;

    return;
    
  }

  
  //removal from end
  if(m_start -> m_next != NULL && m_start -> m_next != NULL){

    for(int i = 0; i < m_size; i++){
      if(tempEnd -> m_next != NULL)
	tempEnd = tempEnd -> m_next;
    
    }
  }


  if(stopLocation == tempEnd -> m_location){
    

    delete tempEnd;
    m_size -= 1;
    
    Stop *tempLast = m_start;
    
    for(int j = 0; j < m_size; j++){
      
      tempLast = tempLast -> m_next;

    }


    tempLast -> m_next = NULL;
    return;
    
  }  

  //removal from middle
  Stop *prev = NULL;
  Stop *curr = m_start;
  Stop *next = curr -> m_next;

  for(int k = 0; k < m_size; k++){

    if(curr -> m_location == stopLocation){

      m_size -=1;
      delete curr;
      prev -> m_next = next;


      return;
      
     }else{
       prev = curr;
       curr = next;
       if(next -> m_next != NULL){
	 
	 next = next -> m_next;
       }
    }
  }
  
}
  
void Route::DisplayStopData(double riderFare){

  Stop *temp = m_start; 
  for(int i = 0; i < m_size; i++){

    cout << temp -> m_name << endl;
    
    double earnings = riderFare * (temp -> m_riders);
    
    cout << "\tEarnings: " << temp -> m_riders << "@" << "3.25" << " = $" << earnings << endl;
    cout << "\tExpenses: " << "$" << temp -> m_cost << endl;
    
    double total = earnings - temp -> m_cost;
    
    cout << "\tTotal: $" << total << endl;
    
    temp = temp -> m_next;
    
  }
  
}



int Route::GetSize(){

  return m_size;

}



ostream &operator<< (ostream &output, Route &myRoute){

  Stop *temp = myRoute.m_start;
  
  for (int i = 0; i < myRoute.GetSize(); i++){
    
    output << temp -> m_name << "(" << temp -> m_location << ")" << endl;
    temp = temp -> m_next;
    
  }
  
  cout << "END ROUTE" << endl;
  
  return output;
  
}
