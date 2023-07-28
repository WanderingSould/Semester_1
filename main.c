#include <stdio.h>
#include <stdlib.h>


typedef struct Airline_Services {

 char Flightnames[30][10] , s_d[30][10] , price_range[11][10];
 int seats_available[10];
} air;


struct address {

 char houseName[30] , city[30] , place[30];

};


typedef struct customer {

 char Name[30];
 int mobile_no , id;
 struct address Address;

} cust;

typedef struct Billing_info {

 char s_d[10] , FlightName[10] , amount[7];
 int seats , flightIndex;
 cust c;

} bill;

// Case 1 functions
void addCustomerInfo(int id);
void addAirlineInfo(air * airindia, int mob);
void Printbill(int extras);

// Case 2 functions
void editBill(air * airindia);
void editseats(int mob);
void editAddress(int mob);

// Case 3 functions
void search();

// Case 4 functions
void delete();


// Other functions
void assignArray(char a1[] , char a2[]);

air AirlineInit();


void main() {

 FILE * f;
 int option , global_id = 35224;
 char ch;

 //bill CustomerBill;
 air AirIndia = AirlineInit();

 do {

 printf("// Airline Reservation System \\\\ \n");
 global_id++;
 printf("\n1.Book Flights \n2.Edit Booking \n3.Search Flights \n4.Delete Booking \n5.Exit \n");

 printf("\nEnter your choice : ");
 scanf("%d" , &option);

 switch(option) {

 case 1: addCustomerInfo(global_id);
 addAirlineInfo(&AirIndia , 0);

 Printbill(0);

 break;
 case 2:editBill(&AirIndia);
 break;
 case 3:search();
 break;
 case 4:delete();
 break;
 case 5:exit(1);

 default:printf("\nOh no! , the choice you have entered is incorrect. Please enter a valid option\n");

 }

 printf("\nDo you want to continue? (y/n) : ");
 scanf(" %c",&ch);


 }while (ch=='y');


}

// Case 1 functions

void addCustomerInfo(int id) {

 FILE * f;
 //cust c;
 bill info;


 f = fopen("CustomDetail" , "ab");
 printf("\nPlease Enter the following Details in order ");
 printf("\nName , Mobile No. , Housename , City , Place \n");
 scanf("%s%d%s%s%s",info.c.Name,&info.c.mobile_no,info.c.Address.houseName,
 info.c.Address.city,info.c.Address.place);
 info.c.id = id;



 fwrite(&info,sizeof(info) , 1 , f);
 fclose(f);

}

void addAirlineInfo(air * airIndia , int mob) {

 FILE * f;
 air airline;
 bill info;
 airline = *airIndia;

 f = fopen("CustomDetail" , "rb");
 if (mob >0) {
 while(fread(&info , sizeof(info) , 1 , f) == 1) {
 if (info.c.mobile_no == mob) {
 break;
 }
 }
 }
 else {
 fread(&info , sizeof(info) , 1 , f);
 }
 fclose(f);


 printf("\nWhich source-destination would you prefer to travel? \n1. %s - %s \n2. %s - %s \n3. %s - %s \n4. %s - %s \n5. %s - %s \n6. %s - %s \n7. %s - %s \n8. %s - %s \n9. %s - %s \n10. %s - %s \n" , airline.s_d[0] , airline.price_range[0] , airline.s_d[1] , airline.price_range[1] , airline.s_d[2] , airline.price_range[2] , airline.s_d[3] , airline.price_range[3] , airline.s_d[4] , airline.price_range[4] , airline.s_d[5] , airline.price_range[5] , airline.s_d[6] , airline.price_range[6] , airline.s_d[7] , airline.price_range[7] , airline.s_d[8] , airline.price_range[8] , airline.s_d[9] , airline.price_range[9] );

 printf("Choose from 1-10 : ");
 scanf("%d" , &info.flightIndex);

 if (info.flightIndex <= 0 && info.flightIndex > 10) {
 printf("Enter a valid number between 1-10");
 exit(1);
 }


 assignArray(airline.price_range[info.flightIndex-1] , info.amount);
 assignArray(airline.Flightnames[info.flightIndex-1] , info.FlightName);
 assignArray(airline.s_d[info.flightIndex-1] , info.s_d);

 if (airline.seats_available[info.flightIndex-1] > 0) {

 printf("\nThere are %d seats available in this flight." , airline.seats_available[info.flightIndex-1]);
 printf("\nPlease enter the number of seats you want to book! : ");
 scanf("%d" , &info.seats);

 if (info.seats > airline.seats_available[info.flightIndex-1]) {
 printf("Excess number of seats entered.");
 exit(1);
 }
 f = fopen("CustomDetail" , "ab");
 fwrite(&info,sizeof(info) , 1 , f);

 airline.seats_available[info.flightIndex - 1] -= info.seats;
 }
 else {
 printf("Seats unavailable in this flight , sorry for the inconvenience.");
 }
 *airIndia = airline;
 fclose(f);
}

void Printbill(int extras) {

 FILE * f;

 bill info;

 printf("\nPrinting Bill...\n");
 printf("...");
 f = fopen("CustomDetail" , "rb");

 while (fread(&info , sizeof(info) , 1 , f) == 1){
 if (extras > 0) {
 if (info.c.mobile_no == extras) {
 printf("\nTicket No. : %d \nName : %s \nMobile No. : %d \nAddress : %s , %s , %s \nFlight Name : %s \nSource-Destination : %s \nPrice : %s \nSeats Booked : %d \n" , info.c.id , info.c.Name , info.c.mobile_no,info.c.Address.houseName, info.c.Address.city,info.c.Address.place , info.FlightName , info.s_d , info.amount , info.seats);
 break;
 }
 }

 printf("\nTicket No. : %d \nName : %s \nMobile No. : %d \nAddress : %s , %s , %s \nFlight Name : %s \nSource-Destination : %s \nPrice : %s \nSeats Booked : %d \n" , info.c.id , info.c.Name , info.c.mobile_no,info.c.Address.houseName, info.c.Address.city,info.c.Address.place , info.FlightName , info.s_d , info.amount , info.seats);

 }
 fclose(f);

}

//Case 2 functions

void editBill(air * airIndia) {

 FILE * f;
 int mob_no,selected;
 bill info;
 int n=2;
 long int l;

 f = fopen("CustomDetail" , "a+b");
 printf("Enter the record to update : ");
 scanf("%d",&n);
 fseek(f,(n-1)*sizeof(bill),SEEK_SET);
 l = ftell(f);

 printf("\nCurrent location : %ld",l);
 fclose(f);


 printf("Which option would you like to edit? \n1.Seats booked \n2.Address \n3.Change flight \n");

 scanf("%d" , &selected);

 switch (selected) {
 case 1:editseats(mob_no);

 break;
 case 2:editAddress(mob_no);

 break;
 case 3:addAirlineInfo(airIndia , mob_no);

 break;

 default:
 break;
 }
 Printbill(mob_no);
}

void editseats(int mob) {

 FILE * f;
 bill info;

 f = fopen("CustomDetail" , "rb");
 if (mob >0) {
 while(fread(&info , sizeof(info) , 1 , f) == 1) {
 if (info.c.mobile_no == mob) {
 break;
 }
 }
 }
 fclose(f);

 f = fopen("CustomDetail" , "wb");

 printf("\nYour current number of seats booked are : %d" , info.seats);
 printf("\nEnter the number of seats you would like to book : ");
 scanf("%d" , &info.seats);

 fwrite(&info, sizeof(info) , 1 , f);
 fclose(f);

}

void editAddress(int mob) {

 FILE * f;
 bill info;

 f = fopen("CustomDetail" , "rb");
 if (mob >0) {
 while(fread(&info , sizeof(info) , 1 , f) == 1) {
 if (info.c.mobile_no == mob) {
 break;
 }
 }
 }
 fclose(f);

 f = fopen("CustomDetail" , "wb");

 printf("\nTo edit your current address please Enter the following Details in order ");
 printf("Housename , City , Place \n");
 scanf("%s%s%s",info.c.Address.houseName,
 info.c.Address.city,info.c.Address.place);


 fwrite(&info,sizeof(info) , 1 , f);
 fclose(f);

}

//Case 3 functions
void search() {
 FILE * f;
 int mob;
 bill info;


 printf("Enter mobile number to search bill : ");
 scanf("%d" , &mob);

 f = fopen("CustomDetail" , "rb");

 while (fread(&info , sizeof(info) , 1 , f) == 1) {
 printf("\n %d" , info.c.mobile_no);
 if (info.c.mobile_no == mob) {
 Printbill(mob);
 }
 }

}

// Case 4 functions
void delete() {
    FILE * fm,*ft;
    int mob_no;
    bill info;

    printf("Enter the mobile_no to delete your booking : ");
    scanf("%d",&mob_no);

    fm = fopen("CustomDetail","rb");
    ft = fopen("Temp","Wb");

    while (fread(&info,sizeof(info),1,fm)==1) {
        if (info.c.mobile_no != mob_no) {
            fwrite(&info,sizeof(info),1,ft);
        }
    }
    fclose(fm);
    fclose(ft);
    remove("CustomDetail");
    rename("Temp","CustomDetail");
}

//Other functions


void assignArray(char a1[] ,char a2[]) {
 int i;

 for(i=0 ; a1[i] != '\0' ; i++) {
 a2[i] = a1[i];
 }
 a2[i] = '\0';

}



air AirlineInit() {

 air AirIndia={ {"A012" , "A175" , "A570" , "A876", "A350" , "A164" , "A561" , "A165" , "A527" , "A408"}, {"COK-DEL" , "MAA-BLR" , "COK-MAA" , "BOM-CCU" , "TRV-IXJ" , "DEL-COK" , "BLR-MAA" , "MAA-COK" , "CCU-BOM" , "IXJ-TRV"} , {"25,000", "10,000" , "15,000" , "20,000" , "30,000" , "25,00" , "10,000" , "15,000" , "20,000" , "30,000" } , {149,149,149,149,149,149,149,149,149,149} };

 return AirIndia;
}
